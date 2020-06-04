#ifndef KINECT_HPP
#define KINECT_HPP

/**
 *	\file			kinect.hpp
 *	\brief			Header of Kinect class
 *
 *					This header contains useful class that manages Kinect sensor
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

#include <model/pattern.hpp>
#include <model/sensor.hpp>

class Kinect : public Sensor
{
    public:
        /**
         * @fn      Kinect
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       cfg             Configuration data of sensors database  
         */
        explicit Kinect(const QJsonDocument& cfg);

        /**
         * @fn      Kinect
         * @brief   Copy constructor of class
         * 
         * @param[in]       other           Kinect instance
         */
        Kinect(const Kinect& other);

        /**
         * @fn      ~Kinect
         * @brief   Destructor of class
         */
        virtual ~Kinect();

        /**
         * @fn      isEmpty
         * @brief   Virtual function that returns true if location is empty, false otherwise
         * 
         * @return          true if location is empty, false otherwise
         */
        virtual bool isEmpty() const override;

    private:
        /**
         * @fn      Kinect
         * @brief   Default constructor of class
         */
        Kinect();
};

#endif // ! KINECT_HPP