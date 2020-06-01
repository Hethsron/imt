#include <view/videoview.hpp>

VideoView::VideoView(QWidget* parent)
    : QVideoWidget(parent) {
        // Ignore size policy
        setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        
        // Setting palette
        QPalette p = palette();
        p.setColor(QPalette::Window, Qt::gray);
        setPalette(p);

        // Setting attribute
        setAttribute(Qt::WA_OpaquePaintEvent);
    }

VideoView::~VideoView() {}

void VideoView::keyPressEvent(QKeyEvent* event) {
    // Check if user press key escape
    if (event->key() == Qt::Key_Escape && isFullScreen()) {
        setFullScreen(false);
        event->accept();
    }
    // Check if user press key Enter
    else if (event->key() == Qt::Key_Enter && event->modifiers() & Qt::Key_Alt) {
        setFullScreen(!isFullScreen());
        event->accept();
    } 
    else {
        QVideoWidget::keyPressEvent(event);
    }
}

void VideoView::mouseDoubleClickEvent(QMouseEvent* event) {
    setFullScreen(!isFullScreen());
    event->accept();
}

void VideoView::mousePressEvent(QMouseEvent* event) {
    QVideoWidget::mousePressEvent(event);
}