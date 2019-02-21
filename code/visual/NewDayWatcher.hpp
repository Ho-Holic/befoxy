#ifndef BEFOXY_VISUAL_NEWDAYWATCHER_HPP
#define BEFOXY_VISUAL_NEWDAYWATCHER_HPP

#include <QObject>
#include <QDateTime>

class NewDayWatcher : public QObject
{
    Q_OBJECT
public:
    NewDayWatcher(QObject* parent = nullptr);
signals:
    void onNewDate(const QDateTime& datetime);
};

#endif // BEFOXY_VISUAL_NEWDAYWATCHER_HPP
