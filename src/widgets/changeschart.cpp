/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#include "changeschart.h"
#include "ui_changeschart.h"
#include "itemsnapshot.h"
#include "changesmanager.h"

using namespace QtCharts;

ChangesChart::ChangesChart(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ChangesChart)
{
	ui->setupUi(this);

	_chart = new QChart();
	_chart->createDefaultAxes();
	_chart->
	_chart->setTitle("Simple line chart example");

	QChartView *chartView = new QChartView(_chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	ui->verticalLayout->addWidget(chartView);
	chartView->show();
}

ChangesChart::~ChangesChart()
{
	delete ui;
}

void ChangesChart::refreshChart(QList<ItemSnapshot*> snapshots)
{
	_chart->removeAllSeries();

	QMap<QString, QLineSeries*> seriesMap;
	for(int i = 0; i < snapshots.length(); i++){
		QMapIterator<QString, QVariant> j(snapshots[i]->properties);
		while(j.hasNext()){
			j.next();
			if(!seriesMap.contains(j.key())){
				seriesMap.insert(j.key(), new QLineSeries());
				seriesMap[j.key()]->setName(j.key());
			}

			QLineSeries* series = seriesMap[j.key()];
			series->append(QDateTime(snapshots[i]->date).toTime_t(), j.value().toInt());
		}
	}

	QMapIterator<QString, QLineSeries*> i(seriesMap);
	while(i.hasNext()){
		i.next();
		_chart->addSeries(i.value());
	}
}
