/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "supplyeditor.h"
#include "ui_itemeditor.h"
#include "datamanager.h"
#include "mainwindow.h"
#include "constants.h"
#include "supplyitem.h"
#include "uuidgenerator.h"

#include <QStandardItemModel>

SupplyEditor::SupplyEditor(MainWindow *mainWindow, QWidget *parent, QString id) :
	QDialog(parent),
	ui(new Ui::ItemEditor)
{
	ui->setupUi(this);
	this->mainWindow = mainWindow;

	qDebug() << "ID received:" << id;

    QStandardItemModel* model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(Constants::supplyPropertyTableHeaders);

    QStandardItemModel* catModel = new QStandardItemModel();
    QSetIterator<QString> i(DataManager::supplyCategories);
    while(i.hasNext()){
        catModel->appendRow(new QStandardItem(i.next()));
    }
    ui->categoryBox->setModel(catModel);

	if(!id.isEmpty()){
		this->id = id;
        SupplyItem *supplyItem = &DataManager::supplyItems[id];

		ui->nameEdit->setProperty("item_uuid", id);
        ui->nameEdit->setText(supplyItem->name);
        ui->categoryBox->setCurrentText(supplyItem->category);
        ui->countBox->setValue(supplyItem->count);
        ui->lowCountBox->setValue(supplyItem->lowCountThreshold);

        QMapIterator<QString, QVariant> i(supplyItem->properties);
		while(i.hasNext()){
			i.next();
			model->appendRow(QList<QStandardItem*>() <<
							 new QStandardItem(i.key()) <<
							 new QStandardItem(i.value().toString()));
		}
	} else {
        ui->nameEdit->setProperty("item_uuid", UUIDGenerator::generateUUID(UUIDGenerator::SUPPLY));
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



SupplyEditor::~SupplyEditor()
{
	delete ui;
}

void SupplyEditor::constructPropertiesMap(QVariantMap &properties) const {
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

void SupplyEditor::on_buttonBox_accepted() {
	if(ui->nameEdit->text().length() <= 0){
		mainWindow->showStatusMessage("Please fill required fields");
		ui->nameEdit->setStyleSheet("color: rgb(200, 0, 0);");
		return;
	}

	QVariantMap properties;
	constructPropertiesMap(properties);

	if(id.isEmpty()){
        SupplyItem supplyItem(ui->nameEdit->property("item_uuid").toString(),
						ui->nameEdit->text(),
                        ui->categoryBox->currentText(),
						ui->countBox->value(),
						ui->lowCountBox->value(),
						properties);
        DataManager::supplyItems.insert(supplyItem.uuid, supplyItem);

        supplyItem.takeSnapshot();

        mainWindow->showStatusMessage("Created "+supplyItem.name+".");
	} else {
        SupplyItem* supplyItem = &DataManager::supplyItems[ui->nameEdit->property("item_uuid").toString()];
        supplyItem->name = ui->nameEdit->text();
        supplyItem->category = ui->categoryBox->currentText();
        supplyItem->count = ui->countBox->value();
        supplyItem->lowCountThreshold = ui->lowCountBox->value();
        supplyItem->properties = properties;

        supplyItem->takeSnapshot();

        mainWindow->showStatusMessage("Edited "+supplyItem->name+".");
	}

    if(!DataManager::supplyCategories.contains(ui->categoryBox->currentText())){
        DataManager::supplyCategories.insert(ui->categoryBox->currentText());
    }

    DataManager::setDirty();

	mainWindow->updateEditorView(MainWindow::EDITORTYPE::SUPPLY);
	mainWindow->deleteItemEditor();
}

void SupplyEditor::on_createProperty_clicked() {
	QAbstractItemModel* model = ui->propertiesView->model();
	QStandardItemModel* smodel = new QStandardItemModel();

    smodel->setHorizontalHeaderLabels(Constants::supplyPropertyTableHeaders);

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

void SupplyEditor::on_deleteProperty_clicked() {
	QItemSelectionModel* selection = ui->propertiesView->selectionModel();
	if(selection->hasSelection()){
		QAbstractItemModel* model = ui->propertiesView->model();

		model->removeRow(selection->selectedRows()[0].row());

		ui->propertiesView->resizeColumnsToContents();
		ui->propertiesView->resizeRowsToContents();
	}
}
