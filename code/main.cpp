#include "visual/Befoxy.hpp"
#include <QApplication>
#include <core/Services.hpp>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  services().init();

  Befoxy w;
  w.show();

  return a.exec();
}
