#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

/**
 *	\file			playlist.hpp
 *	\brief			Header of PlayList class
 *
 *					This header contains useful class to manage media player list
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
#include <QtCore/QtCore>

class PlayList : public QAbstractItemModel
{
    public:
        /**
         * @fn      PlayList
         * @brief   Explicit parameterized constructor of class
         * 
         * @param[in]       parent      QObject parent instance
         */
        explicit PlayList(QObject* parent = nullptr);

        /**
         * @fn      ~PlayList
         * @brief   Destructor of class
         */
        virtual ~PlayList();

        /**
         * @fn      rowCount
         * @brief   Virtual function that returns the number of rows under the given parent
         * 
         * @param[in]       parent      Parent model index
         * @return          Number of rows
         */
        virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        
        /**
         * @fn      columnCount
         * @brief   Virtual function that returns the number of columns for the children of the given parent
         * 
         * @param[in]       parent      Parent model index
         * @return          Number of columns for the children 
         */
        virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        
        /**
         * @fn      index
         * @brief   Virtual function that returns the index of the item in the model specified by the given row, column and parent index
         * 
         * @param[in]       row         Row of the item in the model
         * @param[in]       column      Column of the item in the model
         * @param[in]       parent      Parent model index
         * @return          Index of the item in the model
         */
        virtual QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
        
        /**
         * @fn      parent
         * @brief   Virtual function that returns the parent of the model item with the given index
         * 
         * @param[in]       index       Index model item
         * @return          Parent of the model item
         */
        virtual QModelIndex parent(const QModelIndex& index) const override;
        
        /**
         * @fn      data
         * @brief   Virtual function that returns the data stored under the given role for the item referred to by the index
         * 
         * @param[in]       index       Index that referred item in the data
         * @param[in]       role        Data role
         * @return          Data stored
         */
        virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        
        /**
         * @fn      setData
         * @brief   Virtual function that sets the role data for the item at index to value
         * 
         * @param[in]       index       Index model item
         * @param[in]       value       Value of item
         * @param[in]       role        Role of data
         * @return          true if successful; otherwise returns false
         */
        virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::DisplayRole) override;
        
        /**
         * @fn      getPlaylist
         * @brief   Virtual function that returns media play list data
         * 
         * @return          Media play list array
         */
        virtual QMediaPlaylist* getPlaylist() const;

        /**
         * @fn      setPlaylist
         * @brief   Virtual function that set media play list data
         * 
         * @param[in]       p           QMediaPlaylist instance
         */
        virtual void setPlaylist(QMediaPlaylist* p);

        enum Column
        {
            Title = 0,                                          /*!< Column title index */
            ColumnCount                                         /*!< Column count */
        };

    private slots:
        /**
         * @fn      beginInsertItems
         * @brief   Virtual function that inserts item in the begining of the list
         * 
         * @param[in]       start       Started index of item
         * @param[in]       end         Ended index of item
         */
        virtual void beginInsertItems(int start, int end);

        /**
         * @fn      endInsertItems
         * @brief   Virtual function that inserts item in the end of list
         */
        virtual void endInsertItems();

        /**
         * @fn      beginRemoveItems
         * @brief   Virtual function that removes item in the begining of the list
         * 
         * @param[in]       start       Started index of item
         * @param[in]       end         Ended index of item
         */
        virtual void beginRemoveItems(int start, int end);

        /**
         * @fn      endRemoveItems
         * @brief   Virtual function that removes item in the end of list
         */
        virtual void endRemoveItems();

        /**
         * @fn      changeItems
         * @brief   Virtual function that change item in the list
         * 
         * @param[in]       start       Started index of item
         * @param[in]       end         Ended index of item
         */
        virtual void changeItems(int start, int end);

    private:
        QScopedPointer<QMediaPlaylist> playlist;                /*!< Media play list array */
        QMap<QModelIndex, QVariant> dictionnary;                /*!< Dictionnary of data */
};

#endif // ! PLAYLIST_HPP