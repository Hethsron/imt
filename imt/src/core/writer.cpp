#include <core/writer.hpp>

Writer::Writer(const QString& cfg)
    : Command(), cpu(Processor()), config(cfg), json(QJsonObject()) {}

Writer::~Writer() {}

QJsonObject Writer::getJson() const {
    return json;
}

void Writer::execute() {
    json = cpu.write(config);
}

QJsonObject Writer::release(const QString& cfg) {
    Writer w(cfg);
    w.execute();
    return w.getJson();
}