/*
 * This file is part of EasyRPG Editor.
 *
 * EasyRPG Editor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EasyRPG Editor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EasyRPG Editor. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QWidget>
#include <lcf/rpg/actor.h>
#include "picker_child_widget.h"

namespace Ui {
class PickerCharsetWidget;
}

class QGraphicsScene;
class QGraphicsRectItem;
class QGraphicsPixmapItem;

class PickerCharsetWidget : public PickerChildWidget {
	Q_OBJECT

public:
    explicit PickerCharsetWidget(const int index, const int pattern, const int direction, const bool showUpper, const bool showControls, QWidget* parent = nullptr);
    ~PickerCharsetWidget();

	void clicked(const QPointF& pos) override;
    void redrawImage(QPixmap image, QString filename);
    void imageChanged(QPixmap image, QString filename) override;

	int index() const {
		return m_index;
	}
    int pattern() const {
        return m_pattern;
    }
    int direction() const {
        return m_direction;
    }

private slots:
    void on_directionUpButton_clicked();
    void on_directionRightButton_clicked();
    void on_directionLeftButton_clicked();
    void on_directionDownButton_clicked();
    void on_patternLeftButton_clicked();
    void on_patternMiddleButton_clicked();
    void on_patternRightButton_clicked();

private:
    Ui::PickerCharsetWidget *ui;

	void updateRect();

    QPixmap m_image;
    QString m_filename;
    int cell_width = 24;
    int cell_height = 32;

    int m_index;
    int m_pattern;
    int m_direction;
    bool m_showUpper;
    bool m_showControls;
	QGraphicsRectItem* m_rect = nullptr;
	QGraphicsPixmapItem* m_pixmap = nullptr;

};
