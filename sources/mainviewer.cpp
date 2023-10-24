#include "headers/mainviewer.h"

#include "headers/parser.h"
#include "ui_mainviewer.h"
#include "ui_settings.h"

MainViewer::MainViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainViewer) {
  ui->setupUi(this);
  this->setWindowTitle("3DViewer v1.0");
  settings = new Settings();
  init_obj(&objMain, 1, 1);
  get_settings();
  connect(settings->ui->apply_button, SIGNAL(clicked()), this,
          SLOT(settings_handler()));
  connect(settings->ui->default_button, SIGNAL(clicked()), this,
          SLOT(settings_handler()));
}

MainViewer::~MainViewer() { delete ui; }

void MainViewer::get_settings() {
  ui->glWindow->bg_color_r = settings->ui->bg_color_r->value();
  ui->glWindow->bg_color_g = settings->ui->bg_color_g->value();
  ui->glWindow->bg_color_b = settings->ui->bg_color_b->value();
  ui->glWindow->vertex_r = settings->ui->vertex_color_r->value();
  ui->glWindow->vertex_g = settings->ui->vertex_color_g->value();
  ui->glWindow->vertex_b = settings->ui->vertex_color_b->value();
  ui->glWindow->edge_r = settings->ui->edge_color_r->value();
  ui->glWindow->edge_g = settings->ui->edge_color_g->value();
  ui->glWindow->edge_b = settings->ui->edge_color_b->value();
  ui->glWindow->vertex_size = settings->ui->vertex_size->value();
  ui->glWindow->edge_width = settings->ui->edge_width->value();
  ui->glWindow->vertex_shape = settings->ui->vertex_shape->currentIndex();
  ui->glWindow->edge_type = settings->ui->edge_type->currentIndex();
  ui->glWindow->grid_status = settings->ui->grid_on->isChecked() ? 1 : 0;
  ui->glWindow->proj_type = settings->ui->projection_type->currentIndex();
  ui->glWindow->update();
}

void MainViewer::settings_handler() { get_settings(); }

void MainViewer::closeEvent(QCloseEvent *event) {
  if (event) delete settings;
}

void MainViewer::moveEvent(QMoveEvent *e) {
  if (e) {
    QPoint p = MainViewer::pos();
    settings->move(p.x() - 200, p.y() + 0);
  }
}

void MainViewer::init_ui() {
  ui->spin_move_x->setValue(0);
  ui->spin_move_y->setValue(0);
  ui->spin_move_z->setValue(0);
  ui->spin_rotation_x->setValue(0);
  ui->spin_rotation_y->setValue(0);
  ui->spin_rotation_z->setValue(0);
  ui->spin_scale->setValue(0);
  ui->slider_move_x->setValue(0);
  ui->slider_move_y->setValue(0);
  ui->slider_move_z->setValue(0);
  ui->slider_rotation_x->setValue(0);
  ui->slider_rotation_y->setValue(0);
  ui->slider_rotation_z->setValue(0);
  ui->slider_scale->setValue(0);
}

