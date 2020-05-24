#include <view/mainview.hpp>
#include <core/boxes.hpp>

MainView::MainView(QWidget* parent) 
    : QMainWindow(parent), widget(new QWidget()), statusBar(new QStatusBar()), menuBar(new QMenuBar()), fileMenu(new QMenu()), monitoringMenu(new QMenu()), editMenu(new QMenu()), viewMenu(new QMenu()), toolsMenu(new QMenu()), helpMenu(new QMenu()), monitoringToolBar(new QToolBar()) {
        Boxes infos;
        resize(infos.getWidth(), infos.getHeight());
        setWindowTitle(infos.getTitle());
        setWindowIcon(QIcon(infos.getIcon()));
        setCentralWidget(widget);
        setStyleSheet(infos.getStyleSheet());
        
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
    createMonitoringMenu();
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

void MainView::newMonitoring() {
    QFileDialog dialog(this);

    // Setting QFileDialog instance
    dialog.setWindowTitle("Setting up a configuration from a database");
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setOption(QFileDialog::DontUseNativeDialog, false);
    dialog.setOption(QFileDialog::ReadOnly, true);
    
    // Check if there is no error
    if (dialog.exec()) {
        // TODO : Implementation
        createMonitoringToolBar();
    }
    else {
        statusBar->showMessage("Cannot setting up a configuration from a database");
    }
}

void MainView::openMonitoring() {
    QFileDialog dialog(this);

    // Setting QFileDialog instance
    dialog.setWindowTitle("Open a configuration file from a previous database");
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setOption(QFileDialog::DontUseNativeDialog, false);
    dialog.setOption(QFileDialog::ReadOnly, true);
    dialog.setNameFilter(tr("Files (*.json)"));

    // Check if there is no error
    if (dialog.exec()) {
        // TODO : Implementation
        createMonitoringToolBar();
    }
    else {
        statusBar->showMessage("Cannot open a configuration file from a previous database");
    }
}

void MainView::saveMonitoring() {
    // TODO : Implementation
}

void MainView::saveAsMonitoring() {
    // TODO : Implementation
}

void MainView::closeMonitoring() {
    // TODO : Implementation
}

void MainView::createFileMenu() {
    Boxes infos;
    fileMenu = menuBar->addMenu(tr("&File"));

    // Setting Icons
    const QIcon exitIcon = QIcon(infos.getCollections()[3]);
    const QIcon configIcon = QIcon(infos.getCollections()[11]);

    // Setting Configuration Action
    QAction* configAct = new QAction(configIcon, tr("&Configuration  "), this);
    configAct->setStatusTip(tr("Security configuration"));
    configAct->setIconVisibleInMenu(true);
    // TODO : connect
    fileMenu->addAction(configAct);

    // Adding seperator
    fileMenu->addSeparator();

    // Setting Exit Action
    QAction* exitAct = new QAction(exitIcon, tr("&Exit          "), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    exitAct->setIconVisibleInMenu(true);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAct);
}

void MainView::createMonitoringMenu() {
    Boxes infos;
    monitoringMenu = menuBar->addMenu(tr("&Monitoring"));

    // Setting Icons
    const QIcon newIcon = QIcon(infos.getCollections()[0]);
    const QIcon openIcon = QIcon(infos.getCollections()[1]);
    const QIcon saveIcon = QIcon(infos.getCollections()[2]);
    const QIcon closeIcon = QIcon(infos.getCollections()[3]);

    // Setting New Action
    QAction* newAct = new QAction(newIcon, tr("&New         "), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Setting up a configuration from a database"));
    newAct->setIconVisibleInMenu(true);
    connect(newAct, &QAction::triggered, this, &MainView::newMonitoring);
    monitoringMenu->addAction(newAct);

    // Setting Open Action
    QAction* openAct = new QAction(openIcon, tr("&Open...           "), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a configuration file from a previous database"));
    openAct->setIconVisibleInMenu(true);
    connect(openAct, &QAction::triggered, this, &MainView::openMonitoring);
    monitoringMenu->addAction(openAct);

    // Adding seperator
    monitoringMenu->addSeparator();

    // Setting Save Action
    QAction* saveAct = new QAction(saveIcon, tr("&Save          "), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the configuration file to disk"));
    saveAct->setIconVisibleInMenu(true);
    connect(saveAct, &QAction::triggered, this, &MainView::saveMonitoring);
    monitoringMenu->addAction(saveAct);

    // Setting Save As Action
    QAction* saveAsAct = new QAction(saveIcon, tr("&Save As...          "), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    saveAsAct->setStatusTip(tr("Save the configuration file under a new name"));
    saveAsAct->setIconVisibleInMenu(true);
    connect(saveAsAct, &QAction::triggered, this, &MainView::saveAsMonitoring);
    monitoringMenu->addAction(saveAsAct);

    // Adding seperator
    monitoringMenu->addSeparator();

    // Setting Exit Action
    QAction* closeAct = new QAction(closeIcon, tr("&Close       "), this);
    closeAct->setStatusTip(tr("Stop monitoring"));
    closeAct->setIconVisibleInMenu(true);
    connect(closeAct, &QAction::triggered, this, &MainView::closeMonitoring);
    monitoringMenu->addAction(closeAct);
}

void MainView::createMonitoringToolBar() {
    // Adding new ToolBar
    monitoringToolBar = addToolBar("Sensors");

    // Setting Ambiant Action
    QAction* ambiantAct = new QAction(tr("&Ambiant"), this);
    ambiantAct->setStatusTip(tr("Ambiant sensors data analysis"));
    // TODO : connect
    monitoringToolBar->addAction(ambiantAct);

    // Setting Kinect Action
    QAction* kinectAct = new QAction(tr("&Kinect"), this);
    kinectAct->setStatusTip(tr("Kinect sensor data analysis"));
    // TODO : connect
    monitoringToolBar->addAction(kinectAct);

    // Setting Robots Action
    QAction* robotsAct = new QAction(tr("&Robots"), this);
    robotsAct->setStatusTip(tr("Robots sensors data analysis"));
    // TODO : connect
    monitoringToolBar->addAction(robotsAct);

    // Setting Wearables Action
    QAction* wearablesAct = new QAction(tr("&Wearables"), this);
    wearablesAct->setStatusTip(tr("Wearables sensors data analysis"));
    // TODO : connect
    monitoringToolBar->addAction(wearablesAct);

    // Setting Xsens Action
    QAction* xsensAct = new QAction(tr("&Xsens"), this);
    xsensAct->setStatusTip(tr("Xsens sensors data analysis"));
    // TODO : connect
    monitoringToolBar->addAction(xsensAct);
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
    QAction* undoAct = new QAction(undoIcon, tr("&Undo          "), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last action"));
    undoAct->setIconVisibleInMenu(true);
    // TODO : connect
    editMenu->addAction(undoAct);

    // Setting Redo Action
    QAction* redoAct = new QAction(redoIcon, tr("&Redo          "), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last action"));
    redoAct->setIconVisibleInMenu(true);
    // TODO : connect
    editMenu->addAction(redoAct);

    // Adding separator
    editMenu->addSeparator();

    // Setting Cut Action
    QAction* cutAct = new QAction(cutIcon, tr("&Cut         "), this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    cutAct->setIconVisibleInMenu(true);
    // TODO : connect
    editMenu->addAction(cutAct);

    // Setting Copy Action
    QAction* copyAct = new QAction(copyIcon, tr("&Copy          "), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    copyAct->setIconVisibleInMenu(true);
    // TODO : connect
    editMenu->addAction(copyAct);

    // Setting Paste Action
    QAction* pasteAct = new QAction(pasteIcon, tr("&Paste           "), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    pasteAct->setIconVisibleInMenu(true);
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
    conversionAct->setIconVisibleInMenu(true);
    // TODO : connect
    toolsMenu->addAction(conversionAct);
}

void MainView::createHelpMenu() {
    Boxes infos;
    helpMenu = menuBar->addMenu(tr("&Help"));

    // Setting Icons
    const QIcon aboutIcon = QIcon(infos.getCollections()[10]);
    const QIcon summaryIcon = QIcon(infos.getCollections()[12]);
    
    // Setting Summary Action
    QAction* summaryAct = new QAction(summaryIcon, tr("&Summary...          "), this);
    summaryAct->setShortcuts(QKeySequence::HelpContents);
    summaryAct->setStatusTip(tr("Provide informations about application's functionalities and usage"));
    summaryAct->setIconVisibleInMenu(true);
    // TODO : connect
    helpMenu->addAction(summaryAct);

    // Adding separator
    helpMenu->addSeparator();

    // Setting Forums Action
    QAction* forumsAct = new QAction(tr("&Forums...         "), this);
    forumsAct->setStatusTip(tr("Self-help forum on IMT solution"));
    // TODO : connect
    helpMenu->addAction(forumsAct);

    // Setting Bug tracker
    QAction* bugAct = new QAction(tr("&Bug tracker...           "), this);
    bugAct->setStatusTip(tr("Reports suggestions for improvements in case you encounter problems"));
    // TODO : connect
    helpMenu->addAction(bugAct);

    // Adding separator
    helpMenu->addSeparator();

    // Setting About Action
    QAction* aboutAct = new QAction(aboutIcon, tr("&About IMT         "), this);
    aboutAct->setShortcuts(QKeySequence::WhatsThis);
    aboutAct->setStatusTip(tr("Provide informations about application's version and licences"));
    aboutAct->setIconVisibleInMenu(true);
    connect(aboutAct, &QAction::triggered, this, &MainView::about);
    helpMenu->addAction(aboutAct);
}