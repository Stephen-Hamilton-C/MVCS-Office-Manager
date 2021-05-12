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

CadetEditor::CadetEditor(QString id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CadetEditor)
{
    ui->setupUi(this);

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
        ui->rankBox->addItems(Constants::comboBox_CadetRanks.keys());
    } else {
        ui->rankBox->addItems(Constants::comboBox_SMRanks.keys());
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

	if(!valid){
		MainWindow::getInstance()->showStatusMessage("Please fill required fields");
		return;
	}

	//If creating a new cadet
	if(id.isEmpty()){
		//Create a cadet object using a complete constructor and insert into the DataManager
		Cadet newCadet(QUuid::createUuid().toString(),
					   ui->idBox->text().toInt(),
					   Cadet::GRADE(ui->gradeBox->currentIndex()),
					   ui->gradeBox->currentIndex() == 0 ? Constants::comboBox_CadetRanks[ui->rankBox->currentText()] : Constants::comboBox_SMRanks[ui->rankBox->currentText()],
					   ui->firstNameEdit->text(),
					   ui->lastNameEdit->text(),
					   Constants::comboBox_Flight[ui->flightBox->currentText()],
					   ui->notesEdit->toPlainText());
		DataManager::cadets.insert(newCadet.uuid, newCadet);

		MainWindow::getInstance()->showStatusMessage("Created "+Cadet::getGradeStr(Cadet::GRADE(ui->gradeBox->currentIndex()))+" "+ui->lastNameEdit->text()+".");
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

		MainWindow::getInstance()->showStatusMessage("Edited "+cadet->getGradeStr()+" "+cadet->lastName+".");
	}

	//Refresh Cadets display and close editor window
	MainWindow::getInstance()->updateEditorView(MainWindow::EDITORTYPE::CADET);
	MainWindow::getInstance()->deleteCadetEditor();
}

void CadetEditor::on_buttonBox_rejected() {
	MainWindow::getInstance()->deleteCadetEditor();
}
