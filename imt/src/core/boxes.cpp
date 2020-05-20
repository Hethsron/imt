#include <core/boxes.hpp>

Boxes::Boxes() {
    QDir dir;

    if (dir.cdUp() && dir.cdUp() && dir.cd("resources/assets")) {
        icon = dir.filePath("img/imt.ico");
        splash = dir.filePath("img/imt.png");
        store = dir.filePath("tree/splash.ui");
    }
    else {
        qWarning("cannot find %s", dir.path().toStdString().c_str());
    }

    title = QString("Welcome to Auxilia");
    style = QString("background-color: rgb(4, 19, 43); color: white;");
    message = QString("Are you sure you want to quit? Any unsaved work will be lost");
    height = 820;
    width = 1440;
}

Boxes::~Boxes() {}

QString Boxes::getTitle() const {
    return title;
}

QString Boxes::getIcon() const {
    return icon;
}

QString Boxes::getSplash() const {
    return splash;
}

QString Boxes::getStyle() const {
    return style;
}

QString Boxes::getMessage() const {
    return message;
}

QString Boxes::getStore() const {
    return store;
}

int Boxes::getHeight() const {
    return height;
}

int Boxes::getWidth() const {
    return width;
}