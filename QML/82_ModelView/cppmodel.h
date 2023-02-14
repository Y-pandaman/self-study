#ifndef CPPMODEL_H
#define CPPMODEL_H

#include <QtCore>
#include <QtGui>

class CppModel : public QAbstractListModel
{
//    Q_OBJECT
public:
    enum RoleNames {
        NameRole = Qt::UserRole,
        HueRole = Qt::UserRole +2,
        SaturationRole = Qt::UserRole + 3,
        BrightnessRole = Qt::UserRole + 4
    };

    explicit CppModel(QObject *parent=0);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const override;

private:
    QList<QString> m_data;
    QList<QColor> m_data_;
    QHash<int, QByteArray> m_roleNames;
};

#endif // CPPMODEL_H
