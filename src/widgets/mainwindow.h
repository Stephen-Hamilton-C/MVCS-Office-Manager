/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QItemSelectionModel;

class CadetEditor;
class SupplyEditor;
class InspectionEditor;
class ChangesChart;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Contains UI logic for the main window
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void closeEvent(QCloseEvent *event);

	enum EDITORTYPE {
		CADET,
		SUPPLY,
		INSPECTIONLOGS
	};

	/**
	 * @brief Shows a message on the status bar
	 * @param message The message to display
	 * @param timeout The amount of time the message stays visible
	 */
	void showStatusMessage(QString message, int timeout = 0);
	/**
	 * @brief Refreshes the editor with a new data type
	 * @param editorType The information the editor is going to display
	 */
	void updateEditorView(EDITORTYPE editorType);
	/**
	 * @brief Refreshes the editor with the current data type
	 */
	void updateEditorView();

	/**
	 * @brief Closes the supply item editor, if present
	 */
	void deleteItemEditor();
	/**
	 * @brief Closes the cadet editor, if present
	 */
	void deleteCadetEditor();
	/**
	 * @brief Closes the inspection card editor, if present
	 */
	void deleteCardEditor();

	void setDirty(const bool dirty);

private slots:

	void on_actionCadets_triggered();

	void on_actionSupply_triggered();

	void on_actionInspections_triggered();

	void on_actionFlights_Staff_triggered();

	void on_action_About_triggered();

	void on_actionAbout_Qt_triggered();

	void on_editorEdit_clicked();

	void on_action_Save_triggered();

	void on_editorNew_clicked();

	void on_editorDelete_clicked();

	void on_editorView_doubleClicked(const QModelIndex &index);

	void on_action_Load_triggered();

	void on_actionNew_triggered();

	void on_actionScores_triggered();

	void on_actionCharts_triggered();

	public slots:

	void on_actionSave_as_triggered();

private:

	Ui::MainWindow *ui;

	/**
	 * @brief Changes the index of the stacked widget
	 * @param stackIndex The index to switch to
	 * @param subTitle What to put in the window title when this view is shown
	 */
	void changeView(int stackIndex);

	/**
	 * @brief Gets the UUID of the currently selected row from the editor
	 * @param selection The currently selected row
	 * @param id The variable to store the UUID
	 */
	void getSelectedID(QItemSelectionModel *selection, QString &id) const;

	CadetEditor* cadetEditorWindow = nullptr;
	SupplyEditor* supplyEditorWindow = nullptr;
	InspectionEditor*  cardEditorWindow = nullptr;
	ChangesChart* changesChart = nullptr;

	EDITORTYPE currentEditorType;

	bool dataDirty = false;
};
#endif // MAINWINDOW_H
