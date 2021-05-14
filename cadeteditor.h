/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef CADETEDITOR_H
#define CADETEDITOR_H

#include <QDialog>

class MainWindow;

namespace Ui {
class CadetEditor;
}

/**
 * @brief Contains UI logic for creating and editing CAP Cadets or Senior Members
 */
class CadetEditor : public QDialog
{
    Q_OBJECT

public:
	/**
	 * @brief Creates a new CadetEditor window
	 * @param The UUID of a Cadet to edit. Leave blank if creating a new Cadet.
	 */
	explicit CadetEditor(QString id = "", QWidget *parent = nullptr);
    ~CadetEditor();

private slots:

	/**
	 * @brief Triggered when the member grade is changed
	 * @param The new index of the gradeBox
	 */
    void on_gradeBox_currentIndexChanged(int index);

	/**
	 * @brief Triggered when Return or OK is pressed
	 */
	void on_buttonBox_accepted();

	/**
	 * @brief Triggered when ESC or Cancel is pressed
	 */
	void on_buttonBox_rejected();

private:
    Ui::CadetEditor *ui;

	/**
	 * @brief The UUID of a Cadet stored in `DataManager` to edit, or blank if creating a new Cadet.
	 */
	QString id = "";

    /**
     * @brief The MainWindow instance
     */
    MainWindow* mainWindow;
};

#endif // CADETEDITOR_H
