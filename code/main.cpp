#include "visual/Befoxy.hpp"
#include <QApplication>
#include <QStandardPaths>
#include <core/Services.hpp>
#include <QDir>

#include <QDebug>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  {
      QStringList locations = QStandardPaths::standardLocations(QStandardPaths::DesktopLocation);
      //
      // TODO: make a loop trying to find already created confing inside this locations
      //
      if (!locations.empty()) {
          QString befoxyHome = locations.front()+"/befoxy/";
          QDir dir;
          if(!dir.exists(befoxyHome)) {
              dir.mkpath(befoxyHome);
          }
          services().dataStorage().setStoragePath(befoxyHome);
      }
  }

  services().dataStorage().load();  

  Befoxy w;
  w.resize(320, 320);
  w.show();

  return a.exec();
}
