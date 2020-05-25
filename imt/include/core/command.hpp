#ifndef COMMAND_HPP
#define COMMAND_HPP

/**
 *	\file			command.hpp
 *	\brief			Header of Command class
 *
 *					This header contains useful class that encapsulates the notion of invocation
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

class Command
{
    public:
        /**
         * @fn      Command
         * @brief   Default constructor of class
         */
        Command();

        /**
         * @fn      ~Command
         * @brief   Destructor of class
         */
        virtual ~Command();

        /**
         * @fn      execute
         * @brief   Virtual function that performs operations on some external data source
         */
        virtual void execute() = 0;
};

#endif // ! COMMAND_HPP