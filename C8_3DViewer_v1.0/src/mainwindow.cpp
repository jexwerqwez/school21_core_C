#include "mainwindow.h"

#include <Qt3DRender/QRenderCapture>

#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      re_settings("School 21", "3DViewer") {
  settingsButton = new QPushButton("Settings", this);

  ui->setupUi(this);
  parentWin = new Qt3DCore::QEntity();  // конктруктор корневого окна
  parentWin->setObjectName("Root window");
  view = new Qt3DExtras::Qt3DWindow();  // создаем окно для отображения сцены
  view->defaultFrameGraph()->setClearColor(QRgb(0xffffff));  // стандартный фон
  view->setRootEntity(parentWin);  // устанавливаем корневое окно
  widget = QWidget::createWindowContainer(
      view);  // встраивание виджета view в окно приложения
  widget->setMinimumSize(QSize(100, 100));
  QSize screenSize = view->screen()->size();  // получение размера окна
  widget->setMaximumSize(screenSize);  // и установка его как максимального
  widget->setFocusPolicy(Qt::NoFocus);
  QPushButton *button = new QPushButton("Choose file", this);
  QLineEdit *lineEdit = new QLineEdit(this);

  layout = new QVBoxLayout();  // добавление виджета, кнопки и
                               // текстового поля в лейаут
  layout->addWidget(widget);
  layout->addWidget(button);
  layout->addWidget(lineEdit);
  this->centralWidget()->setLayout(
      layout);  // установка его в качестве центрального виджета

  cameraObj = view->camera();  // создаем объект камеры
  cameraObj->lens()->setPerspectiveProjection(
      45.0f, 16.0f / 9.0f, 0.1f,
      10000.0f);  // устанавливаем параметры проекции камеры
  cameraObj->setPosition(
      QVector3D(0, 2, 0));  // позиция камеры в трехмерном пространстве
  cameraObj->setUpVector(QVector3D(1, 0, 0));  // вектор верха камеры (x, y, z)
  cameraObj->setViewCenter(QVector3D(1, 1, 0));  // центр обзора камеры
  line_material = new Qt3DExtras::QDiffuseSpecularMaterial(parentWin);
  line_material->setAmbient(QColor(Qt::black));
  Qt3DExtras::QOrbitCameraController *cameraController =
      new Qt3DExtras::QOrbitCameraController(parentWin);
  cameraController->setCamera(cameraObj);
  cameraController->setLookSpeed(100.0f);   // Скорость вращения
  cameraController->setLinearSpeed(50.0f);  // Линейная скорость

  object = new Qt3DCore::QEntity(parentWin);
  // открытие файла и его загрузка
  open_object_file(view, lineEdit, button);
  QPushButton *saveModelButton = new QPushButton("Save model render", this);
  layout->addWidget(saveModelButton);
  connect(saveModelButton, &QPushButton::clicked, this,
          [=]() { image_render(); });
  settingsWin = new SettingsWindow(this);
}

void MainWindow::open_object_file(Qt3DExtras::Qt3DWindow *view,
                                  QLineEdit *lineEdit, QPushButton *button) {
  connect(button, &QPushButton::clicked, this, [=]() {
    QString filename = QFileDialog::getOpenFileName(this, "Open a file", "",
                                                    "Obj Files (*.obj)");
    lineEdit->setText(filename);
    if (prevModel != filename) {
      if (mesh != nullptr) {
        object->removeComponent(mesh);
        delete mesh;
      }
      prevModel = filename;
      mesh = new Qt3DRender::QMesh(parentWin);
      mesh->setSource(QUrl::fromLocalFile(filename));
      mesh->setPrimitiveType(
          Qt3DRender::QGeometryRenderer::Lines);  // Установка режима
                                                  // отображения каркаса
      settingsWin->load_settings(&re_settings, cameraObj, mesh, view, object,
                                 line_material);
      object->addComponent(mesh);
      transform = new Qt3DCore::QTransform();
      object->addComponent(transform);
      const char *charstring = qPrintable(filename);
      objInfo = start_parsing(charstring);
      settings(view);
    }
  });
}

void MainWindow::object_info(s21_object object, const char *filename) {
  QString str(filename);
  layout->removeWidget(fileLabel);
  layout->removeWidget(verticesLabel);
  layout->removeWidget(polygonsLabel);
  delete fileLabel;
  delete verticesLabel;
  delete polygonsLabel;
  fileLabel = new QLabel("File: " + str, this);
  verticesLabel = new QLabel(
      "Number of vertices: " + QString::number(object.num_of_vertices), this);
  polygonsLabel = new QLabel(
      "Number of polygons: " + QString::number(object.num_of_polygons), this);
  fileLabel->setFixedSize(QSize(1000, 20));
  verticesLabel->setFixedSize(QSize(250, 20));
  polygonsLabel->setFixedSize(QSize(250, 20));
  layout->addWidget(fileLabel);
  layout->addWidget(verticesLabel);
  layout->addWidget(polygonsLabel);
}

void MainWindow::settings(Qt3DExtras::Qt3DWindow *view) {
  layout->addWidget(settingsButton);
  connect(settingsButton, &QPushButton::clicked, this, [=]() {
    if (!settings_flag) {
      settingsWin->show();
      settingsWin->add_move_sliders(transform);
      settingsWin->add_rotate_sliders(transform);
      settingsWin->add_scale_slider(cameraObj);
      settingsWin->projection_settings(cameraObj, view);
      settingsWin->line_color_settings(object, line_material);
      settingsWin->line_type_settings(mesh);
      settingsWin->background_settings(view);
      settings_flag = true;
    } else {
      settingsWin->show();
    }
  });
}

void MainWindow::image_render() {
  QString filename;
  QScreen *screen = view->screen();
  QPixmap screenshot = screen->grabWindow(view->winId());

  if (!screenshot.isNull()) {
    filename = QFileDialog::getSaveFileName(
        this, "Save Image", "", "JPEG Files (*.jpeg *.jpg);;BMP Files (*.bmp)");
  }
  if (!filename.isEmpty()) {
    screenshot.save(filename);
  }
}

s21_object MainWindow::start_parsing(const char *filename) {
  FILE *fp;
  int num_of_vert = 0;
  s21_object object;
  if ((fp = fopen(filename, "r")) == NULL) {
    printf("Error opening file\n");
  } else {
    object.polygons = NULL;
    object.num_of_polygons = 0;
    object.num_of_vertices = 0;

    s21_vertex vertex;

    num_of_vert = parser_counter(fp, &object);
    object_parser(fp, &object, &vertex, num_of_vert);
    object_info(object, filename);
  }
  return object;
}

MainWindow::~MainWindow() {
  settingsWin->save_settings(&re_settings, cameraObj, mesh, line_material,
                             view);
  delete ui;
}
