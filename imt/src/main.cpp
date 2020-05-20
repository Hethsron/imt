#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <view/mainview.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    int ret;
    try {
        MainView mainView;
        mainView.show();
        ret = app.exec();
    }
    catch(const std::bad_alloc &) {
        return EXIT_FAILURE; // exit the application
    }

    return ret;
}