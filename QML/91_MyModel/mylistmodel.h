#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>

class MyData {
public:
    MyData(QString s, int v): m_string(s), m_value(v) {}
    QString m_string;
    int m_value;
};

class MyListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum MyRoleName {
        Name = Qt::DisplayRole +1,
        Value
    };

    explicit MyListModel(QObject *parent = nullptr);
    static MyListModel * getInstance();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

private:
    QList<MyData> m_data;
};

#endif // MYLISTMODEL_H
