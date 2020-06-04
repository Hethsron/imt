#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

/**
 *	\file			mainview.hpp
 *	\brief			Header of MainView class
 *
 *					This header contains an useful class to manage application main window
 *
 *  \details        System :                Vera GUI
 *                  Component Name :        vera
 *                  Status :                Version 1.0.0 Release 1
 *                  Language :              C++
 * 
 *                  Platform Dependencies:  GNU/Linux, Windows, MacOS
 * 
 *  \copyright      GPLv3+ : GNU GPL version 3 or later
 *                  Licencied Material - Property of IMT ATLANTIQUE
 *                  © Copyright - UHA - ENSISA 2020
 * 
 *	\author			Hethsron Jedaël BOUEYA (hethsron-jedael.boueya@uha.fr)
 * 
 * 	\bug			No known bug to date
 *  \date 			21th May 2020
 */

#include <model/playlist.hpp>
#include <model/sensor.hpp>
#include <view/histogramchart.hpp>
#include <view/playercontrols.hpp>
#include <QtWidgets/QtWidgets>
#include <QtGui/QtGui>

class MainView : public QMainWindow
{
    Q_OBJECT
    
    public:
        /**
         * @fn      MainView
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent      QWidget parent instance
         */
        explicit MainView(QWidget* parent = nullptr);

        /**
         * @fn      ~MainView
         * @brief   Destructor of class
         */
        virtual ~MainView();

    protected:
        /**
         * @fn      closeEvent
         * @brief   Virtual function that receives close event for the widget
         * 
         * @param[in]       event       Close event received
         */
        virtual void closeEvent(QCloseEvent *event) override;

        /**
         * @fn      createActions
         * @brief   Virtual function that creates actions buttons for QMenuBar
         * 
         * @see     createFileMenu
         * @see     createEditMenu
         * @see     createViewMenu
         * @see     createToolsMenu
         * @see     createHelpMenu
         */
        virtual void createActions();

        /**
         * @fn      createStatusBar
         * @brief   Virtual function that creates status bar field
         */
        virtual void createStatusBar();

        /**
         * @fn      createHelpWindow
         * @brief   Virtual function that creates Help Window contents for QMenuBar
         */
        virtual void createHelpWindow();

    private slots:
        /**
         * @fn      about
         * @brief   Virtual function that references About action
         */
        virtual void about();

        /**
         * @fn      newMonitoring
         * @brief   Virtual function that references New action
         */
        virtual void newMonitoring();

        /**
         * @fn      openMonitoring
         * @brief   Virtual function that references Open action
         */
        virtual void openMonitoring();

        /**
         * @fn      saveMonitoring
         * @brief   Virtual function that references Save action
         */
        virtual void saveMonitoring();

        /**
         * @fn      saveAsMonitoring
         * @brief   Virtual function that references Save As action
         */
        virtual void saveAsMonitoring();

        /**
         * @fn      closeMonitoring
         * @brief   Virtual function that references Close action
         */
        virtual void closeMonitoring();

        /**
         * @fn      clearItems
         * @brief   Virtual function that references CLear Items action
         */
        virtual void clearItems();

        /**
         * @fn      openRecent
         * @brief   Virtual function that references Open Recent configuration action
         */
        virtual void openRecent();

        /**
         * @fn      kinectVisualizer
         * @brief   Virtual function that references Kinect Action in QToolBar
         */
        virtual void kinectVisualizer();

        /**
         * @fn      ambiantVisualizer
         * @brief   Virtual function that references Ambiant Action in QToolBar
         */
        virtual void ambiantVisualizer();

        /**
         * @fn      robotsVisualizer
         * @brief   Virtual function that references Robots Action in QToolBar
         */
        virtual void robotsVisualizer();

        /**
         * @fn      wearablesVisualizer
         * @brief   Virtual function that references Wearables Action in QToolBar
         */
        virtual void wearablesVisualizer();

        /**
         * @fn      xsensVisualizer
         * @brief   Virtual function that references Xsens Action in QToolBar
         */
        virtual void xsensVisualizer();

    protected slots:
        /**
         * @fn      changeDuration
         * @brief   Virtual function that references duration change event
         * 
         * @param[in]       duration        Duration value to set
         */
        virtual void changeDuration(qint64 duration);

        /**
         * @fn      changePosition
         * @brief   Virtual function that references position change event
         * 
         * @param[in]       progress        Progress value to set
         */
        virtual void changePosition(qint64 progress);

