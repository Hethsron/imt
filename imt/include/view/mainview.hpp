#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QAction>
#include <QtGui/QCloseEvent>
#include <QtWidgets/QMenu>
#include <QtGui/QIcon>

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