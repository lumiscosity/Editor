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

#include "defines.h"

#include <qmap.h>
const QMap<int, short> m_dictionary(
    {
        {UPLEFT,                              1},
        {UPRIGHT,                             2},
        {UPLEFT+UPRIGHT,                      3},
        {DOWNRIGHT,                           4},
        {UPLEFT+DOWNRIGHT,                    5},
        {UPRIGHT+DOWNRIGHT,                   6},
        {UPLEFT+UPRIGHT+DOWNRIGHT,            7},
        {DOWNLEFT,                            8},
        {DOWNLEFT+UPLEFT,                     9},
        {DOWNLEFT+UPRIGHT,					 10},
        {DOWNLEFT+UPLEFT+UPRIGHT,			 11},
        {DOWNLEFT+DOWNRIGHT,				 12},
        {DOWNLEFT+DOWNRIGHT+UPLEFT,			 13},
        {DOWNLEFT+DOWNRIGHT+UPRIGHT,		 14},
        {DOWNLEFT+DOWNRIGHT+UPLEFT+UPRIGHT,  15},
        {LEFT,								 16},
        {LEFT+UPRIGHT,						 17},
        {LEFT+DOWNRIGHT,					 18},
        {LEFT+UPRIGHT+DOWNRIGHT,			 19},
        {UP,								 20},
        {UP+DOWNRIGHT,						 21},
        {UP+DOWNLEFT,						 22},
        {UP+DOWNRIGHT+DOWNLEFT,				 23},
        {RIGHT,								 24},
        {RIGHT+DOWNLEFT,					 25},
        {RIGHT+UPLEFT,						 26},
        {RIGHT+UPLEFT+DOWNLEFT,				 27},
        {DOWN,								 28},
        {DOWN+UPLEFT,						 29},
        {DOWN+UPRIGHT,						 30},
        {DOWN+UPLEFT+UPRIGHT,				 31},
        {LEFT+RIGHT,						 32},
        {UP+DOWN,							 33},
        {UP+LEFT,							 34},
        {UP+LEFT+DOWNRIGHT,					 35},
        {UP+RIGHT,							 36},
        {UP+RIGHT+DOWNLEFT,					 37},
        {DOWN+RIGHT,						 38},
        {DOWN+RIGHT+UPLEFT,					 39},
        {DOWN+LEFT,							 40},
        {DOWN+LEFT+UPRIGHT,					 41},
        {UP+LEFT+RIGHT,						 42},
        {UP+LEFT+DOWN,						 43},
        {LEFT+RIGHT+DOWN,					 44},
        {UP+RIGHT+DOWN,						 45},
        {UP+DOWN+LEFT+RIGHT,				 46},
        {SAMPLE,							 47},
    }
);


namespace TileOps {
    bool isWater(int terrain_id);
    bool isABWater(int terrain_id);
    bool isDWater(int terrain_id);
    bool isAnimation(int terrain_id);
    bool isDblock(int terrain_id);
    bool isEblock(int terrain_id);
    bool isFblock(int terrain_id);

    short translate(int terrain_id, int _code = 0, int _scode = 0);
    int translate(short tile_id);
}
