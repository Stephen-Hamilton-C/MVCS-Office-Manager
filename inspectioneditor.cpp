/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "inspectioneditor.h"
#include "ui_inspectioneditor.h"
#include "mainwindow.h"
#include "constants.h"

InspectionEditor::InspectionEditor(QString id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InspectionEditor)
{
	ui->setupUi(this);

	//Setup flightBox selections
	ui->flightBox->addItems(Constants::comboBox_Flight.keys());

	//Setup cadetMap so cadets have a clean display name, yet can easily still find UUID from the formatted name.
	cadetMap.clear();

	cadetMap.insert("---Select One---", "");
	QMapIterator<QString, Cadet> i(DataManager::cadets);
	while(i.hasNext()){
		i.next();
		cadetMap.insert(i.value().getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST), i.key());
	}

	ui->cadetBox->clear();
	ui->cadetBox->addItems(cadetMap.keys());

	if(id.isEmpty()){ //If creating a new log
		//QOL: Maybe set it to the most recent Thursday?
		ui->dateEdit->setDate(QDate::currentDate());
	} else if(DataManager::insCards.contains(id)){ //If editing an existing log
		this->id = id;
		InspectionCard* card = &DataManager::insCards[id];

		//Setup UI so it matches the current data for the inspection log
		ui->flightBox->setCurrentText(Cadet::getFlightStr(card->cadetFlightAtInspect));
		ui->cadetBox->setCurrentText(card->getCadet()->getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST));
		ui->dateEdit->setDate(card->date);

		setRadioCheck("appearance", card->appearanceScore);
		setRadioCheck("garments", card->garmentsScore);
		setRadioCheck("accountrements", card->accountrementsScore);
		setRadioCheck("footwear", card->footwearScore);
		setRadioCheck("bearing", card->bearingScore);
	}

}

InspectionEditor::~InspectionEditor()
{
	delete ui;
}

void InspectionEditor::setRadioCheck(QString radioName, int score){
	InspectionEditor::findChild<QRadioButton*>(radioName+QString::number(score))->setChecked(true);
}

InspectionCard::RATING InspectionEditor::getScoreFromRadio(QString radioName){
	InspectionCard::RATING rating = InspectionCard::NEEDSIMPROVEMENT;

	//Checks through a set of radioButtons to see which is set.
	for(int i = 0; i <= 2; i++){
		if(InspectionEditor::findChild<QRadioButton*>(radioName+QString::number(i))->isChecked()){
			rating = InspectionCard::RATING(i);
			break;
		}
	}

	return rating;
}

bool InspectionEditor::radioHasScore(QString radioName){
	for(int i = 0; i <= 2; i++){
		if(InspectionEditor::findChild<QRadioButton*>(radioName+QString::number(i))->isChecked()){
			return true;
		}
	}

	return false;
}

void InspectionEditor::on_buttonBox_accepted() {
	//Check if required fields have been filled
	bool valid = true;

	//Is a valid cadet selected?
	if(ui->cadetBox->currentText() == "---Select One---" || !DataManager::cadets.contains(cadetMap[ui->cadetBox->currentText()])){
		ui->cadetBox->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->cadetBox->setStyleSheet("");
	}

	//Is the date before today?
	if(ui->dateEdit->date().toJulianDay() > QDate::currentDate().toJulianDay()){
		ui->dateEdit->setStyleSheet("color: rgb(200, 0, 0);");
		MainWindow::getInstance()->showStatusMessage("Date invalid: must be before today's date.");
		valid = false;
	} else {
		ui->dateEdit->setStyleSheet("");
	}

	//Does appearance have a score?
	if(!radioHasScore("appearance")){
		ui->appearanceLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->appearanceLabel->setStyleSheet("");
	}

	//Does garments have a score?
	if(!radioHasScore("garments")){
		ui->garmentsLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->garmentsLabel->setStyleSheet("");
	}

	//Does accountrements have a score?
	if(!radioHasScore("accountrements")){
		ui->accountrementsLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->accountrementsLabel->setStyleSheet("");
	}

	//Does footwear have a score?
	if(!radioHasScore("footwear")){
		ui->footwearLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->footwearLabel->setStyleSheet("");
	}

	//Does bearing have a score?
	if(!radioHasScore("bearing")){
		ui->bearingLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->bearingLabel->setStyleSheet("");
	}

	if(!valid){
		return;
	}

	//If creating a new inspection log entry
	if(id.isEmpty()){
		//Create an inspection log object using a complete constructor and insert into the DataManager
		InspectionCard card(QUuid::createUuid().toString(),
							cadetMap[ui->cadetBox->currentText()],
							ui->dateEdit->date(),
							getScoreFromRadio("appearance"),
							getScoreFromRadio("garments"),
							getScoreFromRadio("accountrements"),
							getScoreFromRadio("footwear"),
							getScoreFromRadio("bearing")
							);

		DataManager::insCards.insert(card.uuid, card);
		MainWindow::getInstance()->showStatusMessage("Created inspection log for "+card.getCadet()->getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST)+".");
	} else {
		//Edit the existing inspection log and update it with current values from the editor
		InspectionCard* card = &DataManager::insCards[id];
		Cadet* cadet = &DataManager::cadets[cadetMap[ui->cadetBox->currentText()]];

		//If the assigned cadet to the inspection is different, set the phase and flight at inspect
		if(cadet->uuid != card->cadetUUID){
			card->cadetPhaseAtInspect = cadet->getPhase();
			card->cadetFlightAtInspect = cadet->flight;
			card->cadetUUID = cadet->uuid;
		}

		card->date = ui->dateEdit->date();
		card->appearanceScore = getScoreFromRadio("appearance");
		card->garmentsScore = getScoreFromRadio("garments");
		card->accountrementsScore = getScoreFromRadio("accountrements");
		card->footwearScore = getScoreFromRadio("footwear");
		card->bearingScore = getScoreFromRadio("bearing");

		MainWindow::getInstance()->showStatusMessage("Edited inspection log for "+card->getCadet()->getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST)+".");
	}

	//Refresh inspection log display and close editor window
	MainWindow::getInstance()->updateEditorView(MainWindow::EDITORTYPE::INSPECTIONLOGS);
	MainWindow::getInstance()->deleteCardEditor();
}

void InspectionEditor::on_cadetBox_currentTextChanged(const QString &arg1) {
	if(DataManager::cadets.contains(cadetMap[arg1])){
		Cadet* cadet = &DataManager::cadets[cadetMap[arg1]];
		ui->flightBox->setCurrentText(cadet->getFlightStr());
	}
}
