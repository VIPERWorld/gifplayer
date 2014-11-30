#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QDialog>

namespace Ui
{
    class TestWindow;
}

class QMovie;
class TestWidget : public QDialog
{
    Q_OBJECT
public:
    explicit TestWidget(QWidget *parent = 0);
    ~TestWidget();

private slots:
    void onGoButtonClicked();

protected:
    Ui::TestWindow* m_ui;
};

#endif // TESTWIDGET_H
