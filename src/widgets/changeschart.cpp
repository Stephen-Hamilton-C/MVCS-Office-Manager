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
}

ChangesChart::~ChangesChart()
{
	delete ui;
}

void ChangesChart::refreshChart(QList<ItemSnapshot*> snapshots)
{
	QMap<QString, QLineSeries*> seriesMap;
	for(int i = 0; i < snapshots.length(); i++){
		QMapIterator<QString, QVariant> j(snapshots[i]->properties);
		while(j.hasNext()){
			j.next();
			QLineSeries* series = seriesMap[j.key()];
			if(series == nullptr){
				series = new QLineSeries();
				seriesMap.insert(j.key(), series);
				series->setName(j.key());
			}

			QDateTime moment;
			moment.setDate(snapshots[i]->date);

			series->append(moment.toMSecsSinceEpoch(), j.value().toInt());
		}
	}

	QChart* chart = new QChart();
	chart->setTitle("Changes");

	QMapIterator<QString, QLineSeries*> i(seriesMap);
	while(i.hasNext()){
		i.next();
		chart->addSeries(i.value());
	}

	QDateTimeAxis *axisX = new QDateTimeAxis;
	axisX->setTickCount(10);
	axisX->setFormat("MM/dd/yy");
	axisX->setTitleText("Date");
	chart->addAxis(axisX, Qt::AlignBottom);
	QMapIterator<QString, QLineSeries*> x(seriesMap);

	QValueAxis *axisY = new QValueAxis;
	axisY->setLabelFormat("%i");
	axisY->setTitleText("Value");
	chart->addAxis(axisY, Qt::AlignLeft);
	QMapIterator<QString, QLineSeries*> y(seriesMap);
	while(y.hasNext()){
		y.next();
		y.value()->attachAxis(axisX);
		y.value()->attachAxis(axisY);
	}

	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	ui->chartFrame->layout()->addWidget(chartView);
	chartView->show();

}
