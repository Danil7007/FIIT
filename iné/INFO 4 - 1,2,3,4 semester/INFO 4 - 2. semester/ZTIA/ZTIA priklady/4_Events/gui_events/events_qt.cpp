// Event loop and callbacks using Qt5
// http://doc.qt.io/qt-5/

#include <iostream>
#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>

class MyWindow : public QMainWindow {
  Q_OBJECT

public:
  MyWindow() : QMainWindow() {
    setWindowTitle("Qt Window");
    move(100, 100);
    setFixedSize(320, 320);
  }

protected:
  void mousePressEvent(QMouseEvent *event) {
    std::cout << "MouseEvent button=" << event->button()
              << " x=" << event->x()
              << " y=" << event->y()
              << std::endl;
  }
  void keyPressEvent(QKeyEvent *event) {
    std::cout << "KeyboardEvent key=" << event->key() << std::endl;
    if(event->key() == Qt::Key_Escape) close();
  }
};

#include "events_qt.moc"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MyWindow window;

  window.show();
  return app.exec();
}
