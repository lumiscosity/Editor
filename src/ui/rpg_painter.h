#pragma once

#include <QPainter>
#include <core.h>

class RpgPainter : public QPainter {

public:
    RpgPainter();

    enum TileOverviewMode
    {
        ALL_LOWER,
        NONAUTO_LOWER,
        ALL_UPPER
    };

    void setCachedChipset(QString chipset);
    void beginPainting(QPixmap &dest);
    void renderPanorama(const QRect &dest_rect, QPixmap panorama);
    void renderTile(const short &tile_id, const QRect &dest_rect);
    void renderTileOverview(const TileOverviewMode mode);
    void renderEvent(const lcf::rpg::Event& event, const QRect &dest_rect);
    void endPainting();
    QColor keycolor();
private:
    QColor m_keycolor;
    QString m_chipset;
    QMap<short, QPixmap> *m_chipsetCache = nullptr;
    QMap<QString, QPixmap> *m_eventCache = nullptr;

};
