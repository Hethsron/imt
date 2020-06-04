#include <model/kinect.hpp>

Kinect::Kinect()
    : Sensor() {}

Kinect::Kinect(const QJsonDocument& cfg)
    : Sensor(Type::kinect, Pattern::Kinect, cfg) {}

Kinect::Kinect(const Kinect& other)
    : Sensor(other) {}

Kinect::~Kinect() {}

bool Kinect::isEmpty() const {
    return true;
}