#include <model/measurements.hpp>

Measurements::Measurements()
    : name(QString()) {}

Measurements::Measurements(const QString& key)
    : name(key), time(QVector<double>()), accelX(QVector<double>()), accelY(QVector<double>()), accelZ(QVector<double>()), gyroX(QVector<double>()), gyroY(QVector<double>()), gyroZ(QVector<double>()) {}

Measurements::Measurements(const Measurements& other)
    :name(other.name), time(other.time), accelX(other.accelX), accelY(other.accelY), accelZ(other.accelZ), gyroX(other.gyroX), gyroY(other.gyroY), gyroZ(other.gyroZ) {}

Measurements::Measurements(std::nullptr_t)
    : name(QString()), time(QVector<double>()), accelX(QVector<double>()), accelY(QVector<double>()), accelZ(QVector<double>()), gyroX(QVector<double>()), gyroY(QVector<double>()), gyroZ(QVector<double>()) {}

Measurements::~Measurements() {
    // Check if data is not empty
    if (!isEmpty()) {
        // Clear all data
        clear();
    }
}

QString Measurements::getName() const {
    return name;
}

QVector<double> Measurements::getTime() const {
    return time;
}

QVector<double> Measurements::getAccelX() const {
    return accelX;
}

QVector<double> Measurements::getAccelY() const {
    return accelY;
}

QVector<double> Measurements::getAccelZ() const {
    return accelZ;
}

QVector<double> Measurements::getGyroX() const {
    return gyroX;
}

QVector<double> Measurements::getGyroY() const {
    return gyroY;
}

QVector<double> Measurements::getGyroZ() const {
    return gyroZ;
}

double Measurements::getMaxAccel() const {
    double value = accelX.at(0);

    for (int i = 0; i < accelX.size(); ++i) {
        if (accelX.at(i) > value) {
            value = accelX.at(i);
        }
    }

    for (int i = 0; i < accelY.size(); ++i) {
        if (accelY.at(i) > value) {
            value = accelY.at(i);
        }
    }

    for (int i = 0; i < accelZ.size(); ++i) {
        if (accelZ.at(i) > value) {
            value = accelZ.at(i);
        }
    }

    return value;
}

double Measurements::getMinAccel() const {
    double value = accelX.at(0);
    
    for (int i = 0; i < accelX.size(); ++i) {
        if (accelX.at(i) < value) {
            value = accelX.at(i);
        }
    }

    for (int i = 0; i < accelY.size(); ++i) {
        if (accelY.at(i) < value) {
            value = accelY.at(i);
        }
    }

    for (int i = 0; i < accelZ.size(); ++i) {
        if (accelZ.at(i) < value) {
            value = accelZ.at(i);
        }
    }

    return value;
}

double Measurements::getMaxGyro() const {
    double value = gyroX.at(0);

    for (int i = 0; i < gyroX.size(); ++i) {
        if (gyroX.at(i) > value) {
            value = gyroX.at(i);
        }
    }

    for (int i = 0; i < gyroY.size(); ++i) {
        if (gyroY.at(i) > value) {
            value = gyroY.at(i);
        }
    }

    for (int i = 0; i < gyroZ.size(); ++i) {
        if (gyroZ.at(i) > value) {
            value = gyroZ.at(i);
        }
    }

    return value;
}

double Measurements::getMinGyro() const {
    double value = gyroX.at(0);

    for (int i = 0; i < gyroX.size(); ++i) {
        if (gyroX.at(i) < value) {
            value = gyroX.at(i);
        }
    }

    for (int i = 0; i < gyroY.size(); ++i) {
        if (gyroY.at(i) < value) {
            value = gyroY.at(i);
        }
    }

    for (int i = 0; i < gyroZ.size(); ++i) {
        if (gyroZ.at(i) < value) {
            value = gyroZ.at(i);
        }
    }

    return value;
}

bool Measurements::isEmpty() const {
    return (time.size() == 0 && accelX.size() == 0 && accelY.size() == 0 && accelZ.size() == 0 && gyroX.size() == 0 && gyroY.size() == 0 && gyroZ.size() == 0);
}

void Measurements::clear() {
    // Clear time data
    time.clear();

    // Clear accelorometer data
    accelX.clear();
    accelY.clear();
    accelZ.clear();

    // Clear gyroscope data
    gyroX.clear();
    gyroY.clear();
    gyroZ.clear();
}

void Measurements::append(double ms, const QJsonObject& obj) {
    // Appends time data
    time.append(ms);

    // Appends accelerometer data
    accelX.append(obj.value(QString("accel_x")).toDouble());
    accelY.append(obj.value(QString("accel_y")).toDouble());
    accelZ.append(obj.value(QString("accel_z")).toDouble());

    // Appends gyroscope data
    gyroX.append(obj.value(QString("gyro_x")).toDouble());
    gyroY.append(obj.value(QString("gyro_y")).toDouble());
    gyroZ.append(obj.value(QString("gyro_z")).toDouble());
}

Measurements& Measurements::operator=(const Measurements& other) {
    // Avoid self assignment
    if (this != &other) {
        if (other.name != name) {
            name = other.name;
        }
    }
    return *this;
}

bool Measurements::operator==(const Measurements& other) const {
    return (other.name == name);
}

bool Measurements::operator!=(const Measurements& other) const {
    return (other.name != name);
}