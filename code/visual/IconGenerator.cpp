#include "IconGenerator.hpp"

#include <QIcon>
#include <QPainter>
#include <QPixmap>

QIcon IconGenerator::generate(const QColor& color)
{
    QSize iconSize(32, 32);
    QSize radius(18, 18);

    QPixmap pix(iconSize);
    pix.fill(Qt::transparent);
    {
        QPainter p(&pix);
        p.setBrush(color);
        p.setPen(color);
        QSize position = iconSize / 2 - radius / 2;
        p.drawEllipse(position.width(), position.height(), radius.width(), radius.height());
    }
    return QIcon(pix);
}
