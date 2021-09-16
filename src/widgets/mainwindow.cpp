/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include "datamanager.h"
#include "supplyitem.h"
#include "inspectioncard.h"
#include "cadeteditor.h"
#include "supplyeditor.h"
#include "inspectioneditor.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QCloseEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	DataManager::setMainWindow(this);

	this->setWindowTitle(Constants::name);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
	this->showMaximized();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event){
	if(dataDirty){
		event->ignore();

		QMessageBox::StandardButton response = QMessageBox::question(this, "Exit "+Constants::name, "Save before exiting?",
																	 QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

		if(response == QMessageBox::Yes){
			this->on_action_Save_triggered();
		}

		if(response != QMessageBox::Cancel){
			event->accept();
		}
	}
}

void MainWindow::changeView(int stackIndex){
	ui->stackedWidget->setCurrentIndex(stackIndex);
}

void MainWindow::updateEditorView(){
	updateEditorView(currentEditorType);
}

void MainWindow::updateEditorView(MainWindow::EDITORTYPE editorType){
	currentEditorType = editorType;

	QStandardItemModel *model = new QStandardItemModel();

	int sortColumn = 1;

	switch (editorType) {
		case MainWindow::EDITORTYPE::CADET: {
			model->setHorizontalHeaderLabels(Constants::cadetTableHeader);

			QMapIterator<QString, Cadet> i(DataManager::cadets);
			while(i.hasNext()){
				i.next();
				model->appendRow(QList<QStandardItem*>() <<
								 new QStandardItem(i.value().uuid) <<
								 new QStandardItem(QString::number(i.value().capid)) <<
								 new QStandardItem(i.value().getGradeStr()) <<
								 new QStandardItem(i.value().getRankStr()) <<
								 new QStandardItem(i.value().getFormattedName()) <<
								 new QStandardItem(i.value().getFlightStr()) <<
								 new QStandardItem(i.value().notes));
			}

			sortColumn = 4;
			break;
		}
		case MainWindow::EDITORTYPE::SUPPLY: {
			model->setHorizontalHeaderLabels(Constants::supplyTableHeader);

			QMapIterator<QString, SupplyItem> i(DataManager::supplyItems);
			while(i.hasNext()){
				i.next();

				//Convert that properties list into a human-readable string
				QString propertiesStr;
				QMapIterator<QString, QVariant> j(i.value().properties);
				while (j.hasNext()) {
					j.next();
					propertiesStr += j.key() + ": "+j.value().toString() + (j.hasNext() ? "\n" : "");
				}

				model->appendRow(QList<QStandardItem*>() <<
								 new QStandardItem(i.value().uuid) <<
								 new QStandardItem(i.value().name) <<
								 new QStandardItem(i.value().category) << //This caused infinite recursion??
								 new QStandardItem(QString::number(i.value().count)) <<
								 new QStandardItem(propertiesStr));
			}
			break;
		}
		case MainWindow::EDITORTYPE::INSPECTIONLOGS: {
			model->setHorizontalHeaderLabels(Constants::cardTableHeader);

			QMapIterator<QString, InspectionCard> i(DataManager::insCards);
			while(i.hasNext()){
				i.next();

				model->appendRow(QList<QStandardItem*>() <<
								 new QStandardItem(i.value().uuid) <<
								 new QStandardItem(i.value().getCadet()->getFlightStr()) <<
								 new QStandardItem(i.value().getCadet()->getFormattedName()) <<
								 new QStandardItem(i.value().date.toString()) <<
								 new QStandardItem(i.value().getRatingString(i.value().appearanceScore)) <<
								 new QStandardItem(i.value().getRatingString(i.value().garmentsScore)) <<
								 new QStandardItem(i.value().getRatingString(i.value().accountrementsScore)) <<
								 new QStandardItem(i.value().getRatingString(i.value().footwearScore)) <<
								 new QStandardItem(i.value().getRatingString(i.value().bearingScore)) <<
								 new QStandardItem(i.value().getRatingString(i.value().getOverallRating())));
			}

			sortColumn = 3;
			break;
		}
	}

	ui->editorView->setModel(model);
	ui->editorView->setSortingEnabled(true);
	ui->editorView->sortByColumn(sortColumn, Qt::SortOrder::AscendingOrder);
	ui->editorView->verticalHeader()->setVisible(false);
	ui->editorView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	ui->editorView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	//UUIDs are stored in column 0, let's hide those since the user isn't concerned about UUIDs
	ui->editorView->hideColumn(0);
	ui->editorView->setWordWrap(true);
	ui->editorView->setTextElideMode(Qt::ElideMiddle);
	ui->editorView->resizeRowsToContents();
	ui->editorView->resizeColumnsToContents();
}

void MainWindow::getSelectedID(QItemSelectionModel *selection, QString &id) const {
	if(selection->hasSelection()){
		//Have to do some gymnastics to get the UUID of the selected role
		QAbstractItemModel *model = ui->editorView->model();

		//Since the selection mode is single selection, there should always be only one selected row.
		//Find the index of that row and then get the data at column 0 (the UUID) and convert it into an int.
		//Now that we have the UUID, we can use DataManager to find the cadet pointer.
		int rowIndex = selection->selectedRows()[0].row();
		QModelIndex index = model->index(rowIndex, 0);
		id = model->data(index).toString();
		qDebug() << id << "selected";
	}
}

void MainWindow::on_editorEdit_clicked() {
	QString id = "";
	getSelectedID(ui->editorView->selectionModel(), id);
	if(!id.isEmpty()){
		switch(currentEditorType){
			case MainWindow::EDITORTYPE::CADET: {
				editCadet(id);
				break;
			}
			case MainWindow::EDITORTYPE::SUPPLY: {
				editSupplyItem(id);
				break;
			}
			case MainWindow::EDITORTYPE::INSPECTIONLOGS: {
				cardEditorWindow = new InspectionEditor(this, this, id);
				cardEditorWindow->show();
				cardEditorWindow->setWindowTitle("Edit inspection log for "+DataManager::insCards[id].getCadet()->getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST));
                cardEditorWindow->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
				break;
			}
		}
	}
}

