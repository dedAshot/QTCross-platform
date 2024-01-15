import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Controls.Material


ApplicationWindow {
    visible: true
    width: 360
    height: 520
    title: qsTr("Список контактов")
    header: ToolBar {
        ToolButton {
            id: buttonAddPage
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: 18
            text: (stackView.depth > 1)? qsTr("<"): qsTr(">")
            onClicked: {
                if (stackView.depth > 1) {
                    buttonAdd.visible = false
                    stackView.pop()
                } else {
                    stackView.push(addPage)
                    buttonAdd.visible = true
                }
            }
        }
        Label {

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            text: (stackView.depth > 1)? qsTr("Добавление пользователей"): qsTr("Список контактов")

        }

        ToolButton {
            id: buttonAdd
            visible: false
            anchors.right: parent.right
            font.pointSize: 18
            text: qsTr("+")
            onClicked: {
                console.log("stackView.fnameField: " +stackView.fnameField)
                // Вносим новую запись в базу данных
                database.inserIntoTable(stackView.fnameField , stackView.snameField,
                                        stackView.phoneField)
                myModel.updateModel() // И обновляем модель данных с новой записью
                buttonAdd.visible = false/*
                fnameField.clear()
                snameField.clear()
                phoneField.clear()*/
                stackView.pop()
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: listPage
        property string fnameField : qsTr("Peter")
        property string snameField : qsTr("Gunz")
        property string phoneField : qsTr("+123456789012")
    }


    Component {
        id: listPage
        Rectangle {
            //anchors.fill: parent
            color: "papayawhip"

            ListView {
                id: listView
                anchors.fill: parent
                model: myModel

                delegate: Item {
                    id: item
                    anchors.left: parent.left
                    anchors.right: parent.right
                    height: 57

                    Button {
                        anchors.fill: parent

                        Text {
                            anchors.fill: parent
                            font.pixelSize: 16
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignHCenter
                            text: qsTr(FirstName +" " + SurName +"\n"+ Phone)

                        }
                        onPressAndHold: {
                            database.removeRecord(id)
                            myModel.updateModel();
                            console.log("kakzeti nadorl "/*+FirstName +" " + SurName +"\n"+ Phone*/)
                        }


                    }
                }
            }
        }
    }

    Component {
        id: addPage
        Rectangle {
            //anchors.fill: parent
            color: "papayawhip"

            ColumnLayout {
                id: columnLayout
                anchors.centerIn: parent
                spacing: 20
                property int layoutItemWidth: 145

                TextField {
                    onTextEdited: {stackView.fnameField=text }
                    inputMask: "aaaaaaaaaaaaaaaaaaaa"
                    placeholderText: qsTr("Имя")
                    maximumLength: 20
                    text: qsTr("Peter")
                    Layout.minimumWidth: columnLayout.layoutItemWidth
                }
                TextField {
                    onTextEdited: {stackView.snameField=text }
                    inputMask: "aaaaaaaaaaaaaaaaaaaa"
                    placeholderText: qsTr("Фамилия")
                    maximumLength: 20
                    text: qsTr("Gunz")
                    Layout.minimumWidth: columnLayout.layoutItemWidth
                }
                TextField {
                    onTextEdited: {stackView.phoneField=text }
                    inputMask: "#000000000000"
                    placeholderText: qsTr("Телефон")
                    maximumLength: 20
                    text: qsTr("+123456789012")
                    Layout.minimumWidth: columnLayout.layoutItemWidth
                }
            }
        }
    }

}
