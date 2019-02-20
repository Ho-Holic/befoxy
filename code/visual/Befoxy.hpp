#ifndef BEFOXY_VISUAL_BEFOXY_HPP
#define BEFOXY_VISUAL_BEFOXY_HPP

#include <QWidget>
#include <QSystemTrayIcon>

class QLabel;

class Befoxy : public QWidget
{
    Q_OBJECT
public:
    Befoxy(QWidget* parent = nullptr);
private slots:
    void updateVisual();
    void trayIconActivated(QSystemTrayIcon::ActivationReason);
private:
    QLabel* m_clockText;
    QLabel* m_sprintName;
    QSystemTrayIcon* m_trayIcon = nullptr;
};

#endif // BEFOXY_VISUAL_BEFOXY_HPP
