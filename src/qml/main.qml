import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15
import QtQuick.Window 2.2

ApplicationWindow {
    property string assets:
    (pathIsLocal ? Qt.resolvedUrl(".") : "https://raw.githubusercontent.com/jetrotal/easyRPG_UI/main/")

    id: app
    visible: true

    minimumWidth: 720; minimumHeight: 480
    background:ez.bg;

    component Content : Rectangle {
        anchors.margins:20;
        anchors.fill:parent
        color:"transparent"
        border.color: "red"
    }
    component UI_Library : Item {
        visible:false
        property real resizeFactor: 1
        property var style: {

            "sizes": {
                "text":9 * resizeFactor,
                "topBar":27 * resizeFactor,
                "logo": 16 * resizeFactor,
                "win":16 * resizeFactor,
                "icon":24 * resizeFactor,
                "checkboxSpacing":15 * resizeFactor,
                "checkboxOuter":11 * resizeFactor,
                "checkboxInner":5 * resizeFactor,

            },

            "colors": {
                "bg": "#292b2f",
                "header": "#242529",
                "textA": "#97999C",
                "textB": "#FFF",
                "highlight": "#8AFF4E",
                "separator": "#555",
                "darkBorders": "#1e1e1e",
                "shadowColor":"#222327"
            },

            "images": {
                "logo": assets + "img/ez-logo.svg",
                "bg": assets + "img/bg/tile.svg",
                "icons": {
                    "win": {
                        "url": assets + "img/icons/window/"
                    },
                    "top": {
                        "url": assets + "img/icons/top/"
                    }
                }
            }
        } // STYLES
        property var appButtons: {
            "workSpace": [{
                "obj": "appHome",
                "display": "Home",
            },/*separator*/, {
                "obj": "mapEditor",
                "display": "Map Editor",
            }, {
                "obj": "databaseEditor",
                "display": "Database Editor",
            }, {
                "obj": "eventsEditor",
                "display": "Events Editor",
            },/*separator*/, {
                "obj": "resourceManager",
                "display": "Resource Manager",
            }, {
                "obj": "gameSearch",
                "display": "Search",
            },/*separator*/, {
                "obj": "bgmTest",
                "display": "BGM test",
            },/*separator*/, {
                "obj": "gameSettings",
                "display": "Playtest Settings",
            }, {
                "obj": "gamePlay",
                "display": "Begin Playtest",
            }],
            "window": [{
                "obj": "min",
                "display": "Minimize Window",
            }, {
                "obj": "max",
                "display": "Maximize Window",
            }, {
                "obj": "close",
                "display": "Close Window",
            }],
            "topBar": [{
                "obj": "project",
                "display": "Game Project",
                "contents": [{
                    "obj":"newProject","display":"New Project", "shortcut":"Ctrl+N", "disabled":1
                }, {
                    "obj":"openProject","display":"Open Project", "shortcut":"Ctrl+O", "disabled":1
                }, {
                    "obj":"closeProject","display":"Close Project",  "shortcut":"Ctrl+X"
                },/*separator*/, {
                    "obj":"createDisk","display":"Create Game Disk"
                },/*separator*/, {
                    "obj":"quit","display":"Quit"
                }]
            }, {
                "obj": "maps",
                "display": "Maps",
                "contents": [{
                    "obj":"saveMap","display":"Save Map", "shortcut":"Ctrl+S"
                }, {
                    "obj":"revertMap","display":"Revert Map", "shortcut":"Ctrl+R"
                },/*separator*/, {
                    "obj":"lowerLayer","display":"Lower Layer", "shortcut":"F5"
                }, {
                    "obj":"upperLayer","display":"Upper Layer", "shortcut":"F6"
                }, {
                    "obj":"eventsLayer","display":"Events Layer", "shortcut":"F7"
                },/*separator*/, {
                    "obj":"defaultZoom","display":"Zoom 100%"
                }, {
                    "obj":"zoomIn","display":"Zoom In", "shortcut":"+"
                }, {
                    "obj":"zoomOut","display":"Zoom Out", "shortcut":"-"
                }]
            }, {
                "obj": "view",
                "display": "View",
                "contents": [{
                    "obj":"palette","display":"Palette","checkbox":1,"checked":1
                }, {
                    "obj":"mapTree","display":"Map Tree","checkbox":1,"checked":1
                }]
            }, {
                "obj": "tools",
                "display": "Tools",
                "contents": [{
                    "obj":"database","display":"DataBase", "shortcut":"F8"
                }, {
                    "obj":"resourceManager","display":"Resource Manager"
                }, {
                    "obj":"jukebox","display":"Jukebox"
                }, {
                    "obj":"search","display":"Search"
                },]
            }, {
                "obj": "game",
                "display": "Game",
                "contents": [{
                    "obj":"playTest","display":"PlayTest", "shortcut":"F4"
                },/*separator*/, {
                    "obj":"fullScreen","display":"Fullscreen", "checkbox":1,"checked":1
                }, {
                    "obj":"showTitle","display":"Show Title Background","checkbox":1,"checked":1
                },/*separator*/, {
                    "obj":"playSettings","display":"PlayTest Settings"
                },]
            }, {
                "obj": "help",
                "display": "Help",
                "contents": [{
                    "obj":"contents","display":"Contents", "shortcut":"F1"
                },/*separator*/, {
                    "obj":"about","display":"About"
                }, {
                    "obj":"aboutQt","display":"About Qt"
                },]
            }, {
                "obj": "debug",
                "display": "Debug",
                "contents": [{
                    "obj":"rtpPath","display":"RTP Path"
                }, {
                    "obj":"caching","display":"Enable Caching","checkbox":1,"checked":1
                },/*separator*/, {
                    "obj":"displayButtons","display":"Display Button Actions","checkbox":1,"checked":debugParams.displayButtons * debug
                }, {
                                   "obj":"displayBorders","display":"Display Invisible Borders","checkbox":1,"checked":debugParams.displayBorders * debug
                               },, {
                                   "obj":"listProperties","display":"List Properties on Console","checkbox":1,"checked":debugParams.listProperties * debug
                               },]
            }]
        }

        function listProperties(item) {
            // debug props
            var result="";
            for (var p in item) result += String(item[p]) !== "function() { [native code] }" ? (p +": " + (String(item[p]) ==="[object Object]" ?" {; "+ listProperties(item[p])+" } " : item[p]) +`;`):"";
            return(result.split(';').join(pathIsLocal ? "\n" : "<br>"))
        }


        function detectCommand(bt, type,qmlItem) {
            if (type[1] === "debug") debugFunction(bt)
            if (debugParams.displayButtons===1) footerMark.text = ("running detectCommand() - You clicked: " + JSON.stringify(bt.obj) + "  |  Type: "+JSON.stringify(type))
            else footerMark.text="";

            if (debugParams.listProperties===1) console.log(ez.listProperties(qmlItem))


            if (type === "workspace") return changeWorkspace(bt)
            if (type === "window") return resizeWindow(bt)

        }

        function debugFunction(bt){
            console.log(bt.obj +": "+debugParams[bt.obj])
            debugParams[bt.obj] = debugParams[bt.obj] === 0 ? 1 : 0
            contentBody.border.width = debugParams.displayBorders
        }

        function resizeWindow(bt) {
            if (bt.obj === "min") return app.showMinimized()
            if (bt.obj === "max") return console.log(app.visibility), app.visibility === 4 ? app.showNormal() :app.showMaximized()
            if (bt.obj === "close") return app.close()
        }

        function changeWorkspace(e) {
            currWorkspace.text = "<pre><font color='" + styles.colors.textB + "'>  " + e.display + "  </pre>"
        }

        property Item bg: Rectangle {
            anchors.fill: parent
            color: ez.style.colors.bg
            Image {
                anchors.fill:parent
                fillMode: Image.Tile
                source: ez.style.images.bg
            }
        }


    }
    UI_Library {
        id:ez
    } // ez[variableName] // ez.styles[styleVar] //

    menuBar:Rectangle {
        anchors.left:parent.left
        anchors.right:parent.right
        height:topBar.height
        color: ez.style.colors.header


        Row {

            MenuBar {
                id: topBar
                background.visible:false;
                height:ez.style.sizes.topBar
                width:app.width
                contentItem: Row {
                    Text {
                        text:"<img width='"+ez.style.sizes.logo+"' height='"+ez.style.sizes.logo+"' src='"+ez.style.images.logo+"'></img>"

                        font.pointSize: ez.style.sizes.text
                        padding:6 * ez.resizeFactor

                    }

                }

                Repeater {
                    model: ez.appButtons.topBar
                    MenuBarItem {
                        font.pointSize: ez.style.sizes.text
                        onClicked:ez.detectCommand(modelData, "topBar")
                         visible:(modelData.obj === "debug") ? debug : 1
                        background: Rectangle {
                            color: highlighted ? ez.style.colors.darkBorders : ez.style.colors.header


                        }

                        menu: Menu {

                            id:container
                            property var obj: modelData.obj
                            title: "<font color='"+ (highlighted ? ez.style.colors.textB : ez.style.colors.textA)+"'>" + modelData.display+"</font>"
                            font.pointSize: ez.style.sizes.text
                            width:implicitWidth * ez.resizeFactor

                            background: MenuItem {

                                Rectangle {
                                    width:parent.width+2; height:parent.height+2;
                                    anchors.centerIn:parent
                                    color:ez.style.colors.shadowColor
                                }
                            }

                            //background.visible:false
                            Repeater {
                                id: outerDelegate
                                model: modelData.contents

                                MenuItem {
                                    text: "<font color='"+ (highlighted ? ez.style.colors.textB : ez.style.colors.textA)+"'>"+(modelData ? modelData.display:"")+"</font>"
                                    font.pointSize: ez.style.sizes.text
                                    height: modelData ? undefined : 10
                                    horizontalPadding:15 * ez.resizeFactor
                                    enabled: modelData? (modelData.disabled ? false : true): false
                                    contentItem.opacity: enabled ? 1 :.5

                                    Text{
                                        opacity: parent.contentItem.opacity
                                        text:modelData? (modelData.shortcut ? "<font color='"+ (parent.highlighted ? ez.style.colors.textB : ez.style.colors.textA)+"'>" + modelData.shortcut +"</font> " : "")
                                        : "";
                                        font.pointSize: parent.font.pointSize
                                        padding:parent.padding
                                        anchors.right: parent.right
                                        anchors.rightMargin:parent.horizontalPadding

                                    }

                                    checkable: modelData ? (modelData.checkbox ? modelData.checkbox :false) : false
                                    checked: modelData ? (modelData.checked ? modelData.checked : false ): false

                                    indicator:Column {
                                        anchors.verticalCenter:parent.verticalCenter
                                        x:ez.style.sizes.checkboxSpacing
                                        Rectangle {
                                            width:ez.style.sizes.checkboxOuter; height:ez.style.sizes.checkboxOuter
                                            opacity:parent.parent.checkable;
                                            color:"transparent"
                                            border.color: ez.style.colors.textA
                                            border.width:1 * ez.resizeFactor
                                            Rectangle {
                                                opacity:parent.parent.parent.checked
                                                anchors.centerIn:parent
                                                color: ez.style.colors.textA
                                                width:ez.style.sizes.checkboxInner; height:ez.style.sizes.checkboxInner;
                                            }

                                        }
                                    }

                                    onClicked: ez.detectCommand(modelData, ["topBar",container.obj],this)
                                    Rectangle {
                                        anchors.centerIn:parent
                                        color:ez.style.colors.separator
                                        width:parent.width -25
                                        height: modelData ? 0 : 1
                                    }
                                    background: Rectangle {
                                        color:highlighted ? ez.style.colors.darkBorders: ez.style.colors.bg

                                    }

                                }
                            }
                        }

                    }
                }


            }
        }


        MenuBar {
            height:parent.height
            width:parent.height*3
            background.visible:false
            anchors.right:parent.right
            Repeater {

                model: ez.appButtons.window

                MenuItem {
                    font.pointSize:ez.style.sizes.text
                    width:parent.height; height:parent.height
                    icon.source: ez.style.images.icons.win.url + modelData.obj + ".svg"
                    icon.color: this.hovered ? ez.style.colors.textB : ez.style.colors.textA
                    icon.width:ez.style.sizes.icon; icon.height:ez.style.sizes.icon;
                    onClicked: ez.detectCommand(modelData, "window",this)
                    background:Rectangle {
                        color:ez.style.colors.header;
                    }
                }
            }
        }
    }
    header: Rectangle {
        color:ez.style.colors.header
        width:parent.width+4
        x:-2
        height:headerContents.height
        border.color: ez.style.colors.shadowColor
        border.width:2




        TabBar {
            id:headerContents
            padding: 3 * ez.resizeFactor
            horizontalPadding :15* ez.resizeFactor
            background:Rectangle {
                width:app.width
                visible:false
            }
            Repeater {

                model: ez.appButtons.workSpace
                TabButton {

                    enabled: !modelData ? false : true

                    width:!modelData ? 15: undefined;

                    icon.width:ez.style.sizes.icon; icon.height:ez.style.sizes.icon
                    icon.source: !modelData ? "" : ez.style.images.icons.top.url + modelData.obj+".svg"

                    icon.color: checked ? ez.style.colors.highlight : (hovered ? ez.style.colors.textB :ez.style.colors.textA)
                    font.pointSize: ez.style.sizes.text
                    ToolTip {
                        delay:500
                        text: modelData ? modelData.display : ""
                        visible:modelData? hovered: false
                    }

                    Rectangle {
                        visible: !modelData ? true : false
                        color:ez.style.colors.separator
                        anchors.centerIn: parent
                        width: 1* ez.resizeFactor
                        height:20* ez.resizeFactor
                    }

                    background: Rectangle {
                        visible:hovered * enabled
                        color: ez.style.colors.darkBorders
                    }
                    onClicked: ez.detectCommand(modelData, "workspace",this)

                }

            }

        }

    }
    footer: Rectangle {
        color:ez.style.colors.header
        width:parent.width
        height:menuBar.height/1.1

        Text {
            id:footerMark
            anchors.left:parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins:10 * ez.resizeFactor
            color: ez.style.colors.textA
            text: ""
            font.pointSize: ez.style.sizes.text / 1.05
        }

        Text {
            anchors.right:parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins:footerMark.anchors.margins
            color: ez.style.colors.textA
            text: "easyRPG.org"
            font.pointSize: footerMark.font.pointSize
        }

    }

    Content {
        id:contentBody
        Rectangle {}
    }

    property int pathIsLocal: 0
    property int debug: 1
    property var debugParams:{"displayBorders":debug, "displayButtons":debug, "listProperties":debug }
}
