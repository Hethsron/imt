#ifndef DEEPREADER_HPP
#define DEEPREADER_HPP

/**
 *	\file			deepreader.hpp
 *	\brief			Header of DeepReader class
 *
 *					This header references useful headers of core module
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

#include <core/command.hpp>
#include <core/processor.hpp>

class DeepReader : public Command
{
    public:
        /**
         * @fn      DeepReader
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       cfg     Distinguished name of sensor database
         */
        explicit DeepReader(const QString& cfg);

        /**
         * @fn      ~DeepReader
         * @brief   Destructor of class
         */
        virtual ~DeepReader();
        
        /**
         * @fn      release
         * @brief   Static function that returns list of subjects from activities of sensor database
         * 
         * @param[in]       cfg     Distinguished name of sensor database
         * @return          List of subjects from activities of sensor database
         */
        static QList<QStringList> release(const QString& cfg);

        /**
         * @fn      execute
         * @brief   Virtual function that performs operations on some external data source
         */
        virtual void execute();

        /**
         * @fn      getAssets
         * @brief   Virtual function that returns list of subjects from activities of sensor database
         * 
         * @return          List of subjects from activities of sensor database
         */
        virtual QList<QStringList> getAssets() const;

    private:
        Processor cpu;                              /*!< Processor instance used as receiver */
        QString config;                             /*!< Distinguished name of sensor database */
        QList<QStringList> assets;                  /*!< List of subjects from activities of sensor database */
};

#endif // ! DEEPREADER_HPP