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
 *  \date 			3rd June 2019
 */

#include <QtWidgets/QtWidgets>
#include <QtGui/QtGui>

class MainView : public QMainWindow
{
    public:
        /**
         * @fn      MainView
         * @brief   Default constructor of class
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
         * @brief   Send close event to widget that the user wants to close
         * 
         * @param[in]       event       close event received by the event handler
         */
        void closeEvent(QCloseEvent *event) override;

    private:
        /**
         * @fn      createActions
         * @brief   Creates actions buttons for QMenuBar
         */
        virtual void createActions();

        /**
         * @fn      createStatusBar
         * @brief   Creates status bar field
         */
        virtual void createStatusBar();

        QWidget* widget;                                /*!< Application central widget */
        QStatusBar* statusBar;                          /*!< Application status bar */
        QMenuBar* menuBar;                              /*!< Application menu bar */              

};

#endif // ! MAINVIEW_HPP