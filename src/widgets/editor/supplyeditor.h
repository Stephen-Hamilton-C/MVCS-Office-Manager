/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef SUPPLYEDITOR_H
#define SUPPLYEDITOR_H

#include <QDialog>

class MainWindow;

namespace Ui {
	class ItemEditor;
}

/**
 * @brief Contains UI logic for the supply item editor
 */
class SupplyEditor : public QDialog
{
	Q_OBJECT

public:
	explicit SupplyEditor(MainWindow *mainWindow, QWidget *parent = nullptr, QString id = "");
	~SupplyEditor();

private slots:
	void on_buttonBox_accepted();

	void on_createProperty_clicked();

	void on_deleteProperty_clicked();

private:
	Ui::ItemEditor *ui;

	/**
	 * @brief Creates a QVariantMap from the properties UI
	 * @param properties The variable to store the map into
	 */
	void constructPropertiesMap(QVariantMap &properties) const;

	/**
	 * @brief The UUID of the ItemEditor
	 */
	QString id;

	MainWindow *mainWindow;
};

#endif // SUPPLYEDITOR_H
