#ifndef BEFOXY_VISUAL_ICONGENERATOR_HPP
#define BEFOXY_VISUAL_ICONGENERATOR_HPP

#include <QColor>

class QIcon;

class IconGenerator
{
public:
    static QIcon generate(const QColor& color);
};

#endif // BEFOXY_VISUAL_ICONGENERATOR_HPP
