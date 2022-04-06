import QtQuick 2.12
import QtQuick.Window 2.12
import QtWebView 1.1

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Mospoly Messanger")

    WebView {
        id: webView
        anchors.fill: parent
        url: initialUrl
        onLoadingChanged: {
            if (loadRequest.errorString)
                console.error(loadRequest.errorString);
        }
    }
}
