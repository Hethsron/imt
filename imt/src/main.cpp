#include <controller/controller.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    int ret;
    try {
        ROUTER::render(new Manager());
        ret = app.exec();
    }
    catch(const std::bad_alloc &) {
        return EXIT_FAILURE; // exit the application
    }

    return ret;
}