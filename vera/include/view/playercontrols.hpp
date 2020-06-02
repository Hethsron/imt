#ifndef PLAYERCONTROLS_HPP
#define PLAYERCONTROLS_HPP

/**
 *	\file			playercontrols.hpp
 *	\brief			Header of PlayerControls class
 *
 *					This header contains useful class to manage media  player
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

#include <QtMultimedia/QtMultimedia>
#include <QtWidgets/QtWidgets>
#include <QtCore/QtCore>

class PlayerControls : public QWidget
{
    Q_OBJECT
    
    public:
        /**
         * @fn      PlayerControls
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent      QWidget parent instance
         */
        explicit PlayerControls(QWidget* parent = nullptr);

        /**
         * @fn      ~PlayerControls
         * @brief   Destructor of class
         */
        virtual ~PlayerControls();

        /**
         * @fn      getState
         * @brief   Virtual function that returns state of media player
         * 
         * @return          State of media player
         */
        virtual QMediaPlayer::State getState() const;

        /**
         * @fn      getVolume
         * @brief   Virtual function that returns volume of media player
         * 
         * @return          Volume of media player
         */
        virtual int getVolume() const;

        /**
         * @fn      isMuted
         * @brief   Virtual function that returns muted state of media player
         * 
         * @return          Muted state of media player
         */
        virtual bool isMuted() const;

        /**
         * @fn      getRate
         * @brief   Virtual function that returns playback rate of media player
         * 
         * @return          Playback rate of media player
         */
        virtual qreal getRate() const;

    public slots:
        /**
         * @fn      setState
         * @brief   Virtual function that sets state of media player
         * 
         * @param[in]       s       State of media player
         */
        virtual void setState(QMediaPlayer::State s);

        /**
         * @fn      setvolume
         * @brief   Virtual function that sets volume of media player
         * 
         * @param[in]       v       Volume of media player
         */
        virtual void setVolume(int v);

        /**
         * @fn      setMuted
         * @brief   Virtual function that sets muted state of media player
         * 
         * @param[in]       m       Muted state of media player
         */
        virtual void setMuted(bool m);

        /**
         * @fn      setRate
         * @brief   Virtual function that sets playback rate of media player
         * 
         * @param[in]       r       Playback rate of media player
         */
        virtual void setRate(float r);
    
    signals:
        /**
         * @fn      play
         * @brief   AUTOMOC function that references play signal
         */
        void play();

        /**
         * @fn      pause
         * @brief   AUTOMOC function that references pause signal
         */
        void pause();

        /**
         * @fn      stop
         * @brief   AUTOMOC function that references stop signal
         */
        void stop();

        /**
         * @fn      next
         * @brief   AUTOMOC function that references next signal
         */
        void next();

        /**
         * @fn      previous
         * @brief   AUTOMOC function that references previous signal
         */
        void previous();

        /**
         * @fn      changeVolume
         * @brief   AUTOMOC function that references changing volume signal
         * 
         * @param[in]       v       Volume of media player
         */
        void changeVolume(int v);

        /**
         * @fn      changeMuting
         * @brief   AUTOMOC function that references changing mute signal
         * 
         * @param[in]       m       Muted state of media player
         */
        void changeMuting(bool m);

        /**
         * @fn      changeRate
         * @brief   AUTOMOC function that references changing state signal
         * 
         * @param[in]       r       Playback rate of media player
         */
        void changeRate(qreal r);

    private slots:
        /**
         * @fn      playClicked
         * @brief   Virtual function that references play clicked action
         */
        virtual void playClicked();

        /**
         * @fn      muteClicked
         * @brief   Virtual function that references mute clicked action
         */
        virtual void muteClicked();
        
        /**
         * @fn      updateRate
         * @brief   Virtual function that references playback rate action
         */
        virtual void updateRate();

        /**
         * @fn      onVolumeSlidervalueChanged
         * @brief   Virtual function that references volume slider value changed action
         */
        virtual void onVolumeSliderValueChanged();

    private:
        /**
         * @fn      assignment
         * @brief   Virtual function that references assignment of new values
         */
        virtual void assignment();

        QMediaPlayer::State state;                      /*!< State of media player */
        QAbstractSlider* volume;                        /*!< Volume slider of media player */
        bool muted;                                     /*!< Muted state of media player */
        QComboBox* rate;                                /*!< Playback rate box of media player */
        QAbstractButton* playBut;                       /*!< Play button of media player */
        QAbstractButton* stopBut;                       /*!< Stop button of media player */
        QAbstractButton* nextBut;                       /*!< Next button of media player */
        QAbstractButton* prevBut;                       /*!< Previous button of media player */
        QAbstractButton* muteBut;                       /*!< Mute button of media player */
};

#endif // ! PLAYERCONTROLS_HPP