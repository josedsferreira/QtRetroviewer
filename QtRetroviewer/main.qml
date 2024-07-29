import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

import comm.retroviewer.backend 1.0

Window {
    width: 640
    height: 580
    visible: true
    title: qsTr("Retroviewer")

    property string imagePath: "pics\\placeholder"
    property string originalImagePath: "pics\\placeholder"
    property string resultImagePath: "pics\\result"
    property string savePath: ""
    property bool bayerFlag: false
    property int colorQuantity: 0
    property int rvpalette: 0
    property int brightness: 0
    property double contrast: 1.0
    property double pixelizationFactor: 1.0
    property double gamma: 0.5

    property color color1: "black"
    property color color2: "#1f1f1f"
    property color color3: "#3f3f3f"
    property color color4: "#5f5f5f"
    property color color5: "#7f7f7f"
    property color color6: "#9f9f9f"
    property color color7: "#bfbfbf"
    property color color8: "white"

    property color textColor1: "white"
    property color textColor2: "black"
    property color textColor3: "black"
    property color textColor4: "black"
    property color textColor5: "black"
    property color textColor6: "black"
    property color textColor7: "black"
    property color textColor8: "black"

    function genImage() {
        //if (rvpalette < 0) { rvpalette = 0 }
        if (bayerFlag == false && colorQuantity == 0 && brightness == 0 && contrast == 1.0 && pixelizationFactor == 1.0 && gamma == 0.5){
            startOver()
        }
        else {
            appBackend.generateImage(imagePath, bayerFlag, colorQuantity, brightness, contrast, pixelizationFactor, gamma, color1, color2, color3, color4, color5, color6, color7, color8)
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

        /*
        color1: "black"
        color2: "#1f1f1f"
        color3: "#3f3f3f"
        color4: "#5f5f5f"
        color5: "#7f7f7f"
        color6: "#9f9f9f"
        color7: "#bfbfbf"
        color8: "white"
        */

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

    function updateTextColor(color) {
        var r = color.r
        var g = color.g
        var b = color.b
        var luminance = 0.2126 * r + 0.7152 * g + 0.0722 * b

        // If the luminance is lower than 0.5, consider the color dark and set text to white
        return (luminance < 0.5) ? "white" : "black"
    }

    Backend {
        id: appBackend
    }

    Connections {
        target: appBackend
        onImageGenerated: {
            console.log("Image generated signal received")
            imageDisplayed.source = "image://dynamic/result?" + Date.now(); // Force reload with a timestamp
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
                    id: chooseImageBt
                    text: qsTr("  Choose Image  ")
                    onClicked: {
                        fileDialog.open()
                        startOver()
                    }
                }


                Button {
                            id: resetBt
                            visible: false
                            text: qsTr("  Reset  ")
                            onClicked: {
                                startOver()
                            }
                }
                
                CheckBox {
                            id: ditheringCheck
                            visible: false
                            text: qsTr("Apply dithering")
                            checked: bayerFlag
                            onClicked: {
                                bayerFlag = ditheringCheck.checked // might be unnecessary as it is bound
                                genImage()
                            }
                }
                ColumnLayout {
                            id: quantizationColumn
                            visible: false
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
                                    color1 = "black"
                                    color2 = "white"
                                    textColor1 = "white"
                                    textColor2 = "black"
                                    genImage()
                                }
                            }
                            RadioButton {
                                id: quant4
                                text: qsTr("4 Colors")
                                onClicked: {
                                    colorQuantity = 4
                                    color1 = "black"
                                    color2 = "#3f3f3f"
                                    color3 = "#9f9f9f"
                                    color4 = "white"
                                    textColor1 = "white"
                                    textColor2 = "white"
                                    textColor3 = "black"
                                    textColor4 = "black"
                                    genImage()
                                }
                            }
                            RadioButton {
                                id: quant8
                                text: qsTr("8 Colors")
                                onClicked: {
                                    colorQuantity = 8
                                    color1 = "black"
                                    color2 = "#1f1f1f"
                                    color3 = "#3f3f3f"
                                    color4 = "#5f5f5f"
                                    color5 = "#7f7f7f"
                                    color6 = "#9f9f9f"
                                    color7 = "#bfbfbf"
                                    color8 = "white"
                                    textColor1 = "white"
                                    textColor2 = "white"
                                    textColor3 = "white"
                                    textColor4 = "white"
                                    textColor5 = "black"
                                    textColor6 = "black"
                                    textColor7 = "black"
                                    textColor8 = "black"
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
                            /*
                            RowLayout {
                                Button {
                                    id: paletteBwd
                                    text: qsTr("<")
                                    onClicked: {
                                        rvpalette--
                                        genImage()
                                    }
                                }
                                Button {
                                    id: paletteFwd
                                    text: qsTr(">")
                                    onClicked: {
                                        rvpalette++
                                        genImage()
                                    }
                                }
                            }
                            */
                            RowLayout{
                                Button {
                                    id: color1Bt
                                    text: qsTr(" Color 1 ")
                                    onClicked: colorDialog1.open()
                                    background: Rectangle {
                                        color: color1
                                        radius: 8
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: textColor1
                                        font: parent.font
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }
                                }

                                ColorDialog {
                                    id: colorDialog1
                                    selectedColor: color1
                                    onAccepted: {
                                        color1 = selectedColor
                                        textColor1 = updateTextColor(color1)
                                        genImage()
                                    }
                                }

                                Button {
                                    id: color2Bt
                                    text: qsTr(" Color 2 ")
                                    onClicked: colorDialog2.open()
                                    background: Rectangle {
                                        color: color2
                                        radius: 8
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: textColor2
                                        font: parent.font
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }
                                }

                                ColorDialog {
                                    id: colorDialog2
                                    selectedColor: color2
                                    onAccepted: {
                                        color2 = selectedColor
                                        textColor2 = updateTextColor(color2)
                                        genImage()
                                    }
                                }

                                Button {
                                    id: color3Bt
                                    visible: quant4.checked || quant8.checked
                                    text: qsTr(" Color 3 ")
                                    onClicked: colorDialog3.open()
                                    background: Rectangle {
                                        color: color3
                                        radius: 8
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: textColor3
                                        font: parent.font
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }
                                }

                                ColorDialog {
                                    id: colorDialog3
                                    selectedColor: color3
                                    onAccepted: {
                                        color3 = selectedColor
                                        textColor3 = updateTextColor(color3)
                                        genImage()
                                    }
                                }
                            }
                            RowLayout{

                                Button {
                                    id: color4Bt
                                    visible: quant4.checked || quant8.checked
                                    text: qsTr(" Color 4 ")
                                    onClicked: colorDialog4.open()
                                    background: Rectangle {
                                        color: color4
                                        radius: 8
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: textColor4
                                        font: parent.font
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }
                                }

                                ColorDialog {
                                    id: colorDialog4
                                    selectedColor: color4
                                    onAccepted: {
                                        color4 = selectedColor
                                        textColor4 = updateTextColor(color4)
                                        genImage()
                                    }
                                }

                                Button {
                                    id: color5Bt
                                    visible: quant8.checked
                                    text: qsTr(" Color 5 ")
                                    onClicked: colorDialog5.open()
                                    background: Rectangle {
                                        color: color5
                                        radius: 8
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: textColor5
                                        font: parent.font
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }
                                }

                                ColorDialog {
                                    id: colorDialog5
                                    selectedColor: color5
                                    onAccepted: {
                                        color5 = selectedColor
                                        textColor5 = updateTextColor(color5)
                                        genImage()
                                    }
                                }

                                Button {
                                    id: color6Bt
                                    visible: quant8.checked
                                    text: qsTr(" Color 6 ")
                                    onClicked: colorDialog6.open()
                                    background: Rectangle {
                                        color: color6
                                        radius: 8
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: textColor6
                                        font: parent.font
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }
                                }

                                ColorDialog {
                                    id: colorDialog6
                                    selectedColor: color6
                                    onAccepted: {
                                        color6 = selectedColor
                                        textColor6 = updateTextColor(color6)
                                        genImage()
                                    }
                                }

                            }
                            RowLayout {

                                Button {
                                    id: color7Bt
                                    visible: quant8.checked
                                    text: qsTr(" Color 7 ")
                                    onClicked: colorDialog7.open()
                                    background: Rectangle {
                                        color: color7
                                        radius: 8
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: textColor7
                                        font: parent.font
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }
                                }

                                ColorDialog {
                                    id: colorDialog7
                                    selectedColor: color7
                                    onAccepted: {
                                        color7 = selectedColor
                                        textColor7 = updateTextColor(color7)
                                        genImage()
                                    }
                                }

                                Button {
                                    id: color8Bt
                                    visible: quant8.checked
                                    text: qsTr(" Color 8 ")
                                    onClicked: colorDialog8.open()
                                    background: Rectangle {
                                        color: color8
                                        radius: 8
                                    }
                                    contentItem: Text {
                                        text: parent.text
                                        color: textColor8
                                        font: parent.font
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                        anchors.fill: parent
                                    }
                                }

                                ColorDialog {
                                    id: colorDialog8
                                    selectedColor: color8
                                    onAccepted: {
                                        color8 = selectedColor
                                        textColor8 = updateTextColor(color8)
                                        genImage()
                                    }
                                }
                            }
                }
                
                        Label {
                            text: "Brightness"
                            id: brightnessLabel
                            visible: false
                        }
                        Slider {
                            id: brightnessSlider
                            visible: false
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
                            id: contrastLabel
                            visible: false
                        }
                        Slider {
                            id: contrastSlider
                            visible: false
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
                            id: gammaLabel
                            visible: false
                        }
                        Slider {
                            id: gammaSlider
                            visible: false
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
                            id: pixelizationLabel
                            visible: false
                        }
                        Slider {
                            id: pixelizationSlider
                            visible: false
                            from: 1.0
                            snapMode: Slider.SnapOnRelease
                            stepSize: 0.01
                            value: 1.0
                            to: 0.01
                            live: false
                            onValueChanged: {
                                pixelizationFactor = pixelizationSlider.value
                                genImage()
                            }
                        }
                        Button {
                            id: saveImageBt
                            visible: false
                            text: qsTr("  Save Image  ")
                            onClicked: saveDialog.open()
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
                
                resetBt.visible = true
                ditheringCheck.visible = true
                quantizationColumn.visible = true
                brightnessLabel.visible = true
                brightnessSlider.visible = true
                contrastLabel.visible = true
                contrastSlider.visible = true
                gammaLabel.visible = true
                gammaSlider.visible = true
                gammaLabel.visible = true
                gammaSlider.visible = true
                pixelizationLabel.visible = true
                pixelizationSlider.visible = true
                saveImageBt.visible = true
            }
        }

        FileDialog {
            id: saveDialog
            //currentFolder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0]
            fileMode: FileDialog.SaveFile
            onAccepted: {
                savePath = selectedFile
                appBackend.saveImage(savePath)
            }
        }

    }




}
