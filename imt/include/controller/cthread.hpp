#ifndef CTHREAD_HPP
#define CTHREAD_HPP

/**
 *	\file			cthread.hpp
 *	\brief			Header of CThread class
 *
 *					This header contains an useful class to manage Controller QThread
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
 *  \date 			3rd June 2019
 */

#include <QtCore/QThread>

class CThread : public QThread
{
    public:
        /**
         * @fn      CThread
         * @brief   Default constructor of class
         */
        CThread();

        /**
         * @fn      ~CThread
         * @brief   Destructor of class
         */
        virtual ~CThread();

        /**
         * @fn      run
         * @brief   Reimplementation of QThread running function
         */
        void run() override;
    
    signals:
        /**
         * @fn      mysignal
         * @brief   Owner signal
         * 
         * @param[in]   i   Integer value
         */
        void mysignal(int);

};

#endif // ! CTHREAD_HPP