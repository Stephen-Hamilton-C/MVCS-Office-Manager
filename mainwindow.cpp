#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cadet.h"
#include "supplyitem.h"
#include "constants.h"
#include "datamanager.h"
#include "cadeteditor.h"

#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include <QStandardItemModel>

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

Cadet* cadet = nullptr;

void MainWindow::changeView(int stackIndex, QString subTitle){
    bool goHome = ui->stackedWidget->currentIndex() == stackIndex;
    ui->stackedWidget->setCurrentIndex(goHome ? 0 : stackIndex);
    this->setWindowTitle(Constants::name+(goHome ? "" : " - "+subTitle));
}

void MainWindow::updateEditorView(MainWindow::EDITORTYPE editorType){
	QStandardItemModel *model = new QStandardItemModel();

	switch (editorType) {
		case MainWindow::EDITORTYPE::CADET:
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
		break;
	}


	ui->editorView->setModel(model);
	ui->editorView->verticalHeader()->setVisible(false);
	ui->editorView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	ui->editorView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	//UUIDs are stored in column 0, so let's hide those since the user isn't concerned about UUIDs
	ui->editorView->hideColumn(0);
	ui->editorView->setWordWrap(true);
	ui->editorView->setTextElideMode(Qt::ElideMiddle);
	ui->editorView->resizeRowsToContents();
	ui->editorView->resizeColumnsToContents();
}

void MainWindow::on_actionCadets_triggered() {
    changeView(1, "Cadets");
	updateEditorView(MainWindow::EDITORTYPE::CADET);
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
		Cadet *cadet = &DataManager::cadets[id];
		editorWindow = new CadetEditor(id);
		editorWindow->show();
		editorWindow->setWindowTitle("Edit "+QString(cadet->grade == Cadet::GRADE::CADET ? "Cadet" : "Senior Member")+" "+cadet->getFormattedName(Cadet::NAMEFORMAT::FIRSTLAST)+".");
	}
}

void MainWindow::on_editorDelete_clicked() {
	QString id = "";
	getSelectedID(ui->editorView->selectionModel(), id);
	if(!id.isEmpty() && DataManager::cadets.contains(id)){
		QString name = DataManager::cadets[id].getGradeStr()+" "+DataManager::cadets[id].lastName;
		DataManager::cadets.remove(id);
		showStatusMessage("Deleted "+name+".");
		updateEditorView(MainWindow::EDITORTYPE::CADET);
	} else {
		showStatusMessage("Failed to delete: No cadet found.");
	}
}

void MainWindow::on_actionSupply_triggered() {
    changeView(2, "Supply");
}

void MainWindow::on_actionInspections_triggered() {
    changeView(3, "Inspections");
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
    //Make new cadet dialog appear
	editorWindow = new CadetEditor();
	editorWindow->show();
	editorWindow->setWindowTitle("New Cadet");
}

void MainWindow::showStatusMessage(QString message, int timeout){
	ui->statusBar->showMessage(message, timeout);
}
