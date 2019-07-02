#include "ColorScheme.hpp"

QColor ColorScheme::valueFor(ColorRole role)
{
    if (role == ColorRole::AccentCurrent) {
        return instance().profile().value(instance().m_currentAccent, QColor(Qt::magenta));
    }

    return instance().profile().value(role, QColor(Qt::magenta));
}

void ColorScheme::changeAccent(ColorRole role)
{
    instance().m_currentAccent = role;
}

ColorScheme::ColorScheme()
{
    m_dayColors = {
        { ColorRole::Background, QColor("#cbe8f6") },
        { ColorRole::NeutralText, QColor("#30b6eb") },
        { ColorRole::AccentCurrent, QColor("#30b6eb") },
        { ColorRole::AccentWork, QColor("#d8455c") },
        { ColorRole::AccentRest, QColor("#7ad97c") },
    };

    m_nightColors = {
        { ColorRole::Background, QColor("#0f1421") },
        { ColorRole::NeutralText, QColor("#0080c9") },
        { ColorRole::AccentCurrent, QColor("#0080c9") },
        { ColorRole::AccentWork, QColor("#d24b3d") },
        { ColorRole::AccentRest, QColor("#93dc6f") },
    };

    m_currentAccent = ColorRole::NeutralText;
}

ColorScheme::Profile& ColorScheme::profile()
{
    return m_dayColors;
}

ColorScheme& ColorScheme::instance()
{
    static ColorScheme s_scheme;
    return s_scheme;
}
