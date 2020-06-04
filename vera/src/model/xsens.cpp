#include <model/xsens.hpp>

Xsens::Xsens(const QJsonDocument& cfg)
    : Sensor(Type::Xsens, Pattern::Xsens, cfg) {}

Xsens::Xsens(const Xsens& other)
    : Sensor(other) {}

Xsens::~Xsens() {}

bool Xsens::isEmpty() const {
    return true;
}