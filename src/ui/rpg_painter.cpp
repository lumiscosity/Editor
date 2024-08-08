#include "rpg_painter.h"
#include "common/dbstring.h"

RpgPainter::RpgPainter() {

}

void RpgPainter::beginPainting(QPixmap &dest) {
    this->begin(&dest);
    this->setPen(Qt::yellow);
}

void RpgPainter::renderPanorama(const QRect &dest_rect, QPixmap panorama) {
    this->drawPixmap(dest_rect, panorama);
}

void RpgPainter::renderTile(const short &tile_id, const QRect &dest_rect) {
    this->drawPixmap(dest_rect, core().getCachedTileset(m_chipset)[tile_id]);
}

void RpgPainter::renderTileOverview(const Core::TileOverviewMode mode) {
    switch (mode) {
    case Core::ALL_LOWER:
        for (int terrain_id = 0; terrain_id < 162; terrain_id++)
        {
            QRect rect(((terrain_id)%6)*16,(terrain_id/6)*16,16,16);
            renderTile(core().translate(terrain_id,15), rect);
        }
        renderTile(core().translate(2,0,240), QRect(32,16,16,16));
        break;
    case Core::NONAUTO_LOWER:
        for (int terrain_id = 0; terrain_id < 144; terrain_id++)
        {
            QRect rect(((terrain_id)%6)*16,(terrain_id/6)*16,16,16);
            renderTile(core().translate(terrain_id+18), rect);
        }
        break;
    case Core::ALL_UPPER:
        for (int terrain_id = 0; terrain_id < 144; terrain_id++)
        {
            QRect rect(((terrain_id)%6)*16,(terrain_id/6)*16,16,16);
            renderTile(core().translate(terrain_id+162), rect);
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

        if (!m_eventCache.contains(check))
            cacheEvent(&event, check);
        this->drawPixmap(final_rect, m_eventCache.value(check), QRect(0,6,24,24));
    }
}

void RpgPainter::endPainting()
{
    this->end();
}

QColor RpgPainter::keycolor()
{
    return m_keycolor;
}
