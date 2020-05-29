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
 *  \date 			21th May 2020
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
         * @fn      getCollections
         * @brief   Virtual function that returns collections of PNG distinguished names
         * 
         * @return  Collections of PNG distinguished names
         */
        virtual QList<QString> getCollections() const;

        /**
         * @fn      getTitle
         * @brief   Virtual function that returns application title
         * 
         * @return  Application title
         */
        virtual QString getTitle() const;

        /**
         * @fn      getIcon
         * @brief   Virtual function that returns distinguished name of application icon
         * 
         * @return  Distinguished name of application icon
         */
        virtual QString getIcon() const;

        /**
         * @fn      getSplash
         * @brief   Virtual function that returns distinguished name of application splashscreen
         * 
         * @return  Distinguished name of application splashscreen
         */
        virtual QString getSplash() const;

        
        /**
         * @fn      getConfig
         * @brief   Virtual function that returns distinguished name of application configuration file
         * 
         * @return  Distinguished name of application configuration file
         */
        virtual QString getConfig() const;

        /**
         * @fn      getStyle
         * @brief   Virtual function that returns application stylesheet
         * 
         * @return  Application stylesheet
         */
        virtual QString getStyle() const;

        /**
         * @fn      getStyleSheet
         * brief Virtual function that returns application global stylesheet
         * 
         * @return  Application global stylesheet
         */
        virtual QString getStyleSheet() const;

        /**
         * @fn      getMessage
         * @brief   Virtual function that returns application quit message
         * 
         * @return  Application quit message
         */
        virtual QString getMessage() const;

        /**
         * @fn      getBackground
         * @brief   Virtual function that returns distinguished name of application background
         * 
         * @return  Distinguished name of Applcation background
         */
        virtual QString getBackground() const;

        /**
         * @fn      getQHC
         * @brief   Virtual function that returns Qt Help collection file of html
         * 
         * @return  Application help collection file
         */
        virtual QString getQHC() const;

        /**
         * @fn      getHeight
         * @brief   Virtual function that returns application height
         * 
         * @return  Application height
         */
        virtual int getHeight() const;

        /**
         * @fn      getWidth
         * @brief   Virtual function that returns application width
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

        QList<QString> collections;         /*!< Collection of PNG distinguished names */
        QString title;                      /*!< Application title */
        QString icon;                       /*!< Distinguished name of application Icon */
        QString splash;                     /*!< Distinguished name of application splashscreen */
        QString background;                 /*!< Distinguished name of application background */
        QString config;                     /*!< Distinguished name of application configuration file */
        QString style;                      /*!< Application stylesheet */
        QString stylesheet;                 /*!< Application global stylesheet */
        QString message;                    /*!< Application quit message */
        QString qhc;                        /*!< Application help collection file */
        int height;                         /*!< Application height */
        int width;                          /*!< Application width */
};

#endif // ! BOXES_HPP