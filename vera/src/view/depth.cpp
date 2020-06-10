#include <view/depth.hpp>

Depth::Depth(QWidget* parent)
    : QLabel(parent) {}

Depth::Depth(const QString& fileName, QWidget* parent)
    : QLabel(parent) {
        setPixmap(QPixmap(fileName));
    }

Depth::~Depth() {}