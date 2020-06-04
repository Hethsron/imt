#ifndef BACKWRITER_HPP
#define BACKWRITER_HPP

/**
 *	\file			backwriter.hpp
 *	\brief			Header of BackWriter class
 *
 *					This header contains useful class provides a convenient interface for working with URLs from media files
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

#include <core/processor.hpp>
#include <core/command.hpp>

class BackWriter : public Command
{
    public:
        /**
         * @fn      BackWriter
         * @brief   Explicit paramterized constructor of class
         * 
         * @param[in]       cfg         Distinguished name of sensor database
         */
        explicit BackWriter(const QString& cfg);

        /**
         * @fn      ~BackWriter
         * @brief   Destructor of class
         */
        virtual ~BackWriter();

        /**
         * @fn       release
         * @brief    Static function that writes configuration data from sensors database
         *  
         * @param[in]       cfg     Distinguished name of sensors database
         * @return          Media files URLs
         */
        static QList<QUrl> release(const QString& cfg);

        /**
         * @fn      getUrls
         * @brief   Virtual function that returns media files URLs
         * 
         * @return          Media files URLs
         */
        virtual QList<QUrl> getUrls() const;

        /**
         * @fn      execute
         * @brief   Virtual function that writes configuration data from sensors database
         */
        virtual void execute() override;

    private:
        Processor cpu;                              /*!< Processor instance used as receiver */
        QString config;                             /*!< Distinguished name of sensors database */
        QList<QUrl> urls;                           /*!< Media files URLs */
};

#endif // ! BACKWRITER_HPP