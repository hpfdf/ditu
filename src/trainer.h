#ifndef _TRAINER_H_
#define _TRAINER_H_

#include "contents.h"

class Trainer {
  public:
    Trainer(Floor *floor) : floor_(floor) {
    }

    void AddObject(const Polygon &object) {
        floor_->objects.push_back(object);
    }

    void RemoveObjectsIn(const Polygon &p) {
        std::vector<Polygon> ret;
        for (auto &k : floor_->objects) {
            if (!GeometryUtils::Hit(p, k)) {
                ret.push_back(k);
            }
        }
        floor_->objects = ret;
    }

    void AddComment(const Comment &comment) {
        floor_->comments.push_back(comment);
    }

    void RemoveCommentsIn(const Polygon &p) {
        std::vector<Comment> ret;
        for (auto &k : floor_->comments) {
            if (!GeometryUtils::Hit(p, k)) {
                ret.push_back(k);
            }
        }
        floor_->comments = ret;
    }

    void AddLabel(const Label &label) {
        floor_->labels.push_back(label);
    }

    void RemoveLabelsIn(const Polygon &p) {
        std::vector<Label> ret;
        for (auto &k : floor_->labels) {
            if (!GeometryUtils::Hit(p, k)) {
                ret.push_back(k);
            }
        }
        floor_->labels = ret;
    }

    void BatchAddLabel(const PointList &route, std::vector<JsonObject *ob,
                       float start_time, float end_time)

  private:
    Floor *floor_;
};

#endif
