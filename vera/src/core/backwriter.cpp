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

QStringList BackWriter::compute(const QString& cfg) {
    // Define result
    QStringList result;

    // Loading directory
    QDir dir(cfg);

    // Check if directory exists
    if (dir.exists()) {
        // Set filter
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

        // Set sorting
        dir.setSorting(QDir::Time | QDir::Reversed);

        // Define entry list
        QStringList list = dir.entryList(QStringList() << "*.jsonl" << "*.json", QDir::Files | QDir::Readable | QDir::Writable);

        // Define iterator
        QStringListIterator iterator(list);
        while (iterator.hasNext()) {
            const QString str = iterator.next();
            
            // Append founded files
            result.append(dir.filePath(str));
        }
    }

    // Returns result
    return result;
}