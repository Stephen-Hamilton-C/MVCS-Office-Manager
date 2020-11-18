#include "itemeditor.h"
#include "ui_itemeditor.h"
#include "datamanager.h"
#include "mainwindow.h"

#include <QStandardItemModel>

ItemEditor::ItemEditor(QString id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ItemEditor)
{
	ui->setupUi(this);

	qDebug() << "ID received:" << id;

	if(!id.isEmpty()){
		this->id = id;
		SupplyItem *item = &DataManager::items[id];

		qDebug() << "Contains:" << DataManager::items.contains(id);

		qDebug() << "Item:" << item->toString();

		ui->nameEdit->setProperty("item_uuid", id);
		ui->nameEdit->setText(item->getName());
		ui->countBox->setValue(item->getCount());
		ui->lowCountBox->setValue(item->getLowCount());

		QStandardItemModel* model = new QStandardItemModel();
		QMapIterator<QString, QVariant> i(item->properties);
		while(i.hasNext()){
			i.next();
			model->appendRow(QList<QStandardItem*>() <<
							 new QStandardItem(i.key()) <<
							 new QStandardItem(i.value().toString()));
		}

		model->setHorizontalHeaderLabels(propertyTableHeaders);
		ui->propertiesView->setModel(model);
		ui->propertiesView->verticalHeader()->setVisible(false);
		ui->propertiesView->setWordWrap(true);
		ui->propertiesView->setTextElideMode(Qt::ElideMiddle);
		ui->propertiesView->resizeColumnsToContents();
		ui->propertiesView->resizeRowsToContents();
	} else {
		ui->nameEdit->setProperty("item_uuid", QUuid::createUuid().toString());
	}
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
		MainWindow::getInstance()->showStatusMessage("Please fill required fields");
		ui->nameEdit->setStyleSheet("color: rgb(200, 0, 0);");
		return;
	}

	QVariantMap properties;
	constructPropertiesMap(properties);
	if(id.isEmpty()){
		SupplyItem item(ui->nameEdit->property("item_uuid").toString(),
						ui->nameEdit->text(),
						ui->countBox->value(),
						ui->lowCountBox->value(),
						properties);
		DataManager::items.insert(item.uuid, item);

		MainWindow::getInstance()->showStatusMessage("Created "+item.name+".");
	} else {
		SupplyItem* item = &DataManager::items[ui->nameEdit->property("item_uuid").toString()];
		item->name = ui->nameEdit->text();
		item->count = ui->countBox->value();
		item->lowCountThreshold = ui->lowCountBox->value();
		item->properties = properties;

		MainWindow::getInstance()->showStatusMessage("Edited "+item->name+".");
	}

	MainWindow::getInstance()->updateEditorView(MainWindow::EDITORTYPE::SUPPLY);
	MainWindow::getInstance()->deleteItemEditor();
}

void ItemEditor::on_createProperty_clicked() {
	QAbstractItemModel* model = ui->propertiesView->model();

	if(id.isEmpty()){
		QStandardItemModel* smodel = new QStandardItemModel();
		smodel->appendRow(QList<QStandardItem*>() <<
						 new QStandardItem("New Property") <<
						 new QStandardItem("Value"));

		smodel->setHorizontalHeaderLabels(propertyTableHeaders);
		ui->propertiesView->setModel(smodel);
		ui->propertiesView->verticalHeader()->setVisible(false);
		ui->propertiesView->setWordWrap(true);
		ui->propertiesView->setTextElideMode(Qt::ElideMiddle);
		ui->propertiesView->resizeColumnsToContents();
		ui->propertiesView->resizeRowsToContents();
	} else {

	}

	/*
	QAbstractItemModel* model = ui->propertiesView->model();
	QStandardItemModel* smodel = new QStandardItemModel();

	for(int row = 0; row < model->rowCount(); row++){
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
	*/
}

void ItemEditor::on_deleteProperty_clicked() {

}
