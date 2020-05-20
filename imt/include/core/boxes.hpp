#ifndef BOXES_HPP
#define BOXES_HPP

#include <QtCore/QString>
#include <QtCore/QDir>

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
         * @fn      getStore
         * @brief   Returns application designer store form
         * 
         * @return  Application dddddesigner store form
         */
        virtual QString getStore() const;

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
        QString title;                      /*!< Application title */
        QString icon;                       /*!< Distinguished name of application Icon */
        QString splash;                     /*!< Distinguished name of application splashscreen */
        QString style;                      /*!< Application stylesheet */
        QString message;                    /*!< Application quit message */
        QString store;                      /*!< Application designer store form */
        int height;                         /*!< Application height */
        int width;                          /*!< Application width */
};

#endif // ! BOXES_HPP