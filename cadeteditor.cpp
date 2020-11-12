#include "cadeteditor.h"
#include "ui_cadeteditor.h"
#include "cadet.h"
#include "datamanager.h"
#include "mainwindow.h"

CadetEditor::CadetEditor(int id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CadetEditor)
{
    ui->setupUi(this);
	ui->gradeBox->clear();
	ui->gradeBox->addItem(Cadet::getGradeStr(Cadet::GRADE::CADET));
	ui->gradeBox->addItem(Cadet::getGradeStr(Cadet::GRADE::SENIORMEMBER));

	ui->flightBox->clear();
	ui->flightBox->addItems(Cadet::comboBox_Flight.keys());

	ui->idBox->setValidator(new QIntValidator(0, 999999, this));

	if(id != 0){
		this->id = id;
		Cadet *cadet = &DataManager::cadets[id];
		ui->idBox->setText(QString::number(id));
		ui->gradeBox->setCurrentIndex(cadet->grade);

		ui->rankBox->setCurrentText(cadet->getRankStr());
		ui->firstNameEdit->setText(cadet->firstName);
		ui->lastNameEdit->setText(cadet->lastName);
		ui->flightBox->setCurrentText(cadet->getFlightStr());
		ui->notesEdit->setText(cadet->notes);
	}
}

CadetEditor::~CadetEditor() {
    delete ui;
}

void CadetEditor::on_gradeBox_currentIndexChanged(int index) {
	ui->rankBox->clear();
    if(index == Cadet::GRADE::CADET){
		ui->rankBox->addItems(Cadet::comboBox_CadetRanks.keys());
    } else {
		ui->rankBox->addItems(Cadet::comboBox_SMRanks.keys());
    }
}

void CadetEditor::createCadet(){
	Cadet newCadet(ui->idBox->text().toInt(),
								Cadet::GRADE(ui->gradeBox->currentIndex()),
								ui->gradeBox->currentIndex() == 0 ? Cadet::comboBox_CadetRanks[ui->rankBox->currentText()] : Cadet::comboBox_SMRanks[ui->rankBox->currentText()],
								ui->firstNameEdit->text(),
								ui->lastNameEdit->text(),
								Cadet::comboBox_Flight[ui->flightBox->currentText()],
								ui->notesEdit->toPlainText());
	DataManager::cadets.insert(ui->idBox->text().toInt(), newCadet);
}

void CadetEditor::on_buttonBox_accepted() {
	if(ui->idBox->text().length() <= 0 || ui->lastNameEdit->text().length() <= 0){
		MainWindow::getInstance()->showStatusMessage("Please fill required fields");
		if(ui->idBox->text().length() <= 0){
			ui->idBox->setStyleSheet("color: rgb(200, 0, 0);");
		} else {
			ui->idBox->setStyleSheet("");
		}
		if(ui->lastNameEdit->text().length() <= 0){
			ui->lastNameEdit->setStyleSheet("color: rgb(200, 0, 0);");
		} else {
			ui->lastNameEdit->setStyleSheet("");
		}
		return;
	}
	if(id == 0){
		createCadet();
		MainWindow::getInstance()->showStatusMessage("Created "+Cadet::getGradeStr(Cadet::GRADE(ui->gradeBox->currentIndex()))+" "+ui->lastNameEdit->text()+".");
	} else {
		Cadet* cadet = &DataManager::cadets[ui->idBox->text().toInt()];
		if(id == cadet->capid){
			cadet->grade = Cadet::GRADE(ui->gradeBox->currentIndex());
			cadet->rank = cadet->grade == Cadet::GRADE::CADET ? Cadet::comboBox_CadetRanks[ui->rankBox->currentText()] :
																Cadet::comboBox_SMRanks[ui->rankBox->currentText()];
			cadet->firstName = ui->firstNameEdit->text();
			cadet->lastName = ui->lastNameEdit->text();
			cadet->flight = Cadet::comboBox_Flight[ui->flightBox->currentText()];
			cadet->notes = ui->notesEdit->toPlainText();
		} else {
			DataManager::cadets.remove(id);
			createCadet();
		}
		MainWindow::getInstance()->showStatusMessage("Edited "+cadet->getGradeStr()+" "+cadet->lastName+".");
	}
	delete this;
}

void CadetEditor::on_buttonBox_rejected() {
	delete this;
}
