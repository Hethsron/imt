#ifndef VIDEOVIEW_HPP
#define VIDEOVIEW_HPP

/**
 *	\file			videoview.hpp
 *	\brief			Header of VideoView class
 *
 *					This header contains an useful class to manage events on video widget
 *
 *  System :                IMT GUI
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
 *  \author         Hethsron Jedaël BOUEYA (hethsron-jedael.boueya@uha.fr)
 * 
 *  \bug            No known bug to date
 *  \date           21th May 2020
 */

#include <QtWidgets/QtWidgets>
#include <QtMultimediaWidgets/QtMultimediaWidgets>

class VideoView : public QVideoWidget
{
    public:
        /**
         * @fn      VideoView
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent      QWidget parent instance
         */
        explicit VideoView(QWidget* parent = nullptr);

        /**
         * @fn      ~VideoView
         * @brief   Destructor of class
         */
        virtual ~VideoView();

    protected:
        /**
         * @fn      keyPressEvent
         * @brief   Virtual function that receives key press events for the widget
         * 
         * @param[in]       event       Key press event received
         */
        virtual void keyPressEvent(QKeyEvent* event) override;

        /**
         * @fn      mouseDoubleClickEvent
         * @brief   Virtual function that receives mouve double click events for the widget
         * 
         * @param[in]       event       Mouse double click event received
         */
        virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

        /**
         * @fn      mousePressEvent
         * @brief   Virtual function that receives mouse press event for the widget
         * 
         * @param[in]       event       Mouse press event received
         */
        virtual void mousePressEvent(QMouseEvent* event) override;
};

#endif // ! VIDEOVIEW_HPP