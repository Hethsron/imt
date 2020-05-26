#ifndef READER_HPP
#define READER_HPP

/**
 *	\file			reader.hpp
 *	\brief			Header of Reader class
 *
 *					This header references useful headers of core module
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

#include <core/command.hpp>
#include <core/processor.hpp>

class Reader : public Command
{
    public:
        /**
         * @fn      Reader
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       cfg     Configuration data from sensors database
         * @param[in]       p       Pattern of regex
         */
        explicit Reader(const QJsonDocument& cfg, const QString& p);

        /**
         * @fn      ~Reader
         * @brief   Destructor of class
         */
        virtual ~Reader();
        
        /**
         * @fn      release
         * @brief   Static function that reads configuration data from sensors database
         * 
         * @param[in]       cfg     Configuration data from sensors database
         * @param[in]       p       Pattern of regex
         * @return          Distinguished name of extracted directory
         */
        static QString release(const QJsonDocument& cfg, const QString& p);

        /**
         * @fn      getDir
         * @brief   Virtual function that returns inner distinguished name of extracted directory
         * 
         * @return  Distinguished name of extracted directory
         */
        virtual QString getDir() const;

        /**
         * @fn      execute
         * @brief   Virtual function that reads configuration data from sensors database
         */
        virtual void execute() override;

    private:
        Processor cpu;                              /*!< Processor instance used as receiver */
        QJsonDocument config;                       /*!< Configuration data from sensors database */
        QString pattern;                            /*!< Pattern of regex */
        QString dir;                                /*!< Distinguished name of extracted directory */
};

#endif // READER_HPP