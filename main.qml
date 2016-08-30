import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0


ApplicationWindow {
    visible: true
    width: 1300
    height: 800
    title: qsTr("Hello World")

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1 {
        }

        Page {

        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
