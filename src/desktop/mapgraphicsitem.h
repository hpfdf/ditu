#ifndef MAPGRAPHICSITEM_H
#define MAPGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
#include <limits>

#include "../utils/mapcamera.h"

class MapGraphicsItem : public QGraphicsItem
{
public:
    MapGraphicsItem(MapCamera *camera);
    ~MapGraphicsItem();
    QPointF PaintPos(QPointF p) const {
        float rx, ry;
        camera->RealToScreen(p.x(), p.y(), &rx, &ry);
        return QPointF(rx, ry);
    }

protected:
    MapCamera *camera;
};

class MapPolygon : public MapGraphicsItem
{
public:
    QVector<QPointF> shape;

    void SetColor(QRgb fill, QRgb shape = 0, float width = 1) {
        if (shape == 0) {
            shape = fill;
        }
        pen.setColor(QColor(shape));
        brush.setColor(QColor(fill));
        pen.setWidthF(width);
    }

    MapPolygon(MapCamera *camera): MapGraphicsItem(camera) {}
    ~MapPolygon() {}

    virtual QRectF boundingRect() const {
        float l, r, u, d;
        l = u = std::numeric_limits<float>::max();
        d = r = -std::numeric_limits<float>::max();
        for (const auto &p : shape) {
            auto q = PaintPos(p);
            l = std::min(l, static_cast<float>(q.x()));
            u = std::min(u, static_cast<float>(q.y()));
            r = std::max(r, static_cast<float>(q.x()));
            d = std::max(d, static_cast<float>(q.y()));
        }
        return QRectF(l-1, u-1, r+2-l, d+2-u);
    }

protected:
    QPen pen;
    QBrush brush;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
        painter->setPen(pen);
        painter->setBrush(brush);
        auto buff = shape;
        for (auto &p : buff) {
            p = PaintPos(p);
        }
        painter->drawPolygon(buff.data(), shape.size());
    }
};

#endif // MAPGRAPHICSITEM_H
