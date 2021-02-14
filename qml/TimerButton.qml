import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Button{
    Layout.alignment: Qt.AlignCenter
    Layout.preferredHeight: parent.height / elementNum
    Layout.fillWidth: true
    background: Rectangle {
        border.color: "black"
        radius: 5
        color: timer.isActive ? "darkgray" : "white"
    }
}

