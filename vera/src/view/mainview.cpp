#include <view/mainview.hpp>
#include <view/annotation.hpp>
#include <view/helpbrowser.hpp>
#include <view/videoview.hpp>
#include <core/backwriter.hpp>
#include <core/deepreader.hpp>
#include <core/writer.hpp>
#include <core/boxes.hpp>
#include <model/kinect.hpp>

MainView::MainView(QWidget* parent) 
    : QMainWindow(parent), widget(new QWidget()), statusBar(new QStatusBar()), menuBar(new QMenuBar()), fileMenu(new QMenu()), recentFilesMenu(new QMenu()), monitoringMenu(new QMenu()), editMenu(new QMenu()), viewMenu(new QMenu()), toolsMenu(new QMenu()), helpMenu(new QMenu()), monitoringToolBar(new QToolBar()), config(QJsonDocument()), recentFilesAct(QList<QAction*>()), recentFiles(QStringList()), helpWindow(new QDockWidget()), player(nullptr), playlist(nullptr), videoWidget(nullptr), playlistModel(nullptr), controls(nullptr), customPlot(nullptr), playlistView(nullptr), playlistSlider(nullptr), playlistDuration(nullptr), playlistCover(nullptr), activities(nullptr), subjects(nullptr), loadButton(nullptr), annotationButton(nullptr), colorButton(nullptr), depthButton(nullptr), dButton(nullptr), editorButton(nullptr), skeletonButton(nullptr), video(nullptr), audio(nullptr), videoProbe(nullptr), audioProbe(nullptr), trackInfo(QString()), sensor(nullptr), license(nullptr), depth(QStringList()), depthLabel(nullptr), accelAxis(nullptr), gyroAxis(nullptr), accelX(nullptr), accelY(nullptr), accelZ(nullptr), gyroX(nullptr), gyroY(nullptr), gyroZ(nullptr), names(nullptr), wearables(nullptr), isToolBar(false), isKinect(false), isWearables(false), depthStatus(false), cDuration(0), currentIndex(-1) {
        Boxes infos;
        resize(infos.getWidth(), infos.getHeight());
        setWindowTitle(infos.getTitle());
        setWindowIcon(QIcon(QPixmap(infos.getIcon())));
        setCentralWidget(widget);
        setStyleSheet(infos.getStyleSheet());

        // Moving splash screen in the center of screen
        QSize size = QApplication::screens()[0]->size();
        move((size.width() / 2) - (frameSize().width() / 2), (size.height() / 2) - (frameSize().height() / 2));
        
        // Update license manager
        license = new LicenseManager(this);

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
    helpBrowser->setSource(QUrl("qthelp://vera.summary/doc/index.html"));

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

    // Adding dock widget
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
    QMessageBox::about(this, tr("About Vera"),
            tr("<b>Vera ® Plateform</b> "
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

void MainView::closeWearablesVisualizer() {
    // Reset inner sensor
    if (sensor != nullptr) {
        sensor = nullptr;
    }

    // Close inner customplot
    if (customPlot != nullptr) {
        // Clear customplot layout
        customPlot->plotLayout()->clear();
        
        // Check if customplot is closed
        if (customPlot->close()) {
            customPlot = nullptr;
        }
    }

    // Close inner list widget
    if (names != nullptr) {
        // Clear list widget
        names->clear();

        // Check if list widget is closed
        if (names->close()) {
            names = nullptr;
        }
    }

    // Reset inner wearables data
    if (wearables != nullptr) {
        // Clear wearables measurements data
        wearables->clear();

        // Check if wearables is empty
        if (wearables->isEmpty()) {
            wearables = nullptr;
        }
    }

    // Reset inner accelerometer axis
    if (accelAxis != nullptr) {
        accelAxis = nullptr;
    }

    // Reset inner gyroscope axis
    if (gyroAxis != nullptr) {
        gyroAxis = nullptr;
    }

    // Reset inner accelerometer X graph
    if (accelX != nullptr) {
        accelX = nullptr;
    }

    // Reset inner accelerometer Y graph
    if (accelY != nullptr) {
        accelY = nullptr;
    }

    // Reset inner accelerometer Z graph
    if (accelZ != nullptr) {
        accelZ = nullptr;
    }

    // Reset inner gyroscope X graph
    if (gyroX != nullptr) {
        gyroX = nullptr;
    }

    // Reset inner gyroscope Y graph
    if (gyroY != nullptr) {
        gyroY = nullptr;
    }

    // Reset inner gyroscope Z graph
    if (gyroZ != nullptr) {
        gyroZ = nullptr;
    }

    // Close inner activities spinbox
    if (activities != nullptr) {
        // Check if activities spinbox is closed
        if (activities->close()) {
            activities = nullptr;
        }
    }

    // Close inner subjects spinbox
    if (subjects != nullptr) {
        // Check if subjects spinbox is closed
        if (subjects->close()) {
            subjects = nullptr;
        }
    }

    // Close inner Upload button
    if (loadButton != nullptr) {
        // Check if Load button is closed
        if (loadButton->close()) {
            loadButton = nullptr;
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
    isWearables = false;
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

    // Close inner activities spinbox
    if (activities != nullptr) {
        // Check if activities spinbox is closed
        if (activities->close()) {
            activities = nullptr;
        }
    }

    // Close inner subjects spinbox
    if (subjects != nullptr) {
        // Check if subjects spinbox is closed
        if (subjects->close()) {
            subjects = nullptr;
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

    // Close inner Color Viewer button
    if (colorButton != nullptr) {
        // Check if Color Viewer button is closed
        if (colorButton->close()) {
            colorButton = nullptr;
        }
    }

    // Close inner Depth Viewer button
    if (depthButton != nullptr) {
        // Check if Depth Viewer button is closed
        if (depthButton->close()) {
            depthButton = nullptr;
        }
    }

    // Close inner 3D Viewer button
    if (dButton != nullptr) {
        // Check if 3D Viewer button is closed
        if (dButton->close()) {
            dButton = nullptr;
        }
    }

    // Close inner Skeleton button
    if (skeletonButton !=  nullptr) {
        // Check if Skeleton button is closed
        if (skeletonButton->close()) {
            skeletonButton = nullptr;
        }
    }

    // Close inner Editor button
    if (editorButton != nullptr) {
        // Check if Editor button is closed
        if (editorButton->close()) {
            editorButton = nullptr;
        }
    }

    // Close inner video histogram chart
    if (video != nullptr) {
        // Check if video histogram chart is closed
        if (video->close()) {
            video = nullptr;
        }
    }

    // Close inner audio histogram chart
    if (audio != nullptr) {
        // Check if audio histogram chart is closed
        if (audio->close()) {
            audio = nullptr;
        }
    }

    // Close depth label
    if (depthLabel != nullptr) {
        // Check if depth label is closed
        if (depthLabel->close()) {
            depthLabel = nullptr;
        }
    }

    // Reset inner video probe
    if (videoProbe != nullptr) {
        videoProbe = nullptr;
    }

    // Reset inner audio probe
    if (audioProbe != nullptr) {
        audioProbe = nullptr;
    }

    // Reset inner sensor
    if (sensor != nullptr) {
        sensor = nullptr;
    }

    // Check if depth files is empty
    if (!depth.empty()) {
        // Clear depth files
        depth.clear();
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

    // Check if Wearables visualizer has been enables
    if (isWearables) {
        // Closing Wearables visualizer
        closeWearablesVisualizer();
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

void MainView::changeDuration(qint64 duration) {
    pDuration = duration / 1000;
    playlistSlider->setMaximum(pDuration);
}

void MainView::changePosition(qint64 progress) {
    // Check if slider is not down
    if (!playlistSlider->isSliderDown()) {
        // Set Value
        playlistSlider->setValue(progress / 1000);
    }

    // Update duration info
    updateDurationInfo(progress / 1000);
}

void MainView::updateDurationInfo(qint64 duration) {
    QString str = nullptr;

    // If duration is not null
    if (duration || pDuration) {
        QTime current((duration / 3600) % 60, (duration / 60) % 60, duration % 60, (duration * 1000) % 1000);
        QTime total((pDuration / 3600) % 60, (pDuration / 60) % 60, pDuration % 60, (pDuration * 1000) % 1000);
        
        // Define format
        QString format = QString("mm:ss");

        // Check duration value
        if (pDuration > 3600) {
            // Update format
            format = QString("hh:mm:ss");
        }

        // Update string data
        str = current.toString(format) + " / " + total.toString(format);

        // Check if depth is not empty
        if (!depth.isEmpty()) {
            // Define frame rate
            if (cDuration < pDuration) {
                const int fps = 100 * controls->getRate();

                // Define minimum value
                const int minValue = cDuration * fps;
                
                // Define maximum value
                const int maxValue = fps * (cDuration + 1);

                // Update depth label pixmap
                for (int i = minValue ; i < maxValue && i < depth.size(); ++i) {
                    depthLabel->setPixmap(QPixmap(depth.at(i)));
                }

                // Increase duration
                cDuration++;
            }
            else {
                // Reset current duration
                cDuration = 0;
            }
        }
    }

    // Setting text
    playlistDuration->setText(str);
}

void MainView::changeMetaData() {
    // Check if player meta data is available
    if (player->isMetaDataAvailable()) {
        setTrackInfo(QString("%1 - %2").arg(player->metaData(QMediaMetaData::AlbumArtist).toString()).arg(player->metaData(QMediaMetaData::Title).toString()));
        // Check if cover exist
        if (playlistCover) {
            QUrl url = player->metaData(QMediaMetaData::CoverArtUrlLarge).value<QUrl>();
            playlistCover->setPixmap(!url.isEmpty() ? QPixmap(url.toString()) : QPixmap());
        }
    }
}

void MainView::setTrackInfo(const QString& info) {
    // Update tracking information
    trackInfo = info;

    // Check if status bar exists
    if (statusBar->isEnabled()) {
        // Showing tracking information
        statusBar->showMessage(trackInfo);
    }
}

void MainView::changePlaylistPosition(int progress) {
    // Clear histogram charts
    clearHistogramCharts();
    
    // Setting current index of playlist
    playlistView->setCurrentIndex(playlistModel->index(progress, 0));
}

void MainView::updateStatusInfo(const QString& info) {
    // Check if status bar exists
    if (statusBar->isEnabled()) {
        // Showing status bar information
        statusBar->showMessage(info);
    }
}

void MainView::handleCursor(QMediaPlayer::MediaStatus status) {
    #ifndef QT_NO_CURSOR
        if (status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::BufferingMedia || status == QMediaPlayer::StalledMedia) {
            // Setting cursor
            widget->setCursor(QCursor(Qt::BusyCursor));
        }
        else {
            // Unsetting cursor
            widget->unsetCursor();
        }
    #endif
}

void MainView::changeMediaStatus(QMediaPlayer::MediaStatus status) {
    // Handle cursor
    handleCursor(status);

    // Handle status message
    switch (status) {
        case QMediaPlayer::UnknownMediaStatus:
        case QMediaPlayer::NoMedia:
        case QMediaPlayer::LoadedMedia:
            // Setting status information
            updateStatusInfo(QString());
            break;
        case QMediaPlayer::LoadingMedia:
            // Setting status information
            updateStatusInfo(tr("Loading resource ..."));
            break;
        case QMediaPlayer::BufferingMedia:
        case QMediaPlayer::BufferedMedia:
            // Setting status information
            updateStatusInfo(tr("Buffering %1%").arg(player->bufferStatus()));
            break;
        case QMediaPlayer::StalledMedia:
            // Setting status information
            updateStatusInfo(tr("Stalled %1%").arg(player->bufferStatus()));
            break;
        case QMediaPlayer::EndOfMedia:
            // Setting status info
            QApplication::alert(this);
            break;
        case QMediaPlayer::InvalidMedia:
            // Displaying error message
            printError();
            break;
    }
}

void MainView::changeBufferStatus(int progress) {
    // Check if player media status has changed
    if (player->mediaStatus() == QMediaPlayer::StalledMedia) {
        // Update status info
        updateStatusInfo(tr("Stalled %1%").arg(progress));
    }
    else {
        // Update status info
        updateStatusInfo(tr("Buffering %1%").arg(progress));
    }
}

void MainView::printError() {
    // Update status info
    updateStatusInfo(player->errorString());
}

void MainView::changeState(QMediaPlayer::State state) {
    // Check if state is set to stop
    if (state == QMediaPlayer::StoppedState) {
        // Clear histogram charts
        clearHistogramCharts();
        
        // Update info status
        updateStatusInfo(tr("Stopped"));
    }
}

void MainView::jump(const QModelIndex& index) {
    // Check if index is valid
    if (index.isValid()) {
        // Setting current index
        playlist->setCurrentIndex(index.row());

        // Execute player
        player->play();
    }
}

void MainView::seek(int second) {
    // Setting position
    player->setPosition(second * 1000);
}

void MainView::nameClicked(QListWidgetItem* item) {
    // Setting accelerometer graph data
    accelX->setData(wearables->get(item->text())->getTime(), wearables->get(item->text())->getAccelX());
    accelY->setData(wearables->get(item->text())->getTime(), wearables->get(item->text())->getAccelY());
    accelZ->setData(wearables->get(item->text())->getTime(), wearables->get(item->text())->getAccelZ());

    // Setting xAxis range of accelerometer graph
    accelAxis->axis(QCPAxis::atBottom)->setLabel(tr("Time (s)"));
    accelAxis->axis(QCPAxis::atLeft)->setLabel(tr("Acceleration (m/s^2)"));
    accelAxis->axis(QCPAxis::atLeft)->setRange(wearables->get(item->text())->getMinAccel(), wearables->get(item->text())->getMaxAccel());
    accelAxis->parentPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Setting gyroscope graph data
    gyroX->setData(wearables->get(item->text())->getTime(), wearables->get(item->text())->getGyroX());
    gyroY->setData(wearables->get(item->text())->getTime(), wearables->get(item->text())->getGyroY());
    gyroZ->setData(wearables->get(item->text())->getTime(), wearables->get(item->text())->getGyroZ());

    // Setting xAxis range of gyroscope graph
    gyroAxis->axis(QCPAxis::atBottom)->setLabel(tr("Time (s)"));
    gyroAxis->axis(QCPAxis::atBottom)->setRange(wearables->get(item->text())->getMinTime(), wearables->get(item->text())->getMaxTime());
    gyroAxis->axis(QCPAxis::atLeft)->setLabel(tr("Rotation (°/s)"));
    gyroAxis->axis(QCPAxis::atLeft)->setRange(wearables->get(item->text())->getMinGyro(), wearables->get(item->text())->getMaxGyro());
    gyroAxis->parentPlot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    // Setting accelerometer graph range
    accelX->valueAxis()->setRange(wearables->get(item->text())->getMinAccelX(), wearables->get(item->text())->getMaxAccelX());
    accelY->valueAxis()->setRange(wearables->get(item->text())->getMinAccelY(), wearables->get(item->text())->getMaxAccelY());
    accelZ->valueAxis()->setRange(wearables->get(item->text())->getMinAccelZ(), wearables->get(item->text())->getMaxAccelZ());

    // Setting gyroscope graph range
    gyroX->valueAxis()->setRange(wearables->get(item->text())->getMinGyroX(), wearables->get(item->text())->getMaxGyroX());
    gyroY->valueAxis()->setRange(wearables->get(item->text())->getMinGyroY(), wearables->get(item->text())->getMaxGyroY());
    gyroZ->valueAxis()->setRange(wearables->get(item->text())->getMinGyroZ(), wearables->get(item->text())->getMaxGyroZ());

    // Setting xAxis range
    customPlot->xAxis->setRange(wearables->get(item->text())->getMinTime(), wearables->get(item->text())->getMaxTime());
    
    // Repaints graphs
    customPlot->replot();
}

void MainView::previousClicked() {
    // Check player position
    if (player->position() <= 5000) {
        playlist->previous();
    }
    else {
        player->setPosition(0);
    }
}

void MainView::addToGraphs(const QStringList& jsonls) {
    // Getting wearables
    wearables = (Wearables*) sensor;

    // Setting iterator
    QStringListIterator iterator(jsonls);
    while (iterator.hasNext()) {
        const QString fileName = iterator.next();
        
        // Appends file name data
        wearables->append(fileName);
    }

    // Check if wearables is not empty
    if (!wearables->isEmpty()) {
        // Define row
        int row = 0;

        // Setting iterator
        QStringListIterator iterator(wearables->getNames());
        while (iterator.hasNext()) {
            const QString str = iterator.next();

            // Define widget item
             QListWidgetItem *newItem = new QListWidgetItem();
             newItem->setText(str);
             names->insertItem(row, newItem);

            // Increase row
            row++;
        }
    }
}

void MainView::addToPlaylist(const QList<QUrl>& urls) {
    QListIterator<QUrl> iterator(urls);
    while (iterator.hasNext()) {
        const QUrl url = iterator.next();

        // Check if given url is a playlist
        if (Processor::isPlaylist(url)) {
            // Load url in the playlist
            playlist->load(url);
        }
        else {
            // Adding media
            playlist->addMedia(url);
        }
    }
}

void MainView::clearHistogramCharts() {
    // Invoke readFrame method
    QMetaObject::invokeMethod(video, "readFrame", Qt::QueuedConnection, Q_ARG(QVideoFrame, QVideoFrame()));
    
    // Invoke readBuffer method
    QMetaObject::invokeMethod(audio, "readBuffer", Qt::QueuedConnection, Q_ARG(QAudioBuffer, QAudioBuffer()));
}

void MainView::uploadClicked() {
    // Getting indexes
    const int i = activities->value() - 1;
    const int j = subjects->value() - 1;

    // Check if there is Kinect visualizer
    if (isKinect) {
        // Release back writer
        QList<QUrl> urls = BackWriter::release(sensor->getStorage().at(i).at(j));

        // Check if urls is not empty
        if (!urls.isEmpty()) {
            // Append media files URLs to playlist
            addToPlaylist(urls);
        }
        else {
            QMessageBox::information(this, 
                        tr("No experiences per activity"),
                        tr("The subject you are attempting to upload contains no experiences"));
        }
    }

    // Check if there is Wearables visualizer
    if (isWearables) {
        // Compute back writer
        QStringList jsonls = BackWriter::compute(sensor->getStorage().at(i).at(j));

        // Check if JSON files is not empty
        if (!jsonls.isEmpty()) {
            // Append jsonls files to graphs
            addToGraphs(jsonls);
        }
        else {
            QMessageBox::information(this, 
                        tr("No experiences per activity"),
                        tr("The subject you are attempting to upload contains no experiences"));
        }
    }
}

void MainView::annotationClicked() {
    // Define File Name
    QString fileName = QInputDialog::getText(this, 
                    tr("Add Annotation"), 
                    tr("Annotation name"), 
                    QLineEdit::Normal,
                    tr("Untitled annotation"));

    // Check if name is empty
    if (!fileName.isEmpty()) {
        Annotation* view = new Annotation(fileName, config, this);
        view->show();
    }
}

void MainView::colorClicked() {

}

void MainView::depthClicked() {
    // Check if current index is different
    if (currentIndex != playlist->currentIndex() && !depthStatus) {
        // Update current index
        currentIndex = playlist->currentIndex();

        // Update depth status
        depthStatus = true;

        // Define depth directory
        QRegExp re("(RGB|Video)");
        #if _WIN32
            QRegExp reg("[A-Z]:");
            QString location = playlist->media(playlist->currentIndex()).request().url().toString().split("file://").at(1).split(".").at(0).split(re).at(0).split(reg).at(1) + QString("Depth");
        #else
            QString location = playlist->media(playlist->currentIndex()).request().url().toString().split("file://").at(1).split(".").at(0).split(re).at(0) + QString("Depth");
        #endif // ! _WIN32
        
        QDir dir(location);

        // Check if depth files is empty
        if (!depth.empty()) {
            // Clear depth files
            depth.clear();
        }

        // Check if directory exists
        if (dir.exists()) {
            // Set filter
            dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);

            // Set sorting
            dir.setSorting(QDir::Time | QDir::Reversed);

            // Define entry list
            QStringList list = dir.entryList(QStringList() << "*.png" , QDir::Files | QDir::Readable | QDir::Writable);

            // Define iterator
            QStringListIterator iterator(list);
            while (iterator.hasNext()) {
                const QString str = iterator.next();
                
                // Append founded files
                depth.append(dir.filePath(str));
            }

            // Sort frames
            DeepReader::sort(&depth);
        }
    }
    else if (currentIndex == playlist->currentIndex() && depthStatus) {
        // Hide depth label
        depthLabel->hide();

        // Update depth status
        depthStatus = false;
    }
    else if (currentIndex != playlist->currentIndex() && depthStatus) {
        // Hide depth label
        depthLabel->hide();

        // Update depth status
        depthStatus = false;
    }
    else {
        // Show depth label
        depthLabel->show();

        // Update depth status
        depthStatus = false;

        // Update current index
        currentIndex = -1;
    }
}

void MainView::dClicked() {

}

void MainView::editorClicked() {

}

void MainView::skeletonClicked() {
    
}

void MainView::kinectVisualizer() {
	// Sets status
    isKinect = true;

    // Check if Wearables visualizer has been closed
    if (isWearables) {
        // Closing Wearables visualiser
        closeWearablesVisualizer();
    }

    // Define Kinect sensor
    sensor = new Kinect(config);

    // Define Depth label
    depthLabel = new Depth(this);

    // Define inner player
    player = new QMediaPlayer(this);
    player->setAudioRole(QAudio::VideoRole);

    // Define inner playlist
    playlist = new QMediaPlaylist();
    player->setPlaylist(playlist);
    connect(player, &QMediaPlayer::durationChanged, this, &MainView::changeDuration);
    connect(player, &QMediaPlayer::positionChanged, this, &MainView::changePosition);
    connect(player, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &MainView::changeMetaData);
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &MainView::changePlaylistPosition);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MainView::changeMediaStatus);
    connect(player, &QMediaPlayer::bufferStatusChanged, this, &MainView::changeBufferStatus);
    connect(player, QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error), this, &MainView::printError);
    connect(player, &QMediaPlayer::stateChanged, this, &MainView::changeState);

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
    connect(playlistView, &QAbstractItemView::activated, this, &MainView::jump);

    // Define playlist slider
    playlistSlider = new QSlider(Qt::Horizontal, this);
    playlistSlider->setRange(0, player->duration() / 1000);
    connect(playlistSlider, &QSlider::sliderMoved, this, &MainView::seek);

    // Define video histogram chart
    video = new HistogramChart(this);

    // Define audio histogram chart
    audio = new HistogramChart(this);

    // Define histogram charts layout
    QHBoxLayout* histogramLayout = new QHBoxLayout(this);
    histogramLayout->addWidget(video, 1);
    histogramLayout->addWidget(audio, 2);

    // Define video probe
    videoProbe = new QVideoProbe(this);
    connect(videoProbe, &QVideoProbe::videoFrameProbed, video, &HistogramChart::readFrame);
    videoProbe->setSource(player);

    // Define audio probe
    audioProbe = new QAudioProbe(this);
    connect(audioProbe, &QAudioProbe::audioBufferProbed, audio, &HistogramChart::readBuffer);
    audioProbe->setSource(player);

    // Define playlist label duration
    playlistDuration = new QLabel(this);

    // Define playlist activities
    activities = new QSpinBox(this);
    activities->setPrefix(tr("Activity  "));
    activities->setSuffix(tr(" °"));
    activities->setRange(1, sensor->count());
    activities->setStatusTip(tr("Choose the activity to be monitored"));

    // Define playlist subjects
    subjects = new QSpinBox(this);
    subjects->setPrefix(tr("Subject "));
    subjects->setSuffix(tr(" °"));
    subjects->setRange(1, sensor->count(activities->value() - 1));
    subjects->setStatusTip(tr("Choose the subject to be monitored"));

    // Define Upload push button
    loadButton = new QPushButton(tr("Upload"), this);
    loadButton->setStatusTip(tr("Upload kinect sensor database"));
    connect(loadButton, &QPushButton::clicked, this, &MainView::uploadClicked);

    // Define Skeleton Viewer push button
    skeletonButton = new QPushButton(tr("Skeleton"), this);
    skeletonButton->setStatusTip(tr("Access to skeleton tracking joints"));
    connect(skeletonButton, &QPushButton::clicked, this, &MainView::skeletonClicked);

    // Define Color Viewer push button
    colorButton = new QPushButton(tr("Color"), this);
    colorButton->setStatusTip(tr("Display color view of the data captured by Kinect"));
    connect(colorButton, &QPushButton::clicked, this, &MainView::colorClicked);

    // Define 3D Viewer push button
    dButton = new QPushButton(tr("3D"), this);
    dButton->setStatusTip(tr("Display 3D view of the data captured by Kinect"));
    connect(dButton, &QPushButton::clicked, this, &MainView::dClicked);

    // Define Depth Viewer push button
    depthButton = new QPushButton(tr("Depth"), this);
    depthButton->setStatusTip(tr("Display depth view of the data captured by Kinect"));
    connect(depthButton, &QPushButton::clicked, this, &MainView::depthClicked);

    // Define Annotation push button
    annotationButton = new QPushButton(tr("Annotation"), this);
    annotationButton->setStatusTip(tr("Make annotations"));
    connect(annotationButton, &QPushButton::clicked, this, &MainView::annotationClicked);

    // Define Editor push button
    editorButton = new QPushButton(tr("Video Editor"), this);
    editorButton->setStatusTip(tr("Edit videos and record voice"));
    connect(editorButton, &QPushButton::clicked, this, &MainView::editorClicked);

    // Define player control
    controls = new PlayerControls(this);
    controls->setState(player->state());
    controls->setVolume(player->volume());
    controls->setMuted(controls->isMuted());
    connect(controls, &PlayerControls::play, player, &QMediaPlayer::play);
    connect(controls, &PlayerControls::pause, player, &QMediaPlayer::pause);
    connect(controls, &PlayerControls::stop, player, &QMediaPlayer::stop);
    connect(controls, &PlayerControls::next, playlist, &QMediaPlaylist::next);
    connect(controls, &PlayerControls::previous, this, &MainView::previousClicked);
    connect(controls, &PlayerControls::changeVolume, player, &QMediaPlayer::setVolume);
    connect(controls, &PlayerControls::changeMuting, player, &QMediaPlayer::setMuted);
    connect(controls, &PlayerControls::changeRate, player, &QMediaPlayer::setPlaybackRate);
    connect(controls, &PlayerControls::stop, videoWidget, QOverload<>::of(&QVideoWidget::update));

    connect(player, &QMediaPlayer::stateChanged, controls, &PlayerControls::setState);
    connect(player, &QMediaPlayer::volumeChanged, controls, &PlayerControls::setVolume);
    connect(player, &QMediaPlayer::mutedChanged, controls, &PlayerControls::setMuted);

    // Define display layout
    QBoxLayout* displayLayout = new QHBoxLayout(this);
    displayLayout->addWidget(videoWidget, 2);
    displayLayout->addWidget(depthLabel);
    displayLayout->addWidget(playlistView);
    
    // Define control layout
    QBoxLayout* controlLayout = new QHBoxLayout(this);
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(activities);
    controlLayout->addWidget(subjects);
    controlLayout->addWidget(loadButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(controls);
    controlLayout->addStretch(1);
    controlLayout->addWidget(skeletonButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(colorButton);
    controlLayout->addWidget(dButton);
    controlLayout->addWidget(depthButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(annotationButton);
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
    vLayout->addLayout(histogramLayout);

    // Set Layout
    widget->setLayout(vLayout);

    // Check if player is not available
    if (!player->isAvailable()) {
        QMessageBox::warning(this, tr("Service is not available"),
                                tr("MediaPlayer does not have a valid service \n"
                                    "Please check if the media service plugins are installed"));
        // Deactive playlist controls
        controls->setEnabled(false);

        // Deactive playlist view
        playlistView->setEnabled(false);

        // Deactive Upload push button
        loadButton->setEnabled(false);

        // Deactive Skeleton Viewer push button
        skeletonButton->setEnabled(false);

        // Deactive Color Viewer push button
        colorButton->setEnabled(false);

        // Deactive 3D Viewer push button
        dButton->setEnabled(false);

        // Deactive Depth Viewer push button
        depthButton->setEnabled(false);

        // Deactive Annotation push button
        annotationButton->setEnabled(false);

        // Deactive Editor push button
        editorButton->setEnabled(false);

        // Deactive video histogram
        video->setEnabled(false);

        // Deactive audio histogram
        audio->setEnabled(false);
    }

    // Change meta data
    changeMetaData();
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
    // Sets status
    isWearables = true;

    // Check if kinect visualizer has been closed
    if (isKinect) {
        // Closing Kinect visualiser
        closeKinectVisualizer();
    }

    // Define Wearables sensor
    sensor = new Wearables(config);

    // Define custom plot
    customPlot = new QCustomPlot(this);

    // Clear customplot layout
    customPlot->plotLayout()->clear();

    // Define accelerometer axis
    accelAxis = new QCPAxisRect(customPlot);

    // Define gyrosocope axis
    gyroAxis = new QCPAxisRect(customPlot);

    // Adding title of accelerometer plots
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, tr("Accelerometer graphs in one plot"), QFont("sans", 12, QFont::Bold)));

    // Adding axis of accelerometer plots
    customPlot->plotLayout()->addElement(1, 0, accelAxis);

    // Adding title of gyroscope plots
    customPlot->plotLayout()->addElement(2, 0, new QCPTextElement(customPlot, tr("Gyroscope graphs in one plot"), QFont("sans", 12, QFont::Bold)));

    // Adding axis of gyroscope plots
    customPlot->plotLayout()->addElement(3, 0, gyroAxis);

    // Adding title of legend
    customPlot->plotLayout()->addElement(4, 0, new QCPTextElement(customPlot, tr("Graphs common legend")));

    // Adding general legend
    QCPLayoutGrid *subLayout = new QCPLayoutGrid();
    customPlot->plotLayout()->addElement(5, 0, subLayout);
    subLayout->setMargins(QMargins(20, 10, 20, 10));
    QCPLegend* legend = new QCPLegend();
    legend->setFillOrder(QCPLegend::foColumnsFirst);
    subLayout->addElement(0, 0, legend);

    // Creating plots of accel_x / time
    accelX = customPlot->addGraph(accelAxis->axis(QCPAxis::atBottom), accelAxis->axis(QCPAxis::atLeft));
    accelX->setPen(QPen(Qt::red));
    accelX->setName(tr("accel_x"));

    // Creating plots of accel_y / time
    accelY = customPlot->addGraph(accelAxis->axis(QCPAxis::atBottom), accelAxis->axis(QCPAxis::atLeft));
    accelY->setPen(QPen(Qt::green));
    accelY->setName(tr("accel_y"));

    // Creating plots of accel_z / time
    accelZ = customPlot->addGraph(accelAxis->axis(QCPAxis::atBottom), accelAxis->axis(QCPAxis::atLeft));
    accelZ->setPen(QPen(Qt::blue));
    accelZ->setName(tr("accel_z"));

    // Creating plots of gyro_x / time
    gyroX = customPlot->addGraph(gyroAxis->axis(QCPAxis::atBottom), gyroAxis->axis(QCPAxis::atLeft));
    gyroX->setPen(QPen(Qt::red));
    gyroX->setName(tr("gyro_x"));

    // Creating plots of gyro_y / time
    gyroY = customPlot->addGraph(gyroAxis->axis(QCPAxis::atBottom), gyroAxis->axis(QCPAxis::atLeft));
    gyroY->setPen(QPen(Qt::green));
    gyroY->setName(tr("gyro_y"));

    // Creating plots of gyro_z / time
    gyroZ = customPlot->addGraph(gyroAxis->axis(QCPAxis::atBottom), gyroAxis->axis(QCPAxis::atLeft));
    gyroZ->setPen(QPen(Qt::blue));
    gyroZ->setName(tr("gyro_z"));

    // Define names list view
    names = new QListWidget(this);
    connect(names, &QListWidget::itemDoubleClicked, this, &MainView::nameClicked);

    // Define playlist activities
    activities = new QSpinBox(this);
    activities->setPrefix(tr("Activity  "));
    activities->setSuffix(tr(" °"));
    activities->setRange(1, sensor->count());
    activities->setStatusTip(tr("Choose the activity to be monitored"));

    // Define playlist subjects
    subjects = new QSpinBox(this);
    subjects->setPrefix(tr("Subject "));
    subjects->setSuffix(tr(" °"));
    subjects->setRange(1, sensor->count(activities->value() - 1));
    subjects->setStatusTip(tr("Choose the subject to be monitored"));

    // Define Upload push button
    loadButton = new QPushButton(tr("Upload"), this);
    loadButton->setStatusTip(tr("Upload Wearables sensor database"));
    connect(loadButton, &QPushButton::clicked, this, &MainView::uploadClicked);
    
    // Define display layout
    QBoxLayout* displayLayout = new QHBoxLayout(this);
    displayLayout->addWidget(customPlot, 2);
    displayLayout->addWidget(names);

    // Define control layout
    QBoxLayout* controlLayout = new QHBoxLayout(this);
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(activities);
    controlLayout->addWidget(subjects);
    controlLayout->addWidget(loadButton);
    controlLayout->addStretch(1);

    // Define vertical layout
    QBoxLayout* vLayout = new QVBoxLayout(this);
    vLayout->addLayout(displayLayout);
    vLayout->addLayout(controlLayout);

    // Set Layout
    widget->setLayout(vLayout);
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
    const QIcon exitIcon = QIcon(QPixmap(infos.getCollections().at(3)));
    const QIcon configIcon = QIcon(QPixmap(infos.getCollections().at(11)));

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
    const QIcon newIcon = QIcon(QPixmap(infos.getCollections().at(0)));
    const QIcon openIcon = QIcon(QPixmap(infos.getCollections().at(1)));
    const QIcon saveIcon = QIcon(QPixmap(infos.getCollections().at(2)));
    const QIcon closeIcon = QIcon(QPixmap(infos.getCollections().at(3)));

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
    const QIcon undoIcon = QIcon(QPixmap(infos.getCollections().at(4)));
    const QIcon redoIcon = QIcon(QPixmap(infos.getCollections().at(5)));
    const QIcon cutIcon = QIcon(QPixmap(infos.getCollections().at(6)));
    const QIcon copyIcon = QIcon(QPixmap(infos.getCollections().at(7)));
    const QIcon pasteIcon = QIcon(QPixmap(infos.getCollections().at(8)));

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

void MainView::manageLicense() {
    // Display license manager
    license->show();
}

void MainView::createToolsMenu() {
    Boxes infos;
    toolsMenu = menuBar->addMenu(tr("&Tools"));

    // Setting Icons
    const QIcon extractIcon = QIcon(QPixmap(infos.getCollections().at(9)));

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

    // Adding seperator
    toolsMenu->addSeparator();

    // Setting licences Action
    QAction* licenseAct = new QAction(tr("&Manage License ...       "), this);
    licenseAct->setStatusTip(tr("Product License Registration"));
    connect(licenseAct, &QAction::triggered, this, &MainView::manageLicense);
    toolsMenu->addAction(licenseAct);
}

void MainView::createHelpMenu() {
    Boxes infos;
    helpMenu = menuBar->addMenu(tr("&Help"));

    // Setting Icons
    const QIcon aboutIcon = QIcon(QPixmap(infos.getCollections().at(10)));
    const QIcon summaryIcon = QIcon(QPixmap(infos.getCollections().at(12)));
    
    // Setting Summary Action
    QAction* summaryAct = new QAction(summaryIcon, tr("&Summary ...          "), this);
    summaryAct->setShortcuts(QKeySequence::HelpContents);
    summaryAct->setStatusTip(tr("Provide informations about application's functionalities and usage"));
    summaryAct->setIconVisibleInMenu(true);
    connect(summaryAct, &QAction::triggered, helpWindow, &QWidget::show);
    helpMenu->addAction(summaryAct);

    // Adding separator
    helpMenu->addSeparator();

    // Setting Forums Action
    QAction* forumsAct = new QAction(tr("&Forums ...         "), this);
    forumsAct->setStatusTip(tr("Self-help forum on Vera solution"));
    // TODO : connect
    helpMenu->addAction(forumsAct);

    // Setting Bug tracker
    QAction* bugAct = new QAction(tr("&Bug tracker ...           "), this);
    bugAct->setStatusTip(tr("Reports suggestions for improvements in case you encounter problems"));
    // TODO : connect
    helpMenu->addAction(bugAct);

    // Adding separator
    helpMenu->addSeparator();

    // Setting About Action
    QAction* aboutAct = new QAction(aboutIcon, tr("&About Vera         "), this);
    aboutAct->setShortcuts(QKeySequence::WhatsThis);
    aboutAct->setStatusTip(tr("Provide informations about application's version and licences"));
    aboutAct->setIconVisibleInMenu(true);
    connect(aboutAct, &QAction::triggered, this, &MainView::about);
    helpMenu->addAction(aboutAct);
}