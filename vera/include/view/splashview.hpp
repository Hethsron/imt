#ifndef SPLASHVIEW_HPP
#define SPLASHVIEW_HPP

/**
 *	\file			splashview.hpp
 *	\brief			Header of SplashView class
 *
 *					This header contains an useful class to manage application splash screen
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

#include <QtWidgets/QtWidgets>
#include <QtGui/QtGui>

class SplashView : public QSplashScreen
{
    public:
        /**
         * @fn      SplashView
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       app         QApplication instance
         * @param[in]       parent      QWidget parent instance
         */
        explicit SplashView(QWidget* parent = nullptr);

        /**
         * @fn      ~SplashView
         * @brief   Destructor of class
         */
        virtual ~SplashView();

        /**
         * @fn      getProgress
         * @brief   Virtual function that returns value of progression
         */
        virtual int getProgress() const;

    public slots:
        /**
         * @fn      setMessage
         * @brief   Virtual function that sets message to show in the splashscreen
         * 
         * @param[in]       message     QString instance
         */
        virtual void setMessage(const QString& message);

        /**
         * @fn      setProgress
         * @brief   Virtual function that sets value of progression
         * 
         * @param[in]       value       Integer value
         */
        virtual void setProgress(const int value);

    protected:
        /**
         * @fn      drawContents
         * @brief   Virtual function that draws the contents of the frame on the given painter
         * 
         * @param[in]       painter     QPainter instance
         */
        virtual void drawContents(QPainter* painter) override;
    
    private:
        /**
         * @fn      assignment
         * @brief   Virtual function that assigns right values
         */
        virtual void assignment();

        int progress;                   /*!< Value of progression */
};

#endif // ! SPLASHVIEW_HPP