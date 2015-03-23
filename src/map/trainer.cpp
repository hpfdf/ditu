#include "trainer.h"

Trainer::Trainer(Floor *floor) : floor_(floor) {
}


void Trainer::AddObject(const Polygon &object); {
    floor_->objects.push_back(object);
}

void Trainer::RemoveObjectsIn(const Polygon &p) {
    std::vector<Polygon> ret;
    for (auto &k : floor_->objects) {
        if (!GeometryUtils::Hit(p, k)) {
            ret.push_back(k);
        }
    }
    floor_->objects = ret;
}

void Trainer::AddComment(const Comment &comment) {
    floor_->comments.push_back(comment);
}

void Trainer::RemoveCommentsIn(const Polygon &p) {
    std::vector<Comment> ret;
    for (auto &k : floor_->comments) {
        if (!GeometryUtils::Hit(p, k)) {
            ret.push_back(k);
        }
    }
    floor_->comments = ret;
}

void Trainer::AddLabel(const Label &label) {
    floor_->labels.push_back(label);
}

void Trainer::RemoveLabelsIn(const Polygon &p) {
    std::vector<Label> ret;
    for (auto &k : floor_->labels) {
        if (!GeometryUtils::Hit(p, k)) {
            ret.push_back(k);
        }
    }
    floor_->labels = ret;
}

void Trainer::BatchAddLabel(
        const PointList &route, JsonObject *ob,
        int begin_time, int end_time) {
}

