#include <QApplication>

#include "headers/mainviewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainViewer w;

  w.show();
  return a.exec();
}