void MainViewer::on_slider_move_x_valueChanged(int value) {
  if (ui->spin_move_x->value() != value) {
    move_x(&objMain, (ui->spin_move_x->value() - value) / -100.0);
    ui->spin_move_x->setValue(value);
  }
  if (value == 0) {
    ui->slider_move_x->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_move_y_valueChanged(int value) {
  if (ui->spin_move_y->value() != value) {
    move_y(&objMain, (ui->spin_move_y->value() - value) / -100.0);
    ui->spin_move_y->setValue(value);
  }
  if (value == 0) {
    ui->slider_move_y->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_move_z_valueChanged(int value) {
  if (ui->spin_move_z->value() != value) {
    move_z(&objMain, (ui->spin_move_z->value() - value) / -100.0);
    ui->spin_move_z->setValue(value);
  }
  if (value == 0) {
    ui->slider_move_z->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_rotation_x_valueChanged(int value) {
  if (ui->spin_rotation_x->value() != value) {
    rotate_x(&objMain, (ui->spin_rotation_x->value() - value) / -100.0);
    ui->spin_rotation_x->setValue(value);
  }
  if (value == 0) {
    ui->slider_rotation_x->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_rotation_y_valueChanged(int value) {
  if (ui->spin_rotation_y->value() != value) {
    rotate_y(&objMain, (ui->spin_rotation_y->value() - value) / -100.0);
    ui->spin_rotation_y->setValue(value);
  }
  if (value == 0) {
    ui->slider_rotation_y->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_rotation_z_valueChanged(int value) {
  if (ui->spin_rotation_z->value() != value) {
    rotate_z(&objMain, (ui->spin_rotation_z->value() - value) / -100.0);
    ui->spin_rotation_z->setValue(value);
  }
  if (value == 0) {
    ui->slider_rotation_z->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_scale_valueChanged(int value) {
  if (ui->spin_scale->value() != value && ui->spin_scale->value() < value) {
    ui->spin_scale->setValue(value);
    scale(&objMain, 1.1);
  }
  if (ui->spin_scale->value() != value && ui->spin_scale->value() > value) {
    ui->spin_scale->setValue(value);
    scale(&objMain, 0.9);
  }
  if (value == 0) {
    ui->slider_scale->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_load_file_button_clicked() {
  QString path = QFileDialog::getOpenFileName(this, ("Open .obj file"),
                                              QDir::currentPath(), "*.obj");
  if (objMain.edge_count > 1 && path.length() != 0) {
    init_obj(&objMain, 1, 1);
  }
  int error_code = open_file(qPrintable(path), &objMain);
  if (error_code != OK && path.length() > 0) {
    ui->label_file->setText("Incorrect File");
    QLocale locale = QLocale();
    ui->label_file->setText(QVariant(error_code).toString());
  } else if (path.length() > 0) {
    qsizetype idx = path.lastIndexOf('/') + 1;
    QString file_name = path.right(path.size() - idx);
    ui->label_file->setText(file_name);
    ui->count_vertices->setText(QString::number(objMain.vertex_count));
    ui->count_edges->setText(QString::number(objMain.edge_count));
    ui->glWindow->obj = &objMain;
    ui->glWindow->project = true;
    init_ui();
  }
}

void MainViewer::on_settings_button_clicked() {
  QPoint p = MainViewer::pos();
  settings->move(p.x() - 200, p.y() + 0);
  settings->show();
}

void MainViewer::on_translate_button_clicked() {
  if (ui->slider_move_x->value() != ui->spin_move_x->value()) {
    move_x(&objMain,
           (ui->spin_move_x->value() - ui->slider_move_x->value()) / 100.0);
    ui->slider_move_x->setValue(ui->spin_move_x->value());
  }

  if (ui->slider_move_y->value() != ui->spin_move_y->value()) {
    move_y(&objMain,
           (ui->spin_move_y->value() - ui->slider_move_y->value()) / 100.0);
    ui->slider_move_y->setValue(ui->spin_move_y->value());
  }

  if (ui->slider_move_z->value() != ui->spin_move_z->value()) {
    move_z(&objMain,
           (ui->spin_move_z->value() - ui->slider_move_z->value()) / 100.0);
    ui->slider_move_z->setValue(ui->spin_move_z->value());
  }

  ui->glWindow->update();
}

void MainViewer::on_rotate_button_clicked() {
  if (ui->slider_rotation_x->value() != ui->spin_rotation_x->value()) {
    rotate_x(&objMain,
             (ui->spin_rotation_x->value() - ui->slider_rotation_x->value()) /
                 100.0);
    ui->slider_rotation_x->setValue(ui->spin_rotation_x->value());
  }

  if (ui->slider_rotation_y->value() != ui->spin_rotation_y->value()) {
    rotate_y(&objMain,
             (ui->spin_rotation_y->value() - ui->slider_rotation_y->value()) /
                 100.0);
    ui->slider_rotation_y->setValue(ui->spin_rotation_y->value());
  }

  if (ui->slider_rotation_z->value() != ui->spin_rotation_z->value()) {
    rotate_z(&objMain,
             (ui->spin_rotation_z->value() - ui->slider_rotation_z->value()) /
                 100.0);
    ui->slider_rotation_z->setValue(ui->spin_rotation_z->value());
  }
  /*
  ui->slider_rotation_y->setSliderPosition(ui->spin_rotation_y->value());
  rotate_y(&objMain, ui->spin_rotation_y->value() / 100.0);

  ui->slider_rotation_z->setSliderPosition(ui->spin_rotation_z->value());
  rotate_z(&objMain, ui->spin_rotation_z->value() / 100.0);
*/
  ui->glWindow->update();
}

void MainViewer::on_scale_button_clicked() {
  ui->slider_scale->setSliderPosition(ui->spin_scale->value());
  if (ui->spin_scale->value() > 0)
    scale(&objMain, 1.1 * ui->spin_scale->value());
  if (ui->spin_scale->value() < 0)
    scale(&objMain, -0.9 / ui->spin_scale->value());
  ui->glWindow->update();
}

void MainViewer::on_screenshot_button_clicked() {
  QString savePath = NULL;
  savePath = QFileDialog::getSaveFileName(this, NULL, NULL,
                                          "JPEG (*.jpeg) ;; BMP (*.bmp)");
  if (!savePath.isNull())
    ui->glWindow->grabFramebuffer().save(savePath, NULL, 100);
}

void MainViewer::saveGifFrame() {
  time++;
  *frame = ui->glWindow->grabFramebuffer();
  gif->addFrame(*frame);
  if (time == 60) {
    timer->stop();
    gifSavePath = NULL;
    gifSavePath = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!gifSavePath.isNull()) gif->save(gifSavePath);
  }
}

void MainViewer::on_gif_button_clicked() {
  gif = new QGifImage(QSize(640, 480));
  gif->setDefaultDelay(100);
  frame = new QImage;
  timer = new QTimer(this);
  time = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
  timer->start(100);
}
