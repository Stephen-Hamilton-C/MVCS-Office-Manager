#ifndef INSPECTIONEDITOR_H
#define INSPECTIONEDITOR_H

#include "constants.h"
#include "datamanager.h"

#include <QDialog>

namespace Ui {
	class InspectionEditor;
}

class InspectionEditor : public QDialog
{
	Q_OBJECT

public:
	explicit InspectionEditor(QString id = "", QWidget *parent = nullptr);
	~InspectionEditor();

private slots:
	void on_buttonBox_accepted();

private:
	Ui::InspectionEditor *ui;

	QString id;
	QMap<QString, QString> cadetMap;

	void setRadioCheck(QString radioName, int score);
	InspectionCard::RATING getScoreFromRadio(QString radioName);
};

#endif // INSPECTIONEDITOR_H
