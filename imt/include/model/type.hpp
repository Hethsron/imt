#ifndef TYPE_HPP
#define TYPE_HPP

/**
 *	\file			type.hpp
 *	\brief			Header of Type enumeration class
 *
 *					This header references useful types of sensors
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

enum class Type 
{
    Ambiant,                /*!< Type of Ambiant sensors */
    Annotations,            /*!< Type of Annotations */
    kinect,                 /*!< Type of Kinect sensor */
    Robots,                 /*!< Type of Robots sensors */
    Wearables,              /*!< Type of Wearables sensors */
    Xsens                   /*!< Type of Xsens sensors */
};

#endif // ! TYPE_HPP