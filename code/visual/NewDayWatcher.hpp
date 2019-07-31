#ifndef BEFOXY_VISUAL_NEWDAYWATCHER_HPP
#define BEFOXY_VISUAL_NEWDAYWATCHER_HPP

#include <QObject>
#include <QDateTime>

class NewDayWatcher : public QObject
{
    Q_OBJECT
public:
    NewDayWatcher(QObject* parent = nullptr);
private slots:
    void checkForNewDay();
signals:
    void onNewDate(const QDateTime& datetime);
};

#endif // BEFOXY_VISUAL_NEWDAYWATCHER_HPP
