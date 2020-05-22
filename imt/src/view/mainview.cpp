#include <view/mainview.hpp>
#include <core/boxes.hpp>

MainView::MainView(QWidget* parent) 
    : QMainWindow(parent), widget(new QWidget()), statusBar(new QStatusBar()), menuBar(new QMenuBar()) {
        Boxes infos;
        resize(infos.getWidth(), infos.getHeight());
        setWindowTitle(infos.getTitle());
        setWindowIcon(QIcon(infos.getIcon()));
        setCentralWidget(widget);

        createActions();
        createStatusBar();
    }

MainView::~MainView() {}

void MainView::closeEvent(QCloseEvent *event) {
    Boxes infos;
    QMessageBox msg;
    msg.setText("Quit and close workspace ?");
    msg.setInformativeText(infos.getMessage());
    msg.setStandardButtons(QMessageBox::Save | QMessageBox::Close | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Save);
    int reply = msg.exec();

    switch (reply) {
    case QMessageBox::Save:
        // Save was clicked
        break;
    case QMessageBox::Close:
        // Don't Save was clicked
        event->accept();
        break;
    case QMessageBox::Cancel:
        // Cancel was clicked
        event->ignore();
        break;
    default:
        // should never be reached
        break;
    }
}

void MainView::createActions() {
    Boxes infos;
    menuBar->setStyleSheet(infos.getStyle());
    
    /*QMenu* file =*/ menuBar->addMenu("File");
    /*QMenu* edit =*/ menuBar->addMenu("Edit");
    /*QMenu* select =*/ menuBar->addMenu("Select");
    /*QMenu* view =*/ menuBar->addMenu("View");
    /*QMenu* tools =*/ menuBar->addMenu("Tools");
    /*QMenu* help =*/ menuBar->addMenu("Help");

    // Save MenuBar
    setMenuBar(menuBar);
}

void MainView::createStatusBar() {
    Boxes infos;
    statusBar->setStyleSheet(infos.getStyle());
    statusBar->showMessage("Ready");

    // Save StatusBar
    setStatusBar(statusBar);
}