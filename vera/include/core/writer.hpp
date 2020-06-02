#ifndef WRITER_HPP
#define WRITER_HPP

/**
 *	\file			writer.hpp
 *	\brief			Header of Writer class
 *
 *					This header contains useful class that writes configuration data
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

class Writer : public Command
{
    public:
        /**
         * @fn      Writer
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       cfg     Distinguished name of sensors database
         */
        explicit Writer(const QString& cfg);

        /**
         * @fn      ~Writer
         * @brief   Destructor of class
         */
        virtual ~Writer();

        /**
         * @fn       release
         * @brief    Static function that writes configuration data from sensors database
         *  
         * @param[in]       cfg     Distinguished name of sensors database
         * @return          QJsonObject instance
         */
        static QJsonObject release(const QString& cfg);

        /**
         * @fn      getJson
         * @brief   Virtual function that returns inner QJSonObject instance
         * 
         * @return          QJsonObject instance
         */
        virtual QJsonObject getJson() const;

        /**
         * @fn      execute
         * @brief   Virtual function that writes configuration data from sensors database
         */
        virtual void execute() override;

    private:
        Processor cpu;                              /*!< Processor instance used as receiver */
        QString config;                             /*!< Distinguished name of sensors database */
        QJsonObject json;                           /*!< Configuration file Json data */
};

#endif // ! WRITER_HPP