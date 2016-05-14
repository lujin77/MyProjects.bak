#include <QtCore/QCoreApplication>
#include <QAxObject>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QAxObject *excel = NULL;
    QAxObject *workbooks = NULL;
    QAxObject *workbook = NULL;
    excel = new QAxObject("Excel.Application");
    if (!excel) {
        qDebug()<<"´íÎó!excel¶ÔÏó¶ªÊ§";
    }
    excel->dynamicCall("SetVisible(bool)", false);
    workbooks = excel->querySubObject("WorkBooks");
    workbook = workbooks->querySubObject("Open(QString,QVariant)",QString("d:\\test.xls"));
    QAxObject *worksheet = workbook->querySubObject("WorkSheets(int)",1);
    QAxObject *userange = worksheet->querySubObject("UsedRange");
    QAxObject *rows = userange->querySubObject("Rows");
    QAxObject *columns = userange->querySubObject("Columns");
    int intRowStart = userange->property("Row").toInt();
    int intColStart = userange->property("Column").toInt();
    int intCols = columns->property("Count").toInt();
    int intRows = rows->property("Count").toInt();
    for (int i = intRowStart; i < intRowStart + intRows; ++i) {
        for (int j = intColStart; j < intColStart + intCols; ++j) {
            QAxObject *value = worksheet->querySubObject("Cells(int,int)",i,j);
            qDebug()<<i<<j<<value->property("Value");
        }
    }
    return a.exec();
}
