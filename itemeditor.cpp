/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "itemeditor.h"
#include "ui_itemeditor.h"
#include "datamanager.h"
#include "mainwindow.h"
#include "constants.h"
#include "supplyitem.h"

#include <QStandardItemModel>

ItemEditor::ItemEditor(MainWindow *mainWindow, QWidget *parent, QString id) :
	QDialog(parent),
	ui(new Ui::ItemEditor)
{
	ui->setupUi(this);
	this->mainWindow = mainWindow;

	qDebug() << "ID received:" << id;

    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(Constants::itemPropertyTableHeaders);

    QStandardItemModel* catModel = new QStandardItemModel();
    for(int i = 0; i < DataManager::itemCategories.count(); i++){
        catModel->appendRow(new QStandardItem(DataManager::itemCategories[i]));
    }
    ui->categoryBox->setModel(catModel);

	if(!id.isEmpty()){
		this->id = id;
		SupplyItem *item = &DataManager::items[id];

		ui->nameEdit->setProperty("item_uuid", id);
		ui->nameEdit->setText(item->name);
        ui->categoryBox->setCurrentText(item->category);
		ui->countBox->setValue(item->count);
		ui->lowCountBox->setValue(item->lowCountThreshold);

		QMapIterator<QString, QVariant> i(item->properties);
		while(i.hasNext()){
			i.next();
			model->appendRow(QList<QStandardItem*>() <<
							 new QStandardItem(i.key()) <<
							 new QStandardItem(i.value().toString()));
		}
	} else {
		ui->nameEdit->setProperty("item_uuid", QUuid::createUuid().toString());
        ui->categoryBox->setCurrentText("Miscellaneous");
	}

    ui->propertiesView->setModel(model);
	ui->propertiesView->verticalHeader()->setVisible(false);
	ui->propertiesView->setWordWrap(true);
	ui->propertiesView->setTextElideMode(Qt::ElideMiddle);
	ui->propertiesView->resizeColumnsToContents();
	ui->propertiesView->resizeRowsToContents();
	ui->propertiesView->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	ui->propertiesView->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

    ui->nameEdit->setFocus(Qt::FocusReason::TabFocusReason);
}



ItemEditor::~ItemEditor()
{
	delete ui;
}

void ItemEditor::constructPropertiesMap(QVariantMap &properties) const {
	QAbstractItemModel* model = ui->propertiesView->model();
	if(model == nullptr){
		return;
	}

	for(int row = 0; row < model->rowCount(); row++){
		QModelIndex propNameIndex = model->index(row, 0);
		QModelIndex propValIndex = model->index(row, 1);

		QString propName = model->data(propNameIndex).toString();
		QVariant propVal = model->data(propValIndex);

		properties.insert(propName, propVal);
	}
}

void ItemEditor::on_buttonBox_accepted() {
	if(ui->nameEdit->text().length() <= 0){
		mainWindow->showStatusMessage("Please fill required fields");
		ui->nameEdit->setStyleSheet("color: rgb(200, 0, 0);");
		return;
	}

	QVariantMap properties;
	constructPropertiesMap(properties);

	if(id.isEmpty()){
		SupplyItem item(ui->nameEdit->property("item_uuid").toString(),
						ui->nameEdit->text(),
                        ui->categoryBox->currentText(),
						ui->countBox->value(),
						ui->lowCountBox->value(),
						properties);
		DataManager::items.insert(item.uuid, item);

		mainWindow->showStatusMessage("Created "+item.name+".");
	} else {
		SupplyItem* item = &DataManager::items[ui->nameEdit->property("item_uuid").toString()];
		item->name = ui->nameEdit->text();
        item->category = ui->categoryBox->currentText();
		item->count = ui->countBox->value();
		item->lowCountThreshold = ui->lowCountBox->value();
		item->properties = properties;

		mainWindow->showStatusMessage("Edited "+item->name+".");
	}

    if(!DataManager::itemCategories.contains(ui->categoryBox->currentText())){
        DataManager::itemCategories.append(ui->categoryBox->currentText());
    }

	mainWindow->updateEditorView(MainWindow::EDITORTYPE::SUPPLY);
	mainWindow->deleteItemEditor();
}

void ItemEditor::on_createProperty_clicked() {
	QAbstractItemModel* model = ui->propertiesView->model();
	QStandardItemModel* smodel = new QStandardItemModel();

    smodel->setHorizontalHeaderLabels(Constants::itemPropertyTableHeaders);

	//model->rowCount is freaking gay
	int rows;
	try {
		rows = model->rowCount();
	}  catch (int e) {
		rows = 0;
	}

	for(int row = 0; row < rows; row++){
		QModelIndex propNameIndex = model->index(row, 0);
		QModelIndex propValIndex = model->index(row, 1);

		smodel->appendRow(QList<QStandardItem*>() <<
						  new QStandardItem(model->data(propNameIndex).toString()) <<
						  new QStandardItem(model->data(propValIndex).toString()));
	}

	smodel->appendRow(QList<QStandardItem*>() <<
					  new QStandardItem("New Property") <<
					  new QStandardItem("Value"));

	ui->propertiesView->setModel(smodel);

	ui->propertiesView->resizeColumnsToContents();
	ui->propertiesView->resizeRowsToContents();
}

void ItemEditor::on_deleteProperty_clicked() {
	QItemSelectionModel* selection = ui->propertiesView->selectionModel();
	if(selection->hasSelection()){
		QAbstractItemModel* model = ui->propertiesView->model();

		model->removeRow(selection->selectedRows()[0].row());

		ui->propertiesView->resizeColumnsToContents();
		ui->propertiesView->resizeRowsToContents();
	}
}
