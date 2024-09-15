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

#include "rpg_painter.h"
#include "common/dbstring.h"
#include "common/image_loader.h"
#include "common/tileops.h"

RpgPainter::RpgPainter(QString chipset) {
    setChipset(chipset);
    m_eventCache = &core().getEventCache();
    setRenderHint(QPainter::Antialiasing, false);
    setRenderHint(QPainter::LosslessImageRendering, false);
}

enum TileOverviewMode
{
    ALL_LOWER,
    NONAUTO_LOWER,
    ALL_UPPER
};

void RpgPainter::forceChipset(std::shared_ptr<emhash8::HashMap<short, QPixmap>> chipset) {
    m_chipset = chipset;
}

void RpgPainter::setChipset(QString name) {
    if (name.isEmpty()) {
        return;
    }
    loadChipset(name);
}

void RpgPainter::beginPainting(QPixmap &dest) {
    this->begin(&dest);
    this->setPen(Qt::yellow);
}

void RpgPainter::renderTile(const short &tile_id, const QRect &dest_rect) {
    this->drawPixmap(dest_rect, m_chipset->get_or_return_default(tile_id));
}

void RpgPainter::renderTileOverview(const TileOverviewMode mode) {
    switch (mode) {
    case ALL_LOWER:
        for (int terrain_id = 0; terrain_id < 162; terrain_id++)
        {
            QRect rect(((terrain_id)%6)*16,(terrain_id/6)*16,16,16);
            renderTile(TileOps::translate(terrain_id,15), rect);
        }
        renderTile(TileOps::translate(2,0,240), QRect(32,16,16,16));
        break;
    case NONAUTO_LOWER:
        for (int terrain_id = 0; terrain_id < 144; terrain_id++)
        {
            QRect rect(((terrain_id)%6)*16,(terrain_id/6)*16,16,16);
            renderTile(TileOps::translate(terrain_id+18), rect);
        }
        break;
    case ALL_UPPER:
        for (int terrain_id = 0; terrain_id < 144; terrain_id++)
        {
            QRect rect(((terrain_id)%6)*16,(terrain_id/6)*16,16,16);
            renderTile(TileOps::translate(terrain_id+162), rect);
        }
        break;
    }
}

void RpgPainter::renderEvent(const lcf::rpg::Event& event, const QRect &dest_rect) {
    if (event.pages.empty())
        return;

    const int fact = dest_rect.width();
    QRect final_rect = dest_rect.adjusted(fact/6,fact/6,-fact/6,-fact/6);
    this->drawRect(final_rect.adjusted(-1,-1,0,0));
    if (event.pages[0].character_name.empty())
        renderTile(static_cast<short>(event.pages[0].character_index+10000), final_rect);
    else {

        QString check = ToQString(event.pages[0].character_name);
        int offset = (event.pages[0].character_index * 12 + event.pages[0].character_direction * 3 + event.pages[0].character_pattern);
        QString offset_string = QString::number(offset);
        offset_string = offset_string.leftJustified(3, u'N');
        check.append(offset_string);

        if (!m_eventCache->contains(check))
            core().cacheEvent(&event, check);
        this->drawPixmap(final_rect, m_eventCache->get_or_return_default(check), QRect(0,6,24,24));
    }
}

void RpgPainter::endPainting()
{
    this->end();
}

