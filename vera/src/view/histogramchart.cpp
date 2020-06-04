#include <view/histogramchart.hpp>

HistogramChart::HistogramChart(QWidget* parent)
    : QWidget(parent), audio(QVector<AudioChart*>()), histogram(QVector<qreal>()), isBusy(false), level(128) {
        // Move inner processor to thread
        cpu.moveToThread(&thread);

        // Register meta type
        qRegisterMetaType<QVector<qreal>>("QVector<qreal>");
        connect(&cpu, &Processor::histogramReady, this, &HistogramChart::setHistogram);

        // Starting thread with lowest priority
        thread.start(QThread::LowestPriority);

        // Setting layout
        setLayout(new QHBoxLayout());
    }

HistogramChart::~HistogramChart() {
    // Leave thread
    thread.quit();

    // Wiating 10 seconds
    thread.wait(10000);
}

void HistogramChart::setLevel(int lv) {
    // Update level
    level = lv;
}

void HistogramChart::readFrame(const QVideoFrame& frame) {
    // Check if histogram chart is busy
    if (isBusy && frame.isValid()) {
        // Leave function
        return;
    }

    // Update status
    isBusy = true;

    // Invoke connexion to another method
    QMetaObject::invokeMethod(&cpu, "read", Qt::QueuedConnection, Q_ARG(QVideoFrame, frame), Q_ARG(int, level));
}

void HistogramChart::readBuffer(const QAudioBuffer& buffer) {
    // Check if channels count are different
    if (audio.count() != buffer.format().channelCount()) {
        // Delete all audio chart viewer
        qDeleteAll(audio);

        // Clear audio chart viewer
        audio.clear();

        for (int i = 0; i < buffer.format().channelCount(); ++i) {
            AudioChart *level = new AudioChart(this);
            audio.append(level);
            layout()->addWidget(level);
        }
    }

    QVector<qreal> levels = getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i) {
        // Setting level
        audio.at(i)->setLevel(levels.at(i));
    }
}

void HistogramChart::setHistogram(const QVector<qreal>& hist) {
    // Update status
    isBusy = false;

    // Update histogram
    histogram = hist;

    // Update histogram chart
    update();
}

void HistogramChart::paintEvent(QPaintEvent* event) {
    // Deactive event
    Q_UNUSED(event);

    // Check if audio chart viewers is not empty
    if (!audio.isEmpty()) {
        // Leave function
        return;
    }

    // Define a painter
    QPainter painter(this);

    // Check if histogram chart inner data is empty
    if (histogram.isEmpty()) {
        // Draw histogram chart
        painter.fillRect(0, 0, width(), height(), QColor::fromRgb(0, 0, 0));

        // Leave function
        return;
    }

    // Define histogram chart bar width
    qreal barWidth = width() / (qreal) histogram.size();

    for (int i = 0; i < histogram.size(); ++i) {
        // Define histogram bar height
        qreal barHeight = histogram[i] * height();

        // Draw histogram chart level
        painter.fillRect(barWidth * i, height() - barHeight, barWidth * (i + 1), height(), Qt::red);

        // Clear the rest of the control
        painter.fillRect(barWidth * i, 0, barWidth * (i + 1), height() - barHeight, Qt::black);
    }
}

qreal HistogramChart::getPeakValue(const QAudioFormat& format) const {
    // Check if format is not valid
    if (!format.isValid()) {
        // Return null peak value
        return qreal(0);
    }

    // Check if codec is wrong
    if (format.codec() != "audio/pcm") {
        // Return null peak value
        return qreal(0);
    }

    switch (format.sampleType()) {
        case QAudioFormat::Unknown:
            break;
        case QAudioFormat::Float:
            // Check if format size is not equal to 32
            if (format.sampleSize() != 32) {
                // Return null peak value
                return qreal(0);
            }
            return qreal(1.00003);
            break;
        case QAudioFormat::SignedInt:
            // Check if format size is equal to 32
            if (format.sampleSize() == 32) {
                return qreal(INT_MAX);
            }

            // Check if format size is equal to 16
            if (format.sampleSize() == 16) {
                return qreal(SHRT_MAX);
            }

            // Check if format size is equal to 8
            if (format.sampleSize() == 8) {
                return qreal(CHAR_MAX);
            }
            break;
        case QAudioFormat::UnSignedInt:
            // Check if format size is equal to 32
            if (format.sampleSize() == 32) {
                return qreal(UINT_MAX);
            }

            // Check if format size is equal to 16
            if (format.sampleSize() == 16) {
                return qreal(USHRT_MAX);
            }

            // Check if format size is equal to 8
            if (format.sampleSize() == 8) {
                return qreal(UCHAR_MAX);
            }
            break;
    }

    // Return null peak value
    return qreal(0);
}

