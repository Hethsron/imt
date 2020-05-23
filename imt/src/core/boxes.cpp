#include <core/boxes.hpp>

Boxes::Boxes()
    : collections(QList<QString>()), title("Welcome to Ahora"), icon(""), splash(""), background(""), style("background-color: rgb(4, 19, 43); color: white;"), message("Are you sure you want to quit? Any unsaved work will be lost"), height(820), width(1440) {
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
        background = dir.filePath("splash.jpg");
        splash = dir.filePath("imt.png");
        icon = dir.filePath("imt.ico");
        collections.append("new.png");
        collections.append("open.png");
        collections.append("save.png");
        collections.append("exit.png");
        collections.append("undo.png");
        collections.append("redo.png");
        collections.append("cut.png");
        collections.append("copy.png");
        collections.append("paste.png");
        collections.append("conversion.png");
        collections.append("about.png");
    }
    else {
        qWarning("cannot find %s", dir.path().toStdString().c_str());
    }
}

QList<QString> Boxes::getCollections() const {
    return collections;
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