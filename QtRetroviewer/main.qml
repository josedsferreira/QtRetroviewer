import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Retroviewer")


    RowLayout {
        anchors.fill: parent
        spacing: 0

        Pane{
            id: imagePane
            Layout.fillHeight: true
            Layout.fillWidth: true
            //Layout.preferredWidth: 70

            Image {
                id: imageDisplayed
                //source: "file:///C:/Users/josed/Desktop/Base/Programas/RetroviewerApp/pics/placeholder"
                source: "pics/placeholder"
                //anchors.verticalCenter: parent.verticalCenter
                anchors.fill: parent
                width: parent.width; height: parent.height
                fillMode: Image.PreserveAspectFit
            }
        }

        Pane {
            id: ctrlpane
            Layout.fillHeight: true
            Layout.preferredWidth: parent.width * 0.3;

            ColumnLayout {
                anchors.fill: parent

                Button {
                    id: chooseImageBt
                    text: qsTr("  Choose Image  ")
                    onClicked: fileDialog.open()
                }
                CheckBox {
                    id: ditheringCheck
                    text: qsTr("Apply dithering")
                }
                ColumnLayout {
                    id: quantizationColumn
                    Label {
                        text: "Quantization"
                        //font.pixelSize: 22
                    }
                    RadioButton {
                        id: quantOriginal
                        checked: true
                        text: qsTr("Original")
                    }
                    RadioButton {
                        id: quant2
                        text: qsTr("2 Colors")
                    }
                    RadioButton {
                        id: quant4
                        text: qsTr("4 Colors")
                    }
                    RadioButton {
                        id: quant8
                        text: qsTr("8 Colors")
                    }
                }
                ColumnLayout {
                    id: paletteColumn
                    // must only be visible if a quantization was chosen
                    //visible: false
                    Label {
                        text: "Palette"
                    }
                    RowLayout {
                        Button {
                            id: paletteBwd
                            text: qsTr("<")
                            //onClicked:
                        }
                        Button {
                            id: paletteFwd
                            text: qsTr(">")
                            //onClicked:
                        }
                    }
                }
                Label {
                    text: "Brightness"
                }
                Slider {
                    id: brightnessSlider
                    from: 0
                    snapMode: Slider.SnapOnRelease
                    stepSize: 1
                    to: 100
                }
                Label {
                    text: "Contrast"
                }
                Slider {
                    id: contrastSlider
                    from: 1.0
                    snapMode: Slider.SnapOnRelease
                    stepSize: 0.1
                    to: 3.0
                }
                Label {
                    text: "Gamma"
                }
                Slider {
                    id: gammaSlider
                    from: 0.5
                    snapMode: Slider.SnapOnRelease
                    stepSize: 0.1
                    to: 3.0
                }
                Label {
                    text: "Pixelization"
                }
                Slider {
                    id: pixelizationSlider
                    from: 0.1
                    snapMode: Slider.SnapOnRelease
                    stepSize: 0.1
                    to: 0.9
                }
                Button {
                    id: saveImageBt
                    text: qsTr("  Save Image  ")
                    //onClicked: fileDialog.open()
                }
            }
        }


        FileDialog {
            id: fileDialog
            //currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
            onAccepted: imageDisplayed.source = selectedFile
        }

    }




}
