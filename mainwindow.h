#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include "cadeteditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionCadets_triggered();

    void on_actionSupply_triggered();

    void on_actionInspections_triggered();

    void on_actionFlights_Staff_triggered();

    void on_action_About_triggered();

    void on_actionAbout_Qt_triggered();

    void on_editCadet_clicked();

    void on_action_Save_triggered();

    void on_newCadet_clicked();

	void on_deleteCadet_clicked();

private:

    void changeView(int stackIndex, QString subTitle);

	void getSelectedID(QItemSelectionModel *selection, int &id) const;

	CadetEditor *editor;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