        /**
         * @fn      changeMetaData
         * @brief   Virtual function that references meta data change event
         */
        virtual void changeMetaData();

        /**
         * @fn      changePlaylistPosition
         * @brief   Virtual function that references playlist position change event
         * 
         * @param[in]       progress        Progress  value to set
         */
        virtual void changePlaylistPosition(int progress);

        /**
         * @fn      changeMediaStatus
         * @brief   Virtual function that references media change status event
         * 
         * @param[in]       status          Media status to set
         */
        virtual void changeMediaStatus(QMediaPlayer::MediaStatus status);

        /**
         * @fn      changeBufferStatus
         * @brief   Virtual function that references buffer change status event
         * 
         * @param[in]       progress        Progress value to set
         */
        virtual void changeBufferStatus(int progress);

        /**
         * @fn      printError
         * @brief   Virtual function that references media player error message event
         */
        virtual void printError();

        /**
         * @fn      changeState
         * @brief   Virtual function that references state change event
         * 
         * @param[in]       state           State to set
         */
        virtual void changeState(QMediaPlayer::State state);

        /**
         * @fn      jump
         * @brief   Virtual function that references activated item view event
         * 
         * @param[in]       index           Index of playlist model
         */
        virtual void jump(const QModelIndex& index);

        /**
         * @fn      seek
         * @brief   Virtual function that references playlist slider duration move event
         * 
         * @param[in]       second          Second value to set
         */
        virtual void seek(int second);

        /**
         * @fn      previousClicked
         * @brief   Virtual function that references playlist previous action event
         */
        virtual void previousClicked();

        /**
         * @fn      uploadClicked
         * @brief   Virtual function that references Upload push button clicked event
         */
        virtual void uploadClicked();
        
        /**
         * @fn      annotationClicked
         * @brief   Virtual function that references Annotation push button clicked event
         */
        virtual void annotationClicked();

        /**
         * @fn      colorClicked
         * @brief   Virtual function that references Color push button clicked event
         */
        virtual void colorClicked();

        /**
         * @fn      depthClicked
         * @brief   Virtual function that references Depth push button clicked event
         */
        virtual void depthClicked();

        /**
         * @fn      dClicked
         * @brief   Virtual function that references 3D push button clicked event
         */
        virtual void dClicked();

        /**
         * @fn      editorClicked
         * @brief   Virtual function that references Editor push button clicked event
         */
        virtual void editorClicked();

        /**
         * @fn      skeletonClicked
         * @brief   Virtual function that references Skeleton push button clicked event
         */
        virtual void skeletonClicked();

    protected:
        /**
         * @fn      closeKinectVisualizer
         * @brief   Virtual function that references kinect closing visualizer Action in QMenu
         */
        virtual void closeKinectVisualizer();

        /**
         * @fn      updateDurationInfo
         * @brief   Virtual function that references duration information of Kinect visualizer in playlist
         * 
         * @param[in]       duration        Duration value to update
         */
        virtual void updateDurationInfo(qint64 duration);

        /**
         * @fn      updateStatusInfo
         * @brief   Virtual function that references status information of Kinect visualizer in playlist
         * 
         * @param[in]       info            Status information
         */
        virtual void updateStatusInfo(const QString& info);

        /**
         * @fn      setTrackInfo
         * @brief   Virtual function that creates tracking information on playlist
         * 
         * @param[in]       info            Tracking information
         */
        virtual void setTrackInfo(const QString& info);

        /**
         * @fn      handleCursor
         * @brief   Virtual function that handles cursor on playlist
         * 
         * @param[in]       status          Media player status
         */
        virtual void handleCursor(QMediaPlayer::MediaStatus status);

        /**
         * @fn      addToPlaylist
         * @brief   Virtual function that appends selected urls in playlist
         * 
         * @param[in]       urls            Selected urls to append
         */
        virtual void addToPlaylist(const QList<QUrl>& urls);

    private:
        /**
         * @fn      createFileMenu
         * @brief   Virtual function that creates File menu in MenuBar
         */
        virtual void createFileMenu();

        /**
         * @fn      createMonitoringMenu
         * @brief   Virtual function that creates Monitoring in MenuBar
         */
        virtual void createMonitoringMenu();

        /**
         * @fn      createMonitoringToolBar
         * @brief   Virtual function that creates Toolbar for Monitoring process
         */
        virtual void createMonitoringToolBar();      

