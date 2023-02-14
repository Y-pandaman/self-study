#include "cppmodel.h"

CppModel::CppModel(QObject *parent):QAbstractListModel(parent)
{
    m_data = QColor::colorNames();
    m_roleNames[NameRole] = "name";
    m_roleNames[HueRole] = "hue";
    m_roleNames[SaturationRole] = "saturation";
    m_roleNames[BrightnessRole] = "brightness";

    for(const QString& name: QColor::colorNames()) {
        m_data_.append(QColor(name));
    }
}

int CppModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

QVariant CppModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
   const  QColor& color = m_data_.at(row);

    switch(role) {
    case Qt::DisplayRole:
        return m_data.value(row);
    case NameRole:
        return color.name();
    case HueRole:
        return color.hueF();
    case SaturationRole:
        return color.saturationF();
    case BrightnessRole:
        return color.lightnessF();
    }
    return QVariant();
}

QHash<int, QByteArray> CppModel::roleNames() const
{
    return m_roleNames;
}
