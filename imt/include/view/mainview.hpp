#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

/**
 *	\file			mainview.hpp
 *	\brief			Header of MainView class
 *
 *					This header contains an useful class to manage application main window
 *
 *  \details        System :                IMT GUI
 *                  Component Name :        imt
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

#include <QtWidgets/QtWidgets>
#include <QtGui/QtGui>

class MainView : public QMainWindow
{
    public:
        /**
         * @fn      MainView
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent      QWidget parent instance
         */
        explicit MainView(QWidget* parent = 0);

        /**
         * @fn      ~MainView
         * @brief   Destructor of class
         */
        virtual ~MainView();

    protected:
        /**
         * @fn      closeEvent
         * @brief   Virtual function that send close event to widget that the user wants to close
         * 
         * @param[in]       event       Close event received by the event handler
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

        QWidget* widget;                                /*!< Application central widget */
        QStatusBar* statusBar;                          /*!< Application status bar */
        QMenuBar* menuBar;                              /*!< Application menu bar */
        QMenu* fileMenu;                                /*!< Applicattttion File menu */
        QMenu* monitoringMenu;                          /*!< Application Monitoring menu */
        QMenu* editMenu;                                /*!< Applicattttion Edit menu */
        QMenu* viewMenu;                                /*!< Applicattttion View menu */
        QMenu* toolsMenu;                               /*!< Applicattttion Tools menu */
        QMenu* helpMenu;                                /*!< Applicattttion Help menu */
        QToolBar* monitoringToolBar;                    /*!< Application Monitoring ToolBar */
};

#endif // ! MAINVIEW_HPP