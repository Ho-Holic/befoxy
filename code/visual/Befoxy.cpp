#include "Befoxy.hpp"

#include <QPainter>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QDesktopServices>
#include <QUrl>

#include <core/Services.hpp>
#include <core/Conversion.hpp>
#include <visual/Conversion.hpp>
#include <visual/IconGenerator.hpp>
#include <visual/TapLabel.hpp>
#include <visual/ColorScheme.hpp>

#include <vector>

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
    setWindowFlags(Qt::Popup | Qt::NoDropShadowWindowHint | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);

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

        TapLabel* settings = new TapLabel("[/]", this);
        {
            settings->setAlignment(Qt::AlignCenter);
            setLabelFont(settings, QFont::Light, 30);
            setLabelColor(settings, ColorRole::AccentCurrent);
        }

        QLabel* dummy = new QLabel("   ", this);
        {
            dummy->setAlignment(Qt::AlignCenter);
            setLabelFont(dummy, QFont::Light, 30);
            setLabelColor(dummy, ColorRole::AccentCurrent);
        }


        QHBoxLayout* bottomBar = new QHBoxLayout();
        {
            bottomBar->addWidget(dummy);
            bottomBar->addWidget(progress);
            bottomBar->addWidget(settings);
        }

        connect(tapButton, &TapLabel::clicked, []{
            service<Engine>().tap();
            service<DataStorage>().save();
        });

        connect(settings, &TapLabel::clicked, []{

            // TODO: reload current model and reset current workday for first iterations
            auto settingsPath = service<DataStorage>().settingsFilePath();
            bool success = QDesktopServices::openUrl(QUrl::fromLocalFile(settingsPath));
            if (!success) {
                // TODO: blink with interface window about error
            }
        });

        layout->addWidget(clockText);
        layout->addWidget(sprintName);
        layout->addWidget(tapButton);
        layout->addLayout(bottomBar);


        m_clockText = clockText;
        m_sprintName = sprintName;
        m_tapButton = tapButton;
        m_progress = progress;
        m_settings = settings;
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
    p.setRenderHint(QPainter::Antialiasing);

    QPen pen = p.pen();
    QBrush brush = p.brush();

    qreal radius = 32.;
    int offset = 5;
    {
        brush.setColor(ColorScheme::valueFor(ColorRole::Background));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        p.setBrush(brush);
        p.drawRoundedRect(offset, offset, width() - offset * 2, height() - offset * 2, radius, radius);
    }

    {
        pen.setColor(ColorScheme::valueFor(ColorRole::AccentCurrent));
        pen.setWidth(4);
        p.setPen(pen);
        p.drawRoundedRect(offset, offset, width() - offset * 2, height() - offset * 2, radius, radius);
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
    auto engine = service<Engine>();
    auto sprint = engine.sprint();

    bool showNextSprint = (sprint.state == SprintState::Overtime
                           || sprint.type == SprintType::WorkdayStart);

    if (showNextSprint && engine.hasUpcomingSprint()) {
        sprint = engine.upcomingSprint();
    }

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

    // update progress (write it with fancy std algorithm like Sean Parent would do
    {
        auto ideal = service<Engine>().idealWorkday().sprints;
        auto progress = service<Engine>().nextSprintIndex();
        int current = 0;
        int maximum = 0;

        for (size_t i = 0; i < ideal.size(); ++i) {

            const Sprint& sprint = ideal[i];

            if (sprint.type == SprintType::WorkdayStart || sprint.type == SprintType::WorkdayEnd) {
                continue;
            }
            if (i < progress) {
                current += 1;
            }
            maximum += 1;
        }

        m_progress->setText(QString("%1 / %2").arg(current).arg(maximum));
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
        setLabelColor(m_settings, ColorRole::AccentCurrent);

        if (m_trayIcon) {
            auto iconColor = sprintIconColorMap()(sprint.type);
            m_trayIcon->setIcon(IconGenerator::generate(iconColor));
        }
    }



    update(); // we want to trigger a paintEvent to color background and outline
}


