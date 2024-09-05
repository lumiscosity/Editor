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

#include <QPainter>
#include <core.h>

#include <vendor/hash_map.hpp>

class RpgPainter : public QPainter {

public:
    RpgPainter(QString chipset = QString());

    enum TileOverviewMode
    {
        ALL_LOWER,
        NONAUTO_LOWER,
        ALL_UPPER
    };

    void setChipset(QString chipset);

    void beginPainting(QPixmap &dest);
    void renderPanorama(const QRect &dest_rect);
    void renderTile(const short &tile_id, const QRect &dest_rect);
    void renderTileOverview(const TileOverviewMode mode);
    void renderEvent(const lcf::rpg::Event& event, const QRect &dest_rect);
    void endPainting();

    inline bool chipsetIsNull() {return m_chipset->contains(0);}

    inline std::shared_ptr<emilib::HashMap<short, QPixmap>> &sharePainterTiles() { return m_chipset; };
    void forceChipset(std::shared_ptr<emilib::HashMap<short, QPixmap>> chipset);

private:
    std::shared_ptr<emilib::HashMap<short, QPixmap>> m_chipset = std::make_shared<emilib::HashMap<short, QPixmap>>(emilib::HashMap<short, QPixmap>());
    emilib::HashMap<QString, QPixmap> *m_eventCache = nullptr;
    void loadChipset(QString chipset_name);

};
