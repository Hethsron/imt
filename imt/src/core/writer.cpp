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

namespace WRITER {
    QJsonObject execute(const QString& cfg) {
        Writer writer(cfg);
        writer.execute();
        return writer.getJson();
    }
}