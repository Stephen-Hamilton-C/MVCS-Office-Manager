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
#include <QTableView>
#include "cadeteditor.h"
#include "itemeditor.h"
#include "inspectioneditor.h"

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

	enum EDITORTYPE {
		CADET,
		SUPPLY,
		INSPECTIONLOGS
	};

	void showStatusMessage(QString message, int timeout = 0);
	void updateEditorView(EDITORTYPE editorType);
	void updateEditorView();

	void deleteItemEditor();
	void deleteCadetEditor();
	void deleteCardEditor();

	static MainWindow* getInstance(){
		return ptrInstance;
	}

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

private:

	Ui::MainWindow *ui;

	static MainWindow *ptrInstance;

	void changeView(int stackIndex, QString subTitle);

	void getSelectedID(QItemSelectionModel *selection, QString &id) const;

	CadetEditor* cadetEditorWindow = nullptr;
	ItemEditor* itemEditorWindow = nullptr;
	InspectionEditor*  cardEditorWindow = nullptr;

	EDITORTYPE currentEditorType;
};
#endif // MAINWINDOW_H
