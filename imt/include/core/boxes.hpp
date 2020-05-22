#ifndef BOXES_HPP
#define BOXES_HPP

/**
 *	\file			boxes.hpp
 *	\brief			Header of Boxes class
 *
 *					This header contains an useful class to manage application assets values
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

#include <QtCore/QtCore>

class Boxes
{
    public:
        /**
         * @fn      Boxes
         * @brief   Default constructor of class
         */
        Boxes();

        /**
         * @fn      ~Boxes
         * @brief   Destructor of class
         */
        virtual ~Boxes();

        /**
         * @fn      getTitle
         * @brief   Returns application title
         * 
         * @return  Application title
         */
        virtual QString getTitle() const;

        /**
         * @fn      getIcon
         * @brief   Returns distinguished name of application icon
         * 
         * @return  Distinguished name of application icon
         */
        virtual QString getIcon() const;

        /**
         * @fn      getSplash
         * @brief   Returns distinguished name of application splashscreen
         * 
         * @return  Distinguished name of application splashscreen
         */
        virtual QString getSplash() const;

        /**
         * @fn      getStyle
         * @brief   Returns application stylesheet
         * 
         * @return  Application stylesheet
         */
        virtual QString getStyle() const;

        /**
         * @fn      getMessage
         * @brief   Returns application quit message
         * 
         * @return  Application quit message
         */
        virtual QString getMessage() const;

        /**
         * @fn      getBackground
         * @brief   Returns distinguished name of application background
         * 
         * @return  Distinguished name of Applcation background
         */
        virtual QString getBackground() const;

        /**
         * @fn      getHeight
         * @brief   Returns application height
         * 
         * @return  Application height
         */
        virtual int getHeight() const;

        /**
         * @fn      getWidth
         * @brief   Returns application width
         * 
         * @return  Application width
         */
        virtual int getWidth() const;

    private:
        /**
         * @fn      assignment
         * @brief   Assigns right distinguished names of application
         */
        virtual void assignment();

        QString title;                      /*!< Application title */
        QString icon;                       /*!< Distinguished name of application Icon */
        QString splash;                     /*!< Distinguished name of application splashscreen */
        QString background;                 /*!< Distinguished name of application background */
        QString style;                      /*!< Application stylesheet */
        QString message;                    /*!< Application quit message */
        int height;                         /*!< Application height */
        int width;                          /*!< Application width */
};

#endif // ! BOXES_HPP