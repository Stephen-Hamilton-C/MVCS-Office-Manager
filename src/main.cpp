/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "mainwindow.h"
#include "constants.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setApplicationName(Constants::name);
	QCoreApplication::setApplicationVersion(Constants::version);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
