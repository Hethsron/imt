#ifndef XSENS_HPP
#define XSENS_HPP

/**
 *	\file			xsens.hpp
 *	\brief			Header of Xsens class
 *
 *					This header contains useful class that manages Xsens sensors
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

class Xsens : public Sensor
{
    public:
        /**
         * @fn      Xsens
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       cfg             Configuration data of sensors database  
         */
        explicit Xsens(const QJsonDocument& cfg);

        /**
         * @fn      Xsens
         * @brief   Copy constructor of class
         * 
         * @param[in]       other           Xsens instance
         */
        Xsens(const Xsens& other);

        /**
         * @fn      ~Xsens
         * @brief   Destructor of class
         */
        virtual ~Xsens();

        /**
         * @fn      isEmpty
         * @brief   Virtual function that returns true if location is empty, false otherwise
         * 
         * @return          true if location is empty, false otherwise
         */
        virtual bool isEmpty() const override;

    private:
};

#endif // ! XSENS_HPP