#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include <windows.h>
#include <QMessageBox>

#include <WtsApi32.h>
#pragma comment(lib, "Wtsapi32.lib")

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

const ULONG_PTR CUSTOM_TYPE = 10000;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("ReceiveMessage");
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    MSG *param = static_cast<MSG *>(message);

    switch (param->message)
    {
        case WM_COPYDATA:
        {
            qDebug() << "WM_COPYDATA";
            COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(param->lParam);
            if (cds->dwData == CUSTOM_TYPE)
            {
                qDebug() << "CUSTOM_TYPE";
                QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);
                QMessageBox::information(this, QStringLiteral("Prompt"), strMessage);
                *result = 1;
                return true;
            }
        }
    }
    return QWidget::nativeEvent(eventType, message, result);
}
