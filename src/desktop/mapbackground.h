#ifndef MAPBACKGROUND_H
#define MAPBACKGROUND_H

#include <QPainter>

#include "mapgraphicsitem.h"
#include "../utils/bug.h"

class MapBackground : public MapGraphicsItem
{
public:
    MapBackground(const QImage &image, MapCamera *camera) : MapGraphicsItem(camera) {
        this->image = image.copy();
        x = -image.width() / 2;
        y = -image.height() / 2;
        angle = 0;
    }
    ~MapBackground() {

    }

    virtual QRectF boundingRect() const {
        return QRectF();
    }
    float x, y, angle;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
        auto r = QPointF(x - camera->x, y - camera->y);
        painter->rotate(-(angle + camera->angle)*180/3.1415926535897932384626);
        painter->scale(1 / camera->scale, 1 / camera->scale);

        painter->drawImage(r, image);
    }

private:
    QImage image;
};

#endif // MAPBACKGROUND_H
