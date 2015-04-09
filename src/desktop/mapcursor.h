#ifndef MAPCURSOR_H
#define MAPCURSOR_H

#include "mapgraphicsitem.h"

class MapCursor : public MapGraphicsItem
{
public:
    MapCursor(MapCamera *camera) :
        MapGraphicsItem(camera), enabled(false), orientation_enabled(false) {
        SetColor(0xFF4444FF);
    }
    ~MapCursor() {}

    void SetColor(QRgb fill) {
        brush.setColor(QColor(fill));
    }

    bool enabled, orientation_enabled;
    float x, y, angle;

protected:
    QBrush brush;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
        if (!enabled) {
            return;
        }
        painter->setBrush(brush);
        auto p = PaintPos(QPointF(x, y));
        if (!orientation_enabled) {
            painter->drawEllipse(p, 8, 8);
        } else {

            QPointF p1(10, 0);
            QPointF p2(-7, 5);
            QPointF p3(-7, -5);
            QTransform t;
            t.rotateRadians(angle + camera->angle); // maybe inversed
            p1 = p + t.map(p1);
            p2 = p + t.map(p2);
            p3 = p + t.map(p3);
            QVector<QPointF> ps{p1, p2, p3};
            painter->drawPolygon(ps.data(), 3);
        }
    }

    virtual QRectF boundingRect() const {
        auto p = PaintPos(QPointF(x, y));
        return QRectF(p.x() - 11, p.y() - 11, 22, 22);
    }

};

#endif // MAPCURSOR_H
