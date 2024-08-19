#pragma once

#include <QPainter>
#include <core.h>

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
    QSize setPanorama(QString name);

    void beginPainting(QPixmap &dest);
    void renderPanorama(const QRect &dest_rect);
    void renderTile(const short &tile_id, const QRect &dest_rect);
    void renderTileOverview(const TileOverviewMode mode);
    void renderEvent(const lcf::rpg::Event& event, const QRect &dest_rect);
    void endPainting();
    QColor keycolor();

    inline bool chipsetIsNull(QString chipset) {return m_chipset[0].isNull();}

private:
    QPixmap m_panorama;
    QMap<short, QPixmap> m_chipset;
    QMap<QString, QPixmap> *m_eventCache = nullptr;

};
