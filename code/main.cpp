#include "visual/Befoxy.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Befoxy w;
  w.show();

  return a.exec();
}
