#ifndef FILESYSTEMMODEL_H
#define FILESYSTEMMODEL_H

#include <QtCore/QAbstractListModel>

struct ItemData{
    ItemData(const QString &_path, const QString &_name, const QString &_size, const QString &m_changeTime, const quint8 _type)
        : m_path(_path), m_name(_name), m_size(_size), m_changeTime(m_changeTime), m_type(_type) {}
    QString m_path{};
    QString m_name{};
    QString m_size{};
    QString m_changeTime{};
    quint8 m_type{};
};

class FileSystemModel : public QAbstractListModel
{
    Q_OBJECT
    enum ModelRoles{
        itemIndex = Qt::UserRole + 1,
        itemPath,
        itemName,
        itemSize,
        itemType,
        itemChangeTime
    };
public:
    explicit FileSystemModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data (const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    Q_INVOKABLE void setNewPath(const QString &_path);

    void clearModel();

signals:
    void signal_fileSelected();
private:
    std::vector <ItemData> m_filesSystem;
};

#endif // FILESYSTEMMODEL_H
