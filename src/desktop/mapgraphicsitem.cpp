#include "mapgraphicsitem.h"

MapGraphicsItem::MapGraphicsItem(MapCamera *camera) : QGraphicsItem(0)
{
    this->camera = camera;
}

MapGraphicsItem::~MapGraphicsItem()
{

}

