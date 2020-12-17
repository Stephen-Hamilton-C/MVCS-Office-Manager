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

#include <QMainWindow>

namespace Ui {
class CadetEditor;
}

class CadetEditor : public QMainWindow
{
    Q_OBJECT

public:
	explicit CadetEditor(QString id = "", QWidget *parent = nullptr);
    ~CadetEditor();

private slots:

    void on_gradeBox_currentIndexChanged(int index);

	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

private:
    Ui::CadetEditor *ui;

	QString id = "";
};

#endif // CADETEDITOR_H
