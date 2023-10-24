#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDir>
#include <QSettings>
#include <QWidget>

namespace Ui {
class Settings;
}  // namespace Ui

class Settings : public QWidget {
  Q_OBJECT

 public:
  explicit Settings(QWidget *parent = nullptr);
  ~Settings();
  Ui::Settings *ui;
  QSettings *settings;

 public slots:
  void on_apply_button_clicked();

 private slots:
  void on_vertex_size_decr_button_clicked();
  void on_vertex_size_incr_button_clicked();
  void on_edge_width_decr_button_clicked();
  void on_edge_width_incr_button_clicked();
  void on_cancel_button_clicked();
  void on_default_button_clicked();
  void set_default_settings();

 private:
  QString config_file;
  void load_settings();
  void save_settings();
};

#endif  // SETTINGS_H
