#ifndef BEFOXY_HPP
#define BEFOXY_HPP

#include <QWidget>

class QLabel;

class Befoxy : public QWidget
{
    Q_OBJECT
public:
    Befoxy(QWidget *parent = 0);
private slots:
    void updateVisual();
private:
    QLabel* m_clockText;
};

#endif // BEFOXY_HPP
