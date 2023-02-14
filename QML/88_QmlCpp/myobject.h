#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QtQml>

class MyObject : public QObject
{
    Q_OBJECT
//    QML_ELEMENT
public:
    explicit MyObject(QObject *parent = nullptr);
    static MyObject * getInstance();

    int iValue() const;
    void setIValue(int iValue);

    QString sString() const;
    void setSString(const QString &sString);

    Q_INVOKABLE void func();  // 添加Q_INVOKABLE宏，qml端可直接访问该函数

public slots:
    void cppSlot(int i, QString s);

signals:
    void iValueChanged();
    void sStringChanged();
    void cppSig(QVariant i, QVariant s);

private:
    int m_iValue;
    QString m_sString;

//    Q_PROPERTY(int iValue READ iValue WRITE setIValue NOTIFY iValueChanged)
//    Q_PROPERTY(QString sString READ sString WRITE setSString NOTIFY sStringChanged)
    Q_PROPERTY(int iValue MEMBER m_iValue NOTIFY iValueChanged)
    Q_PROPERTY(QString sString MEMBER m_sString NOTIFY sStringChanged)

};

#endif // MYOBJECT_H
