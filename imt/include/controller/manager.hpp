#ifndef MANAGER_HPP
#define MANAGER_HPP

/**
 *	\file			manager.hpp
 *	\brief			Header of Manager class
 *
 *					This header references useful class to manage splashscreen and main window
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

#include <controller/observer.hpp>
#include <view/splashview.hpp>
#include <view/mainview.hpp>

class Manager : public Observer
{
    public:
         /**
         * @fn      Manager
         * @brief   Explicit default constructor of class
         */
        explicit Manager();

        /**
         * @fn      ~Manager
         * @brief   Destrcutor of class
         */
        virtual ~Manager();

        /**
         * @fn      exec
         * @brief   Virtual function that execute the current manager
         * 
         * @return  Integer value of status
         */
        virtual void exec();

    protected:
        /**
         * @fn      attach
         * @brief   Virtual function that allows to attach application's model
         */
        virtual void attach() override;

        /**
         * @fn      detach
         * @brief   Virtual function that allows to detach application's model
         */
        virtual void detach() override;

        /**
         * @fn      update
         * @brief   Virtual function that allows to update application's model
         */
        virtual void update() override;

    private:
        SplashView* splash;                          /*!< SplashView instance */
        MainView* win;                               /*!< MainView instance */
        

};

#endif // ! MANAGER_HPP
