#include "floorview.h"

#include <QScrollBar>

FloorView::FloorView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    cursor = new MapCursor(&camera);
    scene->addItem(cursor);
    setAcceptDrops(true);
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //*
    cursor->setVisible(true);
    cursor->enabled = true;
    cursor->orientation_enabled = false;
    //*/

    UpdateView();
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
    float x = event->x() - this->width() * .5f;
    float y = event->y() - this->height() * .5f;
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    event->accept();
}

void FloorView::mouseMoveEvent(QMouseEvent *event)
{
    float x = event->x() - this->width() * .5f;
    float y = event->y() - this->height() * .5f;
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    event->accept();
}

void FloorView::mouseReleaseEvent(QMouseEvent *event)
{
    float x = event->x() - this->width() * .5f;
    float y = event->y() - this->height() * .5f;
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    event->accept();
}

