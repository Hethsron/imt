#include <view/audiochart.hpp>

AudioChart::AudioChart(QWidget* parent)
    : QWidget(parent), level(0) {
        // Set minimum and maximum height of audio chart on media player
        setMinimumHeight(15);
        setMaximumHeight(50);
    }

AudioChart::~AudioChart() {}

void AudioChart::setLevel(qreal lv) {
    // Check if levels are diffrent
    if (level != lv) {
        // Update level
        level = lv;
        // Repaint chart
        update();
    }
}

void AudioChart::paintEvent(QPaintEvent* event) {
    // Deactive event
    Q_UNUSED(event);

    // Define a painter
    QPainter painter(this);

    // Draw level in audio chart on media player
    painter.fillRect(0, 0, level * width(), height(), Qt::red);

    // Clear the rest of the control
    painter.fillRect(level * width(), 0, width(), height(), Qt::black);
}