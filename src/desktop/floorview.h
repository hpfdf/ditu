#ifndef FLOORVIEW_H
#define FLOORVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

#include "../utils/mapcamera.h"
#include "mapcursor.h"

class FloorView : public QGraphicsView
{
    Q_OBJECT
public:
    FloorView(QWidget *parent = 0);
    ~FloorView();

    void ResetCamera(const MapCamera &camera) {
        this->camera = camera;
    }

    MapCamera *GetCamera() {
        return &camera;
    }
    void UpdateView() {
        scene->update();
    }

    void SetCursor(float x, float y, float angle = -11) {
        cursor->x = x;
        cursor->y = y;
        cursor->enabled = true;
        if (angle >= -10) {
            cursor->angle = angle;
            cursor->orientation_enabled = true;
        } else {
            cursor->orientation_enabled = false;
        }
    }

    MapCursor *GetCursor() {
        return cursor;
    }

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    QGraphicsScene *scene;
    MapCamera camera;
    MapCursor *cursor;
    QVector<MapGraphicsItem*> items;
    MapGraphicsItem *background;

    // mouse controls:
    enum CommandState {
        NONE = 0,
        DRAG,
        POINT,
        DRAWING,
    } command_state;
    float last_x, last_y;
    float last_rx, last_ry;

signals:
    void LeftPress(float x, float y);
    void RightPress(float x, float y);
    void DoubleClicked();
    void Release(float x, float y);
};

#endif // FLOORVIEW_H
