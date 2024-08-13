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

#include "palette_scene.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>

PaletteScene::PaletteScene(QObject *parent) :
	QGraphicsScene(parent),
	m_cancel(false),
	m_pressed(false)
{
    this->setSceneRect(QRect(0,0,96,448));
    m_selectionItem = new QGraphicsRectItem(QRectF(QRect(0,0,16,16)));
    last_selection = QRectF(QRect(0,0,16,16));
	this->addItem(m_selectionItem);
	m_tiles = new QGraphicsPixmapItem();
	this->addItem(m_tiles);
	m_tiles->setVisible(false);
	QPen selPen(Qt::yellow);
    selPen.setWidth(2);
	m_selectionItem->setPen(selPen);
	m_selectionItem->setVisible(false);
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setOffset(2);
	m_tiles->setGraphicsEffect(effect);
	m_tiles->stackBefore(m_selectionItem);
	setBackgroundBrush(QBrush(QPixmap(":/embedded/share/old_grid.png")));
}

void PaletteScene::onLayerChange()
{
	if (core().layer() == Core::LOWER)
	{
		m_tiles->setPixmap(m_lowerTiles);
        this->setSceneRect(QRect(0,0,96,448));
	}
	else
	{
		m_tiles->setPixmap(m_upperTiles);
        this->setSceneRect(QRect(0,0,96,400));
	}
	m_tiles->graphicsEffect()->setEnabled(core().layer() != Core::LOWER);
}

void PaletteScene::onChipsetChange()
{
    if (false)
	{
		m_tiles->setVisible(false);
		m_selectionItem->setVisible(false);
		return;
	}
	m_tiles->setVisible(true);
	m_selectionItem->setVisible(true);
    m_lowerTiles = QPixmap(96, 448);
    m_upperTiles = QPixmap(96, 400);
    m_lowerTiles.fill(Qt::transparent);
    m_upperTiles.fill(Qt::transparent);
    m_painter.beginPainting(m_lowerTiles);
    m_painter.renderTileOverview(RpgPainter::ALL_LOWER);
    m_painter.endPainting();
    m_painter.beginPainting(m_upperTiles);
    m_painter.renderTileOverview(RpgPainter::ALL_UPPER);
    m_painter.endPainting();
	onLayerChange();
}

void PaletteScene::updateSelectionRect()
{
	QRectF selRect;
    int small_x = (m_initial.x() <= m_current.x()) ? static_cast<int>(m_initial.x())/16 : static_cast<int>(m_current.x())/16;
    int big_x = (m_initial.x() >= m_current.x()) ? static_cast<int>(m_initial.x())/16 : static_cast<int>(m_current.x())/16;
    int small_y = (m_initial.y() <= m_current.y()) ? static_cast<int>(m_initial.y())/16 : static_cast<int>(m_current.y())/16;
    int big_y = (m_initial.y() >= m_current.y()) ? static_cast<int>(m_initial.y())/16 : static_cast<int>(m_current.y())/16;
	//keep inside the scene
	if (small_x < 0)
		small_x = 0;
	if (small_x > 5)
		small_x = 5;
	if (big_x > 5)
		big_x = 5;
	if (small_y < 0)
		small_y = 0;
	if (big_y > 27)
		big_y = 27;
	if (big_y - small_y > 5)
	{
        if (static_cast<int>(m_initial.y())/16 == small_y)
			big_y = small_y + 5;
		else
			small_y = big_y - 5;
    }
    selRect = QRectF(QRect(small_x*16,small_y*16,(big_x-small_x+1)*16,(big_y-small_y+1)*16));

	m_selectionItem->setRect(selRect);
}

void PaletteScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		cancelSelection();
		return;
	}
	else if (event->button() != Qt::LeftButton)
		return;
	m_initial = event->scenePos();
	m_current = event->scenePos();
	updateSelectionRect();
	QGraphicsScene::mousePressEvent(event);
}

void PaletteScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (m_cancel)
        return;
	else
		m_current = event->scenePos();

	updateSelectionRect();
	QGraphicsScene::mouseMoveEvent(event);
}

void PaletteScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && m_cancel)
	{
		m_cancel = false;
		return;
	}
	if (event->button() != Qt::LeftButton)
		return;

	//TODO: set selection
	std::vector<short> sel;
    int x = static_cast<int>(m_selectionItem->rect().left())/16;
    int y = static_cast<int>(m_selectionItem->rect().top())/16;
    int w = static_cast<int>(m_selectionItem->rect().width())/16;
    int h = static_cast<int>(m_selectionItem->rect().height())/16;
    for (int _y = y; _y < y+h; _y++)
        for (int _x = x; _x < x+w; _x++)
            if (core().layer() == Core::LOWER)
                sel.push_back(core().translate(_x+_y*6, SAMPLE));
            else
                sel.push_back(core().translate(_x+_y*6+162, SAMPLE));
    core().setSelection(sel, w, h);
    last_selection = m_selectionItem->boundingRect();
	QGraphicsScene::mouseReleaseEvent(event);
}

void PaletteScene::cancelSelection()
{
	m_cancel = true;
	m_selectionItem->setRect(last_selection);
}


