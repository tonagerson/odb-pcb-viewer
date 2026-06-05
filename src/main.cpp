#include <string_view>
#include <string>
#include "MainWindow.h"

#include <QApplication>
#include <QStyleFactory>

int main (int argc, char *argv[])
{
  QApplication a (argc, argv);
  //a.setStyle(QStyleFactory::create("windows11"));
  MainWindow w;
  w.show ();
  return a.exec ();
}
