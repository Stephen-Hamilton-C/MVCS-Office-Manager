#include "inspectioneditor.h"
#include "ui_inspectioneditor.h"

InspectionEditor::InspectionEditor(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::InspectionEditor)
{
	ui->setupUi(this);
}

InspectionEditor::~InspectionEditor()
{
	delete ui;
}
