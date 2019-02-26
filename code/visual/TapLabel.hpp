#ifndef BEFOXY_VISUAL_TAPLABEL_HPP
#define BEFOXY_VISUAL_TAPLABEL_HPP

#include <QLabel>

class TapLabel : public QLabel
{
    Q_OBJECT
public:
    TapLabel(const QString& text, QWidget* parent = nullptr);
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
};

#endif // BEFOXY_VISUAL_TAPLABEL_HPP
