#include "floorview.h"

#include <QScrollBar>
#include <qmath.h>

#include "mapbackground.h"
#include "../utils/bug.h"

FloorView::FloorView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    cursor = new MapCursor(&camera);
    setAcceptDrops(true);
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //*   DEBUG
    cursor->enabled = true;
    cursor->orientation_enabled = false;
    background = new MapBackground(QImage("../data/floor3.png"), &camera);
    //*/

    scene->addItem(background);
    scene->addItem(cursor);
    UpdateView();
    command_state = NONE;
}

FloorView::~FloorView()
{
    for (auto *item : items)
        delete item;
    delete cursor;
    delete background;
    delete scene;
}

void FloorView::mousePressEvent(QMouseEvent *event)
{
    float x = event->x() - this->width() * .5f;
    float y = event->y() - this->height() * .5f;
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    if (event->buttons() == Qt::LeftButton) {
        if (command_state == NONE) {
            last_rx = rx;
            last_ry = ry;
            last_x = x;
            last_y = y;

            command_state = DRAG;
        }
    } else if (event->buttons() == Qt::RightButton) {
        cursor->x = rx;
        cursor->y = ry;

        UpdateView();
    }

    event->accept();
}

void FloorView::mouseMoveEvent(QMouseEvent *event)
{
    float x = event->x() - this->width() * .5f;
    float y = event->y() - this->height() * .5f;
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    if (command_state == DRAG) {
        float dx, dy;
        camera.ScreenToReal(last_x, last_y, &dx, &dy);
        camera.move(dx - rx, dy - ry);
        last_rx = rx;
        last_ry = ry;
        last_x = x;
        last_y = y;
        UpdateView();
    }
    event->accept();
}

void FloorView::mouseReleaseEvent(QMouseEvent *event)
{
    float x = event->x() - this->width() * .5f;
    float y = event->y() - this->height() * .5f;
    float rx, ry;
    camera.ScreenToReal(x, y, &rx, &ry);
    if (command_state == DRAG) {
        command_state = NONE;
    }
    event->accept();
}

void FloorView::wheelEvent(QWheelEvent *event)
{
    float s = event->delta() / 1200.f;
    if (command_state == DRAG) {
        camera.rotate(s);
    } else {
        camera.scale = exp(log(camera.scale) - s);
    }
    UpdateView();
    event->accept();
}

