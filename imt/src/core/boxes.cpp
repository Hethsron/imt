#include <core/boxes.hpp>

Boxes::Boxes()
    : collections(QList<QString>()), title(QString()), icon(QString()), splash(QString()), background(QString()), config(QString()), style(QString()), stylesheet(QString()), message(QString()), height(820), width(1440) {
    assignment();
}

Boxes::~Boxes() {}

void Boxes::assignment() {
    // Assign new values
    title = QString("Welcome to IMT");
    style = QString("background-color: rgb(4, 19, 43); color: white;");
    message = QString("Are you sure you want to quit? Any unsaved work will be lost");

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
        collections.append("configuration.png");
        collections.append("webHelp.png");

        if (dir.cdUp()) {
            #if _WIN32
                QString filename = dir.filePath("css\\style.css");
                config = dir.filePath("json\\config.json");
            #else
                QString filename = dir.filePath("css/style.css");
                config = dir.filePath("json/config.json");
            #endif

            QFile file(filename);
            if (file.open(QFile::ReadOnly)) {
                stylesheet = QLatin1String(file.readAll());
                file.close();
            }
            else {
                qWarning("Cannot open %s", filename.toStdString().c_str());
            }
        }
        else {
            qWarning("Cannot find %s", dir.path().toStdString().c_str());
        }
    }
    else {
        qWarning("Cannot find %s", dir.path().toStdString().c_str());
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

QString Boxes::getBackground() const {
    return background;
}

QString Boxes::getConfig() const {
    return config;
}

QString Boxes::getStyle() const {
    return style;
}

QString Boxes::getStyleSheet() const {
    return stylesheet;
}

QString Boxes::getMessage() const {
    return message;
}

int Boxes::getHeight() const {
    return height;
}

int Boxes::getWidth() const {
    return width;
}