void MainWindow::editCadet(QString id) {
	Cadet* cadet = &DataManager::cadets[id];
	cadetEditorWindow = new CadetEditor(this, this, id);
	cadetEditorWindow->show();
	cadetEditorWindow->setWindowTitle("Edit "+cadet->getFormattedName(Cadet::NAMEFORMAT::GRADEFIRSTLAST));
    cadetEditorWindow->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void MainWindow::editSupplyItem(QString id){
	supplyEditorWindow = new SupplyEditor(this, this, id);
	supplyEditorWindow->show();
	supplyEditorWindow->setWindowTitle("Edit "+DataManager::supplyItems[id].name);
    supplyEditorWindow->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void MainWindow::on_editorDelete_clicked() {
	QString id = "";
	getSelectedID(ui->editorView->selectionModel(), id);
	if(!id.isEmpty() && QMessageBox::question(this, "Confirm Delete", "Are you sure you want to delete this item?") == QMessageBox::Yes){
		switch(currentEditorType){
			case MainWindow::EDITORTYPE::CADET: {
				if(DataManager::cadets.contains(id)){
					QString name = DataManager::cadets[id].getGradeStr()+" "+DataManager::cadets[id].lastName;
					DataManager::cadets.remove(id);
					showStatusMessage("Deleted "+name+".");
					updateEditorView();
				} else {
					showStatusMessage("Failed to delete: No cadet found.");
				}
				break;
			}
			case MainWindow::EDITORTYPE::SUPPLY: {
				if(DataManager::supplyItems.contains(id)){
					QString name = DataManager::supplyItems[id].name;
					DataManager::supplyItems.remove(id);
					showStatusMessage("Deleted "+name+".");
					updateEditorView();
				} else {
					showStatusMessage("Failed to delete: No supply item found.");
				}
				break;
			}
			case MainWindow::EDITORTYPE::INSPECTIONLOGS: {
				if(DataManager::insCards.contains(id)){
					QString cadetName = DataManager::insCards[id].getCadet()->lastName;
					QDate date = DataManager::insCards[id].date;
					DataManager::insCards.remove(id);
					QString s = cadetName.endsWith("s") ? "'" : "'s";
					showStatusMessage("Deleted "+cadetName+s+" inspection from "+date.toString());
					updateEditorView();
				} else {
					showStatusMessage("Failed to delete: No inspection entry found.");
				}
			}
		}
	}
}

void MainWindow::deleteCadetEditor(){
	if(cadetEditorWindow != nullptr){
		delete cadetEditorWindow;
		cadetEditorWindow = nullptr;
	}
}

void MainWindow::deleteItemEditor(){
	if(supplyEditorWindow != nullptr){
		delete supplyEditorWindow;
		supplyEditorWindow = nullptr;
	}
}

void MainWindow::deleteCardEditor(){
	if(cardEditorWindow != nullptr){
		delete cardEditorWindow;
		cardEditorWindow = nullptr;
	}
}

void MainWindow::setDirty(const bool dirty)
{
	dataDirty = dirty;

	QString dirtyMarker = dirty ? "*" : "";
	this->setWindowTitle(Constants::name + " - " + DataManager::getFilePath() + dirtyMarker);
}

void MainWindow::on_actionCadets_triggered() {
	changeView(1);
	updateEditorView(MainWindow::EDITORTYPE::CADET);
	deleteItemEditor();
	deleteCardEditor();
}

void MainWindow::on_actionSupply_triggered() {
	changeView(1);
	updateEditorView(MainWindow::EDITORTYPE::SUPPLY);
	deleteCadetEditor();
	deleteCardEditor();
}

void MainWindow::on_actionInspections_triggered() {
	changeView(1);
	updateEditorView(MainWindow::EDITORTYPE::INSPECTIONLOGS);
	deleteCadetEditor();
	deleteItemEditor();
}

void MainWindow::on_actionFlights_Staff_triggered() {
	changeView(4);
}

void MainWindow::on_actionScores_triggered()
{
	changeView(2);
}

const QString aboutHTML =
		"<HTML>"
		"<p><b>"+Constants::name+" "+Constants::version+"</b></p>\n"
		"<p>"+Constants::name+" was designed for Civil Air Patrol's Mount Vernon Composite Squadron in the National Capital Wing, but may be used for other squadrons if desired.<p>\n"
		"<p>"+Constants::name+" helps office staff keep track of supply and which cadets or senior members have taken certain items. "
		"It also can show which cadets and flights are doing well with inspections.</p>"
		"<p>"+Constants::name+" was developed as an open source project under the <a href=\"https://www.gnu.org/licenses/gpl-3.0.en.html\">GPL-3.0 License</a>.</p>"
		"<p>You can access the source code here:<br>"
		"<a href=\"https://github.com/Stephen-Hamilton-C/MVCS-Office-Manager\">https://github.com/Stephen-Hamilton-C/MVCS-Office-Manager</a></p>"
		"</HTML>";

void MainWindow::on_action_About_triggered() {
	QMessageBox::about(this, "About "+Constants::name, aboutHTML);
}

void MainWindow::on_actionAbout_Qt_triggered() {
	QApplication::aboutQt();
}

void MainWindow::on_action_Save_triggered() {
	DataManager::writeToFile();
}

void MainWindow::on_editorNew_clicked() {
	switch(currentEditorType){
		case MainWindow::EDITORTYPE::CADET: {
			//Make new cadet dialog appear
			cadetEditorWindow = new CadetEditor(this, this);
			cadetEditorWindow->show();
			cadetEditorWindow->setWindowTitle("New Cadet");
			break;
		}
		case MainWindow::EDITORTYPE::SUPPLY: {
			//Make new supply item dialog appear
			supplyEditorWindow = new SupplyEditor(this, this);
			supplyEditorWindow->show();
			supplyEditorWindow->setWindowTitle("New Supply Item");
			break;
		}
		case MainWindow::EDITORTYPE::INSPECTIONLOGS: {
			//Make new inspection log appear
			cardEditorWindow = new InspectionEditor(this, this);
			cardEditorWindow->show();
			cardEditorWindow->setWindowTitle("New Inspection Log");
			break;
		}
	}
}

void MainWindow::showStatusMessage(QString message, int timeout){
	message = QTime::currentTime().toString("HH:mm") + " - " + message;
	ui->statusBar->showMessage(message, timeout);
}

void MainWindow::on_editorView_doubleClicked(const QModelIndex &index) {
	on_editorEdit_clicked();
}

void MainWindow::on_action_Load_triggered()
{
	QString filePath = QFileDialog::getOpenFileName(this, "Open Data File", QString(), "JSON Files (*.json)");
	if(!filePath.isEmpty()){
		DataManager::readFromFile(filePath);

		updateEditorView();
	}
}

void MainWindow::on_actionSave_as_triggered()
{
	QString filePath = QFileDialog::getSaveFileName(this, "Save Data File", DataManager::getFilePath(), "JSON Files (*.json)");

	//Automatically add .json extension
	QString extension = filePath.right(5);
	if(extension.toLower() != ".json"){
		filePath += ".json";
	}

	if(!filePath.isEmpty() && filePath.toLower() != ".json"){
		DataManager::writeToFile(filePath);
	}
}

void MainWindow::on_actionNew_triggered()
{
	//TODO: Check if need to save and prompt before making new file
	if(dataDirty){
		on_actionSave_as_triggered();
	}

	DataManager::newFile();

	updateEditorView();
}
