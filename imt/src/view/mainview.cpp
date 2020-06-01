#include <view/mainview.hpp>
#include <view/helpbrowser.hpp>
#include <view/videoview.hpp>
#include <core/writer.hpp>
#include <core/boxes.hpp>

MainView::MainView(QWidget* parent) 
    : QMainWindow(parent), widget(new QWidget()), statusBar(new QStatusBar()), menuBar(new QMenuBar()), fileMenu(new QMenu()), recentFilesMenu(new QMenu()), monitoringMenu(new QMenu()), editMenu(new QMenu()), viewMenu(new QMenu()), toolsMenu(new QMenu()), helpMenu(new QMenu()), monitoringToolBar(new QToolBar()), config(QJsonDocument()), recentFilesAct(QList<QAction*>()), recentFiles(QStringList()), helpWindow(new QDockWidget()), player(nullptr), playlist(nullptr), videoWidget(nullptr), playlistModel(nullptr), controls(nullptr), playlistView(nullptr), playlistSlider(nullptr), playlistDuration(nullptr), playlistActivities(nullptr), playlistSubjects(nullptr), loadButton(nullptr), annotationButton(nullptr), editorButton(nullptr), isToolBar(false), isKinect(false) {
        Boxes infos;
        resize(infos.getWidth(), infos.getHeight());
        setWindowTitle(infos.getTitle());
        setWindowIcon(QIcon(infos.getIcon()));
        setCentralWidget(widget);
        setStyleSheet(infos.getStyleSheet());
        
        createHelpWindow();
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

void MainView::createHelpWindow() {
    Boxes infos;

    // Creating QHelpEngine instance
    QHelpEngine* helpEngine = new QHelpEngine(infos.getQHC());
    helpEngine->setupData();

    // Setting help window
    helpWindow = new QDockWidget(tr("&Help"), this);

    // Setting allowed areas for QDockWidget
    helpWindow->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // Setting splitter
    QSplitter* helpPanel = new QSplitter(Qt::Horizontal);

    // Setting help browser
    HelpBrowser* helpBrowser = new HelpBrowser(helpEngine);
    helpBrowser->setSource(QUrl("qthelp://imt.summary/doc/index.html"));

    // Setting tab widget
    QTabWidget* tabWidget = new QTabWidget();
    tabWidget->addTab((QWidget*) helpEngine->contentWidget(), tr("Summary"));
    tabWidget->addTab((QWidget*) helpEngine->indexWidget(), tr("Index"));

    helpPanel->insertWidget(0, tabWidget);
    helpPanel->insertWidget(1, helpBrowser);
    helpPanel->setStretchFactor(1, 1);

    helpWindow->setWidget(helpPanel);
    helpWindow->hide();
    
    connect((QWidget*) helpEngine->contentWidget(),SIGNAL(linkActivated(QUrl)), helpBrowser, SLOT(setSource(QUrl)));
    connect((QWidget*) helpEngine->indexWidget(), SIGNAL(linkActivated(QUrl, QString)), helpBrowser, SLOT(setSource(QUrl)));

    addDockWidget(Qt::RightDockWidgetArea, helpWindow);
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
            tr("<b>IMT ® Plateform</b> "
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

        // Check if tool bar exists
        if (!isToolBar) {
            // Create monitoring toolbar
            createMonitoringToolBar();
        }
        else {
            // Removes all actions from the toolbar
            monitoringToolBar->clear();

            // Create monitoring toolbar
            createMonitoringToolBar();
        }

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
            
            // Check if tool bar exists
            if (!isToolBar) {
                // Create monitoring toolbar
                createMonitoringToolBar();
            }
            else {
                // Removes all actions from the toolbar
                monitoringToolBar->clear();

                // Create monitoring toolbar
                createMonitoringToolBar();
            }

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

        // Store recent config file
        recentFiles.append(infos.getConfig());

        // Remove duplicates entry from list
        recentFiles.removeDuplicates();

        // Update recent actions
        updateRecentActions();

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

            // Store recent config file
            recentFiles.append(filename);

            // Remove duplicates entry from list
            recentFiles.removeDuplicates();

            // Update recent actions
            updateRecentActions();

            // Show success message
            statusBar->showMessage(tr("Configuration file saved under new name"));
        }
    }
}

