/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef CHANGESCHART_H
#define CHANGESCHART_H

#include <QWidget>
#include <QtCharts>

class ItemSnapshot;

namespace Ui {
	class ChangesChart;
}

class ChangesChart : public QWidget
{
		Q_OBJECT

	public:
		explicit ChangesChart(QWidget *parent = nullptr);
		~ChangesChart();

		void refreshChart(QList<ItemSnapshot*> snapshots);

	private:
		Ui::ChangesChart *ui;
};

#endif // CHANGESCHART_H
