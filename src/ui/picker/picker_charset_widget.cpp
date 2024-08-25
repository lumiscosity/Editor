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

#include "picker_charset_widget.h"
#include "ui_picker_charset_widget.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <ui/map/map_scene.h>

PickerCharsetWidget::PickerCharsetWidget(int index, int pattern, int direction, MapScene *map, QWidget *parent) :
    PickerChildWidget(parent),
    m_index(index),
    m_pattern(pattern),
    m_direction(direction),
    m_map(map),
    ui(new Ui::PickerCharsetWidget) {
    if (map) {
        ui->setupUi(this);

        m_painter.forceChipset(map->sharePainterTiles());

        switch (m_pattern) {
        case 0:
            ui->patternLeftButton->setChecked(true);
            break;
        case 2:
            ui->patternRightButton->setChecked(true);
            break;
        default:
            ui->patternMiddleButton->setChecked(true);
            break;
        }

        switch (m_direction) {
        case 0:
            ui->directionUpButton->setChecked(true);
            break;
        case 1:
            ui->directionRightButton->setChecked(true);
            break;
        case 3:
            ui->directionLeftButton->setChecked(true);
            break;
        default:
            ui->directionDownButton->setChecked(true);
            break;
        }
    }
}

PickerCharsetWidget::~PickerCharsetWidget() {
    delete ui;
}

void PickerCharsetWidget::clicked(const QPointF& pos) {
    int x = static_cast<int>(pos.x() / cell_width);
    int y = static_cast<int>(pos.y() / cell_height);
    m_index = (m_filename.isEmpty()) ? std::clamp(y * 6 + x, 0, 143) : std::clamp(y * 4 + x, 0, 7);
	updateRect();
}

void PickerCharsetWidget::imageChanged(QPixmap image, QString filename) {
    m_image = image;
    m_filename = filename;
    redrawImage(image, filename);
}

void PickerCharsetWidget::redrawImage(QPixmap image, QString filename) {
    if (!m_pixmap) {
        m_view->setMinimumSize(196, 132);
        m_view->scale(2.0, 2.0);
        m_pixmap = new QGraphicsPixmapItem();
    }

    if (filename.isEmpty() && m_map) {
        cell_width = cell_height = 16;
        this->hide();
        m_painter.beginPainting(image);
        m_painter.renderTileOverview(RpgPainter::ALL_UPPER);
        m_painter.endPainting();
        m_pixmap->setPixmap(image);
        m_view->setItem(m_pixmap);
        updateRect();
    } else {
        if (m_map){
            this->show();
        }
        if (filename.startsWith("$")) {
            cell_width = image.width() / 12;
            cell_height = image.height() / 8;
        } else {
            cell_width = 24;
            cell_height = 32;
        }

        QPixmap new_image = (filename.isEmpty() && m_map) ? QPixmap(96, 384) : QPixmap(cell_width * 4, cell_height * 2);
        new_image.fill(QColor(0,0,0,0));

        m_painter.beginPainting(new_image);
        for (int i = 0; i < 8; ++i) {
            int src_x = ((i % 4) * cell_width * 3 + (m_pattern * cell_width));
            int src_y = (i >= 4) ? (m_direction + 4) * cell_height : m_direction * cell_height;
            int target_x = (i % 4) * cell_width;
            int target_y = i >= 4 ? cell_height : 0;
            m_painter.drawPixmap(QRect(target_x, target_y, cell_width, cell_height), image, QRect(src_x, src_y, cell_width, cell_height));
        }

        m_painter.endPainting();
        m_pixmap->setPixmap(new_image);
        m_view->setItem(m_pixmap);
        updateRect();
    }
}

void PickerCharsetWidget::updateRect() {
	if (!m_rect) {
		m_rect = new QGraphicsRectItem();

		QPen selPen(Qt::white);
		selPen.setWidth(2);
		m_rect->setPen(selPen);

		m_view->scene()->addItem(m_rect);
	}

    if (m_filename.isEmpty()) {
        m_rect->setRect(QRect(
            (m_index % 6) * cell_width,
            m_index / 6 * cell_height,
            cell_width,
            cell_height));
    } else {
        m_rect->setRect(QRect(
            (m_index % 4) * cell_width,
            m_index / 4 * cell_height,
            cell_width,
            cell_height));
    }
}

void PickerCharsetWidget::on_directionUpButton_clicked()
{
    m_direction = 0;
    redrawImage(m_image, m_filename);
}


void PickerCharsetWidget::on_directionRightButton_clicked()
{
    m_direction = 1;
    redrawImage(m_image, m_filename);
}


void PickerCharsetWidget::on_directionLeftButton_clicked()
{
    m_direction = 3;
    redrawImage(m_image, m_filename);
}


void PickerCharsetWidget::on_directionDownButton_clicked()
{
    m_direction = 2;
    redrawImage(m_image, m_filename);
}


void PickerCharsetWidget::on_patternLeftButton_clicked()
{
    m_pattern = 0;
    redrawImage(m_image, m_filename);
}


void PickerCharsetWidget::on_patternMiddleButton_clicked()
{
    m_pattern = 1;
    redrawImage(m_image, m_filename);
}


void PickerCharsetWidget::on_patternRightButton_clicked()
{
    m_pattern = 2;
    redrawImage(m_image, m_filename);
}

