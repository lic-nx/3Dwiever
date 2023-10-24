#include "../headers/settings.h"

#include "ui_settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent), ui(new Ui::Settings) {
  ui->setupUi(this);
  config_file = QDir::homePath() + "/settings.conf";
  settings = new QSettings(config_file, QSettings::IniFormat);
  load_settings();
  ui->vertex_color_r->setSuffix(" R");
  ui->vertex_color_g->setSuffix(" G");
  ui->vertex_color_b->setSuffix(" B");
  ui->edge_color_r->setSuffix(" R");
  ui->edge_color_g->setSuffix(" G");
  ui->edge_color_b->setSuffix(" B");
  ui->bg_color_r->setSuffix(" R");
  ui->bg_color_g->setSuffix(" G");
  ui->bg_color_b->setSuffix(" B");
}

Settings::~Settings() {
  save_settings();
  delete ui;
}

void Settings::load_settings() {
  ui->vertex_color_r->setValue(settings->value("vertex_color_r", 150).toInt());
  ui->vertex_color_g->setValue(settings->value("vertex_color_g", 170).toInt());
  ui->vertex_color_b->setValue(settings->value("vertex_color_b", 200).toInt());
  ui->vertex_size->setValue(settings->value("vertex_size", 1).toInt());
  ui->vertex_shape->setCurrentIndex(settings->value("vertex_shape", 0).toInt());
  ui->edge_color_r->setValue(settings->value("edge_color_r", 150).toInt());
  ui->edge_color_g->setValue(settings->value("edge_color_g", 170).toInt());
  ui->edge_color_b->setValue(settings->value("edge_color_b", 200).toInt());
  ui->edge_width->setValue(settings->value("edge_width", 1).toInt());
  ui->edge_type->setCurrentIndex(settings->value("edge_type", 1).toInt());
  ui->bg_color_r->setValue(settings->value("bg_color_r", 30).toInt());
  ui->bg_color_g->setValue(settings->value("bg_color_g", 30).toInt());
  ui->bg_color_b->setValue(settings->value("bg_color_b", 30).toInt());
  ui->projection_type->setCurrentIndex(
      settings->value("projection_type", 1).toInt());
  ui->grid_off->setChecked(true);
}

void Settings::save_settings() {
  settings->setValue("vertex_color_r",
                     QVariant::fromValue(ui->vertex_color_r->value()));
  settings->setValue("vertex_color_g",
                     QVariant::fromValue(ui->vertex_color_g->value()));
  settings->setValue("vertex_color_b",
                     QVariant::fromValue(ui->vertex_color_b->value()));
  settings->setValue("vertex_size",
                     QVariant::fromValue(ui->vertex_size->value()));
  settings->setValue("vertex_shape",
                     QVariant::fromValue(ui->vertex_shape->currentIndex()));
  settings->setValue("edge_color_r",
                     QVariant::fromValue(ui->edge_color_r->value()));
  settings->setValue("edge_color_g",
                     QVariant::fromValue(ui->edge_color_g->value()));
  settings->setValue("edge_color_b",
                     QVariant::fromValue(ui->edge_color_b->value()));
  settings->setValue("edge_width",
                     QVariant::fromValue(ui->edge_width->value()));
  settings->setValue("edge_type",
                     QVariant::fromValue(ui->edge_type->currentIndex()));
  settings->setValue("bg_color_r",
                     QVariant::fromValue(ui->bg_color_r->value()));
  settings->setValue("bg_color_g",
                     QVariant::fromValue(ui->bg_color_g->value()));
  settings->setValue("bg_color_b",
                     QVariant::fromValue(ui->bg_color_b->value()));
  settings->setValue("projection_type",
                     QVariant::fromValue(ui->projection_type->currentIndex()));
}

void Settings::set_default_settings() {
  settings->setValue("vertex_color_r", QVariant::fromValue(150));
  settings->setValue("vertex_color_g", QVariant::fromValue(170));
  settings->setValue("vertex_color_b", QVariant::fromValue(200));
  settings->setValue("vertex_size", QVariant::fromValue(1));
  settings->setValue("vertex_shape", QVariant::fromValue(0));
  settings->setValue("edge_color_r", QVariant::fromValue(150));
  settings->setValue("edge_color_g", QVariant::fromValue(170));
  settings->setValue("edge_color_b", QVariant::fromValue(200));
  settings->setValue("edge_width", QVariant::fromValue(1));
  settings->setValue("edge_type", QVariant::fromValue(1));
  settings->setValue("bg_color_r", QVariant::fromValue(30));
  settings->setValue("bg_color_g", QVariant::fromValue(30));
  settings->setValue("bg_color_b", QVariant::fromValue(30));
  settings->setValue("projection_type", QVariant::fromValue(1));
}

void Settings::on_vertex_size_decr_button_clicked() {
  if (ui->vertex_size->value() > 1) {
    ui->vertex_size->setValue(ui->vertex_size->value() - 1);
  }
}

void Settings::on_vertex_size_incr_button_clicked() {
  if (ui->vertex_size->value() < 10) {
    ui->vertex_size->setValue(ui->vertex_size->value() + 1);
  }
}

void Settings::on_edge_width_decr_button_clicked() {
  if (ui->edge_width->value() > 1) {
    ui->edge_width->setValue(ui->edge_width->value() - 1);
  }
}

void Settings::on_edge_width_incr_button_clicked() {
  if (ui->edge_width->value() < 10) {
    ui->edge_width->setValue(ui->edge_width->value() + 1);
  }
}

void Settings::on_cancel_button_clicked() { hide(); }

void Settings::on_default_button_clicked() {
  set_default_settings();
  load_settings();
}

void Settings::on_apply_button_clicked() { save_settings(); }
