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
}

void TilesetScene::set_chipset(QString name) {
    chipset = ImageLoader::Load(core().project()->findFile(CHIPSET, name, FileFinder::FileType::Image), false);
    item.setPixmap(chipset);
}

void TilesetScene::force_chipset(QPixmap chipset) {
    item.setPixmap(chipset);
}

QPixmap& TilesetScene::share_chipset() {
    return chipset;
}
