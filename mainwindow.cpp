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

/* Create and Save test code
void MainWindow::on_createCadet_clicked() {
    qDebug() << "Creating cadet...";

    cadet = new Cadet(
                585448,
                Cadet::GRADE::CADET,
                Cadet::RANK::LT2ND,
                "Stephen",
                "Hamilton",
                Cadet::FLIGHT::STAFF,
                "Executive Officer\n"
                "Cyber Patriot Team Captain"
                );

    qDebug() << "Created cadet. \n" << cadet->toString();
}



void MainWindow::on_saveCadet_clicked() {
    if(cadet != nullptr){
        qDebug() << "Saving cadet...";

        QFile saveFile("cadet.json");

        if(saveFile.open(QIODevice::WriteOnly)){
            QJsonObject saveObject;
            cadet->write(saveObject);
            saveFile.write(QJsonDocument(saveObject).toJson());
            qDebug() << "Cadet saved. \n" << saveObject;
        }
    }
}

void MainWindow::on_loadCadet_clicked() {
    qDebug() << "Loading cadet...";

    QFile loadFile("cadet.json");

    if(loadFile.open(QIODevice::ReadOnly)){
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        if(cadet == nullptr){
            cadet = new Cadet();
        }

        cadet->read(loadDoc.object());

        qDebug() << "Cadet Loaded: " << cadet->toString();
    }
}

SupplyItem* item = nullptr;

void MainWindow::on_createItem_clicked() {
    qDebug() << "Creating item...";

    QVariantMap prop = QVariantMap();
    prop.insert("Size", "10R");

    item = new SupplyItem("ABU Blouse", 3, 0, prop);

    qDebug() << "Created item. \n" << item->toString();
}

void MainWindow::on_saveItem_clicked() {
    if(item != nullptr){
        qDebug() << "Saving item...";

        QFile saveFile("item.json");

        if(saveFile.open(QIODevice::WriteOnly)){
            QJsonObject saveObject;
            item->write(saveObject);
            saveFile.write(QJsonDocument(saveObject).toJson());
            qDebug() << "item saved. \n" << saveObject;
        }
    }
}

void MainWindow::on_loadItem_clicked() {
    qDebug() << "Loading item...";

    QFile loadFile("item.json");

    if(loadFile.open(QIODevice::ReadOnly)){
        QByteArray saveData = loadFile.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

        if(item == nullptr){
            item = new SupplyItem();
        }

        item->read(loadDoc.object());

        qDebug() << "Item Loaded: " << item->toString();
    }
}
*/

void MainWindow::changeView(int stackIndex, QString subTitle){
    bool goHome = ui->stackedWidget->currentIndex() == stackIndex;
    ui->stackedWidget->setCurrentIndex(goHome ? 0 : stackIndex);
    this->setWindowTitle(Constants::name+(goHome ? "" : " - "+subTitle));
}

void MainWindow::updateCadetView(){
	QStandardItemModel *model = new QStandardItemModel();

	model->setHorizontalHeaderLabels(Cadet::tableHeader);

	ui->cadetsView->setModel(model);
	ui->cadetsView->verticalHeader()->setVisible(false);
	ui->cadetsView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	ui->cadetsView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

	QMapIterator<int, Cadet> i(DataManager::cadets);
	while(i.hasNext()){
		i.next();
		model->appendRow(QList<QStandardItem*>() << new QStandardItem(QString::number(i.value().capid)) <<
						 new QStandardItem(i.value().getGradeStr()) <<
						 new QStandardItem(i.value().getRankStr()) <<
						 new QStandardItem(i.value().getFormattedName()) <<
						 new QStandardItem(i.value().getFlightStr()) <<
						 new QStandardItem(i.value().notes));
	}

	ui->cadetsView->setWordWrap(true);
	ui->cadetsView->setTextElideMode(Qt::ElideMiddle);
	ui->cadetsView->resizeRowsToContents();
	ui->cadetsView->resizeColumnsToContents();
}

void MainWindow::on_actionCadets_triggered() {
    changeView(1, "Cadets");
	updateCadetView();
}

void MainWindow::getSelectedID(QItemSelectionModel *selection, int &id) const {
	if(selection->hasSelection()){
		//Have to do some gymnastics to get the CAPID of the selected role
		QAbstractItemModel *model = ui->cadetsView->model();

		//Since the selection mode is single selection, there should always be only one selected row.
		//Find the index of that row and then get the data at column 0 (the CAPID) and convert it into an int.
		//Now that we have the CAPID, we can use DataManager to find the cadet pointer.
		int rowIndex = selection->selectedRows()[0].row();
		QModelIndex index = model->index(rowIndex, 0);
		id = model->data(index).toInt();
		qDebug() << id << "selected";
	}
}

void MainWindow::on_editCadet_clicked() {
	int id = 0;
	getSelectedID(ui->cadetsView->selectionModel(), id);
	if(id != 0){
		Cadet *cadet = &DataManager::cadets[id];
		editor = new CadetEditor(id);
		editor->show();
		editor->setWindowTitle("Edit "+QString(cadet->grade == Cadet::GRADE::CADET ? "Cadet" : "Senior Member")+" "+cadet->getFormattedName(Cadet::NAMEFORMAT::FIRSTLAST)+".");
	}
}

void MainWindow::on_deleteCadet_clicked() {
	int id = 0;
	getSelectedID(ui->cadetsView->selectionModel(), id);
	if(id != 0 && DataManager::cadets.contains(id)){
		QString name = DataManager::cadets[id].getGradeStr()+" "+DataManager::cadets[id].lastName;
		DataManager::cadets.remove(id);
		showStatusMessage("Deleted "+name+".");
		updateCadetView();
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

void MainWindow::on_newCadet_clicked() {
    //Make new cadet dialog appear
	editor = new CadetEditor();
    editor->show();
	editor->setWindowTitle("New Cadet");
}

void MainWindow::showStatusMessage(QString message, int timeout){
	ui->statusBar->showMessage(message, timeout);
}