        /**
         * @fn      createEditMenu
         * @brief   Virtual function that creates Edit menu in MenuBar
         */
        virtual void createEditMenu();

        /**
         * @fn      createViewMenu
         * @brief   Virtual function that creates View menu in MenuBar
         */
        virtual void createViewMenu();
        
        /**
         * @fn      createToolsMenu
         * @brief   Virtual function that creates Tools menu in MenuBar
         */
        virtual void createToolsMenu();

        /**
         * @fn      createHelpMenu
         * @brief   Virtual function that creates Help menu in MenuBar
         */
        virtual void createHelpMenu();

        /**
         * @fn      updateRecentActions
         * @brief   Virtual function that updates recent actions in MenuBar
         */
        virtual void updateRecentActions();

        /**
         * @fn      openRecentFile
         * @brief   Virtual function that open recent configuration file in MenuBar
         * 
         * @param[in]       filename        Recent configuration file
         */
        virtual void openRecentFile(const QString& filename);

        /**
         * @fn      clearHistogramCharts
         * @brief   Virtual function that clear all histogram chart in kinect media player
         */
        virtual void clearHistogramCharts();

        QWidget* widget;                                /*!< Application central widget */
        QStatusBar* statusBar;                          /*!< Application status bar */
        QMenuBar* menuBar;                              /*!< Application menu bar */
        QMenu* fileMenu;                                /*!< Applicattttion File menu */
        QMenu* recentFilesMenu;                         /*!< Application recent files menu */
        QMenu* monitoringMenu;                          /*!< Application Monitoring menu */
        QMenu* editMenu;                                /*!< Applicattttion Edit menu */
        QMenu* viewMenu;                                /*!< Applicattttion View menu */
        QMenu* toolsMenu;                               /*!< Applicattttion Tools menu */
        QMenu* helpMenu;                                /*!< Applicattttion Help menu */
        QToolBar* monitoringToolBar;                    /*!< Application Monitoring ToolBar */
        QJsonDocument config;                           /*!< Application configuration data */
        QList<QAction*> recentFilesAct;                 /*!< Application recent files action list */
        QStringList recentFiles;                        /*!< Application recent files */
        QDockWidget* helpWindow;                        /*!< Application help window */
        QMediaPlayer* player;                           /*!< Application inner media player */
        QMediaPlaylist* playlist;                       /*!< Application inner media playlist */
        QVideoWidget* videoWidget;                      /*!< Application inner video widget */
        PlayList* playlistModel;                        /*!< Application inner playlist model */
        PlayerControls* controls;                       /*!< Application inner player controls */
        QAbstractItemView* playlistView;                /*!< Application inner playlist view */
        QSlider* playlistSlider;                        /*!< Application inner playlist slider */
        QLabel* playlistDuration;                       /*!< Application inner playlist duration label */ 
        QLabel* playlistCover;                          /*!< Application inner playlist cover label */
        QSpinBox* playlistActivities;                   /*!< Application inner playlist activities QSpinBox */
        QSpinBox* playlistSubjects;                     /*!< Application inner playlist subjects QSpinBox */
        QPushButton* loadButton;                        /*!< Application inner playlist Upload push button */
        QPushButton* annotationButton;                  /*!< Application inner playlist Annotation push button */
        QPushButton* colorButton;                       /*!< Application inner playlist Color Viewer button */
        QPushButton* depthButton;                       /*!< Application inner playlist Depth Viewer button */
        QPushButton* dButton;                           /*!< Applicatioo inner playlist 3D Viewer button */
        QPushButton* editorButton;                      /*!< Application inner playlist Editor push button */
        QPushButton* skeletonButton;                    /*!< Application inner playlist Skeleton push button */
        HistogramChart* video;                          /*!< Application inner video histogram chart */
        HistogramChart* audio;                          /*!< Application inner audio histogram chart */
        QVideoProbe* videoProbe;                        /*!< Application inner video probe */
        QAudioProbe* audioProbe;                        /*!< Application inner audio probe */
        QString trackInfo;                              /*!< Application inner playlist track information */
        Sensor* sensor;                                 /*!< Application inner sensor */
        bool isToolBar;                                 /*!< Application main tool bar status */
        bool isKinect;                                  /*!< Application kinet tool status */
        qint64 pDuration;                               /*!< Application playlist duration */
};

#endif // ! MAINVIEW_HPP