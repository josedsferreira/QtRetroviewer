import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import comm.retroviewer.backend 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Retroviewer")

    property string imagePath: "pics\\placeholder"
    property string originalImagePath: "pics\\placeholder"
    property string resultImagePath: "pics\\result"
    property bool bayerFlag: false
    property int colorQuantity: 0
    property int rvpalette: 0
    property int brightness: 0
    property double contrast: 1.0
    property double pixelizationFactor: 1.0
    property double gamma: 0.5

    function genImage() {
        if (bayerFlag == false && colorQuantity == 0 && brightness == 0 && contrast == 1.0 && pixelizationFactor == 1.0 && gamma == 0.5){
            startOver()
        }
        else {
            appBackend.generateImage(imagePath, bayerFlag, colorQuantity, rvpalette, brightness, contrast, pixelizationFactor, gamma)
        }
    }

    function startOver() {
        console.log("Reset called")
        imagePath = originalImagePath
        imageDisplayed.source = imagePath
        bayerFlag = false
        colorQuantity = 0
        rvpalette = 0
        brightness = 0
        contrast = 1.0
        pixelizationFactor = 1
        gamma = 0.5

        ditheringCheck.checked = bayerFlag
        quantOriginal.checked = true
        quant2.checked = false
        quant4.checked = false
        quant8.checked = false
        brightnessSlider.value = brightness
        contrastSlider.value = contrast
        gammaSlider.value = gamma
        pixelizationSlider.value = pixelizationFactor
    }

    Backend {
        id: appBackend
    }

    Connections {
        target: appBackend
        onImageGenerated: {
            console.log("Image generated signal received")
            //imageDisplayed.source = "pics\\placeholder";  // Force reload (not solving it)
            //imageDisplayed.source = resultImagePath;
            imageDisplayed.source = "image://dynamic/result?" + Date.now(); // Force reload with a timestamp
            //imageDisplayed.source = resultImagePath + "?" + Date.now();
            console.log("image displayed changed")
        }
    }


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
                source: "pics\\placeholder"
                cache: false
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
                    id: resetBt
                    text: qsTr("  Reset  ")
                    onClicked: {
                        startOver()
                    }
                }
                Button {
                    id: chooseImageBt
                    text: qsTr("  Choose Image  ")
                    onClicked: {
                        fileDialog.open()
                        startOver()
                    }
                }
                CheckBox {
                    id: ditheringCheck
                    text: qsTr("Apply dithering")
                    checked: bayerFlag
                    onClicked: {
                        bayerFlag = ditheringCheck.checked // might be unnecessary as it is bound
                        genImage()
                    }
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
                        onClicked: {
                            colorQuantity = 0
                            genImage()
                        }
                    }
                    RadioButton {
                        id: quant2
                        text: qsTr("2 Colors")
                        onClicked: {
                            colorQuantity = 2
                            genImage()
                        }
                    }
                    RadioButton {
                        id: quant4
                        text: qsTr("4 Colors")
                        onClicked: {
                            colorQuantity = 4
                            genImage()
                        }
                    }
                    RadioButton {
                        id: quant8
                        text: qsTr("8 Colors")
                        onClicked: {
                            colorQuantity = 8
                            genImage()
                        }
                    }
                }
                ColumnLayout {
                    id: paletteColumn
                    // must only be visible if a quantization was chosen
                    visible: !quantOriginal.checked
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
                    live: false
                    onValueChanged: {
                        brightness = brightnessSlider.value
                        genImage()
                    }
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
                    live: false
                    onValueChanged: {
                        contrast = contrastSlider.value
                        genImage()
                    }
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
                    live: false
                    onValueChanged: {
                        gamma = gammaSlider.value
                        genImage()
                    }
                }
                Label {
                    text: "Pixelization"
                }
                Slider {
                    id: pixelizationSlider
                    from: 1.0
                    snapMode: Slider.SnapOnRelease
                    stepSize: 0.1
                    value: 1.0
                    to: 0.1
                    live: false
                    onValueChanged: {
                        pixelizationFactor = pixelizationSlider.value
                        genImage()
                    }
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
            onAccepted: {
                imageDisplayed.source = selectedFile
                originalImagePath = selectedFile
                imagePath = selectedFile
            }
        }

    }




}
