#include <core/boxes.hpp>

Boxes::Boxes()
    : title("Welcome to Ahora"), icon(""), splash(""), background(""), style("background-color: rgb(4, 19, 43); color: white;"), message("Are you sure you want to quit? Any unsaved work will be lost"), height(820), width(1440) {
    assignment();
}

Boxes::~Boxes() {}

void Boxes::assignment() {
    #if _WIN32
        QString assets = QString("resources\\assets\\img");
    #else
        QString assets = QString("resources/assets/img");
    #endif

    QDir dir;
    if (dir.cdUp() && dir.cdUp() && dir.cd(assets)) {
        icon = dir.filePath("ahora.ico");
        splash = dir.filePath("ahora.png");
        background = dir.filePath("splash.jpg");
    }
    else {
        qWarning("cannot find %s", dir.path().toStdString().c_str());
    }
}

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

QString Boxes::getBackground() const {
    return background;
}

int Boxes::getHeight() const {
    return height;
}

int Boxes::getWidth() const {
    return width;
}