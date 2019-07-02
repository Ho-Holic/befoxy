#ifndef BEFOXY_CORE_COLORSCHEME_HPP
#define BEFOXY_CORE_COLORSCHEME_HPP

#include <QMap>
#include <QColor>

enum class ColorRole
{
    Background,
    NeutralText,
    AccentCurrent,
    AccentWork,
    AccentRest,

    // TODO: make meaningfull accent system

    //    AccentBackgroundCurrent,
    //    AccentBackgroundWork,
    //    AccentBackgroundRest,
    //    AccentTextCurrent,
    //    AccentTextWork,
    //    AccentTextRest,
};

enum class ColorAccent
{
    Neutral,
    Work,
    Rest,
};

class ColorScheme
{
public:
    using Profile = QMap<ColorRole, QColor>;
public:
    static QColor valueFor(ColorRole role);
    static void changeAccent(ColorRole role);
private:
    static ColorScheme& instance();
private:
    ColorScheme();    
    Profile& profile();
private:
    Profile m_dayColors;
    Profile m_nightColors;
    ColorRole m_currentAccent;
};

#endif // BEFOXY_CORE_COLORSCHEME_HPP
