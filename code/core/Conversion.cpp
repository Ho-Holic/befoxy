#include "Conversion.hpp"

QString sprintTimeMap(const SprintTime& time)
{
    return QString("%1:%2:%3").arg(time.hour).arg(time.min).arg(time.sec);
}

SprintTime sprintTimeMap(const QString& time)
{

    auto splitted = time.split(":");

    Q_ASSERT(splitted.size() == 3);

    // TODO: add error handling
    auto h = splitted[0].toInt();
    auto m = splitted[1].toInt();
    auto s = splitted[2].toInt();

    return SprintTime{h, m, s};
}

QString timePointMap(const TimePoint& timePoint)
{
    return QString("%1").arg(timePoint.time_since_epoch().count());
}

TimePoint timePointMap(const QString& timePoint)
{
    static_assert (std::is_same<Clock::duration::rep, long long>::value, "Clock precision loss!");

    Clock::duration::rep ns = timePoint.toLongLong();
    TimePoint::duration duration(ns);

    return TimePoint(duration);
}

//
// TODO: Create proper storage format
//
// Current is: '+35m-15m+1h-15m'
//
// Mixed time intervals are not allowed. So you can't
// do something like '+1h35m10s-2h+35m15s' and this is not required now
//
// Possible extension is: '(+35m -10m) * 4 -1h + (+35m -10m) * 4'
//

QString sprintSchemeMap(const std::vector<Sprint>& scheme)
{
    QString result;
    for (auto sprint : scheme) {

        QString prefix;
        switch (sprint.type) {
        case SprintType::Work: prefix = "+"; break;
        case SprintType::Rest: prefix = "-"; break;
        default:;
        }

        QString suffix;
        if (sprint.time.hour > 0) {
            suffix = QString("%1h").arg(sprint.time.hour);
        } else if (sprint.time.min > 0) {
            suffix = QString("%1m").arg(sprint.time.min);
        } else if (sprint.time.sec > 0) {
            suffix = QString("%1s").arg(sprint.time.sec);
        }

        if (!prefix.isEmpty() && !suffix.isEmpty()) {
            result = result + prefix + suffix;
        }

    }
    return result;
}

std::vector<Sprint> sprintSchemeMap(const QString& scheme)
{
    std::vector<Sprint> result;

    result.push_back({ SprintType::WorkdayStart, SprintState::Normal, {0, 0, 0}, {}, {}, {} });

    QString copyScheme = scheme.simplified();
    copyScheme.replace(" ", "");

    enum class ParseState
    {
        Prefix,
        Number,
        Suffix,
    };

    ParseState state = ParseState::Prefix;
    SprintType sprintType = SprintType::Unknown;
    SprintTime sprintTime;
    QString number;

    for (QChar c : copyScheme) {

        switch (state) {
        case ParseState::Prefix: {
            if (c == "+") {
                sprintType = SprintType::Work;
            } else if (c == "-") {
                sprintType = SprintType::Rest;
            }
            state = ParseState::Number;
            break;
        }
        case ParseState::Number: {
            if (c.isDigit()) {
                number.append(c);
                break;
            }
            // [[fallthrough]]; // TODO: uncomment this in C++17
            state = ParseState::Suffix;
        }
        case ParseState::Suffix: {

            if (c == "h") {
                sprintTime.hour = number.toLongLong();
            } else if (c == "m") {
                sprintTime.min = number.toLongLong();
            } else if (c == "s") {
                sprintTime.sec = number.toLongLong();
            }

            number = ""; // clear the number buffer

            result.push_back({ sprintType,  SprintState::Normal, sprintTime, {}, {}, {} });
            state = ParseState::Prefix;
            break;
        }
        }
    }

    result.push_back({ SprintType::WorkdayEnd,  SprintState::Normal, {0, 0, 0}, {}, {}, {} });

    return result;
}
