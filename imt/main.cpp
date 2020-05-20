#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <core/boxes.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
    Boxes boxes;
    std::cout << boxes.getIcon().toStdString() << std::endl;
    std::cout << boxes.getSplash().toStdString() << std::endl;
    std::cout << boxes.getStore().toStdString() << std::endl;
    QApplication app(argc, argv);
    QWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(QApplication::translate("toplevel", "Top-level widget"));
    return app.exec();
}