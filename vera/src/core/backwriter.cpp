#include <core/backwriter.hpp>

BackWriter::BackWriter(const QString& cfg)
    : Command(), config(cfg), urls(QList<QUrl>()) {}

BackWriter::~BackWriter() {}

QList<QUrl> BackWriter::getUrls() const {
    return urls;
}

void BackWriter::execute() {
    urls = cpu.writeBack(config);
}

QList<QUrl> BackWriter::release(const QString& cfg) {
    BackWriter w(cfg);
    w.execute();
    return w.getUrls();
}