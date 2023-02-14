#include "mylistmodel.h"

MyListModel::MyListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_data.append(MyData("zhangsan", 111));
    m_data.append(MyData("lisi", 222));
    m_data.append(MyData("wangwu", 333));
    m_data.append(MyData("zhaoliu", 444));
}

MyListModel *MyListModel::getInstance()
{
    static MyListModel * obj = new MyListModel;
    return obj;
}

QVariant MyListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

int MyListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
    return m_data.count();
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    if(role == MyRoleName::Name) {
            return m_data[index.row()].m_string;
    }
    else if(role == MyRoleName::Value) {
        return m_data[index.row()].m_value;
    }

    return QVariant();
}

// 字符串和枚举的映射
QHash<int, QByteArray> MyListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(MyRoleName::Name, "name"); // 字符串是QML端用
    roles.insert(MyRoleName::Value, "value"); // 枚举是C++中的data函数来判断
    return roles;
}
