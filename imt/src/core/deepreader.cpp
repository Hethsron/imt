#include <core/deepreader.hpp>

DeepReader::DeepReader(const QString& cfg)
    : Command(), config(cfg), assets(QList<QStringList>()) {}

DeepReader::~DeepReader() {}

void DeepReader::execute() {
    assets = cpu.deepRead(config);
}

QList<QStringList> DeepReader::getAssets() const {
    return assets;
}

QList<QStringList> DeepReader::release(const QString& cfg) {
    DeepReader dr(cfg);
    dr.execute();
    return dr.getAssets();
}