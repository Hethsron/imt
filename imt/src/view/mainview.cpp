#include <view/mainview.hpp>
#include <core/boxes.hpp>

MainView::MainView(QWidget* parent) 
    : QMainWindow(parent), widget(new QWidget()), statusBar(new QStatusBar()), menuBar(new QMenuBar()), fileMenu(new QMenu()), editMenu(new QMenu()), viewMenu(new QMenu()), toolsMenu(new QMenu()), helpMenu(new QMenu()) {
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

    // Creating menu toolbar
    createFileMenu();
    createEditMenu();
    createViewMenu();
    createToolsMenu();
    createHelpMenu();

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

void MainView::about() {
    QMessageBox::about(this, tr("About IMT"),
            tr("<b>IMT</b> "
            "<p>Version: 1.0.0 Release 1<br>"
            "Date: 2020-05-21<br>"
            "Dependencies : QT5 Framework<br>"
            "GPLv3+ : GNU GPL version 3 or later<br>"
            "© Copyright - UHA - ENSISA 2020</p>"));
}

void MainView::createFileMenu() {
    Boxes infos;
    fileMenu = menuBar->addMenu(tr("&File"));

    // Setting Icons
    const QIcon newIcon = QIcon(infos.getCollections()[0]);
    const QIcon openIcon = QIcon(infos.getCollections()[1]);
    const QIcon saveIcon = QIcon(infos.getCollections()[2]);
    const QIcon exitIcon = QIcon(infos.getCollections()[3]);

    // Setting New Action
    QAction* newAct = new QAction(newIcon, tr("&New File"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new config file"));
    // TODO : connect
    fileMenu->addAction(newAct);

    // Setting Open Action
    QAction* openAct = new QAction(openIcon, tr("&Open File..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing config file"));
    // TODO : connect
    fileMenu->addAction(openAct);

    // Setting Save Action
    QAction* saveAct = new QAction(saveIcon, tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the config file to disk"));
    // TODO : connect
    fileMenu->addAction(saveAct);

    // Adding seperator
    fileMenu->addSeparator();

    // Setting Exit Action
    QAction* exitAct = fileMenu->addAction(exitIcon, tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
}

void MainView::createEditMenu() {
    Boxes infos;
    editMenu = menuBar->addMenu(tr("&Edit"));

    // Setting Icons
    const QIcon undoIcon = QIcon(infos.getCollections()[4]);
    const QIcon redoIcon = QIcon(infos.getCollections()[5]);
    const QIcon cutIcon = QIcon(infos.getCollections()[6]);
    const QIcon copyIcon = QIcon(infos.getCollections()[7]);
    const QIcon pasteIcon = QIcon(infos.getCollections()[8]);

    // Setting Undo Action
    QAction* undoAct = new QAction(undoIcon, tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last action"));
    // TODO : connect
    editMenu->addAction(undoAct);

    // Setting Redo Action
    QAction* redoAct = new QAction(redoIcon, tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last action"));
    // TODO : connect
    editMenu->addAction(redoAct);

    // Adding separator
    editMenu->addSeparator();

    // Setting Cut Action
    QAction* cutAct = new QAction(cutIcon, tr("&Cut"), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    // TODO : connect
    editMenu->addAction(cutAct);

    // Setting Copy Action
    QAction* copyAct = new QAction(copyIcon, tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    // TODO : connect
    editMenu->addAction(copyAct);

    // Setting Paste Action
    QAction* pasteAct = new QAction(pasteIcon, tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    // TODO : connect
    editMenu->addAction(pasteAct);
}

void MainView::createViewMenu() {
    viewMenu = menuBar->addMenu(tr("&View"));
}

void MainView::createToolsMenu() {
    Boxes infos;
    toolsMenu = menuBar->addMenu(tr("&Tools"));

    // Setting Icons
    const QIcon conversionIcon = QIcon(infos.getCollections()[9]);

    // Setting Conversion Action
    QAction* conversionAct = new QAction(conversionIcon, tr("&Conversion"), this);
    conversionAct->setStatusTip(tr("Convert kinect files to more standard format files"));
    // TODO : connect
    toolsMenu->addAction(conversionAct);
}

void MainView::createHelpMenu() {
    Boxes infos;
    helpMenu = menuBar->addMenu(tr("&Help"));

    // Setting Icons
    const QIcon aboutIcon = QIcon(infos.getCollections()[10]);

    // Setting About Action
    QAction* aboutAct = new QAction(aboutIcon, tr("&About IMT"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &MainView::about);
    helpMenu->addAction(aboutAct);
}