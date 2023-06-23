/*LiuZeyu*/
import wirelessModel 1.0
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import QtQuick.Controls.Styles 1.1
import QtQuick.Dialogs 1.1
import QtQuick 2.12
import QtQuick.Layouts 1.11
import QtQuick.Window 2.12
import QtQuick.VirtualKeyboard 2.4
import QtQuick.Controls 2.5
import QtQuick.LocalStorage 2.0
import QtGraphicalEffects 1.0
import timeSet 1.0
import sensorData 1.0
import detcMoveToThread 1.0
import QtCharts 2.0

Window {
    id: window
    visible: true
    width: 1024
    height: 600
    title: qsTr("Hello World")
    property bool unfold: false;
    function currentDateTime(){
        return Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss ddd");
    }
    DetcMoveToThread{
        id:detc
    }

    //top bar
    Rectangle{
        x:0
        y:0
        id:topbar
        width: 1024
        height: 30
        color: "#7d7d7d"
        radius: 0
        //当前日期时间

        Text {
            x:5
            y:5
            id: textDateTime
            color: "white"
        }
        //定时器
        Timer{
            id: timer
            interval: 1000 //间隔(单位毫秒):1000毫秒=1秒
            repeat: true //重复
            onTriggered:{
                textDateTime.text = currentDateTime();
            }
        }

        Component.onCompleted: {
            timer.start();
        }

    }
    //main interface
    Item{
        id:interfaceItem
        x:0
        y:30
        width: 1024
        height: 570
        SwipeView{
            id: swpieView
            currentIndex: 0
            anchors.fill: parent

            //参数
            Rectangle{
                id : dataRect
                x:0
                y:0
                Image {
                    source: 'qrc:/Image/background.png'
                }
                //color: "black"
                gradient: Gradient {
                    GradientStop {
                        position: 0
                        color: "#9795f0"
                    }

                    GradientStop {
                        position: 1
                        color: "#fbc8d4"
                    }
                }
                property int detcFreq : 500;
                SensorDataModel{
                    id : sensordata
                }


                Text {
                    id: text6
                    x: 38
                    y: 21
                    color: "#ffffff"
                    text: qsTr("电力参数")
                    font.pixelSize: 40
                    font.bold: true
                }

                ListModel
                {
                    id:elecData
                    ListElement{name: "A相电压有效值";key: 0x01}
                    ListElement{name: "B相电压有效值";key: 0x02}
                    ListElement{name: "C相电压有效值";key: 0x03}

                    ListElement{name: "AB电压夹角";key: 0x04}
                    ListElement{name: "AC电压夹角";key: 0x05}
                    ListElement{name: "BC电压夹角";key: 0x06}

                    ListElement{name: "A相流压夹角";key: 0x07}
                    ListElement{name: "B相流压夹角";key: 0x08}
                    ListElement{name: "C相流压夹角";key: 0x09}

                    ListElement{name: "A相电流有效值";key: 0x0a}
                    ListElement{name: "B相电流有效值";key: 0x0b}
                    ListElement{name: "C相电流有效值";key: 0x0c}
                    ListElement{name: "合相电流有效值";key: 0x0d}

                    ListElement{name: "频率";key: 0x0e}

                    ListElement{name: "A相有功功率";key: 0x0f}
                    ListElement{name: "B相有功功率";key: 0x10}
                    ListElement{name: "C相有功功率";key: 0x11}
                    ListElement{name: "合相有功功率";key: 0x12}

                    ListElement{name: "矢量电压和有效值";key: 0x13}
                    ListElement{name: "矢量电流和有效值";key: 0x14}
                    // ListElement{name: "矢量电流和有效值";key: 0x15}

                    ListElement{name: "A相基波有功功率";key: 0x16}
                    ListElement{name: "B相基波有功功率";key: 0x17}
                    ListElement{name: "C相基波有功功率";key: 0x18}
                    ListElement{name: "合相基波有功功率";key: 0x19}

                    ListElement{name: "A相基波有功电能";key: 0x1a}
                    ListElement{name: "B相基波有功电能";key: 0x1b}
                    ListElement{name: "C相基波有功电能";key: 0x1c}
                    ListElement{name: "合相基波有功电能";key: 0x1d}

                    ListElement{name: "A相无功功率";key: 0x1e}
                    ListElement{name: "B相无功功率";key: 0x1f}
                    ListElement{name: "C相无功功率";key: 0x20}
                    ListElement{name: "合相无功功率";key: 0x21}

                    ListElement{name: "A相视在功率";key: 0x22}
                    ListElement{name: "B相视在功率";key: 0x23}
                    ListElement{name: "C相视在功率";key: 0x24}
                    ListElement{name: "合相视在功率";key: 0x25}

                    ListElement{name: "A相功率因数";key: 0x26}
                    ListElement{name: "B相功率因数";key: 0x27}
                    ListElement{name: "C相功率因数";key: 0x28}
                    ListElement{name: "合相功率因数";key: 0x29}

                    ListElement{name: "A相有功电能";key: 0x2a}
                    ListElement{name: "B相有功电能";key: 0x2b}
                    ListElement{name: "C相有功电能";key: 0x2c}
                    ListElement{name: "合相有功电能";key: 0x2d}

                    ListElement{name: "A相视在电能";key: 0x2f}
                    ListElement{name: "B相视在电能";key: 0x30}
                    ListElement{name: "C相视在电能";key: 0x31}
                    ListElement{name: "合相视在电能";key: 0x32}

                    ListElement{name: "芯片温度";key: 0x33}

                }

                GridView {
                    id: gridView
                    x: 75
                    y: 115
                    width: 924
                    height: 383
                    clip: true
                    model: elecData
                    cellHeight: 150
                    cellWidth : 305
                    delegate: Column{
                        Rectangle{
                            width : 267
                            height: 130
                            radius: 10
                            Label {
                                //x:150
                                x: 25
                                y: 16
                                font.pointSize: 12
                                text: name;
                                anchors.horizontalCenter: parent.TopLeft
                            }
                            Text{
                            //Text {
                                id:sensorDataText
                                //x:130
                                y:55

                                font.pointSize: 50
                                color: "#A9A9A9"
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignRight
                                anchors.right: parent.right
                                //anchors.horizontalCenter: parent.TopLeft
                                //horizontalAlignment: parent.AlignRight
                                Timer{
                                    id: sensorTimer
                                    interval: dataRect.detcFreq //间隔(单位毫秒):1000毫秒=1秒
                                    repeat: true    //重复
                                    onTriggered:{
                                        detc.timeOver();
                                        sensorDataText.text = detc.dataToQML(key);
                                    }
                                }

                                Component.onCompleted: {
                                    sensorTimer.start();
                                }

                            //}
                            }

                            /* ChartView{
                                       id:dataChart
                                       antialiasing: true
                                       backgroundColor: "transparent"
                                       animationOptions: ChartView.SeriesAnimations
                                       legend.visible:false
                                       height: parent.height+5
                                       width: parent.width+20
                                       x: -15
                                       y:15
                                       property int charttimer: 0


                                       ValueAxis {
                                              visible: false
                                              id: myAxisX
                                              min:0//Qt.formatDateTime(new Date(), "ss"); //10>dataChart.charttimer? 0:dataChart.charttimer-1
                                              max:10//Qt.formatDateTime(new Date(), "ss")+10; //10>dataChart.charttimer? 10:dataChart.charttimer+1
                                              tickCount: 11
                                              labelsColor: "black"
                                              labelsFont.pointSize: 5
                                              labelFormat: '%d'
                                       }
                                          ValueAxis{
                                              id:myAxisY
                                              min:-500
                                              max:500
                                              tickCount: 7
                                              labelsColor: "black"
                                              labelsFont.pointSize: 5
                                              labelFormat: '%d'
                                          }

                                          LineSeries {
                                              id:lineSeries
                                              name: "LineSeries"
                                              axisX: myAxisX
                                              axisY: myAxisY
                                              color: "#00f00f"
                                              width: 2
                                          }

                                          Timer{
                                              id:chartTimer
                                              interval: dataRect.detcFreq
                                              running: true
                                              repeat: true
                                              onTriggered: {
                                                  //lineSeries.append(dataChart.charttimer,Math.random()*50)
                                                  lineSeries.append(dataChart.charttimer,Number(detc.dataToQML(key)))
                                                  dataChart.charttimer = dataChart.charttimer+1
                                                  if (dataChart.charttimer >= (myAxisX.tickCount+1)) {
                                                        dataChart.scrollRight(dataChart.plotArea.width / (myAxisX.tickCount-1))
                                                  }
                                              }
                                          }
                                }*/

                        }
                    }
                }


                RoundButton {
                    id: saveBTN
                    x: 896
                    y: 40
                    width: 64
                    height: 58

                    Image {
                        id: saveImage
                        x: 0
                        y: 0
                        width: 50
                        height: 50
                        anchors.verticalCenterOffset: -2
                        anchors.horizontalCenterOffset: -7
                        anchors.centerIn: parent
                        source: "qrc:/Image/save.png"
                    }
                    background: Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                    }

                    onClicked: {
                        detc.dataToSQL();
                        sqlitOBJ.refreshList();
                        historyList.model = {};
                        historyList.model = sqlitOBJ.model;
                        //historyList.remove.objectName(model);


                    }

                }

                RoundButton {
                    id: detcBTN
                    x: 767
                    y: 40
                    width: 62
                    height: 50
                    visible : false
                    Image {
                        id: detcImage
                        x: 0
                        width: 50
                        height: 50
                        anchors.verticalCenterOffset: 0
                        anchors.horizontalCenterOffset: 0
                        anchors.centerIn: parent
                        source: "qrc:/Image/detc.png"
                    }
                    background: Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                    }
                    onPressed: {
                        dataRect.detcFreq = 1;
                    }
                    onReleased: {
                        dataRect.detcFreq = 999999;
                    }
                    //onClicked: {
                    //    dataRect.detcFreq = 1;
                    //sensordata.detcMeter();
                    // dataRect.sensorDataText.text = sensordata.dataToQML(dataRect.key);
                    //}

                }

            }
            //设置
            Rectangle{
                id: rectangle1
                x:0
                y:0
                //width: interfaceRoot.width
                // height: interfaceRoot.height
                Image {
                    source: 'qrc:/Image/background.png'
                }
                color: "#dcdcdc"
                Text {
                    id: text3
                    x: 38
                    y: 21
                    color: "#ffffff"
                    text: qsTr("设置")
                    font.bold: true
                    font.pixelSize: 40

                }

                Rectangle {
                    //id: rectangle
                    x: 38
                    y: 104
                    width: 947
                    height: 408
                    color: "white"
                    radius: 11
                    layer.enabled: true
                    rotation: 0
                    transformOrigin: Item.Center
                    border.width: 3
                    clip: false
                    border.color: "white"

                    ComboBox {
                        id: comboBoxFreq
                        x: 744
                        y: 44
                        width: 137
                        height: 40
                        //editable: false
                        Connections {
                            target: comboBoxFreq
                        }
                        //flat: false
                        //currentIndex: -1
                        // displayText: " 1s"
                        model: [500, 1000, 2000 , 5000 ,10000 ]
                        onActivated:{
                            dataRect.detcFreq = comboBoxFreq.currentText;
                        }
                        delegate: ItemDelegate {
                            width: comboBoxFreq.width
                            contentItem: Text {
                                text: modelData
                                color: "black"
                                font: comboBoxFreq.font
                                elide: Text.ElideRight
                                verticalAlignment: Text.AlignVCenter
                            }
                            highlighted: comboBoxFreq.highlightedIndex === index;


                        }
                        indicator: Canvas {
                            id: canvas
                            x: comboBoxFreq.width - width - comboBoxFreq.rightPadding
                            y: comboBoxFreq.topPadding + (comboBoxFreq.availableHeight - height) / 2
                            width: 12
                            height: 8
                            contextType: "2d"

                            Connections {
                                target: comboBoxFreq
                                function onPressedChanged() { canvas.requestPaint(); }
                            }

                            onPaint: {
                                context.reset();
                                context.moveTo(0, 0);
                                context.lineTo(width, 0);
                                context.lineTo(width / 2, height);
                                context.closePath();
                                context.fillStyle = comboBoxFreq.pressed ? "gray" : "gray";
                                context.fill();
                            }
                        }
                        contentItem: Text {
                            leftPadding: 10
                            rightPadding: comboBoxFreq.indicator.width + comboBoxFreq.spacing
                            text: comboBoxFreq.displayText
                            font: comboBoxFreq.font
                            color: comboBoxFreq.pressed ? "black" : "black"
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            border.color: comboBoxFreq.pressed ? "gray" : "gray"
                            border.width: comboBoxFreq.visualFocus ? 2 : 1
                            radius: 10
                        }
                        popup: Popup {
                            y: comboBoxFreq.height - 1
                            width: comboBoxFreq.width
                            implicitHeight: contentItem.implicitHeight
                            padding: 1

                            contentItem: ListView {
                                clip: true
                                implicitHeight: contentHeight
                                model: comboBoxFreq.popup.visible ? comboBoxFreq.delegateModel : null
                                currentIndex: comboBoxFreq.highlightedIndex

                                ScrollIndicator.vertical: ScrollIndicator { }
                            }

                            background: Rectangle {
                                border.color: "gray"
                                radius: 5
                            }
                        }


                    }

                    Switch {
                        id: wlanSW
                        x: 772
                        y: 250
                        hoverEnabled: true
                        onPressed: {
                            /*if (wirelessonFlag)
                                wlanText.text = "Scanning..."
                            else
                                wlanText.text = "WLAN"*/
                            //wirelessonFlag = !wirelessonFlag
                        }
                        onToggled: {
                            if(checked){
                                //console.log("ok")
                                //if(!WINenv)
                                myWirelessListModel.wirelessInit()
                            }
                            else {

                                if(playList.count != 0)
                                    myWirelessListModel.remove(0, playList.count - 1)
                                if(!WINenv)
                                    myWirelessListModel.wirelessClose()
                                wirelessRect.mystate = 0
                                //console.log("no")
                            }
                        }
                    }

                    Text {
                        id: element6
                        x: 42
                        y: 317
                        width: 175
                        height: 40
                        text: qsTr("手动采样")
                        verticalAlignment: Text.AlignVCenter
                        lineHeight: 1
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 25
                        fontSizeMode: Text.FixedSize
                    }

                    Switch {
                        id: mannal
                        x: 772
                        y: 317
                        onToggled: {
                            if(checked){
                                detcBTN.visible = true;
                                dataRect.detcFreq = 9999999;
                            }else{
                                detcBTN.visible = false;
                                dataRect.detcFreq = comboBoxFreq.currentText;
                            }
                        }
                    }

                    Text {
                        id: element
                        x: 42
                        y: 44
                        width: 175
                        height: 40
                        text: qsTr("采样频率")
                        verticalAlignment: Text.AlignVCenter
                        lineHeight: 1
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 25
                        fontSizeMode: Text.FixedSize
                    }

                    Text {
                        id: element4
                        x: 42
                        y: 250
                        width: 175
                        height: 40
                        text: qsTr("WLAN")
                        verticalAlignment: Text.AlignVCenter
                        lineHeight: 1
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 25
                        fontSizeMode: Text.FixedSize
                    }

                    Switch {
                        id: element3
                        x: 772
                        y: 184
                    }

                    Text {
                        id: element2
                        x: 42
                        y: 184
                        width: 175
                        height: 40
                        text: qsTr("蜂窝网络")
                        verticalAlignment: Text.AlignVCenter
                        lineHeight: 1
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 25
                        fontSizeMode: Text.FixedSize
                    }

                    ComboBox {
                        id: comboBoxNTP
                        x: 744
                        y: 113
                        width: 137
                        height: 40
                        editable: false
                        Connections {
                            target: comboBoxNTP
                        }
                        TimesetModel{
                            id : myTimeSetModel
                        }
                        textRole: "key"
                        model: ListModel {
                            id: model
                            ListElement { key: "ntp.ntsc.ac.cn"}
                            ListElement { key: "cn.ntp.org.cn"}
                            ListElement { key: "time1.aliyun.com"}
                        }
                        onActivated: {
                            myTimeSetModel.setNTPServer(comboBoxNTP.currentText);
                            myTimeSetModel.setNtp();
                        }

                        delegate: ItemDelegate {
                            width: comboBoxNTP.width
                            contentItem: Text {
                                text: key
                                color: "black"
                                font: comboBoxNTP.font
                                elide: Text.ElideRight
                                verticalAlignment: Text.AlignVCenter
                            }
                            highlighted: comboBoxNTP.highlightedIndex === index;
                            //required property int index
                            //required property var modelData

                        }
                        indicator: Canvas {
                            id: canvas2
                            x: comboBoxNTP.width - width - comboBoxNTP.rightPadding
                            y: comboBoxNTP.topPadding + (comboBoxNTP.availableHeight - height) / 2
                            width: 12
                            height: 8
                            contextType: "2d"

                            Connections {
                                target: comboBoxNTP
                                function onPressedChanged() { canvas2.requestPaint(); }
                            }

                            onPaint: {
                                context.reset();
                                context.moveTo(0, 0);
                                context.lineTo(width, 0);
                                context.lineTo(width / 2, height);
                                context.closePath();
                                context.fillStyle = comboBoxNTP.pressed ? "gray" : "gray";
                                context.fill();
                            }
                        }
                        contentItem: Text {
                            leftPadding: 10
                            rightPadding: comboBoxNTP.indicator.width + comboBoxNTP.spacing
                            text: comboBoxNTP.displayText
                            font: comboBoxNTP.font
                            color: comboBoxNTP.pressed ? "black" : "black"
                            horizontalAlignment: Text.AlignLeft
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            border.color: comboBoxNTP.pressed ? "gray" : "gray"
                            border.width: comboBoxNTP.visualFocus ? 2 : 1
                            radius: 10
                        }
                        popup: Popup {
                            y: comboBoxNTP.height - 1
                            width: comboBoxNTP.width
                            implicitHeight: contentItem.implicitHeight
                            padding: 1

                            contentItem: ListView {
                                clip: true
                                implicitHeight: contentHeight
                                model: comboBoxNTP.popup.visible ? comboBoxNTP.delegateModel : null
                                currentIndex: comboBoxNTP.highlightedIndex

                                ScrollIndicator.vertical: ScrollIndicator { }
                            }

                            background: Rectangle {
                                border.color: "gray"
                                radius: 5
                            }
                        }


                    }

                    Text {
                        id: element1
                        x: 42
                        y: 113
                        width: 175
                        height: 40
                        text: qsTr("NTP服务器")
                        verticalAlignment: Text.AlignVCenter
                        lineHeight: 1
                        horizontalAlignment: Text.AlignLeft
                        font.pixelSize: 25
                        fontSizeMode: Text.FixedSize
                    }
                }
            }
            //网络连接
            Rectangle{
                id:wirelessRect
                x:0
                y:0
                property int mystate
                property bool wirelessonFlag: true
                //width: interfaceRoot.width
                //height: interfaceRoot.height
                Image {
                    source: 'qrc:/Image/background.png'
                }

                Text {
                    id: text5
                    x: 38
                    y: 21
                    color: "#ffffff"
                    text: qsTr("无线局域网")
                    font.pixelSize: 40
                    font.bold: true
                }
                Dialog{
                    id: wifiDialog
                    x: 0
                    y: 0
                    height: parent.height
                    width: parent.width
                    modal: true
                    background: FastBlur{
                        id:blur
                        width: 1024
                        height: 600
                        source: wirelessRect
                        radius: 32
                    }

                    property string pskValue: " "
                    property string ssidValue: " "
                    property string message: " "
                    signal toggleConnet
                    signal toggleCancel

                    onToggleConnet: {
                        if (wifiDialog.pskValue != "")
                            myWirelessListModel.getMyWifiSSIDPSK(wifiDialog.ssidValue, wifiDialog.pskValue)
                        else
                            myWirelessListModel.passwordLessConnection(wifiDialog.ssidValue)
                    }
                    Rectangle{
                        id: bg
                        anchors.bottom: inputPanel.top
                        anchors.bottomMargin: 50
                        width: 300
                        height: 200
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "transparent"


                        TextField  {
                            id: input
                            anchors.top:bg.top
                            anchors.topMargin: 100

                            anchors.horizontalCenter: parent.horizontalCenter
                            //placeholderText: message
                            color: "white"
                            property color checkedColor: "#D5DBDB"

                            signal doubleClicked(var/*MouseEvent*/ event)

                            //placeholderText: qsTr("请输入内容")
                            font.pixelSize: 15
                            font.weight: Font.Thin
                            antialiasing: true

                            background: Rectangle {
                                implicitWidth: 213
                                implicitHeight: 42
                                radius: 8
                                color: input.enabled ? "transparent" : "#F4F6F6"
                                border.color: input.enabled ? input.checkedColor : "#D5DBDB"
                                border.width: 2
                                opacity: input.enabled ? 1 : 0.7

                                layer.enabled: input.hovered
                                layer.effect: DropShadow {
                                    id: dropShadow
                                    transparentBorder: true
                                    color: input.checkedColor
                                    samples: 10
                                }
                            }

                            cursorDelegate: Rectangle {
                                width: 1
                                height: parent.height * 0.4
                                color: input.checkedColor
                                visible: input.focus

                                Timer {
                                    interval: 600
                                    repeat: true
                                    running: input.focus
                                    onRunningChanged: parent.visible = running
                                    onTriggered: parent.visible = !parent.visible
                                }
                            }

                            onDoubleClicked: selectAll()

                            // note: This signal was introduced in QtQuick.Controls 2.1 (Qt 5.8).
                            onPressed: {
                                _private.mouseEvent = event
                                _private.isCheckDoubleClickedEvent++

                                if (! _checkDoubleClickedEventTimer.running)
                                    _checkDoubleClickedEventTimer.restart()
                            }

                            // Private
                            Item {
                                id: _private
                                property int isCheckDoubleClickedEvent: 0
                                property var/*MouseEvent*/ mouseEvent

                                Timer {
                                    id: _checkDoubleClickedEventTimer
                                    running: false
                                    repeat: false
                                    interval: 180
                                    onTriggered: {
                                        if (_private.isCheckDoubleClickedEvent >= 2) {
                                            // Double Clicked Event
                                            input.doubleClicked(_private.mouseEvent)
                                        }

                                        stop()
                                        _private.isCheckDoubleClickedEvent = 0
                                    }
                                }
                            }
                        }

                        Button{
                            Text {
                                id: cancel
                                text: qsTr("取消")
                                anchors.centerIn: parent
                                font.pixelSize: 15
                            }
                            anchors.top: input.bottom
                            anchors.topMargin: 5
                            anchors.left: input.left
                            height: input.height
                            width: input.width/2-5
                            onClicked: {
                                wifiDialog.toggleCancel()
                                wifiDialog.close()
                            }
                            background: Rectangle{
                                radius: 20
                                height: parent.height
                                width: parent.width
                                color: "#eeeeeeee"
                            }
                        }

                        Button{
                            Text {
                                id: enter
                                text: qsTr("连接")
                                anchors.centerIn: parent
                                color: input.text.length < 8 ? "black" : "#0490f6"
                                font.pixelSize: 15
                            }
                            anchors.top: input.bottom
                            anchors.topMargin: 5
                            anchors.right: input.right
                            height: input.height
                            width: input.width/2-5
                            onClicked: {
                                if(input.text.length >= 0){
                                    wifiDialog.pskValue = input.text
                                    console.log(wifiDialog.pskValue)
                                    wifiDialog.toggleConnet()
                                    wifiDialog.close()
                                }
                            }

                            background: Rectangle{
                                radius: 20
                                height: parent.height
                                width: parent.width
                                color: "#eeeeeeee"
                            }
                        }

                    }

                    InputPanel {
                        id: inputPanel
                        z: 50
                        //x: -11
                        x: -24
                        y: wifiDialog.height
                        width: wifiDialog.width
                        //visible: myWireless.visible
                        states: State {
                            name: "visible"
                            when: inputPanel.active
                            PropertyChanges {
                                target: inputPanel
                                y: wifiDialog.height - inputPanel.height
                            }
                        }
                        transitions: Transition {
                            from: ""
                            to: "visible"
                            reversible: true
                            ParallelAnimation {
                                NumberAnimation {
                                    properties: "y"
                                    duration: 250
                                    easing.type: Easing.InOutQuad
                                }
                            }
                        }
                    }

                }

                Rectangle {
                    id: mywireless
                    x: 38
                    y: 104
                    width: 947
                    height: 408
                    color: "#ffffff"
                    radius: 11
                    layer.enabled: true
                    transformOrigin: Item.Center
                    border.width: 3
                    rotation: 0
                    border.color: "#fdfdfd"
                    clip: false
                    visible: true
                    Item {
                        id: formState
                        states: State {
                            name: "right"
                            PropertyChanges {
                                target: myWireless
                                x: 0
                            }
                        }
                        transitions: Transition {
                            NumberAnimation {
                                property: "x"
                                easing.type: Easing.InOutQuart
                                duration: 500
                            }
                        }
                    }
                    WirelessListModel {
                        id: myWirelessListModel
                        onCurrentIndexChanged: {
                            playList.currentIndex = currentIndex
                        }
                        onReturnMainWinWifiResult: {
                            wirelessRect.mystate = state
                        }
                        onWirelessReadyChanged: {
                            //if (readyFlag)
                            //wlanText.text = "WLAN"
                        }
                    }

                    ListView{
                        id: playList
                        visible: true
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.bottom: parent.bottom
                        width: parent.width
                        orientation:ListView.Vertical
                        clip: true
                        z: 1
                        spacing: 5
                        model: myWirelessListModel
                        delegate: Rectangle {
                            id: itembg
                            width: playList.width
                            height: 50
                            color: mouserArea.pressed ?  Qt.rgba(46, 46, 46, 0.1) : "transparent"
                            MouseArea {
                                id: mouserArea
                                anchors.fill: parent
                                acceptedButtons: Qt.LeftButton | Qt.RightButton
                                onClicked: {
                                    wirelessRect.mystate = 0
                                    myWirelessListModel.currentIndex = index
                                    //console.log(wifiName.text)
                                    wifiDialog.ssidValue = wifiName.text
                                    wifiDialog.message = "请输入" + (wifiName.text + "的密码")
                                    wifiDialog.open()
                                }
                            }
                            Text {
                                id: wifiName
                                verticalAlignment: Text.AlignVCenter
                                height: 50
                                anchors.right: parent.right
                                anchors.rightMargin: 150
                                anchors.left: wifiLevelIcon.right
                                anchors.leftMargin: 20
                                text:  title
                                elide: Text.ElideRight
                                color: mouserArea.pressed ? "black" : "black"
                                font.pixelSize: 20
                            }
                            Image {
                                id: wifiLevelIcon
                                anchors.left: parent.left
                                anchors.leftMargin: 20
                                anchors.verticalCenter: parent.verticalCenter
                                width: 30
                                height: 22
                                source: wifilevl(level)
                                function wifilevl(arg){
                                    var intArg = parseInt(arg)
                                    switch (intArg){
                                    case 0:
                                        return "qrc:/Image/level0.png"
                                    case 1:
                                        return "qrc:/Image/level1.png"
                                    case 2:
                                        return "qrc:/Image/level2.png"
                                    case 3:
                                        return "qrc:/Image/level3.png"
                                    case 4:
                                        return "qrc:/Image/level4.png"
                                    case 5:
                                        return "qrc:/Image/level5.png"
                                    default:
                                        return "qrc:/Image/level5.png"
                                    }
                                }
                            }
                            Text {
                                id: connectStateText
                                text: connectsate()
                                anchors.left: wifiName.right
                                anchors.leftMargin: 5
                                anchors.right: parent.right
                                horizontalAlignment:Text.AlignHCenter
                                anchors.verticalCenter: parent.verticalCenter
                                color: "gray"
                                function connectsate(){
                                    if (wifiDialog.ssidValue === wifiName.text) {
                                        switch (wirelessRect.mystate){
                                        case 1:
                                            return qsTr("已连接")
                                        case 2:
                                            return qsTr("密码错误/已断开")
                                        case 3:
                                            return qsTr("正在连接...")
                                        default:
                                            return qsTr("")
                                        }
                                    } else return qsTr("")
                                }
                            }
                        }
                    }


                }

                RoundButton {
                    id: refreshBtn
                    x: 926
                    y: 30
                    width: 50
                    height: 50
                    //enabled: wlanSwitch.checked
                    //opacity: wlanSwitch.checked ? 1 : 0
                    //anchors.top: wlanSwitch.bottom
                    //anchors.horizontalCenter: wlanSwitch.horizontalCenter
                    Image {
                        id: refreshImage
                        width: 20
                        height: 20
                        anchors.centerIn: parent
                        source: "qrc:/Image/refresh.png"
                    }
                    background: Rectangle {
                        anchors.fill: parent
                        color: "transparent"
                    }

                    onClicked: {
                        if (wlanSW.checked) {
                            refreshAnima.running = true
                            //wlanText.text = "Scanning..."
                        }
                        if(playList.count != 0 && wlanSW.checked)
                            myWirelessListModel.remove(0, playList.count - 1)
                    }
                    RotationAnimator {
                        id: refreshAnima
                        target: refreshBtn
                        from: 0
                        to: 360
                        duration: 1000
                        //loops: Animation.Infinite
                        running: false
                        onRunningChanged: {
                            if (running === false) {
                                from = refreshBtn.rotation;
                                to = from+360;
                            }
                        }
                        onStopped: {
                            if (wlanSW.checked) {
                                myWirelessListModel.wirelessInit()
                            }
                        }
                    }
                }


            }
            //历史记录
            Rectangle{
                id:historyRootRect
                x:0
                y:0
                property string dialogStr: " "
                property int flag: 0
                //historyDialog
                Dialog{
                    id:historyDialog
                    height: parent.height
                    width: 1024//parent.height
                    x:0
                    y:0
                    background:Image {
                        id: historyDialogbg
                        source: "qrc:/Image/dialogbackground.png"
                    }
                    Text {
                        id: historyDataText
                        x: 38
                        y: 21
                        text: historyRootRect.dialogStr
                        color: "#ffffff"
                        font.pixelSize: 40
                        font.bold: true
                    }
                    ListModel
                    {
                        id:historyListData
                        ListElement{name: "A相电压有效值";key: 0x01}
                        ListElement{name: "B相电压有效值";key: 0x02}
                        ListElement{name: "C相电压有效值";key: 0x03}

                        ListElement{name: "AB电压夹角";key: 0x04}
                        ListElement{name: "AC电压夹角";key: 0x05}
                        ListElement{name: "BC电压夹角";key: 0x06}

                        ListElement{name: "A相流压夹角";key: 0x07}
                        ListElement{name: "B相流压夹角";key: 0x08}
                        ListElement{name: "C相流压夹角";key: 0x09}

                        ListElement{name: "A相电流有效值";key: 0x0a}
                        ListElement{name: "B相电流有效值";key: 0x0b}
                        ListElement{name: "C相电流有效值";key: 0x0c}
                        ListElement{name: "合相电流有效值";key: 0x0d}

                        ListElement{name: "频率";key: 0x0e}

                        ListElement{name: "A相有功功率";key: 0x0f}
                        ListElement{name: "B相有功功率";key: 0x10}
                        ListElement{name: "C相有功功率";key: 0x11}
                        ListElement{name: "合相有功功率";key: 0x12}

                        ListElement{name: "矢量电压和有效值";key: 0x13}
                        ListElement{name: "矢量电流和有效值";key: 0x14}
                        // ListElement{name: "矢量电流和有效值";key: 0x15}

                        ListElement{name: "A相基波有功功率";key: 0x16}
                        ListElement{name: "B相基波有功功率";key: 0x17}
                        ListElement{name: "C相基波有功功率";key: 0x18}
                        ListElement{name: "合相基波有功功率";key: 0x19}

                        ListElement{name: "A相基波有功电能";key: 0x1a}
                        ListElement{name: "B相基波有功电能";key: 0x1b}
                        ListElement{name: "C相基波有功电能";key: 0x1c}
                        ListElement{name: "合相基波有功电能";key: 0x1d}

                        ListElement{name: "A相无功功率";key: 0x1e}
                        ListElement{name: "B相无功功率";key: 0x1f}
                        ListElement{name: "C相无功功率";key: 0x20}
                        ListElement{name: "合相无功功率";key: 0x21}

                        ListElement{name: "A相视在功率";key: 0x22}
                        ListElement{name: "B相视在功率";key: 0x23}
                        ListElement{name: "C相视在功率";key: 0x24}
                        ListElement{name: "合相视在功率";key: 0x25}

                        ListElement{name: "A相功率因数";key: 0x26}
                        ListElement{name: "B相功率因数";key: 0x27}
                        ListElement{name: "C相功率因数";key: 0x28}
                        ListElement{name: "合相功率因数";key: 0x29}

                        ListElement{name: "A相有功电能";key: 0x2a}
                        ListElement{name: "B相有功电能";key: 0x2b}
                        ListElement{name: "C相有功电能";key: 0x2c}
                        ListElement{name: "合相有功电能";key: 0x2d}

                        ListElement{name: "A相视在电能";key: 0x2f}
                        ListElement{name: "B相视在电能";key: 0x30}
                        ListElement{name: "C相视在电能";key: 0x31}
                        ListElement{name: "合相视在电能";key: 0x32}

                        ListElement{name: "芯片温度";key: 0x33}

                    }
                    GridView{
                        id:historyGirdView
                        x:75
                        y:115
                        width:924
                        height: 383
                        clip: true
                        cellHeight: 150
                        cellWidth: 305
                       //model: sqlitOBJ.dataModel
                        model: historyListData
                        delegate: Column{
                            Rectangle{
                                width: 267
                                height: 130
                                radius: 10
                                Text {
                                    x: 25
                                    y: 16
                                    text: name;
                                    anchors.horizontalCenter: parent.TopLeft
                                    id: historyName
                                }
                                Text {
                                    id: historySensorDataText
                                    x:180
                                    y:50
                                    font.pointSize: 50
                                    color: "#A9A9A9"
                                    anchors.horizontalCenter: parent.TopLeft
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignRight
                                    anchors.right: parent.right
                                    text: {
                                        if(historyRootRect.flag === 0){
                                            "null"
                                        }else{
                                            sqlitOBJ.refreshData(historyRootRect.dialogStr);
                                            sqlitOBJ.dataToQML(key)
                                        }
                                    }
                                }


                            }
                        }
                    }


                    RoundButton{
                        x:900
                        y:15
                        background:Image {
                            width: 60
                            height: 60
                            id: close
                            source: "qrc:/Image/close.png"
                        }
                     onClicked: historyDialog.close();
                    }

                }

                Image {
                    source: 'qrc:/Image/background.png'
                }

                Text {
                    id: text7
                    x: 38
                    y: 21
                    color: "#ffffff"
                    text: qsTr("历史记录")
                    font.bold: true
                    font.pixelSize: 40
                }

                Rectangle {
                    id:historyRect
                    x: 38
                    y: 104
                    width: 947
                    height: 408
                    color: "#00000000"
                    radius: 11
                    border.color: "#00000000"
                    border.width: 3
                    clip: false
                    layer.enabled: true
                    rotation: 0
                    transformOrigin: Item.Center

                    ListView {
                        id: historyList
                        x: 0
                        y: 0
                        width: 947
                        height: 408
                        clip: true
                        spacing:20
                        model: sqlitOBJ.model

                        delegate: Button {
                            id:historyDataBTN
                            height: 100
                            width: 940
                            property color clr_font: "#ffffff"
                            property color clr_backNormal: "white"
                            property color clr_backPress: "lightgray"
                            property color clr_boardNormal: "white"
                            property color clr_boardPress: "lightgray"

                            //color: "lightgray"
                            Text {
                                text: modelData;
                                font.pointSize: 20
                                color: "#5f5f5f"
                                anchors.centerIn: parent ;
                                anchors.horizontalCenterOffset: -250
                                anchors.verticalCenterOffset: 0

                                //anchors.leftMargin: 100
                            }
                            Image {
                                id: modelIMG
                                source: "qrc:/Image/enter.png"
                                height: 50
                                width: 50
                                anchors.centerIn: parent ;
                                anchors.horizontalCenterOffset: 400
                                anchors.verticalCenterOffset: 0
                            }
                            background: Rectangle {
                                    implicitWidth: 100
                                    implicitHeight: 40
                                    opacity: enabled ? 1 : 0.3
                                    color: historyDataBTN.down ? clr_backPress : clr_backNormal
                                    border.color: historyDataBTN.down ? clr_boardPress : clr_boardNormal
                                    border.width: 1
                                    radius: 30
                                }

                            onClicked: {
                                //sqlitOBJ.refreshData(modelData);
                                historyRootRect.dialogStr = modelData;
                                console.log(historyRootRect.dialogStr);
                                historyRootRect.flag = 1
                                historyDialog.open();
                            }

                        }

                    }
                }

            }
        }
    }
    //menu
    Rectangle{
        id:barRoot
        x: 783
        y: 526
        width: 200
        height: 90
        color: "transparent";
        border.color: "#00000000"

        Rectangle{
            id: barRect;
            width: unfold ? 1000 : 0;
            height: 35;
            anchors.centerIn: parent;
            color: "transparent";
            clip: true;
            Behavior on width{
                NumberAnimation{duration:200;}
            }

            ListModel{
                id: appModel;
                ListElement{
                    index : 0;
                    name: "电力参数";

                }
                ListElement{
                    index : 1;
                    name: "功能设置";

                }
                ListElement{
                    index : 2;
                    name: "网络连接";

                }
                ListElement{
                    index : 3;
                    name: "历史记录";

                }
            }

            Component{
                id: appDelegate;
                Rectangle {
                    id: delegateBackground;
                    width: barRect.width;
                    height: 50;
                    radius: 5;
                    color: "transparent";
                    //显示APP文字
                    Text {
                        anchors.leftMargin: 40;
                        color: "white"
                        text: name;
                        font.pixelSize: 20;
                    }
                    //鼠标处理
                    MouseArea{
                        anchors.fill: parent;
                        hoverEnabled: true;
                        onEntered: delegateBackground.color = "#10000000";
                        onExited: delegateBackground.color = "#00000000";
                        onClicked: {
                            console.log(name);
                            console.log(index);
                            swpieView.currentIndex = index;
                        }
                    }
                }
            }

            GridView{
                id: appGrid;
                width:700;

                height: parent.height;
                anchors.left: parent.left;
                anchors.top: parent.top;
                anchors.topMargin: 0;
                model: appModel;
                delegate: appDelegate;
                cellWidth: 150;
                cellHeight: 50;
            }
        }
        // 展开/收回按钮
        Rectangle{
            width: 30;
            height: width;
            radius: 10;
            color: "transparent";
            border.color: "#ffffff"
            border.width: 5;
            anchors.left: barRoot.right;
            anchors.leftMargin: -width/2;
            anchors.verticalCenter: barRect.verticalCenter;
            Image {
                width: 24;
                height: 24;
                anchors.centerIn: parent;
                mipmap: true;
                //此处使用旋转1180度实现展开按钮图标和收回按钮图标
                rotation: unfold? 180:0;
                //source: "qrc:/image/arrows.png";
            }

            MouseArea{
                anchors.fill: parent;
                onClicked: {
                    unfold = !unfold;

                }
            }
        }

    }
}




