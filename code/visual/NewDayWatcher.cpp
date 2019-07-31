#include "NewDayWatcher.hpp"
#include <QTimer>
#include <core/DataStorage.hpp>
#include <core/Services.hpp>

NewDayWatcher::NewDayWatcher(QObject* parent)
:   QObject(parent)
{
    //
    // TODO: design good new day watcher
    //
    QTimer* timer = new QTimer(this);
    timer->setInterval(1000 * 60); // check every minute
    timer->setSingleShot(false);

    connect(timer, SIGNAL(timeout()), this, SLOT(checkForNewDay()));
    timer->start();

}

void NewDayWatcher::checkForNewDay()
{
    service<DataStorage>().loadEngine();
}
