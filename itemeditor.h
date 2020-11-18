#ifndef ITEMEDITOR_H
#define ITEMEDITOR_H

#include <QDialog>
#include <supplyitem.h>

namespace Ui {
	class ItemEditor;
}

class ItemEditor : public QDialog
{
	Q_OBJECT

public:
	explicit ItemEditor(QString id = "", QWidget *parent = nullptr);
	~ItemEditor();

private slots:
	void on_buttonBox_accepted();

	void on_createProperty_clicked();

	void on_deleteProperty_clicked();

private:
	Ui::ItemEditor *ui;

	const QStringList propertyTableHeaders { "Name", "Value" };

	void constructPropertiesMap(QVariantMap &properties) const;

	QString id;
};

#endif // ITEMEDITOR_H
