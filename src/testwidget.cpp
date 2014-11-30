#include "testwidget.h"
#include "ui_testwidget.h"
#include "gifplayer.h"
#include "gifloader.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QMovie>
#include <QMouseEvent>

TestWidget::TestWidget(QWidget *parent) :
    QDialog(parent)
{
    m_ui = new Ui::TestWindow;
    m_ui->setupUi(this);
    connect(m_ui->goButton, SIGNAL(clicked()), this, SLOT(onGoButtonClicked()));
}

TestWidget::~TestWidget()
{
    delete m_ui;
}

void TestWidget::onGoButtonClicked()
{
    QString url = m_ui->urlEdit->text();
    if (url.isEmpty())
        return;

    GifPlayer* player = new GifPlayer();
    player->play(url);
    m_ui->gifLayout->addWidget(player);

    GifLoader::instance()->load(url, player);
}
