#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractNativeEventFilter>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
