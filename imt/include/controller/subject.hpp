#ifndef SUBJECT_HPP
#define SUBJECT_HPP

/**
 *	\file			subject.hpp
 *	\brief			Header of Subject class
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

#include <controller/observer.hpp>
#include <QtCore/QtCore>

class Subject
{
    public:
        /**
         * @fn      Subject
         * @brief   Default constructor of class
         */
        Subject();

        /**
         * @fn      ~Subject
         * @brief   Destrcutor of class
         */
        virtual ~Subject();

        /**
         * @fn      subscribe
         * @brief   Virtual function that allows to subscribe application's controller
         * 
         * @param[in]       o       Observer instance
         */
        virtual void subscribe(Observer* o) = 0;

        /**
         * @fn      unsubscribe
         * @brief   Virtual function that allows to subscribe application's controller
         * 
         * @param[in]       o       Observer instance
         */
        virtual void unsubscribe(Observer* o) = 0;

        /**
         * @fn      notify
         * @brief   Virtual function that allows to give notification
         */
        virtual void notify() const;

    protected:
        QList<Observer*> collections;               /*!< Collections of Observer instance */
};

#endif // ! SUBJECT_HPP