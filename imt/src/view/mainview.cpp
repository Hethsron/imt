#include <view/mainview.hpp>
#include <core/writer.hpp>
#include <core/boxes.hpp>

MainView::MainView(QWidget* parent) 
    : QMainWindow(parent), widget(new QWidget()), statusBar(new QStatusBar()), menuBar(new QMenuBar()), fileMenu(new QMenu()), monitoringMenu(new QMenu()), editMenu(new QMenu()), viewMenu(new QMenu()), toolsMenu(new QMenu()), helpMenu(new QMenu()), monitoringToolBar(new QToolBar()), config(QJsonDocument()) {
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
        saveMonitoring();
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
    QString cfg = QFileDialog::getExistingDirectory(this,
            tr("Setting up configuration from sensors database"), "",
            QFileDialog::DontUseNativeDialog | QFileDialog::ShowDirsOnly | QFileDialog::ReadOnly | QFileDialog::DontResolveSymlinks);
    
    // Check if pathname if empty
    if (cfg.isEmpty()) {
        statusBar->showMessage(tr("Unable to set up configuration from sensors database"));
        return;
    }
    else {
        QDir dir(cfg);

        // Check if directory exists
        if (!dir.exists()) {
            QMessageBox::information(this, 
                    tr("Unable to find sensors database"),
                    tr("Selected sensors database [%s] doesn't exists", cfg.toStdString().c_str()));
            return;
        }

        // Update configuration
        config.setObject(Writer::release(cfg));

        // Create monitoring toolbar
        createMonitoringToolBar();

        // TODO : Implementation (Navigation bar)
    }
}

void MainView::openMonitoring() {
    QString filename = QFileDialog::getOpenFileName(this,
            tr("Open configuration file"), "",
            tr("Configuration File (*.json)"), nullptr,
            QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly);

    // Check if file name is empty
    if (filename.isEmpty()) {
        statusBar->showMessage(tr("Unable to open configuration file"));
        return;
    }
    else {
        QFile file(filename);

        // Check if file is not open on readonly
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::information(this, 
                    tr("Unable to open configuration file"),
                    file.errorString());
            return;
        }

        // Read data configuration
        const QString data = file.readAll();

        // Close file stream
        file.close();

        // Parse data configuration to Json format
        config = QJsonDocument::fromJson(data.toUtf8());


        // Check if config file is empty
        if (config.isEmpty()) {
            QMessageBox::information(this, 
                    tr("No configuration in file"),
                    tr("The file you are attempting to open contains no configuration"));
        }
        else {
            
            // Create monitoring toolbar
            createMonitoringToolBar();

            // TODO : Implementation (Navigation bar)
        }
    }
}

void MainView::saveMonitoring() {
    // Check if config is empty
    if (config.isEmpty()) {
        QMessageBox::information(this, 
                    tr("No configuration in the application system"),
                    tr("The configuration you are attempting to save doesn't exist yet"));
            return;
    }
    else {
        Boxes infos;
        QFile file(infos.getConfig());

        // Check if file is not open on writeonly
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate)) {
            QMessageBox::information(this, 
                    tr("Unable to save configuration file"),
                    file.errorString());
            return;
        }

        // Write Json file
        file.write(config.toJson());

        // Close file stream
        file.close();

        // Show success message
        statusBar->showMessage(tr("Configuration file saved"));
    }
}

void MainView::saveAsMonitoring() {
    QString filename = QFileDialog::getSaveFileName(this, 
            tr("Save configuration file under a new name"), "", 
            tr("Configuration file (*.json)"));

    // Check if filename is empty
    if (filename.isEmpty()) {
        statusBar->showMessage("Cannot save configuration file under new name");
        return;
    }
    else {
        // Check if config is empty
        if (config.isEmpty()) {
            QMessageBox::information(this, 
                    tr("No configuration in the application system"),
                    tr("The configuration you are attempting to save doesn't exist yet"));
            return;
        }
        else {
            QFile file(filename);

            // Check if file is not open on writeonly
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Truncate)) {
                QMessageBox::information(this, 
                        tr("Unable to save configuration file"),
                        file.errorString());
                return;
            }

            // Write Json file
            file.write(config.toJson());

            // Close file stream
            file.close();

            // Show success message
            statusBar->showMessage(tr("Configuration file saved under new name"));
        }
    }
}

void MainView::closeMonitoring() {
    // TODO : Implementation

    // Removes all actions from the toolbar
    monitoringToolBar->clear();

    // Remove configuration data from the system
    if (!config.isEmpty()) {
        config = QJsonDocument();
    }
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
    saveAsAct->setStatusTip(tr("Save the configuration file under new name"));
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
    const QIcon extractIcon = QIcon(infos.getCollections()[9]);

    // Setting XEF toolkit Action
    QAction* xefAct = new QAction(extractIcon, tr("&XEF toolkit          "), this);
    xefAct->setStatusTip(tr("Extracting Kinect Studio XEF files on multiple platforms format"));
    xefAct->setIconVisibleInMenu(true);
    // TODO : connect
    toolsMenu->addAction(xefAct);

    // Adding seperator
    toolsMenu->addSeparator();

    // Setting MVN toolkit Action
    QAction* mvnAct = new QAction(extractIcon, tr("&MVN toolkit         "), this);
    mvnAct->setStatusTip(tr("Extracting Xsens MVN files on multiple platforms format"));
    mvnAct->setIconVisibleInMenu(true);
    // TODO : connect
    toolsMenu->addAction(mvnAct);
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