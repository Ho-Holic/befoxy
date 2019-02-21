#include "Befoxy.hpp"
#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <core/Services.hpp>
#include <core/Conversion.hpp>
#include <visual/Conversion.hpp>
#include <visual/IconGenerator.hpp>

Befoxy::Befoxy(QWidget *parent)
:   QWidget(parent)
{
    this->setWindowFlags(Qt::Popup);

    // layout
    {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QLabel* clockText = new QLabel("00:00", this);
        QFont clockFont = clockText->font();
        clockFont.setPointSize(72);
        clockText->setFont(clockFont);
        clockText->setAlignment(Qt::AlignCenter);

        QLabel* sprintName = new QLabel("", this);
        QFont sprintFont = sprintName->font();
        sprintFont.setPointSize(30);
        sprintName->setFont(sprintFont);
        sprintName->setAlignment(Qt::AlignCenter);


        QPushButton* tapButton = new QPushButton(this);

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
        auto dummyIconColor = sprintIconColorMap()(SprintType::Unknown);
        QSystemTrayIcon* icon = new QSystemTrayIcon(IconGenerator::generate(dummyIconColor), this);
        connect(icon, &QSystemTrayIcon::activated, this, &Befoxy::trayIconActivated);
        icon->show();

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

    updateVisual();
}

void Befoxy::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger: {

        //auto screenRect = QApplication::desktop()->screenGeometry();

        auto foxyRect = this->geometry();

        // tray at top right
        //foxyRect.moveTo(m_trayIcon->geometry().bottomLeft());

        //if (!screenRect.intersects(foxyRect)) break;

        //foxyRect.moveTo(m_trayIcon->geometry().);

        this->move(m_trayIcon->geometry().bottomRight() - QPoint(foxyRect.width(), 0));
        this->show();
        break;
    }
    case QSystemTrayIcon::Context: QApplication::instance()->quit(); break;
    default:;
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
    m_sprintName->setText(QString("%1 (%2)").arg(type).arg(state));

    auto iconColor = sprintIconColorMap()(sprint.type);
    m_trayIcon->setIcon(IconGenerator::generate(iconColor));

}


