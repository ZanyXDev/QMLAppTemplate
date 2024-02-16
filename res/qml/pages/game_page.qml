import QtQuick 2.15
import QtQuick.Controls 2.15 as QQC2
import QtQuick.Layouts 1.15

import common 1.0
import "qrc:/res/js/util.js" as Utils

QQC2.Page {
    id: root

    // ----- Property Declarations
    // Required properties should be at the top.

    // https://doc.qt.io/qt-5/qtqml-syntax-objectattributes.html#a-note-about-accessing-attached-properties-and-signal-handlers
    property bool pageActive: false

    // ----- Signal declarations
    // ----- Size information
    // ----- Then comes the other properties. There's no predefined order to these.
    onPageActiveChanged: {
        AppSingleton.toLog(`GamePage.onActivated pageActive ${pageActive}`)      
    }
    // ----- Visual children.
    background: {
        null
    }
    Component.onCompleted: {
        AppSingleton.toLog(`GamePage [${root.height}h,${root.width}w]`)
    }

    //-------------


    //-------------
    // ----- Qt provided non-visual children    
}
