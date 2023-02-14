import QtQuick 2.14
import QtQuick.Window 2.12
import QtQuick.Controls 1.4

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListModel {
          id: libraryModel
          ListElement {
              title: "A Masterpiece"
              author: "Gabriel"
          }
          ListElement {
              title: "Brilliance"
              author: "Jens"
          }
          ListElement {
              title: "Outstanding"
              author: "Frederik"
          }
      }

    TableView {
          TableViewColumn {
              role: "title"
              title: "Title"
              width: 100
          }
          TableViewColumn {
              role: "author"
              title: "Author"
              width: 200
          }
          model: libraryModel
      }
}