void MainView::closeKinectVisualizer() {
    // Reset inner player
    if (player != nullptr) {
        player = nullptr;
    }

    // Reset inner playlist
    if (playlist != nullptr) {
        // Check if playlist is empty
        if (!playlist->isEmpty()) {
            playlist->clear();
        }
        playlist = nullptr;
    }

    // Close inner video widget
    if (videoWidget != nullptr) {
        // Check if video widget is closed
        if (videoWidget->close()) {
            videoWidget = nullptr;
        }
    }

    // Close inner playlist view
    if (playlistView != nullptr) {
        // Check if playlist view is closed
        if (playlistView->close()) {
            playlistView = nullptr;
        }
    }

    // Close inner playlist slider
    if (playlistSlider != nullptr) {
        // Check if playlist slider is closed
        if (playlistSlider->close()) {
            playlistSlider = nullptr;
        }
    }

    // Close inner playlist activities
    if (playlistActivities != nullptr) {
        // Check if playlist activities spinbox is closed
        if (playlistActivities->close()) {
            playlistActivities = nullptr;
        }
    }

    // Close inner playlist subjects
    if (playlistSubjects != nullptr) {
        // Check if playlist subjects spinbox is closed
        if (playlistSubjects->close()) {
            playlistSubjects = nullptr;
        }
    }

    // Close inner playlist controls
    if (controls != nullptr) {
        // Check if player controller is closed
        if (controls->close()) {
            controls = nullptr;
        }
    }

    // Close inner Upload button
    if (loadButton != nullptr) {
        // Check if Upload button is closed
        if (loadButton->close()) {
            loadButton = nullptr;
        }
    }

    // Close inner Annotation button
    if (annotationButton != nullptr) {
        // Check if Annotation button is closed
        if (annotationButton->close()) {
            annotationButton = nullptr;
        }
    }

    // Close inner Editor button
    if (editorButton != nullptr) {
        // Check if Editor button is closed
        if (editorButton->close()) {
            editorButton = nullptr;
        }
    }

    // Reset inner layout
    if (widget->layout() != nullptr) {
        // Check if widget is closed
        if (widget->close()) {
            // Define new widget
            widget = new QWidget();
            // Update central widget
            setCentralWidget(widget);
        }
    }

    // Reset status
    isKinect = false;
}

void MainView::closeMonitoring() {
    // Check if kinect visualizer has been enabled
    if (isKinect) {
        // Closing Kinect visualiser
        closeKinectVisualizer();
    }

    // Removes all actions from the toolbar
    monitoringToolBar->clear();
    isToolBar = false;

    // Remove configuration data from the system
    if (!config.isEmpty()) {
        config = QJsonDocument();
    }
}

void MainView::clearItems() {
    const int sizes = static_cast<int>(7);

    // Clear list of files
    if (!recentFiles.isEmpty()) {
        recentFiles.clear();

        for (int i = 0; i <= sizes; ++i) {
            recentFilesAct.at(i)->setVisible(false);
        }
    }
}

void MainView::openRecentFile(const QString& filename) {
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
            
            // Check if tool bar exists
            if (!isToolBar) {
                // Create monitoring toolbar
                createMonitoringToolBar();
            }
            else {
                // Removes all actions from the toolbar
                monitoringToolBar->clear();

                // Create monitoring toolbar
                createMonitoringToolBar();
            }

            // TODO : Implementation (Navigation bar)
        }
    }
}

void MainView::openRecent() {
    // Catching sended action
    QAction* action = qobject_cast<QAction*>(sender());
    
    // Check if sended action is not null
    if (action) {
        openRecentFile(action->text());
    }
}

