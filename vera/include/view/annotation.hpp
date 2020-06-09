#ifndef ANNOTATION_HPP
#define ANNOTATION_HPP

/**
 *  \file           annotation.hpp
 *  \brief          Header of Annotation class
 *
 *                  This header contains an useful class to manage annotation
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
 *  \author         Hethsron Jedaël BOUEYA (hethsron-jedael.boueya@uha.fr)
 * 
 *  \bug            No known bug to date
 *  \date           21th May 2020
 */

#include <QtWidgets/QtWidgets>
#include <QtCore/QtCore>

class GeneralTab : public QWidget
{
    public:
        /**
         * @fn      GeneralTab
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       fileInfo        File information
         * @param[in]       location        File location
         * @param[in]       parent          QWidget instance
         */
        explicit GeneralTab(const QFileInfo& fileInfo, const QString& location, QWidget* parent = nullptr);
        
        /**
         * @fn      ~GeneralTab
         * @brief   Destructor of class
         */
        virtual ~GeneralTab();
};

class SecurityTab : public QWidget
{
    public:
        /**
         * @fn      SecurityTab
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       fileInfo        File information
         * @param[in]       parent          QWidget instance
         */
        explicit SecurityTab(const QFileInfo& fileInfo, QWidget* parent = nullptr);
        
        /**
         * @fn      ~SecurityTab
         * @brief   Destructor of class
         */
        virtual ~SecurityTab();
};

class DetailsTab : public QWidget
{
    public:
        /**
         * @fn      DetailsTab
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       fileInfo        File information
         * @param[in]       parent          QWidget instance
         */
        explicit DetailsTab(const QFileInfo& fileInfo, QWidget* parent = nullptr);
        
        /**
         * @fn      ~DetailsTab
         * @brief   Destructor of class
         */
        virtual ~DetailsTab();

        /**
         * @fn      get
         * @brief   Virtual function that returns QJsonDocument instance
         * 
         * @return          QJsonDocument instance
         */
        virtual QJsonDocument get() const;

    private:
        QLineEdit* titleValueLabel;                 /*!< QLineEdit inner title instance */
        QLineEdit* videoRangeValueLabel;            /*!< QLineEdit inner range instance */
        QTextEdit* descriptionValueLabel;           /*!< QTextEdit inner text instance */
        QJsonDocument storage;                      /*!< Annotation contents */
        bool status;                                /*!< Annotation status */
};

class Annotation : public QDialog
{
    public:
        /**
         * @fn      Annotation
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       fileName        File name
         * @param[in]       cfg             Configuration Json Document
         * @param[in]       parent          QWidget instance
         */
        explicit Annotation(const QString& fileName, const QJsonDocument& cfg, QWidget* parent = nullptr);
        
        /**
         * @fn      ~Annotation
         * @brief   Destructor of class
         */
        virtual ~Annotation();

        /**
         * @fn      write
         * @brief   Virtual function that writes annotations
         */
        virtual void write();

    private:
        QTabWidget* widget;                         /*!< QTabWidget inner instance */
        QDialogButtonBox* button;                   /*!< QDialogButtonBox inner instance */
        DetailsTab* details;                        /*!< Annotation details */
        QJsonDocument config;                       /*!< Configuration Json document */
        QString location;                           /*!< File information */
        QString name;                               /*!< File Name */
};

#endif // ! ANNOTATION_HPP