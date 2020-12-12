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
		ui->cadetBox->setCurrentText(DataManager::cadets[card->cadetUUID].getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST));
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

	for(int i = 1; i <= 3; i++){
		if(InspectionEditor::findChild<QRadioButton*>(radioName+QString::number(i))->isChecked()){
			rating = InspectionCard::RATING(i);
			break;
		}
	}

	return rating;
}

void InspectionEditor::on_buttonBox_accepted() {
	//Check if cadet, flight, date, and scores are valid

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
		MainWindow::getInstance()->showStatusMessage("Created inspection log for "+DataManager::cadets[card.cadetUUID].getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST)+".");
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

		MainWindow::getInstance()->showStatusMessage("Edited inspection log for "+DataManager::cadets[card->cadetUUID].getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST)+".");
	}

	MainWindow::getInstance()->updateEditorView(MainWindow::EDITORTYPE::INSPECTIONLOGS);
	MainWindow::getInstance()->deleteCardEditor();
}
