#include <view/helpbrowser.hpp>

HelpBrowser::HelpBrowser(QHelpEngine* heg, QWidget* parent)
    : QTextBrowser(parent), helpEngine(heg) {}

HelpBrowser::~HelpBrowser() {}

QVariant HelpBrowser::loadResource(int type, const QUrl& url) {
    if (url.scheme() == "qthelp") {
        return QVariant(helpEngine->fileData(url));
    }
    else {
        return QTextBrowser::loadResource(type, url);
    }
}