#ifndef PATTERN_HPP
#define PATTERN_HPP

/**
 *	\file			pattern.hpp
 *	\brief			Header of Pattern struct
 *
 *					This header references useful sensors pattern regular expressions
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

struct Pattern
{
    static const QString Ambiant;               /*!< Regular expression pattern of Ambiant sensors */
    static const QString Annotations;           /*!< Regular expression pattern of Annotations */
    static const QString Kinect;                /*!< Regular expression pattern of Kinect sensor */
    static const QString Robots;                /*!< Regular expression pattern of Robots sensors */
    static const QString Wearables;             /*!< Regular expression pattern of Wearables sensors */
    static const QString Xsens;                 /*!< Regular expression pattern of Xsens sensors */
};

#endif // ! PATTERN_HPP