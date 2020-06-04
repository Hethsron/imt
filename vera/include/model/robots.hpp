#ifndef ROBOTS_HPP
#define ROBOTS_HPP

/**
 *	\file			robots.hpp
 *	\brief			Header of Robots class
 *
 *					This header contains useful class that manages Robots sensors
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

class Robots : public Sensor
{
    public:
        /**
         * @fn      Robots
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       cfg             Configuration data of sensors database  
         */
        explicit Robots(const QJsonDocument& cfg);

        /**
         * @fn      Robots
         * @brief   Copy constructor of class
         * 
         * @param[in]       other           Robots instance
         */
        Robots(const Robots& other);

        /**
         * @fn      ~Robots
         * @brief   Destructor of class
         */
        virtual ~Robots();

        /**
         * @fn      isEmpty
         * @brief   Virtual function that returns true if location is empty, false otherwise
         * 
         * @return          true if location is empty, false otherwise
         */
        virtual bool isEmpty() const override;

    private:
        /**
         * @fn      Robots
         * @brief   Default constructor of class
         */
        Robots();
};

#endif // ! ROBOTS_HPP