void MainView::kinectVisualizer() {
    // Define inner player
    player = new QMediaPlayer(this);
    player->setAudioRole(QAudio::VideoRole);

    // Define inner playlist
    playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);
    // TODO : connect player

    // Define video widget
    videoWidget = new VideoView(this);
    player->setVideoOutput(videoWidget);

    // Define playlist model
    playlistModel = new PlayList(this);
    playlistModel->setPlaylist(playlist);

    // Define playlist view
    playlistView = new QListView(this);
    playlistView->setModel(playlistModel);
    playlistView->setCurrentIndex(playlistModel->index(playlist->currentIndex(), 0));
    // TODO : connect playlist view

    // Define playlist slider
    playlistSlider = new QSlider(Qt::Horizontal, this);
    playlistSlider->setRange(0, player->duration() / 1000);
    // TODO : connect playlist slider

    // Define playlist label duration
    playlistDuration = new QLabel(this);

    // Define playlist activities
    playlistActivities = new QSpinBox(this);
    playlistActivities->setPrefix(tr("Activity      "));
    playlistActivities->setRange(1, 100);
    playlistActivities->setStatusTip(tr("Choose the activity to be monitored"));

    // Define playlist subjects
    playlistSubjects = new QSpinBox(this);
    playlistSubjects->setPrefix(tr("Subject     "));
    playlistSubjects->setRange(1, 100);
    playlistSubjects->setStatusTip(tr("Choose the subject to be monitored"));

    // Define Upload push button
    loadButton = new QPushButton(tr("Upload"), this);
    loadButton->setStatusTip(tr("Upload kinect sensor database"));
    // TODO : connect annotation push button

    // Define Annotation push button
    annotationButton = new QPushButton(tr("Annotation"), this);
    annotationButton->setStatusTip(tr("Make annotations"));
    // TODO : connect annotation push button

    // Define Editor push button
    editorButton = new QPushButton(tr("Video Editor"), this);
    editorButton->setStatusTip(tr("Edit videos and record voice"));
    // TODO : connect editor push button

    // Define player control
    controls = new PlayerControls(this);
    controls->setState(player->state());
    controls->setVolume(player->volume());
    controls->setMuted(controls->isMuted());
    // TODO : connect controls

    // Define display layout
    QBoxLayout* displayLayout = new QHBoxLayout(this);
    displayLayout->addWidget(videoWidget, 2);
    displayLayout->addWidget(playlistView);
    
    // Define control layout
    QBoxLayout* controlLayout = new QHBoxLayout(this);
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(playlistActivities);
    controlLayout->addWidget(playlistSubjects);
    controlLayout->addWidget(loadButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(controls);
    controlLayout->addStretch(1);
    controlLayout->addWidget(annotationButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(editorButton);
    controlLayout->addStretch(1);

    // Define horizontal layout
    QHBoxLayout* hLayout = new QHBoxLayout(this);
    hLayout->addWidget(playlistSlider);
    hLayout->addWidget(playlistDuration);

    // Define vertical layout
    QBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addLayout(displayLayout);
    vLayout->addLayout(hLayout);
    vLayout->addLayout(controlLayout);

    // Set Layout
    widget->setLayout(vLayout);

    // Set status
    isKinect = true;
}

void MainView::ambiantVisualizer() {
    // Check if kinect visualizer has been closed
    if (isKinect) {
        // Closing Kinect visualiser
        closeKinectVisualizer();
    }
}

void MainView::robotsVisualizer() {
    // Check if kinect visualizer has been closed
    if (isKinect) {
        // Closing Kinect visualiser
        closeKinectVisualizer();
    }
}

void MainView::wearablesVisualizer() {
    // Check if kinect visualizer has been closed
    if (isKinect) {
        // Closing Kinect visualiser
        closeKinectVisualizer();
    }
}

void MainView::xsensVisualizer() {
    // Check if kinect visualizer has been closed
    if (isKinect) {
        // Closing Kinect visualiser
        closeKinectVisualizer();
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

void MainView::updateRecentActions() {
    const int sizes = static_cast<int>(7);

    // Check if file is empty
    if (!recentFiles.isEmpty()) {
        for (int i = 0; recentFiles.size() <= sizes && i < recentFiles.size(); ++i) {
            recentFilesAct.at(i)->setText(recentFiles.at(i));
            recentFilesAct.at(i)->setVisible(true);
        }
        recentFilesAct.at(sizes)->setVisible(true);
    }
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

    // Adding seperator
    monitoringMenu->addSeparator();

    // Setting Open Action
    QAction* openAct = new QAction(openIcon, tr("&Open...           "), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a configuration file from a previous database"));
    openAct->setIconVisibleInMenu(true);
    connect(openAct, &QAction::triggered, this, &MainView::openMonitoring);
    monitoringMenu->addAction(openAct);

    // Setting Open Recent Action
    recentFilesMenu = monitoringMenu->addMenu(tr("&Open Recent          "));
    recentFilesMenu->setStatusTip(tr("Open previous configuration files"));

    const int sizes = static_cast<int>(7);
    for (int i = 0; i < sizes; ++i) {
        QAction* recentAct = new QAction(this);
        recentAct->setVisible(false);
        connect(recentAct, &QAction::triggered, this, &MainView::openRecent);
        recentFilesAct.append(recentAct);
    }

    QAction* clearItem = new QAction(tr("&Clear Items           "), this);
    clearItem->setVisible(false);
    connect(clearItem, &QAction::triggered, this, &MainView::clearItems);
    recentFilesAct.append(clearItem);

    QListIterator<QAction*> iterator(recentFilesAct);
    while (iterator.hasNext()) {
        recentFilesMenu->addAction(iterator.next());
    }

    // Update Recent Actions
    updateRecentActions();    
    
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
    connect(ambiantAct, &QAction::triggered, this, &MainView::ambiantVisualizer);
    monitoringToolBar->addAction(ambiantAct);

    // Setting Kinect Action
    QAction* kinectAct = new QAction(tr("&Kinect"), this);
    kinectAct->setStatusTip(tr("Kinect sensor data analysis"));
    connect(kinectAct, &QAction::triggered, this, &MainView::kinectVisualizer);
    monitoringToolBar->addAction(kinectAct);

    // Setting Robots Action
    QAction* robotsAct = new QAction(tr("&Robots"), this);
    robotsAct->setStatusTip(tr("Robots sensors data analysis"));
    connect(robotsAct, &QAction::triggered, this, &MainView::robotsVisualizer);
    monitoringToolBar->addAction(robotsAct);

    // Setting Wearables Action
    QAction* wearablesAct = new QAction(tr("&Wearables"), this);
    wearablesAct->setStatusTip(tr("Wearables sensors data analysis"));
    connect(wearablesAct, &QAction::triggered, this, &MainView::wearablesVisualizer);
    monitoringToolBar->addAction(wearablesAct);

    // Setting Xsens Action
    QAction* xsensAct = new QAction(tr("&Xsens"), this);
    xsensAct->setStatusTip(tr("Xsens sensors data analysis"));
    connect(xsensAct, &QAction::triggered, this, &MainView::xsensVisualizer);
    monitoringToolBar->addAction(xsensAct);

    isToolBar = true;
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
    connect(summaryAct, &QAction::triggered, helpWindow, &QWidget::show);
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