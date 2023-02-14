#ifndef DOMXML_H
#define DOMXML_H
#include <QDomDocument>
#include <QString>
#include <QStringList>

class DomXML {
public:
  DomXML();

  static void createXML(QString filePath); // 创建XML空文件
  static void appendXML(QString filePath, QStringList list);
  static void writeXML(QDomDocument &doc, QDomElement &root, QStringList list);
  static void readXML(QString filePath, QStringList &factoryList,
                      QStringList &brandList, QStringList &priceList,
                      QStringList &numList, QStringList &totalList);
};

#endif // DOMXML_H
