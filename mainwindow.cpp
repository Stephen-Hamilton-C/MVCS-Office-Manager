#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cadet.h"
#include "supplyitem.h"
#include "constants.h"
#include "datamanager.h"
#include "cadeteditor.h"
#include "itemeditor.h"

#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>

MainWindow* MainWindow::ptrInstance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
	if(ptrInstance != nullptr){
		delete this;
	}
	ptrInstance = this;
    ui->setupUi(this);
    this->setWindowTitle(Constants::name);
    this->showMaximized();

	DataManager::readFromFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeView(int stackIndex, QString subTitle){
	bool goHome = false; //ui->stackedWidget->currentIndex() == stackIndex;
    ui->stackedWidget->setCurrentIndex(goHome ? 0 : stackIndex);
    this->setWindowTitle(Constants::name+(goHome ? "" : " - "+subTitle));
}

void MainWindow::updateEditorView(){
	updateEditorView(currentEditorType);
}

void MainWindow::updateEditorView(MainWindow::EDITORTYPE editorType){
	currentEditorType = editorType;

	QStandardItemModel *model = new QStandardItemModel();
	//QSortFilterProxyModel filterModel;
	//filterModel.setSourceModel(model);

	int sortColumn = 1;

	switch (editorType) {
		case MainWindow::EDITORTYPE::CADET: {
			model->setHorizontalHeaderLabels(Cadet::tableHeader);

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
			model->setHorizontalHeaderLabels(SupplyItem::tableHeader);

			QMapIterator<QString, SupplyItem> i(DataManager::items);
			while(i.hasNext()){
				i.next();

				//Convert that properties list into a human-readable string
				QString propertiesStr;
				QMapIterator<QString, QVariant> j(i.value().properties);
				while (j.hasNext()) {
					j.next();
					propertiesStr += j.key() + ": "+j.value().toString() + "\n";
				}

				model->appendRow(QList<QStandardItem*>() <<
								 new QStandardItem(i.value().uuid) <<
								 new QStandardItem(i.value().name) <<
								 new QStandardItem(QString::number(i.value().count)) <<
								 new QStandardItem(propertiesStr));
			}
			break;
		}
		case MainWindow::EDITORTYPE::INSPECTIONLOGS: {
			model->setHorizontalHeaderLabels(InspectionCard::tableHeader);

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
				Cadet* cadet = &DataManager::cadets[id];
				cadetEditorWindow = new CadetEditor(id);
				cadetEditorWindow->show();
				cadetEditorWindow->setWindowTitle("Edit "+QString(cadet->grade == Cadet::GRADE::CADET ? "Cadet" : "Senior Member")+" "+cadet->getFormattedName(Cadet::NAMEFORMAT::FIRSTLAST));
				break;
			}
			case MainWindow::EDITORTYPE::SUPPLY: {
				itemEditorWindow = new ItemEditor(id);
				itemEditorWindow->show();
				itemEditorWindow->setWindowTitle("Edit "+DataManager::items[id].name);
				break;
			}
			case MainWindow::EDITORTYPE::INSPECTIONLOGS: {
				//TODO: Create Inspection editor window
				break;
			}
		}
	}
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
				if(DataManager::items.contains(id)){
					QString name = DataManager::items[id].name;
					DataManager::items.remove(id);
					showStatusMessage("Deleted "+name+".");
					updateEditorView();
				} else {
					showStatusMessage("Failed to delete: No item found.");
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
	if(itemEditorWindow != nullptr){
		delete itemEditorWindow;
		itemEditorWindow = nullptr;
	}
}

void MainWindow::deleteCardEditor(){
	//TODO: Create Inspection editor window
}

void MainWindow::on_actionCadets_triggered() {
	changeView(1, "Cadets");
	updateEditorView(MainWindow::EDITORTYPE::CADET);
	deleteItemEditor();
	deleteCardEditor();
}

void MainWindow::on_actionSupply_triggered() {
	changeView(1, "Supply");
	updateEditorView(MainWindow::EDITORTYPE::SUPPLY);
	deleteCadetEditor();
	deleteCardEditor();
}

void MainWindow::on_actionInspections_triggered() {
	changeView(1, "Inspection Logs");
	updateEditorView(MainWindow::EDITORTYPE::INSPECTIONLOGS);
	deleteCadetEditor();
	deleteItemEditor();
}

void MainWindow::on_actionFlights_Staff_triggered() {
    changeView(4, "Flights & Staff");
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
	showStatusMessage("Saving...");
    DataManager::writeToFile();
	showStatusMessage("Saved.");
}

void MainWindow::on_editorNew_clicked() {
	switch(currentEditorType){
		case MainWindow::EDITORTYPE::CADET: {
			//Make new cadet dialog appear
			cadetEditorWindow = new CadetEditor();
			cadetEditorWindow->show();
			cadetEditorWindow->setWindowTitle("New Cadet");
			break;
		}
		case MainWindow::EDITORTYPE::SUPPLY: {
			//Make new item dialog appear
			itemEditorWindow = new ItemEditor();
			itemEditorWindow->show();
			itemEditorWindow->setWindowTitle("New Item");
		}
		case MainWindow::EDITORTYPE::INSPECTIONLOGS: {
			//TODO: Create Inspection editor window
		}
	}
}

void MainWindow::showStatusMessage(QString message, int timeout){
	ui->statusBar->showMessage(message, timeout);
}

void MainWindow::on_editorView_doubleClicked(const QModelIndex &index) {
	on_editorEdit_clicked();
}
