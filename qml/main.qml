import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.12

Window {
    visible: true
    title: "Timer"
    width: 350
    height: 550
    readonly property int elementNum: 7
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        Rectangle {
            id: timeField
            border.color: "black"
            Layout.preferredHeight: parent.height / elementNum
            Layout.fillWidth: true
            Text {
                id: displayedTime
                anchors.centerIn: parent
                text: timer.time
            }
        }
        TimerButton {
            id: startStopButton
            text: timer.isActive ? "Pause" : "Start"
            background: Rectangle{
                border.color: "black"
                color: timer.isActive ? "red" : "green"
            }
            onClicked: timer.isActive ? timer.pause() : timer.start()

        }
        TimerButton {
            id: tapButton
            text: "Tap"
            background: Rectangle{
                border.color: "black"
                color: timer.isActive ? "white" : "darkgray"
            }
            onClicked: {
                if(timer.isActive){
                    timer.tap()
                }
            }
        }
        TimerButton {
            id: resetButton
            text: "Reset"
            onClicked: {
                if(!timer.isActive){
                    timer.reset()
                }
            }
        }
        TimerButton {
            id: setTimeButton
            text: "Set time"
            onClicked: {
                if(!timer.isActive){
                    setInitialTimeDialog.open()
                }
            }
        }
        TimerButton {
            id: setSoundButton
            text: "Set timeout sound"
            onClicked: {
                if(!timer.isActive){
                    audioFileDialog.open()
                }
            }
        }
        Rectangle{
            id: timeStampRectangle
            Layout.preferredHeight: parent.height / elementNum
            Layout.fillWidth: true
            border.color: "black"
            clip: true
            ListView{
                anchors.fill: parent
                id: viewTimeStamps
                flickableDirection: Flickable.VerticalFlick
                boundsBehavior: Flickable.StopAtBounds
                ScrollBar.vertical: ScrollBar {
                    policy: ScrollBar.AlwaysOn
                }
                delegate: Rectangle {
                    id: timeStampItem
                    width: viewTimeStamps.width
                    height: viewTimeStamps.height / 2
                    border.color: "black"
                    radius: 5
                    color: timer.isActive ? "red" : "green"
                    Text {
                        id: timeStampText
                        text: modelData
                        anchors.centerIn: parent
                    }
                }
                model: timer.timeStampsModel

            }
            Text {
                visible: !viewTimeStamps.count
                id: placeHolderTimestamps
                text: "Timestamps"
                anchors.centerIn: parent
                color: "gray"
            }
        }
    }

    Dialog{
        id: setInitialTimeDialog
        title: "Input initial time"
        standardButtons: Dialog.Ok | Dialog.Cancel
        height: 100
        width: 100
        TextField{
            id: initialTime
            width: parent.width
            placeholderText: "mm:ss:zzz"
        }
        onAccepted: timer.time = initialTime.text
    }
    FileDialog{
        id: audioFileDialog
        title: "Choose alarm sound"
        nameFilters: ["Audio files (*.wav)"]
        onAccepted: timer.setAlarmSound(audioFileDialog.fileUrl)
    }
}
