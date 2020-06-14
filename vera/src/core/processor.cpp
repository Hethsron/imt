#include <core/processor.hpp>

Processor::Processor()
    : QObject() {}

Processor::~Processor() {}

QJsonObject Processor::write(const QString& cfg) const {
    QDir dir(cfg);
    
    // Define QJsonObject instance
	QJsonObject obj;

    // Check if given directory exists
    if (dir.exists()) {
        // Set entry lists to find
        QStringList list = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDir::Name);

        // Define pattern of regex
		QString pattern = QString("^(Ambiant(s)?|Annotation(s)?|Kinect|Robot(s)?|Wearable(s)?|Xsens)$");
		
        // Define regex
        QRegularExpression re(pattern, QRegularExpression::CaseInsensitiveOption);

        // Define iterator
        QStringListIterator iterator(list);
        while(iterator.hasNext()) {
            const QString str = iterator.next();
            QRegularExpressionMatch match = re.match(str);

            // Check if finded directory match with regex
            if (match.hasMatch()) {
                
                // Save configuration data
                obj[str] = dir.filePath(str);
            }
        }
    }

    // Returns configuration data
    return obj;
}

QList<QUrl> Processor::writeBack(const QString& cfg) const {
    // Define URLs
    QList<QUrl> urls;

    // Define directory
    QDir dir(cfg);

    // Check if given directory exists
    if (dir.exists()) {
        // Set filter
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

        // Set sorting
        dir.setSorting(QDir::Name | QDir::Reversed);

        // Define entry list
        QStringList list = dir.entryList(QStringList() << "*.avi" << "*.mp4" << "*.wmv", QDir::Files | QDir::Readable | QDir::Writable);

        // Define iterator
        QStringListIterator iterator(list);
        while (iterator.hasNext()) {
            const QString str = iterator.next();
            
            // Append URL
            urls.append(QUrl::fromLocalFile(dir.filePath(str)));
        }
    }

    // Returns URLs
    return urls;
}

QString Processor::read(const QJsonDocument& cfg, const QString& pattern) const {
    QJsonObject obj = cfg.object();

    // Define founded data
    QString result;

    // Check if QJsonObject instance is empty
    if (!obj.isEmpty()) {
        // Set entry list to compare
        QStringList list = obj.keys();

        // Define regex
        QRegularExpression re(pattern, QRegularExpression::CaseInsensitiveOption);

        // Define iterator
        QStringListIterator iterator(list);
        while(iterator.hasNext()) {
            const QString str = iterator.next();
            QRegularExpressionMatch match = re.match(str);

            // Check if finded key match with given pattern regex
            if (match.hasMatch()) {

                // Save distinguished name
                result = obj.take(str).toString();

                // Leave loop
                break;
            }
        }
    }

    return result;
}

QList<QStringList> Processor::deepRead(const QString& cfg) const {
    QList<QStringList> assets;

    // Define root directory
    QDir root(cfg);

    // Check if root directory exists
    if (root.exists()) {
        // Get and sort inner directory in list
        QStringList list = root.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDir::Name);

        // Define activity pattern
        QString act = QString("^(a\\d+)$");

        // Define activity regex
        QRegularExpression actReg(act, QRegularExpression::CaseInsensitiveOption);

        // Define activity iterator
        QStringListIterator actIterator(list);
        while (actIterator.hasNext()) {
            const QString actStr = actIterator.next();
            QRegularExpressionMatch actMatch = actReg.match(actStr);

            // Check if finded key match with given pattern regex
            if (actMatch.hasMatch()) {
                // Define child directory
                QDir child(root.filePath(actStr));

                // Check if child directory exists
                if (child.exists()) {
                    // Define asset
                    QStringList asset;

                    // Cet and sort inner directory in list
                    QStringList ls = child.entryList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks, QDir::Name);

                    // Define subject pattern
                    QString subj = QString("^(s\\d+)$");

                    // Define subject regex
                    QRegularExpression subjReg(subj, QRegularExpression::CaseInsensitiveOption);

                    // Define subject iterator
                    QStringListIterator subjIterator(ls);
                    while (subjIterator.hasNext()) {
                        const QString subjStr = subjIterator.next();
                        QRegularExpressionMatch subjMatch = subjReg.match(subjStr);

                        // Check if finded key match with given pattern regex
                        if (subjMatch.hasMatch()) {

                            // Append subject in subjects list
                            asset.append(child.filePath(subjStr));
                        }
                    }

                    // Append subjects list in activities list
                    assets.append(asset);
                }
            }
        }
    }

    return assets;
}

bool Processor::isPlaylist(const QUrl& url) {
    // Check if url is not a local file
    if (!url.isLocalFile()) {
        return false;
    }

    // Define file information
    const QFileInfo fileInfo(url.toLocalFile());

    return (fileInfo.exists() && !fileInfo.suffix().compare(QLatin1String("m3u"), Qt::CaseInsensitive));
}

void Processor::read(QVideoFrame frame, int level) {
    // Define histogram data
    QVector<qreal> histogram(level);

    do {
        // Check if level is null
        if (!level) {
            // Leave loop
            break;
        }

        // Check if frame map is not on readonly
        if (!frame.map(QAbstractVideoBuffer::ReadOnly)) {
            // Leave loop
            break;
        }

        // Check frame pixel format
        if (frame.pixelFormat() == QVideoFrame::Format_YUV420P || frame.pixelFormat() == QVideoFrame::Format_NV12) {
            // Read YUV data
            uchar* b = frame.bits();
            for (int i = 0; i < frame.height(); ++i) {
                // Get last pixel
                uchar* lastPixel = b + frame.width();
                for (uchar* currentPixel = b; currentPixel < lastPixel; ++currentPixel) {
                    histogram[(*currentPixel * level) >> 8] += 1.0;
                }
                // Update YUV data
                b += frame.bytesPerLine();
            }
        }
        else {
            // Get image format
            QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());

            // Check if format is valid
            if (imageFormat != QImage::Format_Invalid) {
                // Read RGB data
                QImage image(frame.bits(), frame.width(), frame.height(), imageFormat);
                
                // Convert RGB data to RGB format
                image = image.convertToFormat(QImage::Format_RGB32);
                const QRgb* b = (const QRgb*) image.bits();
                for (int i = 0; i < image.height(); ++i) {
                    // Get last pixel
                    const QRgb* lastPixel = b + frame.width();
                    for (const QRgb* currentPixel = b; currentPixel < lastPixel; ++currentPixel) {
                        histogram[(qGray(*currentPixel) * level) >> 8] += 1.0;
                    }

                    // Update RGB data
                    b = (const QRgb*) ((uchar*) b + image.bytesPerLine());
                }
            }
        }

        // Find maximum value
        qreal maxValue = 0.0;
        for (int i = 0; i < histogram.size(); ++i) {
            // Check maximum value
            if (histogram[i] > maxValue) {
                // Update max value
                maxValue = histogram[i];
            }
        }

        // Check max value
        if (maxValue > 0.0) {
            for (int i = 0; i < histogram.size(); ++i) {
                histogram[i] /= maxValue;
            }
        }

        // Unmap frame
        frame.unmap();
    } 
    while (false);


    // Send signal
    emit histogramReady(histogram);
}