#include "trainer.h"

Trainer::Trainer(Floor *floor) : floor_(floor) {
}


void Trainer::AddObject(const Polygon &object) {
    floor_->objects.append(object);
}

void Trainer::RemoveObjectsIn(const Polygon &p) {
    JsonObjectList<Polygon> ret;
    for (auto &k : floor_->objects) {
        if (!GeometryUtils::Hit(p, k)) {
            ret.append(k);
        }
    }
    floor_->objects = ret;
}

void Trainer::AddComment(const Comment &comment) {
    floor_->comments.append(comment);
}

void Trainer::RemoveCommentsIn(const Polygon &p) {
    JsonObjectList<Comment> ret;
    for (auto &k : floor_->comments) {
        /*
        if (!GeometryUtils::Hit(p, k.)) {
            ret.append(k);
        }*/
    }
    floor_->comments = ret;
}

void Trainer::AddLabel(const Label &label) {
    floor_->labels.append(label);
}

void Trainer::RemoveLabelsIn(const Polygon &p) {
    JsonObjectList<Label> ret;
    for (auto &k : floor_->labels) {
        if (!GeometryUtils::Inside(k.pos, p)) {
            ret.append(k);
        }
    }
    floor_->labels = ret;
}


