#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

/**
 *	\file			processor.hpp
 *	\brief			Header of Processor class
 *
 *					This header contains useful class that performs operations on some external data source
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

class Processor
{
    public:
        /**
         * @fn      Processor
         * @brief   Default constructor of class
         */
        Processor();
        
        /**
         * @fn      ~Processor
         * @brief   Destructor of class
         */
        virtual ~Processor();

        /**
         * @fn      write
         * @brief   Virtual function that writes configuration data from given sensors database
         * 
         * @param[in]       filename        Distinguished name of sensors database
         * @return          QJsonObject instance
         */
        virtual QJsonObject write(const QString& filename) const;

        /**
         * @fn      read
         * @brief   Virtual function that reads distinguished name according to given pattern
         * 
         * @param[in]       cfg             Configuration data from sensors database
         * @param[in]       pattern         Given regex pattern
         * @return          Distinguished name extracted from configuration data
         */
        virtual QString read(const QJsonDocument& cfg, const QString& pattern) const;
};

#endif // ! PROCESSOR_HPP