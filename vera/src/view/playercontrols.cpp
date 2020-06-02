#include <view/playercontrols.hpp>

PlayerControls::PlayerControls(QWidget* parent)
    : QWidget(parent), state(QMediaPlayer::StoppedState), volume(nullptr), muted(false), rate(nullptr), playBut(nullptr), stopBut(nullptr), nextBut(nullptr), prevBut(nullptr), muteBut(nullptr) {
        assignment();
    }

PlayerControls::~PlayerControls() {}

void PlayerControls::assignment() {
    // Define Play button
    playBut = new QToolButton(this);
    playBut->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playBut, &QAbstractButton::clicked, this, &PlayerControls::playClicked);

    // Define Stop button
    stopBut = new QToolButton(this);
    stopBut->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    connect(stopBut, &QAbstractButton::clicked, this, &PlayerControls::stop);

    // Define Next button
    nextBut = new QToolButton(this);
    nextBut->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    connect(nextBut, &QAbstractButton::clicked, this, &PlayerControls::next);

    // Define Previous button
    prevBut = new QToolButton(this);
    prevBut->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    connect(prevBut, &QAbstractButton::clicked, this, &PlayerControls::previous);

    // Define Mute button
    muteBut = new QToolButton(this);
    muteBut->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));
    connect(muteBut, &QAbstractButton::clicked, this, &PlayerControls::muteClicked);

    // Define Volume slider
    volume = new QSlider(Qt::Horizontal, this);
    volume->setRange(0, 100);
    connect(volume, &QSlider::valueChanged, this, &PlayerControls::onVolumeSliderValueChanged);

    // Define Rate box
    rate = new QComboBox(this);
    rate->addItem("0.5x", QVariant(0.5));
    rate->addItem("1.0x", QVariant(1.0));
    rate->addItem("2.0x", QVariant(2.0));
    connect(rate, QOverload<int>::of(&QComboBox::activated), this, &PlayerControls::updateRate);

    // Set position of each widgets
    QBoxLayout *layout = new QHBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(stopBut);
    layout->addWidget(prevBut);
    layout->addWidget(playBut);
    layout->addWidget(nextBut);
    layout->addWidget(muteBut);
    layout->addWidget(volume);
    layout->addWidget(rate);
    setLayout(layout);
}

QMediaPlayer::State PlayerControls::getState() const {
    return state;
}

void PlayerControls::setState(QMediaPlayer::State s) {
    // Check if states are differents
    if (s != state) {
        // Update state
        state = s;

        switch (s) {
            case QMediaPlayer::StoppedState:
                stopBut->setEnabled(false);
                playBut->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                break;
            case QMediaPlayer::PlayingState:
                stopBut->setEnabled(true);
                playBut->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
                break;
            case QMediaPlayer::PausedState:
                stopBut->setEnabled(true);
                playBut->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
                break;
        } 
    }
}

int PlayerControls::getVolume() const {
    // Convert slider value to audio linear volume
    qreal linearVolume = QAudio::convertVolume(volume->value() / qreal(100), QAudio::LogarithmicVolumeScale, QAudio::LinearVolumeScale);
    
    // Return volume
    return qRound(linearVolume * 100);
}

void PlayerControls::setVolume(int v) {
    // Convert volume to slider value
    qreal logarithmicVolume = QAudio::convertVolume(v / qreal(100), QAudio::LinearVolumeScale, QAudio::LogarithmicVolumeScale);

    // Update slider value
    volume->setValue(qRound(logarithmicVolume * 100));
}

bool PlayerControls::isMuted() const {
    return muted;
}

void PlayerControls::setMuted(bool m) {
    // Check if muted states are diffrent
    if (m != muted) {
        // Update muted state
        muted = m;

        // Update Icon
        muteBut->setIcon(style()->standardIcon(m ? QStyle::SP_MediaVolumeMuted : QStyle::SP_MediaVolume));
    }
}

void PlayerControls::playClicked() {
    // Check state
    switch (state) {
        case QMediaPlayer::StoppedState:
        case QMediaPlayer::PausedState:
            emit play();
            break;
        case QMediaPlayer::PlayingState:
            emit pause();
            break;
    }
}

void PlayerControls::muteClicked() {
    emit changeMuting(!muted);
}

qreal PlayerControls::getRate() const {
    // Return playback rate
    return rate->itemData(rate->currentIndex()).toDouble();
}

void PlayerControls::setRate(float r) {
    for (int i = 0; i < rate->count(); ++i) {
        if (qFuzzyCompare(r, float(rate->itemData(i).toDouble()))) {
            rate->setCurrentIndex(i);
            return;
        }
    }

    rate->addItem(QString("%1x").arg(r), QVariant(r));
    rate->setCurrentIndex(rate->count() - 1);
}

void PlayerControls::updateRate() {
    emit changeRate(getRate());
}

void PlayerControls::onVolumeSliderValueChanged() {
    emit changeVolume(getVolume());
}