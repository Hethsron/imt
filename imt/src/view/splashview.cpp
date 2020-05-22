#include <view/splashview.hpp>
#include <core/boxes.hpp>

SplashView::SplashView(QWidget* parent)
    : QSplashScreen(parent), progress(0) {
        assignment();
    }

SplashView::~SplashView() {}

void SplashView::assignment() {
    Boxes infos;
    setPixmap(QPixmap(infos.getBackground()));
    setWindowFlag(Qt::WindowTransparentForInput);
    setWindowIcon(QIcon(infos.getIcon()));

    // Moving splash screen in the center of screen
    QSize size = QApplication::screens()[0]->size();
    move((size.width() / 2) - (frameSize().width() / 2), (size.height() / 2) - (frameSize().height() / 2));

    showMessage("Powered by the Visual Studio ® Plateform", Qt::AlignBottom, Qt::white);
}

int SplashView::getProgress() const {
    return progress;
}

void SplashView::setProgress(const int value) {
    progress = value;
    if (progress >= 100) {
        progress = 100;
    }

    if (progress < 0) {
        progress = 0;
    }

    repaint();
    QApplication::processEvents();
}

void SplashView::setMessage(const QString& message) {
    clearMessage();
    showMessage(message, Qt::AlignBottom, Qt::white);
}

void SplashView::drawContents(QPainter* painter) {
    QSplashScreen::drawContents(painter);

    // Setting style for progress bar
    QStyleOptionProgressBar pbStyle;
    pbStyle.initFrom(this);
    pbStyle.state = QStyle::State_Enabled;
    pbStyle.textVisible = false;
    pbStyle.minimum = 0;
    pbStyle.maximum = 100;
    pbStyle.progress = progress;
    pbStyle.invertedAppearance = false;
    pbStyle.text = QString("%1%").arg(progress);
    pbStyle.textVisible = true;
    pbStyle.rect = QRect(QPoint(700, 700), QSize(500, 10));
    style()->drawControl(QStyle::CE_ProgressBar, &pbStyle, painter, this);
}