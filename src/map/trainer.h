#ifndef _TRAINER_H_
#define _TRAINER_H_

#include "contents.h"

// Define how to edit a floor.
class Trainer {
  public:
    Trainer(Floor *floor);

    // Add elements to the floor.
    void AddObject(const Polygon &object);
    void AddLabel(const Label &label);
    void AddComment(const Comment &comment);

    // Remove elements that hit or inside a given polygon.
    void RemoveObjectsIn(const Polygon &p);
    void RemoveCommentsIn(const Polygon &p);
    void RemoveLabelsIn(const Polygon &p);

    // Add a series of label by a route. Assume the speed is consistent.
    void BatchAddLabel(const JsonObjectList<Point> &route, const JsonObjectList<Observe> &ob,
                       int begin_time, int end_time);

  private:
    Floor *floor_;
};

#endif
