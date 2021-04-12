#include "widget.h"
#include <QApplication>
const QString& app_path() {
    static QString path(QApplication::applicationDirPath() + "/");
    return path;
}

QString load_txt_file(const QString& file_name)
{
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return QString("");
    }

    QByteArray data_byte = file.readAll();
    QTextStream ts(&data_byte);
    ts.setCodec("UTF-8");
    return ts.readAll();
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(load_txt_file(app_path() + QStringLiteral("qsswhite.config")));
    Widget w;
    w.show();
    return a.exec();
}
