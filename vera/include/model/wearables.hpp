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

#include <model/measurements.hpp>
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

        /**
         * @fn      contains
         * @brief   Virtual function that returns true if measurement data contains given name, false otherwise
         * 
         * @param[in]       name            Given measurement name
         * @return          true if measurement data contains given name, false otherwise
         */
        virtual bool contains(const QString& name) const;

        /**
         * @fn      get
         * @brief   Virtual function that returns the measurement data that match with the given name, nullptr otherwise
         * 
         * @param[in]       name            Given measurement name
         * @return          Measurement data, nullptr otherwise
         */
        virtual Measurements* get(const QString& name) const;

        /**
         * @fn      append
         * @brief   Virtual function that appends measurements data from given distinguished name of JSON file
         * 
         * @param[in]       fileName        Given distinguished name of JSON file
         */
        virtual void append(const QString& fileName);

        /**
         * @fn      clear
         * @brief   Virtual function that clears the measurements data
         */
        virtual void clear();

    private:
        /**
         * @fn      Wearables
         * @brief   Default constructor of class
         */
        Wearables();

        QVector<Measurements*> measurements;                /*!< Wearables measurements data */
};

#endif // WEARABLES_HPP