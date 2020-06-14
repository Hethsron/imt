#include <model/playlist.hpp>

PlayList::PlayList(QObject* parent)
    : QAbstractItemModel(parent) {}

PlayList::~PlayList() {}

int PlayList::rowCount(const QModelIndex &parent) const {
    // Return number of rows
    return (playlist 
            && !parent.isValid()) ? playlist->mediaCount() : 0;
}

int PlayList::columnCount(const QModelIndex &parent) const {
    // Return number of columns
    return (!parent.isValid()) ? ColumnCount : 0;
}

QModelIndex PlayList::index(int row, int column, const QModelIndex &parent) const {
    // Return index of the item in the model
    return (playlist 
            && !parent.isValid() 
            && row >= 0 
            && row < playlist->mediaCount()
            && column >= 0 
            && column < ColumnCount) ? createIndex(row, column) : QModelIndex();
}

QModelIndex PlayList::parent(const QModelIndex& index) const {
    // Deactive index
    Q_UNUSED(index);

    // Return parent of model item
    return QModelIndex();
}

QVariant PlayList::data(const QModelIndex& index, int role) const {
    // Check if index is valid and if role match with specific role
    if (index.isValid() && role == Qt::DisplayRole) {
        QVariant value = dictionnary[index];
        if (!value.isValid() && index.column() == Title) {
            #if _WIN32
                QUrl location = playlist->media(index.row()).request().url();
            #else
                QUrl location = playlist->media(index.row()).canonicalUrl();
            #endif // _WIN32
            
            return QFileInfo(location.path()).fileName();
        }
        // Return data stored
        return value;
    }
    // Return empty data
    return QVariant();
}

bool PlayList::setData(const QModelIndex& index, const QVariant& value, int role) {
    Q_UNUSED(role);

    // Update value
    dictionnary[index] = value;

    // Emit signal
    emit dataChanged(index, index);

    // Return status
    return true;
}

QMediaPlaylist* PlayList::getPlaylist() const {
    // Returns play list data
    return playlist.data();
}

void PlayList::setPlaylist(QMediaPlaylist* p) {
    // Check if play list data is not null
    if (playlist) {
        disconnect(playlist.data(), &QMediaPlaylist::mediaAboutToBeInserted, this, &PlayList::beginInsertItems);
        disconnect(playlist.data(), &QMediaPlaylist::mediaInserted, this, &PlayList::endInsertItems);
        disconnect(playlist.data(), &QMediaPlaylist::mediaAboutToBeRemoved, this, &PlayList::beginRemoveItems);
        disconnect(playlist.data(), &QMediaPlaylist::mediaRemoved, this, &PlayList::endRemoveItems);
        disconnect(playlist.data(), &QMediaPlaylist::mediaChanged, this, &PlayList::changeItems);
    }
    
    // Begin reset play list data
    beginResetModel();
    playlist.reset(p);

    // Check if play list data is not null
    if (playlist) {
        connect(playlist.data(), &QMediaPlaylist::mediaAboutToBeInserted, this, &PlayList::beginInsertItems);
        connect(playlist.data(), &QMediaPlaylist::mediaInserted, this, &PlayList::endInsertItems);
        connect(playlist.data(), &QMediaPlaylist::mediaAboutToBeRemoved, this, &PlayList::beginRemoveItems);
        connect(playlist.data(), &QMediaPlaylist::mediaRemoved, this, &PlayList::endRemoveItems);
        connect(playlist.data(), &QMediaPlaylist::mediaChanged, this, &PlayList::changeItems);
    }

    // End rest play list data
    endResetModel();
}

void PlayList::beginInsertItems(int start, int end) {
    // Clear data
    dictionnary.clear();

    // Insert data in rows
    beginInsertRows(QModelIndex(), start, end);
}

void PlayList::endInsertItems() {
    endInsertRows();
}

void PlayList::beginRemoveItems(int start, int end) {
    // clear data
    dictionnary.clear();

    // Remove data in rows
    beginRemoveRows(QModelIndex(), start, end);
}

void PlayList::endRemoveItems() {
    endRemoveRows();
}

void PlayList::changeItems(int start, int end) {
    // Clear data
    dictionnary.clear();

    // Emit signal
    emit dataChanged(index(start, 0), index(end, ColumnCount));
}