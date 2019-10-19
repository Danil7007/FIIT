#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QMainWindow window;
  window.resize(200, 200);
  window.setWindowTitle("QT Example");
  window.show();

  QWidget wgt(&window);
  window.setCentralWidget(&wgt);
  wgt.show();

  QPushButton hello("Hello World!", &wgt);
  hello.resize(100, 30);
  hello.move(15, 15);
  hello.show();

  QLabel label("Hello Again!", &wgt);
  label.resize(100, 30);
  label.move(15, 50);
  label.show();

  QObject::connect(&hello, SIGNAL(clicked()), &a, SLOT(quit()));

  return a.exec();
}
