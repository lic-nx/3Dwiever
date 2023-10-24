#ifndef MAINVIEWER_H
#define MAINVIEWER_H

#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "glview.h"
#include "qgifimage.h"
#include "settings.h"

extern "C" {
#include "headers/parser.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainViewer;
}
QT_END_NAMESPACE

class MainViewer : public QMainWindow {
  Q_OBJECT

 public:
  MainViewer(QWidget *parent = nullptr);
  ~MainViewer();
  void get_settings();

 private slots:
  void on_load_file_button_clicked();
  void on_translate_button_clicked();
  void on_rotate_button_clicked();
  void on_scale_button_clicked();
  void on_settings_button_clicked();
  void on_screenshot_button_clicked();
  void on_gif_button_clicked();
  void on_slider_move_x_valueChanged(int value);
  void on_slider_move_y_valueChanged(int value);
  void on_slider_move_z_valueChanged(int value);
  void on_slider_rotation_x_valueChanged(int value);
  void on_slider_rotation_y_valueChanged(int value);
  void on_slider_rotation_z_valueChanged(int value);
  void on_slider_scale_valueChanged(int value);
  void settings_handler();
  void saveGifFrame();

 private:
  Ui::MainViewer *ui;
  glView *gl;
  QGifImage *gif;
  QString gifSavePath;
  obj_t objMain;
  Settings *settings;
  QImage *frame;
  QTimer *timer;
  int time;
  void init_ui();
  void moveEvent(QMoveEvent *e);
  void closeEvent(QCloseEvent *event);
};

#endif  // MAINVIEWER_H
