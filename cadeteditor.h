#ifndef CADETEDITOR_H
#define CADETEDITOR_H

#include <QMainWindow>
#include "cadet.h"

namespace Ui {
class CadetEditor;
}

class CadetEditor : public QMainWindow
{
    Q_OBJECT

public:
	explicit CadetEditor(int id = 0, QWidget *parent = nullptr);
    ~CadetEditor();

private slots:

    void on_gradeBox_currentIndexChanged(int index);

	void on_buttonBox_accepted();

	void on_buttonBox_rejected();

private:
    Ui::CadetEditor *ui;

	int id = 0;

	void createCadet();
};

#endif // CADETEDITOR_H