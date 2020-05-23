#ifndef ROUTER_HPP
#define ROUTER_HPP

/**
 *	\file			router.hpp
 *	\brief			Header of Router class
 *
 *					This header contains useful class to manage Observer instance
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

#include <controller/subject.hpp>
#include <controller/observer.hpp>

namespace ROUTER {
    /**
     * @fn          render
     * @brief       Rendering one shot notification
     * 
     * @param[in]           o       Observer instance
     */
    void render(Observer* o);
}

class Router : public Subject
{
    public:
        /**
         * @fn      Router
         * @brief   Default constructor of class
         */
        Router();

        /**
         * @fn      ~Router
         * @brief   Destrcutor of class
         */
        virtual ~Router();

        /**
         * @fn      subscribe
         * @brief   Virtual function that allows to subscribe application's controller
         * 
         * @param[in]       o       Observer instance
         */
        virtual void subscribe(Observer* o) override;

        /**
         * @fn      unsubscribe
         * @brief   Virtual function that allows to subscribe application's controller
         * 
         * @param[in]       o       Observer instance
         */
        virtual void unsubscribe(Observer* o) override;
};

#endif // ! ROUTER_HPP