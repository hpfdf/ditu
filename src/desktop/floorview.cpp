#include "floorview.h"

#include <QScrollBar>

FloorView::FloorView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);
    cursor = new MapCursor(&camera);
    scene->addItem(cursor);
    setAcceptDrops(true);
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //*
    cursor->enabled = true;
    cursor->orientation_enabled = false;
    //*/
}

FloorView::~FloorView()
{
    for (auto *item : items)
        delete item;
    delete cursor;
    delete scene;
}

void FloorView::mousePressEvent(QMouseEvent *event)
{
    float x = event->x(), y = event->y();
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    event->accept();
}

void FloorView::mouseMoveEvent(QMouseEvent *event)
{
    float x = event->x(), y = event->y();
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    event->accept();
}

void FloorView::mouseReleaseEvent(QMouseEvent *event)
{
    float x = event->x(), y = event->y();
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    event->accept();
}

