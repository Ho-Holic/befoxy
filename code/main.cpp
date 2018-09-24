#include "visual/Befoxy.hpp"
#include <QApplication>
#include <QStandardPaths>
#include <core/Services.hpp>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QString path = QStandardPaths::locate(QStandardPaths::DesktopLocation, "befoxy_data.json");

  services().dataStorage().setStoragePath(path);
  services().dataStorage().deserialize();
  services().engine().init(services().dataStorage().idealWorkday());

  Befoxy w;
  w.resize(320, 320);
  w.show();

  return a.exec();
}
