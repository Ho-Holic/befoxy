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
#include <visual/ColorScheme.hpp>

namespace
{
    void setLabelColor(QLabel* label, const ColorRole& role)
    {
        QPalette clockPalette = label->palette();
        clockPalette.setColor(label->foregroundRole(),
                              ColorScheme::valueFor(role));
        label->setPalette(clockPalette);
    }

    void setLabelFont(QLabel* label, int pointSize, int weight)
    {
        QFont font = label->font();
        font.setPointSize(pointSize);
        font.setWeight(weight);
        label->setFont(font);
    }
}

Befoxy::Befoxy(QWidget *parent)
:   QWidget(parent)
{
    this->setWindowFlags(Qt::Popup);

    // layout
    {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QLabel* clockText = new QLabel("00:00", this);
        {            
            clockText->setAlignment(Qt::AlignCenter);
            setLabelFont(clockText, QFont::Bold, 72);
            setLabelColor(clockText, ColorRole::AccentCurrent);
        }

        QLabel* sprintName = new QLabel("", this);
        {            
            sprintName->setAlignment(Qt::AlignCenter);
            setLabelFont(sprintName, QFont::Light, 30);
            setLabelColor(sprintName, ColorRole::AccentCurrent);
        }

        TapLabel* tapButton = new TapLabel("[ tap ]", this);
        {
            tapButton->setAlignment(Qt::AlignCenter);
            setLabelFont(tapButton, QFont::DemiBold, 48);
            setLabelColor(tapButton, ColorRole::AccentCurrent);
        }

        QLabel* progress = new QLabel("", this);
        {
            progress->setAlignment(Qt::AlignCenter);
            setLabelFont(progress, QFont::Light, 30);
            setLabelColor(progress, ColorRole::AccentCurrent);
        }

        connect(tapButton, &TapLabel::clicked, []{
            services().engine().tap();
            services().dataStorage().save();
        });

        layout->addWidget(clockText);
        layout->addWidget(sprintName);
        layout->addWidget(tapButton);
        layout->addWidget(progress);


        m_clockText = clockText;
        m_sprintName = sprintName;
        m_tapButton = tapButton;
        m_progress = progress;
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

void Befoxy::paintEvent(QPaintEvent* event)
{
    QPainter p(this);        

    QPen pen = p.pen();
    QBrush brush = p.brush();

    {
        brush.setColor(ColorScheme::valueFor(ColorRole::Background));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        p.setBrush(brush);
        p.drawRect(0, 0, width(), height());
    }

    {
        pen.setColor(ColorScheme::valueFor(ColorRole::AccentCurrent));
        pen.setWidth(8);
        p.setPen(pen);
        p.drawRect(0, 0, width(), height());
    }
    QWidget::paintEvent(event);
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

    // update progress
    {
        auto progress = services().engine().workProgress();
        m_progress->setText(QString("%1 / %2").arg(progress.current).arg(progress.maximum));
    }

    // updateColors
    {
        switch (sprint.type) {
        case SprintType::Work: ColorScheme::changeAccent(ColorRole::AccentWork); break;
        case SprintType::Rest: ColorScheme::changeAccent(ColorRole::AccentRest); break;
        default: ColorScheme::changeAccent(ColorRole::NeutralText);
        }
        setLabelColor(m_clockText, ColorRole::AccentCurrent);
        setLabelColor(m_sprintName, ColorRole::AccentCurrent);
        setLabelColor(m_tapButton, ColorRole::AccentCurrent);
        setLabelColor(m_progress, ColorRole::AccentCurrent);

        if (m_trayIcon) {
            auto iconColor = sprintIconColorMap()(sprint.type);
            m_trayIcon->setIcon(IconGenerator::generate(iconColor));
        }
    }



    update(); // we want to trigger a paintEvent to color background and outline
}


