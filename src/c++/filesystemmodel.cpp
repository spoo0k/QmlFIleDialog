#include "filesystemmodel.h"
#include <QtCore/QDir>
#include <QtCore/QDebug>
#include <QtCore/QDateTime>
#include <cmath>

FileSystemModel::FileSystemModel(QObject *parent)
    : QAbstractListModel{parent}
{

}

int FileSystemModel::rowCount(const QModelIndex &) const
{
    return m_filesSystem.size();
}

QVariant FileSystemModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) {
        return QVariant();
    }
    switch (role) {
    case ModelRoles::itemIndex:{
        return index.row();
    }
    case ModelRoles::itemPath:{
        return m_filesSystem.at(index.row()).m_path;
    }
    case ModelRoles::itemName:{
        return m_filesSystem.at(index.row()).m_name;
    }
    case ModelRoles::itemChangeTime:{
        return m_filesSystem.at(index.row()).m_changeTime;
    }
    case ModelRoles::itemSize:{
        return m_filesSystem.at(index.row()).m_size;
    }
    case ModelRoles::itemType:{
        return m_filesSystem.at(index.row()).m_type;
    }
    default:{
        return QVariant();
    }
    }
}

QHash<int, QByteArray> FileSystemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ModelRoles::itemIndex] = "itemIndex";
    roles[ModelRoles::itemPath] = "itemPath";
    roles[ModelRoles::itemName] = "itemName";
    roles[ModelRoles::itemSize] = "itemSize";
    roles[ModelRoles::itemType] = "itemType";
    roles[ModelRoles::itemChangeTime] = "itemChangeTime";
    return roles;
}

void FileSystemModel::setNewPath(const QString &_path)
{
    auto file = QFileInfo(_path);
    if (!file.exists()){
        return;
    }
    if (file.isFile()){
        emit signal_fileSelected();
        return;
    }
    if(!file.isDir()){
        /// ????
        return;
    }
    clearModel();
    auto dir = QDir(_path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::Dirs);
    for (auto item : dir.entryInfoList()){
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        if (item.isDir()){
            qDebug() << item.filePath() << item.metadataChangeTime() << QDir(item.filePath()).count() - 2;
            m_filesSystem.push_back(ItemData(item.filePath(), item.fileName(), QString::number(QDir(item.filePath()).count() - 2), item.lastModified().toString(), 1));
            continue;
        }
        quint64 fileSize = item.size();
        QString fileSizeString;
        if (fileSize < 1024) {
            fileSizeString = QString::number(fileSize) + "b";
        }
        else if (fileSize > 1024 && fileSize < std::pow(1024, 2)) {
            fileSizeString =  QString::number(fileSize / 1024, 'f', 3) + " kb";
        }
        else if (fileSize > std::pow(1024, 2) && fileSize < std::pow(1024, 3)) {
//            return (fileSize / (1024 * 1024)).toFixed(3) + " mb";
            fileSizeString =  QString::number(fileSize / std::pow(1024, 2), 'f', 3) + " mb";
        }
        else if (fileSize > std::pow(1024, 3) && fileSize < std::pow(1024, 4)) {
//            return (fileSize / (1024 * 1024)).toFixed(3) + " mb";
            fileSizeString =  QString::number(fileSize / std::pow(1024, 3), 'f', 3) + " gb";
        }

        m_filesSystem.push_back(ItemData(item.filePath(), item.fileName(), fileSizeString, item.lastModified().toString(), 1));
        qDebug() << item.filePath() << item.metadataChangeTime() << item.size();
        endInsertRows();
    }
}

void FileSystemModel::clearModel()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_filesSystem.clear();
    endRemoveRows();
}
