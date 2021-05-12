/*
 * This file is a part of {{ dc045.manager }}.
 *
 * Developed for MVCS Office Manager.
 * See the LICENSE file at the top-level directory of this distribution for license details.
 * Licensed under the GNU General Public License V3
 * C/2Lt Stephen Hamilton, Civil Air Patrol
*/
#ifndef INSPECTIONEDITOR_H
#define INSPECTIONEDITOR_H

#include "inspectioncard.h"

#include <QDialog>

namespace Ui {
	class InspectionEditor;
}

/**
 * @brief Contains UI logic for the inspection editor
 */
class InspectionEditor : public QDialog
{
	Q_OBJECT

public:
	/**
	 * @brief Creates a new InspectionEditor window
	 * @param The UUID of an inspection log entry to edit. Leave blank if creating a new log entry.
	 */
	explicit InspectionEditor(QString id = "", QWidget *parent = nullptr);
	~InspectionEditor();

private slots:
	/**
	 * @brief Triggered when Return or OK is pressed
	 */
	void on_buttonBox_accepted();

	/**
	 * @brief Triggered when the cadetBox selection changes
	 */
	void on_cadetBox_currentTextChanged(const QString &arg1);

private:
	Ui::InspectionEditor *ui;

	/**
	 * @brief The UUID of an inspection log entry stored in `DataManager` to edit, or blank if creating a new log entry.
	 */
	QString id;
	/**
	 * @brief Maps text from the cadetBox to a cadet UUID
	 */
	QMap<QString, QString> cadetMap;

	/**
	 * @brief Sets a radio button to be checked
	 * @param radioName The name of the radio button to check
	 * @param score The score the cadet got on this section. Must be 0, 1, or 2
	 */
	void setRadioCheck(QString radioName, int score);
	/**
	 * @brief Gets the score from a radio button set
	 * @param radioName The name of the button set to check.
	 * @return
	 */
	InspectionCard::RATING getScoreFromRadio(QString radioName);
	/**
	 * @brief Checks if at least one radio button in a set has been checked.
	 * @param radioName The name of the button set to confirm if one has been checked.
	 */
	bool radioHasScore(QString radioName);
};

#endif // INSPECTIONEDITOR_H
