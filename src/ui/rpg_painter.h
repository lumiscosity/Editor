#include <QPainter>
#include <core.h>

class RpgPainter : public QPainter {

public:
    RpgPainter();

    void beginPainting(QPixmap &dest);
    void renderPanorama(const QRect &dest_rect);
    void renderTile(const short &tile_id, const QRect &dest_rect);
    void renderTileOverview(const Core::TileOverviewMode mode);
    void renderEvent(const lcf::rpg::Event& event, const QRect &dest_rect);
    void endPainting();
private:
    Core m_cache;
    QColor m_keycolor;
    QString m_chipset;

};
