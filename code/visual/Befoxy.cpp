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
#include <visual/TapLabel.hpp>

Befoxy::Befoxy(QWidget *parent)
:   QWidget(parent)
{
    this->setWindowFlags(Qt::Popup);

    // layout
    {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QLabel* clockText = new QLabel("00:00", this);
        clockText->setAlignment(Qt::AlignCenter);
        {
            QFont clockFont = clockText->font();
            clockFont.setPointSize(72);
            clockFont.setWeight(QFont::Bold);
            clockText->setFont(clockFont);
        }

        QLabel* sprintName = new QLabel("", this);
        sprintName->setAlignment(Qt::AlignCenter);
        {
            QFont sprintFont = sprintName->font();
            sprintFont.setPointSize(30);
            sprintFont.setWeight(QFont::Light);
            sprintName->setFont(sprintFont);
        }

        TapLabel* tapButton = new TapLabel("[ tap ]", this);
        tapButton->setAlignment(Qt::AlignCenter);
        {
            QFont tapFont = tapButton->font();
            tapFont.setPointSize(48);
            tapFont.setWeight(QFont::DemiBold);
            tapButton->setFont(tapFont);
        }

        connect(tapButton, &TapLabel::clicked, []{
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

        auto screenRect = QApplication::desktop()->screenGeometry();

        auto foxyRect = this->geometry();
        auto trayRect = m_trayIcon->geometry();
        auto foxySize = QPoint(foxyRect.width(), foxyRect.height());

        // 1. check tray at top right
        foxyRect.moveTo(trayRect.bottomRight() - QPoint(foxyRect.width(), 0));
        if (!screenRect.contains(foxyRect, true)) {

            // 2. check tray at bottom right
            foxyRect.moveTo(trayRect.topRight() - foxySize);

            if (!screenRect.contains(foxyRect, true)) {

                // 3. check tray at right bottom
                //
                // TODO: this condition not working because
                // it 'bottom right' tray position is fine to
                // We need some kind of best fit between two positions
                //
                foxyRect.moveTo(trayRect.bottomLeft() - foxySize);

                if (!screenRect.contains(foxyRect, true)) {
                    // 4. check tray at left bottom
                    foxyRect.moveTo(trayRect.bottomRight() - QPoint(0, foxyRect.height()));
                    if (!screenRect.contains(foxyRect, true)) {
                        foxyRect.moveTo(screenRect.center() - foxySize / 2);
                    }
                }
            }
        }



        this->move(foxyRect.topLeft());
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

    if (m_trayIcon) {
        auto iconColor = sprintIconColorMap()(sprint.type);
        m_trayIcon->setIcon(IconGenerator::generate(iconColor));
    }
}


