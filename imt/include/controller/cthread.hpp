#ifndef CTHREAD_HPP
#define CTHREAD_HPP

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