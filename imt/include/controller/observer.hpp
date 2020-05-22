#ifndef OBSERVER_HPP
#define OBSERVER_HPP

/**
 *	\file			observer.hpp
 *	\brief			Header of Observer class
 *
 *					This header references useful class to oberve views
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
    
    protected:
        /**
         * @fn      attach
         * @brief   Virtual function that allows to attach application's model
         */
        virtual void attach() = 0;

        /**
         * @fn      detach
         * @brief   Virtual function that allows to detach application's model
         */
        virtual void detach() = 0;

        /**
         * @fn      update
         * @brief   Virtual function that allows to update application's model
         */
        virtual void update() = 0;
};

#endif // ! OBSERVER_HPP