void RpgPainter::loadChipset(QString chipset_name) {
    QPixmap o_chipset = ImageLoader::Load(core().project()->findFile(CHIPSET, chipset_name, FileFinder::FileType::Image), true);
    if (!o_chipset)
        o_chipset = ImageLoader::Load(core().rtpPath(CHIPSET, chipset_name), true);
    if (!o_chipset)
    {
        qWarning()<<"Chipset"<<chipset_name<<"not found.";
        o_chipset = core().createDummyPixmap(480,256);
    }

    int r_tileSize = o_chipset.width()/30;
    int r_tileHalf = r_tileSize/2;
    int tilesize = core().tileSize();

    /* BindWaterTiles */

    /*
     * TileIDs:
     * 0- WaterA
     * 1- WaterB
     * 2- DeepWater
     * 3- Ground
     */
    //Go through all posible combinations
    for (int terrain_id = 0; terrain_id < 4; terrain_id++)
        for (int tile_u = 0; tile_u < 4; tile_u++)
            for (int tile_d = 0; tile_d < 4; tile_d++)
                for (int tile_l = 0; tile_l < 4; tile_l++)
                    for (int tile_r = 0; tile_r < 4; tile_r++)
                        for (int tile_ul = 0; tile_ul < 4; tile_ul++)
                            for (int tile_ur = 0; tile_ur < 4; tile_ur++)
                                for (int tile_dl = 0; tile_dl < 4; tile_dl++)
                                    for (int tile_dr = 0; tile_dr < 4; tile_dr++)
                                    {
                                        int _code, _scode;
                                        if (terrain_id == 3)
                                            // Once main foreach reaches ground, we have finished
                                            break;
                                        int u=0,d=0,l=0,r=0,ul=0,ur=0,dl=0,dr=0,sul=0,sur=0,sdl=0,sdr=0;

                                        if (!TileOps::isWater(tile_u))
                                            u = UP;
                                        if (!TileOps::isWater(tile_d))
                                            d = DOWN;
                                        if (!TileOps::isWater(tile_l))
                                            l = LEFT;
                                        if (!TileOps::isWater(tile_r))
                                            r = RIGHT;
                                        _code = u+d+l+r;
                                        // DeepWater Special Corners
                                        if (TileOps::isDWater(terrain_id))
                                        {
                                            if (TileOps::isABWater(tile_u) && TileOps::isABWater (tile_l) && TileOps::isWater (tile_ul))
                                                sul = UPLEFT;
                                            if (TileOps::isABWater(tile_u) && TileOps::isABWater (tile_r) && TileOps::isWater (tile_ur))
                                                sur = UPRIGHT;
                                            if (TileOps::isABWater(tile_d) && TileOps::isABWater (tile_l) && TileOps::isWater (tile_dl))
                                                sdl = DOWNRIGHT;
                                            if (TileOps::isABWater(tile_d) && TileOps::isABWater (tile_r) && TileOps::isWater (tile_dr))
                                                sdr = DOWNLEFT;
                                        }
                                        else
                                        {
                                            if (TileOps::isDWater (tile_u) && TileOps::isDWater (tile_l) && TileOps::isWater(tile_ul))
                                                sul = UPLEFT;
                                            if (TileOps::isDWater (tile_u) && TileOps::isDWater (tile_r) && TileOps::isWater(tile_ur))
                                                sur = UPRIGHT;
                                            if (TileOps::isDWater (tile_d) && TileOps::isDWater (tile_l) && TileOps::isWater(tile_dl))
                                                sdl = DOWNRIGHT;
                                            if (TileOps::isDWater (tile_d) && TileOps::isDWater (tile_r) && TileOps::isWater(tile_dr))
                                                sdr = DOWNLEFT;
                                        }
                                        _scode = sul+sur+sdl+sdr;
                                        if ((u+l) == 0 && tile_ul == 3)
                                            ul = UPLEFT;
                                        if ((u+r) == 0 && tile_ur == 3)
                                            ur = UPRIGHT;
                                        if ((d+l) == 0 && tile_dl == 3)
                                            dl = DOWNLEFT;
                                        if ((d+r) == 0 && tile_dr == 3)
                                            dr = DOWNRIGHT;
                                        _code += ul+ur+dl+dr;
                                        short id = TileOps::translate(terrain_id,_code,_scode);
                                        if (m_chipset->contains(id)) //item exist?
                                            continue;
                                        // Water B uses second block of 3x4 tiles for borders
                                        // Water A and Deep Water uses first block
                                        int border_xoffset = (terrain_id == 1) ? 3*r_tileSize : 0;
                                        /*
         * Get base
         */
                                        QPixmap p_tile(tilesize, tilesize);
                                        p_tile.fill(QColor(0,0,0,0));
                                        QPainter p(&p_tile);
                                        if (TileOps::isABWater (terrain_id))
                                            p.drawPixmap(0,0,tilesize,tilesize,o_chipset.copy(0, 4*r_tileSize,r_tileSize,r_tileSize));
                                        else
                                            p.drawPixmap(0,0,tilesize,tilesize,o_chipset.copy(0, 7*r_tileSize,r_tileSize,r_tileSize));
                                        // Draw UpperLeft corner
                                        int dest_x = 0, dest_y = 0;
#define blit(x,y) p.drawPixmap(dest_x,dest_y,tilesize/2,tilesize/2,o_chipset.copy(x, y,r_tileHalf,r_tileHalf))
                                        if (u+l == 5)
                                            blit(border_xoffset, 0);
                                        else if (u)
                                            blit(border_xoffset, 2*r_tileSize);
                                        else if (l)
                                            blit(border_xoffset, r_tileSize);
                                        else if (ul)
                                            blit(border_xoffset, 3*r_tileSize);
                                        else if (sul)
                                        {
                                            if (TileOps::isABWater (terrain_id))
                                                blit(0, 5*r_tileSize);
                                            else
                                                blit(0, 6*r_tileSize);
                                        }
                                        //Draw UpperRight corner
                                        dest_x = tilesize/2;
                                        if (u+r == 9)
                                            blit(border_xoffset+r_tileHalf, 0);
                                        else if (u)
                                            blit(border_xoffset+r_tileHalf, 2*r_tileSize);
                                        else if (r)
                                            blit(border_xoffset+r_tileHalf, r_tileSize);
                                        else if (ur)
                                            blit(border_xoffset+r_tileHalf, 3*r_tileSize);
                                        else if (sur)
                                        {
                                            if (TileOps::isABWater (terrain_id))
                                                blit(r_tileHalf, 5*r_tileSize);
                                            else
                                                blit(r_tileHalf, 6*r_tileSize);
                                        }
                                        //Draw LowerRight corner
                                        dest_y = tilesize/2;
                                        if (d+r == 10)
                                            blit(border_xoffset+r_tileHalf, r_tileSize/2);
                                        else if (d)
                                            blit(border_xoffset+r_tileHalf, r_tileSize*5/2);
                                        else if (r)
                                            blit(border_xoffset+r_tileHalf, r_tileSize*3/2);
                                        else if (dr)
                                            blit(border_xoffset+r_tileHalf, r_tileSize*7/2);
                                        else if (sdr)
                                        {
                                            if (TileOps::isABWater (terrain_id))
                                                blit(tilesize/2, r_tileSize*11/2);
                                            else
                                                blit(tilesize/2, r_tileSize*13/2);
                                        }
                                        //Draw LowerLeft corner
                                        dest_x = 0;
                                        if (d+l == 6)
                                            blit(border_xoffset, r_tileSize/2);
                                        else if (d)
                                            blit(border_xoffset, r_tileSize*5/2);
                                        else if (l)
                                            blit(border_xoffset, r_tileSize*3/2);
                                        else if (dl)
                                            blit(border_xoffset, r_tileSize*7/2);
                                        else if (sdl)
                                        {
                                            if (TileOps::isABWater (terrain_id))
                                                blit(0, r_tileSize*11/2);
                                            else
                                                blit(0, r_tileSize*13/2);
                                        }
#undef blit
                                        m_chipset->do_assign(id, p_tile);
                                    }

    /* Register AnimationTiles */
    QPixmap a_tile(tilesize, tilesize);
    a_tile.fill(QColor(0,0,0,0));
    QPainter a(&a_tile);
    a.drawPixmap(0,0,tilesize,tilesize,o_chipset.copy(3*r_tileSize,4*r_tileSize,r_tileSize,r_tileSize));
    for (int i = 0; i < 50; i++) {
       m_chipset->do_assign(TileOps::translate(3) + i, a_tile);
    }
    a.drawPixmap(0,0,tilesize,tilesize,o_chipset.copy(4*r_tileSize,4*r_tileSize,r_tileSize,r_tileSize));
    for (int i = 0; i < 50; i++) {
       m_chipset->do_assign(TileOps::translate(4) + i, a_tile);
    }
    a.drawPixmap(0,0,tilesize,tilesize,o_chipset.copy(5*r_tileSize,4*r_tileSize,r_tileSize,r_tileSize));
    for (int i = 0; i < 50; i++) {
       m_chipset->do_assign(TileOps::translate(5) + i, a_tile);
    }

    /* BindGroundTiles */
    // Each tileset contains 5 columns with a size of 6x16 tiles
    int tileset_col = 0;

    // Each tileset column contains 4 blocks with a size of 3x4 tiles
    // Anyway we should skip water colums because they are already stored
    int block_col = 0;
    int block_row = 2;

    int terrain_id = 6;

    while (tileset_col < 2)
    {
        int orig_x = (2 * tileset_col + block_col) *3*r_tileSize;
        int orig_y = block_row *4*r_tileSize;
        QPixmap p_block = o_chipset.copy(orig_x, orig_y, 3*r_tileSize, 4*r_tileSize);

        /*
         * Generate binded cache and store them on hash table
         */

        //Simulate all posible combinations

        std::vector<bool> is_binded;
        is_binded.push_back(true);
        is_binded.push_back(false);
#define forx(_type,_iter,_coll) for (_type::iterator _iter = _coll.begin(); _iter != _coll.end(); ++_iter)

        forx(std::vector<bool>, bu, is_binded)
            forx(std::vector<bool>, bd, is_binded)
            forx(std::vector<bool>, bl, is_binded)
            forx(std::vector<bool>, br, is_binded)
            forx(std::vector<bool>, bul, is_binded)
            forx(std::vector<bool>, bur, is_binded)
            forx(std::vector<bool>, bdl, is_binded)
            forx(std::vector<bool>, bdr, is_binded)
#undef forx
        {
            int u = 0, d = 0, l = 0, r = 0;
            if (*bu) u = UP;
            if (*bd) d = DOWN;
            if (*bl) l = LEFT;
            if (*br) r = RIGHT;
            int ul = 0, ur = 0, dl = 0, dr = 0;
            if (u + l == 0 && *bul)
                ul = UPLEFT;
            if (u + r == 0 && *bur)
                ur = UPRIGHT;
            if (d + l == 0 && *bdl)
                dl = DOWNLEFT;
            if (d + r == 0 && *bdr)
                dr = DOWNRIGHT;

            short id = TileOps::translate (terrain_id, u+d+l+r+ul+ur+dl+dr);
            if (m_chipset->contains(id)) //item exist?
                continue;

            /*
             * Get base
             */
            QPixmap p_tile(tilesize, tilesize);
            p_tile.fill(QColor(0,0,0,0));
            QPainter p(&p_tile);

            /*
             * Draw upper_left corner
             */
            int dest_x = 0;
            int dest_y = 0;
#define blit(x,y) p.drawPixmap(dest_x,dest_y,tilesize/2,tilesize/2, p_block.copy(x, y,r_tileHalf,r_tileHalf))
            if (u+l == 5)
                blit(0, r_tileSize);
            else if (u)
            {
                if (r)
                    blit(r_tileSize*2, r_tileSize);
                else
                    blit(r_tileSize, r_tileSize);
            }
            else if (l)
            {
                if (d)
                    blit(0, r_tileSize*3);
                else
                    blit(0, r_tileSize*2);
            }
            else if (ul)
                blit(r_tileSize*2, 0);
            else //0
            {
                if (d+r == 10)
                    blit(r_tileSize*2, r_tileSize*3);
                else if (r)
                    blit(r_tileSize*2, r_tileSize*2);
                else if (d)
                    blit(r_tileSize*1, r_tileSize*3);
                else
                    blit(r_tileSize*1, r_tileSize*2);
            }
            /*
             * Draw upper_right corner
             */
            dest_x = tilesize/2;
            if (u+r == 9)
                blit(r_tileSize*5/2, r_tileSize);
            else if (u)
            {
                if(l)
                    blit(r_tileSize/2, r_tileSize);
                else
                    blit(r_tileSize*3/2, r_tileSize);
            }
            else if (r)
            {
                if (d)
                    blit(r_tileSize*5/2, r_tileSize*3);
                else
                    blit(r_tileSize*5/2, r_tileSize*2);
            }
            else if (ur)
                blit(r_tileSize*5/2, 0);
            else //0
            {
                if (d+l == 6)
                    blit(r_tileSize/2, r_tileSize*3);
                else if (l)
                    blit(r_tileSize/2, r_tileSize*2);
                else if (d)
                    blit(r_tileSize*3/2, r_tileSize*3);
                else
                    blit(r_tileSize*3/2, r_tileSize*2);
            }
            /*
             * Draw down_left corner
             */
            dest_x = 0;
            dest_y = tilesize/2;
            if (d+l == 6)
                blit(0, r_tileSize*7/2);
            else if (d)
            {
                if (r)
                    blit(r_tileSize*2, r_tileSize*7/2);
                else
                    blit(r_tileSize, r_tileSize*7/2);
            }
            else if (l)
            {
                if (u)
                    blit(0, r_tileSize*3/2);
                else
                    blit(0, r_tileSize*5/2);
            }
            else if (dl)
                blit(r_tileSize*2, r_tileHalf);
            else
            {
                if (u+r == 9)
                    blit(r_tileSize*2, r_tileSize*3/2);
                else if (r)
                    blit(r_tileSize*2, r_tileSize*5/2);
                else if (u)
                    blit(r_tileSize, r_tileSize*3/2);
                else
                    blit(r_tileSize, r_tileSize*5/2);
            }
            /*
             * Draw down_right corner
             */
            dest_x = tilesize/2;
            if (d+r == 10)
                blit(r_tileSize*5/2, r_tileSize*7/2);
            else if (d)
            {
                if (l)
                    blit(r_tileSize/2, r_tileSize*7/2);
                else
                    blit(r_tileSize*3/2, r_tileSize*7/2);
            }
            else if (r)
            {
                if (u)
                    blit(r_tileSize*5/2, r_tileSize*3/2);
                else
                    blit(r_tileSize*5/2, r_tileSize*5/2);
            }
            else if (dr)
                blit(r_tileSize*5/2, r_tileHalf);
            else //0
            {
                if (u+l == 5)
                    blit(r_tileHalf,r_tileSize*3/2);
                else if (l)
                    blit(r_tileHalf,r_tileSize*5/2);
                else if (u)
                    blit(r_tileSize*3/2,r_tileSize*3/2);
                else
                    blit(r_tileSize*3/2,r_tileSize*5/2);
            }
#undef blit
            /*
             * Register tile
             */
            m_chipset->do_assign(id, p_tile);
        }

        terrain_id++;
        block_col++;

        // Go to the next block
        if (block_col > 1) {
            block_col = 0;
            block_row++;
        }

        // Go to the next column
        if (block_row > 3) {
            block_row = 0;
            tileset_col++;
        }
    }
    int tile_row = 0;
    /* Register E and F blocks */
    while (tileset_col < 5 )
    {
        for (int col = 0; col < 6; col++)
        {
            QPixmap ef_tile(tilesize, tilesize);
            ef_tile.fill(QColor(0,0,0,0));
            QPainter ef(&ef_tile);
            int orig_x = tileset_col*6*r_tileSize+col*r_tileSize;
            int orig_y = tile_row*r_tileSize;
            ef.drawPixmap(0,0,tilesize,tilesize,o_chipset.copy(orig_x,orig_y,r_tileSize,r_tileSize));
            ef.end();
            m_chipset->do_assign(TileOps::translate(terrain_id), ef_tile);
            terrain_id++;
        }

        tile_row++;
        if (tile_row == 16)
        {
            tile_row = 0;
            tileset_col++;
        }
    }
}

