#ifndef BEFOXY_VISUAL_BEFOXY_HPP
#define BEFOXY_VISUAL_BEFOXY_HPP

#include <QWidget>
#include <QSystemTrayIcon>

class QLabel;
class QPaintEvent;

class Befoxy : public QWidget
{
    Q_OBJECT
public:
    Befoxy(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event);
private slots:
    void updateVisual();
    void trayIconActivated(QSystemTrayIcon::ActivationReason);
private:
    QLabel* m_clockText;
    QLabel* m_sprintName;
    QLabel* m_tapButton;
    QLabel* m_progress;
    QLabel* m_settings;
    QSystemTrayIcon* m_trayIcon = nullptr;
};

#endif // BEFOXY_VISUAL_BEFOXY_HPP
