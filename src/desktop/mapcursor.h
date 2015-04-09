#ifndef MAPCURSOR_H
#define MAPCURSOR_H

#include "mapgraphicsitem.h"

class MapCursor : public MapGraphicsItem
{
public:
    MapCursor(MapCamera *camera) :
        MapGraphicsItem(camera), enabled(false), orientation_enabled(false) {
        brush = QBrush(QColor(0, 0, 255, 127));
        setVisible(true);
        x = y = angle = 0;
    }
    ~MapCursor() {}

    void SetColor(QRgb fill) {
        brush.setColor(QColor(fill));
    }

    bool enabled, orientation_enabled;
    float x, y, angle;

    virtual QRectF boundingRect() const {
        auto p = PaintPos(QPointF(x, y));
        return QRectF(p.x() - 11, p.y() - 11, 22, 22);
    }

protected:
    QBrush brush;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
        if (!enabled) {
            return;
        }
        painter->setPen(QPen(QBrush(QColor(0,0,0,0)), 0));
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


};

#endif // MAPCURSOR_H
