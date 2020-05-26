#ifndef DEEPREADER_HPP
#define DEEPREADER_HPP

/**
 *	\file			deepreader.hpp
 *	\brief			Header of DeepReader class
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

    private:
        Processor cpu;                              /*!< Processor instance used as receiver */
        QString config;                             /*!< Distinguished name of sensor database */
};

#endif // ! DEEPREADER_HPP