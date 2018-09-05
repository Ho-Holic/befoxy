#include "Befoxy.hpp"
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <core/Services.hpp>

Befoxy::Befoxy(QWidget *parent)
:   QWidget(parent)
{
    // layout
    {
        QLabel* clockText = new QLabel("00:00", this);
        m_clockText = clockText;
    }

    // update visual loop
    {
        QTimer* timer = new QTimer(this);
        timer->setInterval(1000);
        timer->setSingleShot(false);

        connect(timer, SIGNAL(timeout()), this, SLOT(updateVisual()));
        timer->start();
    }
}

void Befoxy::updateVisual()
{
    auto sprint = services().engine().sprint();
    if (sprint.time.hour > 0) {
        m_clockText->setText(QString("%1").arg(sprint.time.hour));
    } else {
        m_clockText->setText(QString("%1:%2").arg(sprint.time.min).arg(sprint.time.sec));
    }
}
