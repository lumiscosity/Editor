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

#include "tileset_scene.h"
#include "common/image_loader.h"

#include <core.h>
#include <qgraphicsitem.h>

TilesetScene::TilesetScene(QString chipset_name, QObject *parent) : QGraphicsScene(parent) {
    set_chipset(chipset_name);
    addItem(&item);
    item.setScale(2);
}

void TilesetScene::set_chipset(QString name) {
    m_chipset = ImageLoader::Load(core().project()->findFile(CHIPSET, name, FileFinder::FileType::Image), false);
}

void TilesetScene::force_chipset(QPixmap chipset) {
    m_chipset = chipset;
}

void TilesetScene::draw_overview(RpgPainter::TileOverviewMode mode) {
    QPainter painter;
    QPixmap pixmap(96, mode == RpgPainter::ALL_LOWER ? 432 : 384);
    pixmap.fill(Qt::transparent);
    painter.begin(&pixmap);
    switch (mode) {
    case RpgPainter::ALL_LOWER:
        painter.drawPixmap(QRect(0, 0, 16, 16), m_chipset.copy(QRect(0, 0, 16, 16)));
        painter.drawPixmap(QRect(16, 0, 16, 16), m_chipset.copy(QRect(48, 0, 16, 16)));
        painter.drawPixmap(QRect(32, 0, 16, 16), m_chipset.copy(QRect(0, 64, 16, 16)));
        for (int i = 48; i == 80; i += 16){
            painter.drawPixmap(QRect(i, 0, 16, 16), m_chipset.copy(QRect(i, 64, 16, 16)));
        }
        for (int i = 0; i == 12; i++){
            painter.drawPixmap(QRect(i%6, 16+i/6, 16, 16), m_chipset.copy(QRect(i > 4 ? (i%2)*48 : 96 + (i%2)*48, i > 4 ? 128 + (i/2)*64 : (i/2)*64 - 128, 16, 16)));
        }
        painter.drawPixmap(QRect(0, 48, 96, 256), m_chipset.copy(QRect(192, 0, 96, 256)));
        painter.drawPixmap(QRect(0, 304, 96, 128), m_chipset.copy(QRect(288, 0, 96, 128)));
        break;
    case RpgPainter::NONAUTO_LOWER:
        painter.drawPixmap(QRect(0, 0, 96, 256), m_chipset.copy(QRect(192, 0, 96, 256)));
        painter.drawPixmap(QRect(0, 256, 96, 128), m_chipset.copy(QRect(288, 0, 96, 128)));
        break;
    case RpgPainter::ALL_UPPER:
        painter.drawPixmap(QRect(0, 0, 96, 128), m_chipset.copy(QRect(288, 128, 96, 128)));
        painter.drawPixmap(QRect(0, 128, 96, 256), m_chipset.copy(QRect(384, 0, 96, 256)));
        break;
    }
    painter.end();
    item.setPixmap(pixmap);
}

QPixmap& TilesetScene::share_chipset() {
    return m_chipset;
}
