/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "cadeteditor.h"
#include "ui_cadeteditor.h"
#include "cadet.h"
#include "datamanager.h"
#include "mainwindow.h"
#include "constants.h"
#include "uuidgenerator.h"

#include <QMessageBox>

CadetEditor::CadetEditor(MainWindow *mainWindow, QWidget *parent, QString id) :
	QDialog(parent),
	ui(new Ui::CadetEditor)
{
	ui->setupUi(this);
	this->mainWindow = mainWindow;

	//Setup gradeBox selections
	ui->gradeBox->clear();
	ui->gradeBox->addItem(Cadet::getGradeStr(Cadet::GRADE::CADET));
	ui->gradeBox->addItem(Cadet::getGradeStr(Cadet::GRADE::SENIORMEMBER));

	//Setup flightBox selections
	ui->flightBox->clear();
	ui->flightBox->addItems(Constants::comboBox_Flight.keys());

	//Set idBox to only take numbers as an input
	ui->idBox->setValidator(new QIntValidator(0, 999999, this));

	//If editing an existing cadet
	if(!id.isEmpty() && DataManager::cadets.contains(id)){
		//Setup UI so it matches the current data for the cadet
		this->id = id;
		Cadet *cadet = &DataManager::cadets[id];
		ui->idBox->setText(QString::number(cadet->capid));

		ui->gradeBox->setCurrentIndex(cadet->grade);

		ui->rankBox->setCurrentText(cadet->getRankStr());
		ui->firstNameEdit->setText(cadet->firstName);
		ui->lastNameEdit->setText(cadet->lastName);
		ui->flightBox->setCurrentText(cadet->getFlightStr());
		ui->notesEdit->setText(cadet->notes);
	}

	ui->idBox->setFocus(Qt::FocusReason::TabFocusReason);
}

CadetEditor::~CadetEditor() {
	delete ui;
}

void CadetEditor::on_gradeBox_currentIndexChanged(int index) {
	//Cadets and Senior Members have different ranks, so update the rankBox if the gradeBox is changed
	ui->rankBox->clear();
	if(index == Cadet::GRADE::CADET){
		//I would add by the comboBox_CadetRanks keys constant, but the keys get alphabetically sorted.
		//This makes selecting rank really awkward, so I had to put the rank display names into their own array.
		//This keeps the order of the ranks.
		for(int i = 0; i < 16; i++){
			ui->rankBox->addItem(Constants::cadetRankDisplayNames[i]);
		}
	} else {
		//Same as above, would've used comboBox_SMRanks keys constant, but they get alphabetically sorted.
		for(int i = 0; i < 13; i++){
			ui->rankBox->addItem(Constants::smRankDisplayNames[i]);
		}
	}
}

void CadetEditor::on_buttonBox_accepted() {
	//Check if required fields have been filled
	bool valid = true;

	//Is CapID filled?
	if(ui->idBox->text().length() <= 0){
		ui->idBox->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->idBox->setStyleSheet("");
	}

	//Is last name filled?
	if(ui->lastNameEdit->text().length() <= 0){
		ui->lastNameEdit->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->lastNameEdit->setStyleSheet("");
	}

	//Show status message if required fields not filled
	if(!valid){
		mainWindow->showStatusMessage("Please fill required fields");
		return;
	}

	//If creating a new cadet
	if(id.isEmpty()){
		QString lastName = ui->lastNameEdit->text();
		QString firstName = ui->firstNameEdit->text();

		QString possibleMatchID;
		int matchWeight = 0;
		QMapIterator<QString, Cadet> i(DataManager::cadets);
		while(i.hasNext()){
			i.next();
			const Cadet cadet = i.value();
			if(cadet.lastName.toLower() == lastName.toLower() &&
					cadet.firstName.toLower() == firstName.toLower()){
				//No better match than exact first and last names
				possibleMatchID = cadet.uuid;
				break;
			} else if(cadet.lastName.toLower() == lastName.toLower() && matchWeight < 2){
				possibleMatchID = cadet.uuid;
				matchWeight = 2;
			} else if(cadet.lastName.toLower() == firstName.toLower() && matchWeight < 1){
				possibleMatchID = cadet.uuid;
				matchWeight = 1;
			} else if(cadet.firstName.toLower() == lastName.toLower() && matchWeight < 1){
				possibleMatchID = cadet.uuid;
				matchWeight = 1;
			}
		}

		if(possibleMatchID.length() > 0){
			Cadet* cadet = &DataManager::cadets[possibleMatchID];
			//Ask if user wants to edit existing similar cadet instead
			QMessageBox::StandardButton response = QMessageBox::question(this,
																		 "Possible duplicate entry",
																		 "Another cadet with a similar name already exists ("+cadet->getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST)+"). Do you want to edit this cadet instead?",
																		 QMessageBox::Yes | QMessageBox::No);

			if(response == QMessageBox::Yes){
				mainWindow->editCadet(possibleMatchID);
				delete this;
				return;
			}
		}
		//Create a cadet object using a complete constructor and insert into the DataManager
		Cadet newCadet(UUIDGenerator::generateUUID(UUIDGenerator::CADET),
					   ui->idBox->text().toInt(),
					   Cadet::GRADE(ui->gradeBox->currentIndex()),
					   ui->gradeBox->currentIndex() == 0 ? Constants::comboBox_CadetRanks[ui->rankBox->currentText()] : Constants::comboBox_SMRanks[ui->rankBox->currentText()],
					   firstName,
					   lastName,
					   Constants::comboBox_Flight[ui->flightBox->currentText()],
					   ui->notesEdit->toPlainText());
		DataManager::cadets.insert(newCadet.uuid, newCadet);

		newCadet.takeSnapshot();

		//Show status message that the cadet was just created
		mainWindow->showStatusMessage("Created "+Cadet::getGradeStr(Cadet::GRADE(ui->gradeBox->currentIndex()))+" "+ui->lastNameEdit->text()+".");
	} else {
		//Edit the existing cadet and update it with current values from the editor
		Cadet* cadet = &DataManager::cadets[id];
		cadet->capid = ui->idBox->text().toInt();
		cadet->grade = Cadet::GRADE(ui->gradeBox->currentIndex());
		cadet->rank = cadet->grade == Cadet::GRADE::CADET ? Constants::comboBox_CadetRanks[ui->rankBox->currentText()] :
															Constants::comboBox_SMRanks[ui->rankBox->currentText()];
		cadet->firstName = ui->firstNameEdit->text();
		cadet->lastName = ui->lastNameEdit->text();
		cadet->flight = Constants::comboBox_Flight[ui->flightBox->currentText()];
		cadet->notes = ui->notesEdit->toPlainText();

		cadet->takeSnapshot();

		//Show status message that the cadet was just edited
		mainWindow->showStatusMessage("Edited "+cadet->getGradeStr()+" "+cadet->lastName+".");
	}

	DataManager::setDirty();

	//Refresh Cadets display and close editor window
	mainWindow->updateEditorView(MainWindow::EDITORTYPE::CADET);
	mainWindow->deleteCadetEditor();
}

void CadetEditor::on_buttonBox_rejected() {
	mainWindow->deleteCadetEditor();
}
