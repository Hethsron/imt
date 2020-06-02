#ifndef OBSERVER_HPP
#define OBSERVER_HPP

/**
 *	\file			observer.hpp
 *	\brief			Header of Observer class
 *
 *					This header references useful class to oberve views
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

class Observer
{
    public:
        /**
         * @fn      Observer
         * @brief   Default constructor of class
         */
        Observer();

        /**
         * @fn      ~Observer
         * @brief   Destrcutor of class
         */
        virtual ~Observer();
    
        /**
         * @fn      notify
         * @brief   Virtual function that allows to treat Observer
         */
        virtual void notify() = 0;
};

#endif // ! OBSERVER_HPP
