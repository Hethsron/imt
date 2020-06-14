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

void DeepReader::sort(QStringList* frames) {
    QList<int> array;

    // Define digit regex, that represents zero or more numbers
    QRegExp re("\\d*");

    // Get frame number to array
    for (int i = 0; i < frames->size(); ++i) {
        const QString finded = frames->at(i).split("frame").at(1).split(".png").at(0);
        
        // Check if finded is digit
        if (re.exactMatch(finded)) {

            // Convert digit to integer
            array.append(finded.toInt());
        }
    }

    // Sort array
    for (int i = 0; i < array.size() - 1; ++i) {
        // Define minimum
        int min = i;

        // Find the minimum value in unsorted array
        for (int j = i + 1; j < array.size(); ++j) {
            if (array[j] < array[min]) {
                min = j;
            }
        }

        // Swap the founded minimum element with the first one
        if (min != i) {
            int temp = array[min];
            array[min] = array[i];
            array[i] = temp;
        }
    }

    QRegExp reg("\\d*.png");
    QString prefix = frames->at(0).split(reg).at(0);

    // Clear depth files
    frames->clear();

    for (int i = 0; i < array.size(); ++i) {
        const QString fileName = prefix +  QString::number(i) + QString(".png");
        frames->append(fileName);
    }

    // Clear sorted array
    array.clear();
}

QList<QStringList> DeepReader::release(const QString& cfg) {
    DeepReader dr(cfg);
    dr.execute();
    return dr.getAssets();
}