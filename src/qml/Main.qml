import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

import "FileDialog" as FileDialog
ApplicationWindow {
    visible: true;
    visibility: "FullScreen"

    FileDialog.CustomFileDialog{

    }

    Shortcut {
        sequence: StandardKey.Quit
        context: Qt.ApplicationShortcut
        onActivated: Qt.quit()
    }
}
