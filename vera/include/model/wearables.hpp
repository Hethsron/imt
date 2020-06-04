#ifndef WEARABLES_HPP
#define WEARABLES_HPP

/**
 *	\file			wearables.hpp
 *	\brief			Header of Wearables class
 *
 *					This header contains useful class that manages Wearables sensors
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

class Wearables : public Sensor
{
    public:
        /**
         * @fn      Wearables
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       cfg             Configuration data of sensors database  
         */
        explicit Wearables(const QJsonDocument& cfg);

        /**
         * @fn      Wearables
         * @brief   Copy constructor of class
         * 
         * @param[in]       other           Wearables instance
         */
        Wearables(const Wearables& other);

        /**
         * @fn      ~Wearables
         * @brief   Destructor of class
         */
        virtual ~Wearables();

        /**
         * @fn      isEmpty
         * @brief   Virtual function that returns true if location is empty, false otherwise
         * 
         * @return          true if location is empty, false otherwise
         */
        virtual bool isEmpty() const override;

    private:
};

#endif // WEARABLES_HPP