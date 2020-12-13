#include "inspectioneditor.h"
#include "ui_inspectioneditor.h"
#include "mainwindow.h"

InspectionEditor::InspectionEditor(QString id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InspectionEditor)
{
	ui->setupUi(this);

	ui->flightBox->addItems(Constants::comboBox_Flight.keys());

	//cadet grade + rank + name, UUID
	cadetMap.clear();

	cadetMap.insert("---Select One---", "");
	QMapIterator<QString, Cadet> i(DataManager::cadets);
	while(i.hasNext()){
		i.next();
		cadetMap.insert(i.value().getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST), i.key());
	}

	ui->cadetBox->clear();
	ui->cadetBox->addItems(cadetMap.keys());

	if(id.isEmpty()){
		ui->dateEdit->setDate(QDate::currentDate());
	} else {
		this->id = id;
		InspectionCard* card = &DataManager::insCards[id];

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
	bool valid = true;

	if(ui->cadetBox->currentText() == "---Select One---" || !DataManager::cadets.contains(cadetMap[ui->cadetBox->currentText()])){
		ui->cadetBox->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->cadetBox->setStyleSheet("");
	}

	if(ui->dateEdit->date().toJulianDay() > QDate::currentDate().toJulianDay()){
		ui->dateEdit->setStyleSheet("color: rgb(200, 0, 0);");
		MainWindow::getInstance()->showStatusMessage("Date invalid: must be before today's date.");
		valid = false;
	} else {
		ui->dateEdit->setStyleSheet("");
	}

	if(!radioHasScore("appearance")){
		ui->appearanceLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->appearanceLabel->setStyleSheet("");
	}

	if(!radioHasScore("garments")){
		ui->garmentsLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->garmentsLabel->setStyleSheet("");
	}

	if(!radioHasScore("accountrements")){
		ui->accountrementsLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->accountrementsLabel->setStyleSheet("");
	}

	if(!radioHasScore("footwear")){
		ui->footwearLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->footwearLabel->setStyleSheet("");
	}

	if(!radioHasScore("bearing")){
		ui->bearingLabel->setStyleSheet("color: rgb(200, 0, 0);");
		valid = false;
	} else {
		ui->bearingLabel->setStyleSheet("");
	}

	if(!valid){
		return;
	}

	if(id.isEmpty()){
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
		InspectionCard* card = &DataManager::insCards[id];
		Cadet* cadet = &DataManager::cadets[cadetMap[ui->cadetBox->currentText()]];

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

	MainWindow::getInstance()->updateEditorView(MainWindow::EDITORTYPE::INSPECTIONLOGS);
	MainWindow::getInstance()->deleteCardEditor();
}

void InspectionEditor::on_cadetBox_currentTextChanged(const QString &arg1) {
	if(DataManager::cadets.contains(cadetMap[arg1])){
		Cadet* cadet = &DataManager::cadets[cadetMap[arg1]];
		ui->flightBox->setCurrentText(cadet->getFlightStr());
	}
}
