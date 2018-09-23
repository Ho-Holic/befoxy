#ifndef BEFOXY_VISUAL_BEFOXY_HPP
#define BEFOXY_VISUAL_BEFOXY_HPP

#include <QWidget>

class QLabel;

class Befoxy : public QWidget
{
    Q_OBJECT
public:
    Befoxy(QWidget* parent = nullptr);
private slots:
    void updateVisual();
private:
    QLabel* m_clockText;
    QLabel* m_sprintName;
};

#endif // BEFOXY_VISUAL_BEFOXY_HPP
