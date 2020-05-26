#include <core/reader.hpp>

Reader::Reader(const QJsonDocument& cfg, const QString& p)
    : Command(), cpu(Processor()), config(cfg), pattern(p), dir(QString()) {}

Reader::~Reader() {}

QString Reader::getDir() const {
    return dir;
}

void Reader::execute() {
    dir = cpu.read(config, pattern);
}

QString Reader::release(const QJsonDocument& cfg, const QString& p) {
    Reader r(cfg, p);
    r.execute();
    return r.getDir();
}