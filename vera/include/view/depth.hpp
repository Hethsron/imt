#ifndef DEPTH_HPP
#define DEPTH_HPP

/**
 *	\file			depth.hpp
 *	\brief			Header of Depth class
 *
 *					This header contains an useful class to manage depth viewer
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

#include <QtWidgets/QtWidgets>
#include <QtCore/QtCore>

class Depth : public QLabel
{
    public:
        /**
         * @fn      Depth
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent          QWidget parent instance
         */
        explicit Depth(QWidget* parent = nullptr);
        
        /**
         * @fn      Depth
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       fileName        Image file
         * @param[in]       parent          QWidget parent instance
         */
        explicit Depth(const QString& fileName, QWidget* parent = nullptr);
        
        /**
         * @fn      ~Depth
         * @brief   Destructor of class
         */
        virtual ~Depth();
};

#endif // ! DEPTH_HPP