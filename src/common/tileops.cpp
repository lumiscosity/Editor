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

#include "tileops.h"

bool TileOps::isWater(int terrain_id)
{
    return terrain_id >= 0 && terrain_id <= 2;
}

bool TileOps::isABWater(int terrain_id)
{
    return terrain_id == 0 || terrain_id == 1;
}

bool TileOps::isDWater(int terrain_id)
{
    return terrain_id == 2;
}

bool TileOps::isAnimation(int terrain_id)
{
    return terrain_id >= 3 && terrain_id <= 5;
}

bool TileOps::isDblock(int terrain_id)
{
    return terrain_id >= 6 && terrain_id <= 17;
}

bool TileOps::isEblock(int terrain_id)
{
    return terrain_id >= 18 && terrain_id <= 161;
}

bool TileOps::isFblock(int terrain_id)
{
    return terrain_id >= 162 && terrain_id <= 305;
}

short TileOps::translate(int terrain_id, int _code, int _scode)
{
    if (terrain_id < 0)
        return 0x7FFF;
    if (isWater(terrain_id))
        return (static_cast<short>(terrain_id)*1000+m_dictionary[_code]+m_dictionary[_scode]*50);
    if (isAnimation(terrain_id))
        return (3000+(static_cast<short>(terrain_id)-3)*50+m_dictionary[_code]);
    if (isDblock(terrain_id))
        return (4000+(static_cast<short>(terrain_id)-6)*50+m_dictionary[_code]);
    if (isEblock(terrain_id))
        return (5000+static_cast<short>(terrain_id)-18);
    if (isFblock(terrain_id))
        return (10000+static_cast<short>(terrain_id)-162);
    return 0x7FFF;
}

int TileOps::translate(short tile_id)
{
    if (tile_id < 0)
        return -1;
    else if (tile_id < 3000)
        return tile_id/1000;
    else if (tile_id >= 3000 && tile_id < 3150)
        return (tile_id-3000)/50+3;
    else if (tile_id >= 4000 && tile_id < 4600)
        return (tile_id-4000)/50+6;
    else if (tile_id >= 5000 && tile_id < 5162)
        return tile_id-5000+18;
    else if (tile_id >= 10000 && tile_id < 10144)
        return tile_id-10000+161;
    else
        return -1;
}