template <class T>
QVector<qreal> getBufferLevel(const T* buffer, int frame, int channel) {
    // Define max value
    QVector<qreal> maxValue;
    maxValue.fill(0, channel);

    for (int i = 0; i < frame; ++i) {
        for (int j = 0; j < channel; ++j) {
            // Get value
            qreal value = qAbs(qreal(buffer[i * channel + j]));

            // Check if value is maximum
            if (value > maxValue.at(j)) {
                // Replace max value
                maxValue.replace(j, value);
            }
        }
    }

    // Return audio buffer levels
    return maxValue;
}

QVector<qreal> HistogramChart::getBufferLevels(const QAudioBuffer& buffer) const {
    // Define max value
    QVector<qreal> maxValue;

    // Check if buffer is not valid
    if (!buffer.isValid()) {
        return maxValue;
    }

    // Check if buffer format is not valid
    if (!buffer.format().isValid()) {
        return maxValue;
    }

    // Check if buffer byte order format is different to little endian
    if (buffer.format().byteOrder() != QAudioFormat::LittleEndian) {
        return maxValue;
    }

    // Check if buffer codec format is wrong
    if (buffer.format().codec() != "audio/pcm") {
        return maxValue;
    }

    // Define channel count
    const int channelCount = buffer.format().channelCount();
    maxValue.fill(0, channelCount);

    // Get peak value
    qreal peakValue = getPeakValue(buffer.format());

    // Compare peak value
    if (qFuzzyCompare(peakValue, qreal(0))) {
        return maxValue;
    }

    switch (buffer.format().sampleType()) {
        case QAudioFormat::Unknown:
        case QAudioFormat::UnSignedInt:
            // Check  if buffer format size is equal to 32
            if (buffer.format().sampleSize() == 32) {
                maxValue = getBufferLevel(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
            }

            // Check  if buffer format size is equal to 16
            if (buffer.format().sampleSize() == 16) {
                maxValue = getBufferLevel(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
            }

            // Check  if buffer format size is equal to 8
            if (buffer.format().sampleSize() == 8) {
                maxValue = getBufferLevel(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
            }

            for (int i = 0; i < maxValue.size(); ++i) {
                maxValue[i] = qAbs(maxValue.at(i) - peakValue / 2) / (peakValue / 2);
            }
            break;
        case QAudioFormat::Float:
            // Check  if buffer format size is equal to 32
            if (buffer.format().sampleSize() == 32) {
                maxValue = getBufferLevel(buffer.constData<float>(), buffer.frameCount(), channelCount);
            }

            for (int i = 0; i < maxValue.size(); ++i) {
                maxValue[i] /= peakValue;        
            }
            break;
        case QAudioFormat::SignedInt:
            // Check  if buffer format size is equal to 32
            if (buffer.format().sampleSize() == 32) {
                maxValue = getBufferLevel(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
            }

            // Check  if buffer format size is equal to 16
            if (buffer.format().sampleSize() == 16) {
                maxValue = getBufferLevel(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
            }

            // Check  if buffer format size is equal to 8
            if (buffer.format().sampleSize() == 8) {
                maxValue = getBufferLevel(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
            }

            for (int i = 0; i < maxValue.size(); ++i) {
                maxValue[i] /= peakValue;
            }
            break;
    }

    // Retun max value
    return maxValue;
}