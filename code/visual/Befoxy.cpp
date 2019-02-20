#include "Befoxy.hpp"
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <core/Services.hpp>
#include <core/Conversion.hpp>
#include <visual/Conversion.hpp>
#include <QSystemTrayIcon>

Befoxy::Befoxy(QWidget *parent)
:   QWidget(parent)
{
    // layout
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QLabel* clockText = new QLabel("00:00", this);        
        QPushButton* tapButton = new QPushButton(this);
        QLabel* sprintName = new QLabel("", this);

        connect(tapButton, &QPushButton::clicked, []{
            services().engine().tap();
        });

        layout->addWidget(clockText);
        layout->addWidget(sprintName);
        layout->addWidget(tapButton);


        m_clockText = clockText;
        m_sprintName = sprintName;
    }

    // icon
    bool hasIcon = QSystemTrayIcon::isSystemTrayAvailable();
    if (hasIcon) {
        QSystemTrayIcon* icon = new QSystemTrayIcon(this);
        m_trayIcon = icon;
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
        m_clockText->setText(QString("%1:%2")
            .arg(sprint.time.hour, 2, 10, QChar('0'))
            .arg(sprint.time.min, 2, 10, QChar('0')));
    } else {
        m_clockText->setText(QString("%1:%2")
            .arg(sprint.time.min, 2, 10, QChar('0'))
            .arg(sprint.time.sec, 2, 10, QChar('0')));
    }
    auto type = sprintTypeMap()(sprint.type);
    auto state = sprintStateMap()(sprint.state);
    m_sprintName->setText(type + ": " + state);

    auto iconPath = sprintIconPathMap()(sprint.type);
    m_trayIcon->setIcon(QIcon(iconPath));

}
