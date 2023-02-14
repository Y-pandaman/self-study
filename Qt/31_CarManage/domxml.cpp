#include "domxml.h"
#include <QDateTime>
#include <QDebug>
#include <QDomDocument>              // 文件
#include <QDomElement>               // 元素
#include <QDomProcessingInstruction> // 格式头部
#include <QFile>
#include <QTextStream> // 文本流
#define cout qDebug() << __FILE__ << __LINE__

DomXML::DomXML() {}

void DomXML::createXML(QString filePath) {
  QFile file(filePath); // 关联文件名
  if (file.exists()) {
    cout << "文件已存在";
    return; // 如果存在就不创建
  } else {
    bool isOk = file.open(QIODevice::WriteOnly);
    if (isOk) {
      QDomDocument doc; // 创建xml文档对象

      // 创建xml头部格式
      QDomProcessingInstruction ins;
      ins = doc.createProcessingInstruction(
          "xml", "version=\'1.0\' encoding=\'utf-8\'");
      // 追加元素
      doc.appendChild(ins);

      // 根节点元素
      QDomElement root = doc.createElement("日销售清单");
      doc.appendChild(root);

      // 保存
      QTextStream textStream(&file); // 文本流关联文件
      doc.save(textStream, 4);       // 4代表缩进距离
      file.close();

    } else {
      cout << "错误";
      return;
    }
  }
}

void DomXML::appendXML(QString filePath, QStringList list) {
  QFile file(filePath);
  bool isOk = file.open(QIODevice::ReadOnly);
  if (isOk) {
    // file和XML文档对象关联
    QDomDocument doc;
    isOk = doc.setContent(&file);
    if (isOk) {     // 关联成功
      file.close(); // 关闭文件
      // 获取根节点元素
      QDomElement root = doc.documentElement();

      QDateTime date = QDateTime::currentDateTime();
      QString dateStr = date.toString("yyyy-MM-dd");

      // 判断根节点下有没有子节点
      if (root.hasChildNodes()) {
        // 查找最后一个子节点
        QDomElement lastEmt = root.lastChildElement();
        if (lastEmt.attribute("date") == dateStr) { // 判断是否有当天日期
          writeXML(doc, lastEmt, list);
        } else {
          // 创建日期子节点元素
          QDomElement dateEmt = doc.createElement("日期");
          // 创建date属性
          QDomAttr dateAttr = doc.createAttribute("date");
          // 设置属性的值
          dateAttr.setNodeValue(dateStr);
          // 关联节点和属性
          dateEmt.setAttributeNode(dateAttr);
          // 把日期节点追加到根节点
          root.appendChild(dateEmt);
          // 写有效数据
          writeXML(doc, dateEmt, list);
        }
      } else {
        // 创建日期子节点元素
        QDomElement dateEmt = doc.createElement("日期");
        // 创建date属性
        QDomAttr dateAttr = doc.createAttribute("date");
        // 设置属性的值
        dateAttr.setNodeValue(dateStr);
        // 关联节点和属性
        dateEmt.setAttributeNode(dateAttr);
        // 把日期节点追加到根节点
        root.appendChild(dateEmt);
        // 写有效数据
        writeXML(doc, dateEmt, list);
      }

      // 保存文件
      isOk = file.open(QIODevice::WriteOnly);
      if (isOk) {
        QTextStream textStream(&file);
        doc.save(textStream, 4);
        file.close();
      }

    } else {
      cout << "关联失败";
      return;
    }
  } else {
    cout << "文件不存在";
  }
}

void DomXML::writeXML(QDomDocument &doc, QDomElement &root, QStringList list) {
  // 获取当前时间
  QDateTime time = QDateTime::currentDateTime();
  QString timeStr = time.toString("hh-mm-ss");

  // 创建时间节点元素
  QDomElement timeEmt = doc.createElement("时间");
  // 创建属性
  QDomAttr timeAttr = doc.createAttribute("time");
  // 给属性设置值
  timeAttr.setNodeValue(timeStr);
  // 关联节点元素和属性
  timeEmt.setAttributeNode(timeAttr);
  // 把时间节点追加到日期节点
  root.appendChild(timeEmt);

  QDomElement factory = doc.createElement("厂家");
  QDomElement brand = doc.createElement("品牌");
  QDomElement price = doc.createElement("报价");
  QDomElement num = doc.createElement("数量");
  QDomElement total = doc.createElement("金额");

  QDomText factory_text = doc.createTextNode(list.at(0));
  factory.appendChild(factory_text);
  QDomText brand_text = doc.createTextNode(list.at(1));
  brand.appendChild(brand_text);
  QDomText price_text = doc.createTextNode(list.at(2));
  price.appendChild(price_text);
  QDomText num_text = doc.createTextNode(list.at(3));
  num.appendChild(num_text);
  QDomText total_text = doc.createTextNode(list.at(4));
  total.appendChild(total_text);

  timeEmt.appendChild(factory);
  timeEmt.appendChild(brand);
  timeEmt.appendChild(price);
  timeEmt.appendChild(num);
  timeEmt.appendChild(total);
}

void DomXML::readXML(QString filePath, QStringList &factoryList,
                     QStringList &brandList, QStringList &priceList,
                     QStringList &numList, QStringList &totalList) {
  QFile file(filePath);
  bool isOk = file.open(QIODevice::ReadOnly);
  if (isOk) {
    // file和XML文档对象关联
    QDomDocument doc;
    isOk = doc.setContent(&file);
    if (isOk) { // 关联成功
      // 获取根节点
      QDomElement root = doc.documentElement();
      file.close();
      QDateTime date = QDateTime::currentDateTime();
      QString dateStr=date.toString("yyyy-MM-dd");
      if (root.hasChildNodes()) {
        // 找最后一个节点元素
        QDomElement lastEmt = root.lastChildElement();
        // 判断有没有当天日期
        if(lastEmt.attribute("date") == dateStr){
            //找出当前日期所有时间子节点
            QDomNodeList dateList = lastEmt.childNodes();
            for(int i =0; i< dateList.size(); i++){
                QDomNodeList timeList = dateList.at(i).toElement().childNodes(); // 转换成元素，找到时间节点下的所有节点

                QString factory = timeList.at(0).toElement().text();
                factoryList.append(factory);
                QString brand = timeList.at(1).toElement().text();
                brandList.append(brand);
                QString price = timeList.at(2).toElement().text();
                priceList.append(price);
                QString num = timeList.at(3).toElement().text();
                numList.append(num);
                QString total = timeList.at(4).toElement().text();
                totalList.append(total);
            }
        }
        else{
            cout << "当天没有销售记录";
            return;
        }
      } else {
        cout << "没有子节点";
        return;
      }
    } else {
      cout << "关联出错";
      return;
    }
  } else {
    cout << "读取错误";
    return;
  }
}
