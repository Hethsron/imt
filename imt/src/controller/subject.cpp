#include <controller/subject.hpp>

Subject::Subject()
    : collections(QList<Observer*>()) {}

Subject::~Subject() {}

void Subject::notify() const {
    QListIterator<Observer*> iterator(collections);

    while ((iterator.hasNext())) {
        Observer* o = iterator.next();
        o->notify();
    }
}