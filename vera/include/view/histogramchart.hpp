#ifndef HISTOGRAMCHART_HPP
#define HISTOGRAMCHART_HPP

/**
 *	\file			histogramchart.hpp
 *	\brief			Header of HistogramChart class
 *
 *					This header contains an useful class to manage histogram chart on a media player
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

#include <view/audiochart.hpp>
#include <core/processor.hpp>

/**
 * @fn              getBufferLevel
 * @brief           Template static functin that returns audio buffer levels for each channel
 * 
 * @param[in]       buffer            Audio buffer
 * @param[in]       frame             Frame count
 * @param[in]       channel           Channel count
 * @return          Audio buffer levels
 */
template <class T>
static QVector<qreal> getBufferLevel(const T* buffer, int frame, int channel);

class HistogramChart : public QWidget
{
    Q_OBJECT
    
    public:
        /**
         * @fn      HistogramChart
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent      QWidget parent instance
         */
        explicit HistogramChart(QWidget* parent = nullptr);

        /**
         * @fn      ~HistogramChart
         * @brief   Destructor of class
         */
        virtual ~HistogramChart();

        /**
         * @fn      setLevel
         * @brief   Virtual function that sets histogram chart level
         * 
         * @param[in]       lv          Histogram chart level
         */
        virtual void setLevel(int lv);

    public slots:
        /**
         * @fn      readFrame
         * @brief   Virtual function that reads video frame for media player
         * 
         * @param[in]       frame       Video frame
         */
        virtual void readFrame(const QVideoFrame& frame);

        /**
         * @fn      readBuffer
         * @brief   Virtual function that reads audio buffer for media player
         * 
         * @param[in]       buffer      Audio buffer
         */
        virtual void readBuffer(const QAudioBuffer& buffer);

        /**
         * @fn      setHistogram
         * @brief   Virtual function that sets histogram chart inner data on media player
         * 
         * @param[in]       hist        Histogram chart data
         */
        virtual void setHistogram(const QVector<qreal>& hist);

    protected:
        /**
         * @fn      paintEvent
         * @brief   Virtual function that receives paint event for the widget
         * 
         * @param[in]       event       Paint event received
         */
        virtual void paintEvent(QPaintEvent* event) override;

    private:
    	/**
         * @fn      getBufferLevels
         * @brief   Virtual function that returns audio buffer levels for each channel
         * 
         * @param[in]       buffer      Audio buffer
         * @return          Audio buffer levels
         */
        QVector<qreal> getBufferLevels(const QAudioBuffer& buffer) const;

        /**
         * @fn      getPeakValue
         * @brief   Virtual function that returns peak value of audio format
         * 
         * @param[in]       format      Audio format
         */
        virtual qreal getPeakValue(const QAudioFormat& format) const;
        
        QVector<AudioChart*> audio;                             /*!< Histogram chart inner Audio chart viewers */
        QVector<qreal> histogram;                               /*!< Histogram chart inner data */
        QThread thread;                                         /*!< Histogram chart inner Processor thread */
        Processor cpu;                                          /*!< Histogram chart inner Processor */
        bool isBusy;                                            /*!< histogram chart inner status */
        int level;                                              /*!< Histogram chart inner level */

};

#endif // ! HISOGRAMCHART_HPP