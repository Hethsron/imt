#include <controller/router.hpp>

Router::Router()
    : Subject() {}

Router::~Router() {}

void Router::subscribe(Observer* o) {
    collections.append(o);
}

void Router::unsubscribe(Observer* o) {
    collections.removeOne(o);
}

namespace ROUTER {
    void render(Observer* o) {
        Router* router = new Router();
        router->subscribe(o);
        router->notify();
    }
}