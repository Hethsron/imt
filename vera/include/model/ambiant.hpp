#ifndef AMBIANT_HPP
#define AMBIANT_HPP

/**
 *	\file			ambiant.hpp
 *	\brief			Header of Ambiant class
 *
 *					This header contains useful class that manages Ambiant sensors
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

#include <model/pattern.hpp>
#include <model/sensor.hpp>

class Ambiant : public Sensor
{
    public:
        /**
         * @fn      Ambiant
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       cfg             Configuration data of sensors database  
         */
        explicit Ambiant(const QJsonDocument& cfg);

        /**
         * @fn      Ambiant
         * @brief   Copy constructor of class
         * 
         * @param[in]       other           Ambiant instance
         */
        Ambiant(const Ambiant& other);

        /**
         * @fn      ~Ambiant
         * @brief   Destructor of class
         */
        virtual ~Ambiant();

        /**
         * @fn      isEmpty
         * @brief   Virtual function that returns true if location is empty, false otherwise
         * 
         * @return          true if location is empty, false otherwise
         */
        virtual bool isEmpty() const override;

    private:
};

#endif // ! AMBIANT_HPP