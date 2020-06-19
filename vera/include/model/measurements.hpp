#ifndef MEASUREMENTS_HPP
#define MEASUREMENTS_HPP

/**
 *	\file			measurements.hpp
 *	\brief			Header of Measurements class
 *
 *					This header contains useful class to manage Wearables measurements
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

#include <QtCore/QtCore>
#include <iostream>

class Measurements
{
    public:
        /**
         * @fn      Measurements
         * @brief   Default constructor of class
         */
        Measurements();

        /**
         * @fn      Measurements
         * @brief   Parameterized constructor of class
         * 
         * @param[in]       key             Measurements name
         */
        Measurements(const QString& key);

        /**
         * @fn      Measurements
         * @brief   Copy constructor of class
         * 
         * @param[in]       other           Measurements instance
         */
        Measurements(const Measurements& other);

        /**
         * @fn      Measurements
         * @brief   Copy constructor of class
         * 
         * @param[in]       ptr             Null instance
         */
        Measurements(std::nullptr_t ptr);

        /**
         * @fn      ~Measurements
         * @brief   Destructor of class
         */
        virtual ~Measurements();

        /**
         * @fn      getName
         * @brief   Virtual function that returns the measurement name
         * 
         * @return          Measurement name
         */
        virtual QString getName() const;

        /**
         * @fn      getTime
         * @brief   Virtual function that returns the measurements time data
         * 
         * @return          Measurements time data
         */
        virtual QVector<double> getTime() const;

        /**
         * @fn      getAccelX
         * @brief   Virtual function that returns the accelerometer X data
         * 
         * @return          Accelerometer X data
         */
        virtual QVector<double> getAccelX() const;

        /**
         * @fn      getAccelY
         * @brief   Virtual function that returns the accelerometer Y data
         * 
         * @return          Accelerometer Y data
         */
        virtual QVector<double> getAccelY() const;

        /**
         * @fn      getAccelZ
         * @brief   Virtual function that returns the accelerometer Z data
         * 
         * @return          Accelerometer Z data
         */
        virtual QVector<double> getAccelZ() const;

        /**
         * @fn      getGyroX
         * @brief   Virtual function that returns the gyroscope X data
         * 
         * @return          Gyroscope X data
         */
        virtual QVector<double> getGyroX() const;

        /**
         * @fn      getGyroY
         * @brief   Virtual function that returns the gyroscope Y data
         * 
         * @return          Gyroscope Y data
         */
        virtual QVector<double> getGyroY() const;

        /**
         * @fn      getGyroZ
         * @brief   Virtual function that returns the gyroscope Z data
         * 
         * @return          Gyroscope Z data
         */
        virtual QVector<double> getGyroZ() const;

        /**
         * @fn      getMaxAccelX
         * @brief   Virtual function that returns the maximum value of the plot accelX
         * 
         * @return          Maximum value of the plot accelX
         */
        virtual double getMaxAccelX() const;

        /**
         * @fn      getMaxAccelY
         * @brief   Virtual function that returns the maximum value of the plot accelY
         * 
         * @return          Maximum value of the plot accelY
         */
        virtual double getMaxAccelY() const;

        /**
         * @fn      getMaxAccelZ
         * @brief   Virtual function that returns the maximum value of the plot accelZ
         * 
         * @return          Maximum value of the plot accelZ
         */
        virtual double getMaxAccelZ() const;

        /**
         * @fn      getMinAccelX
         * @brief   Virtual function that returns the minimum value of the plot accelX
         * 
         * @return          Minimum value of the plot accelX
         */
        virtual double getMinAccelX() const;

        /**
         * @fn      getMinAccelY
         * @brief   Virtual function that returns the minimum value of the plot accelY
         * 
         * @return          Minimum value of the plot accelY
         */
        virtual double getMinAccelY() const;

        /**
         * @fn      getMinAccelZ
         * @brief   Virtual function that returns the minimum value of the plot accelZ
         * 
         * @return          Minimum value of the plot accelZ
         */
        virtual double getMinAccelZ() const;

        /**
         * @fn      getMaxGyroX
         * @brief   Virtual function that returns the maximum value of the plot gyroX
         * 
         * @return          Maximum value of the plot gyroX
         */
        virtual double getMaxGyroX() const;

         /**
         * @fn      getMaxGyroY
         * @brief   Virtual function that returns the maximum value of the plot gyroY
         * 
         * @return          Maximum value of the plot gyroY
         */
        virtual double getMaxGyroY() const;

         /**
         * @fn      getMaxGyroZ
         * @brief   Virtual function that returns the maximum value of the plot gyroZ
         * 
         * @return          Maximum value of the plot gyroZ
         */
        virtual double getMaxGyroZ() const;

        /**
         * @fn      getMinGyroX
         * @brief   Virtual function that returns the minimum value of the plot gyroX
         * 
         * @return          Minimum value of the plot gyroX
         */
        virtual double getMinGyroX() const;

        /**
         * @fn      getMinGyroY
         * @brief   Virtual function that returns the minimum value of the plot gyroY
         * 
         * @return          Minimum value of the plot gyroY
         */
        virtual double getMinGyroY() const;

        /**
         * @fn      getMinGyroZ
         * @brief   Virtual function that returns the minimum value of the plot gyroZ
         * 
         * @return          Minimum value of the plot gyroZ
         */
        virtual double getMinGyroZ() const;

        /**
         * @fn      isEmpty
         * @brief   Virtual function that returns true if time, accelerometer and gyroscope data are empty, false otherwise
         * 
         * @return          true if time, accelerometer and gyroscope data are empty, false otherwise
         */
        virtual bool isEmpty() const;

        /**
         * @fn      clear
         * @brief   Virtual function that clears all time, accelerometer and gyroscope data
         */
        virtual void clear();

        /**
         * @fn      append
         * @brief   Virtual function that appends time, accelerometer and gyroscope data from given JSON object
         * 
         * @param[in]       ms              Current time
         * @param[in]       obj             Given JSON object
         */
        virtual void append(double ms, const QJsonObject& obj);

        /**
         * @fn      operator=
         * @brief   Assignment operator overloading
         * 
         * @param[in]       other           Measurement instance
         * @return          Right Measurement instance
         */
        Measurements& operator=(const Measurements& other);

        /**
         * @fn      operator==
         * @brief   Equality operator overloading
         * 
         * @param[in]       other           Measurement instance
         * @return          true if measurement seems to be the same, false otherwise
         */
        bool operator==(const Measurements& other) const;

        /**
         * @fn      operator!=
         * @brief   Inequality operator overloading
         * 
         * @param[in]       other           Measurement instance
         * @return          true if measurement doesn't seem to be the same, false otherwise
         */
        bool operator!=(const Measurements& other) const;
    
    private:
        QString name;                       /*!< Measurement name */
        QVector<double> time;               /*!< Measurement time */
        QVector<double> accelX;             /*!< Accelerometer X data */
        QVector<double> accelY;             /*!< Accelerometer Y data */
        QVector<double> accelZ;             /*!< Accelerometer Z data */
        QVector<double> gyroX;              /*!< Gyroscope X data */
        QVector<double> gyroY;              /*!< Gyroscope Y data */
        QVector<double> gyroZ;              /*!< Gyroscope Z data */
};

#endif // ! MEASUREMENTS_HPP