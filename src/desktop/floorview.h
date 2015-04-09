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

    MapCursor *GetCursor() {
        return cursor;
    }

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    QGraphicsScene *scene;
    MapCamera camera;
    MapCursor *cursor;
    QVector<MapGraphicsItem*> items;

signals:
    void LeftPress(float x, float y);
    void RightPress(float x, float y);
    void DoubleClicked();
    void Release(float x, float y);
};

#endif // FLOORVIEW_H
