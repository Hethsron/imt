#ifndef AUDIOCHART_HPP
#define AUDIOCHART_HPP

/**
 *	\file			audiochart.hpp
 *	\brief			Header of AudioChart class
 *
 *					This header contains an useful class to manage audio chart on a media player
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

#include <QtWidgets/QtWidgets>
#include <QtCore/QtCore>

class AudioChart : public QWidget
{
    public:
        /**
         * @fn      AudioChart
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent      QWidget parent instance
         */
        explicit AudioChart(QWidget* parent = nullptr);

        /**
         * @fn      ~AudioChart
         * @brief   Destructor of class
         */
        virtual ~AudioChart();

        /**
         * @fn      setLevel
         * @brief   Virtual function that sets inner audio chart level
         * 
         * @param[in]       lv          Audio chart level
         */
        virtual void setLevel(qreal lv);

    protected:
        /**
         * @fn      paintEvent
         * @brief   Virtual function that receives paint event for the widget
         * 
         * @param[in]       event       Paint event received
         */
        virtual void paintEvent(QPaintEvent* event) override;

    private:
        qreal level;                                /*!< Audio chart inner level */
};

#endif // ! AUDIOCHART_HPP