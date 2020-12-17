/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/

//Source: https://stackoverflow.com/questions/9183050/vertical-qlabel-or-the-equivalent

#ifndef VERTICALLABEL_H
#define VERTICALLABEL_H

#include <QLabel>
#include <QPainter>

/**
 * @ref https://stackoverflow.com/questions/9183050/vertical-qlabel-or-the-equivalent
 */
class VerticalLabel : public QLabel
{
	Q_OBJECT

public:
	explicit VerticalLabel(QWidget *parent=0);
	explicit VerticalLabel(const QString &text, QWidget *parent=0);

protected:
	void paintEvent(QPaintEvent*);
	QSize sizeHint() const ;
	QSize minimumSizeHint() const;
};

#endif // VERTICALLABEL_H
