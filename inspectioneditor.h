#ifndef INSPECTIONEDITOR_H
#define INSPECTIONEDITOR_H

#include <QDialog>

namespace Ui {
	class InspectionEditor;
}

class InspectionEditor : public QDialog
{
	Q_OBJECT

public:
	explicit InspectionEditor(QWidget *parent = nullptr);
	~InspectionEditor();

private:
	Ui::InspectionEditor *ui;
};

#endif // INSPECTIONEDITOR_H
