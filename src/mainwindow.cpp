#include <iostream>
#include <string>
#include <QTimer>
#include <ui_mainwindow.h>

#include "include/mainwindow.h"

data appData;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
  ui->setupUi(this);


  QTimer *killTimer = new QTimer(ui->killPushButton);
  killTimer->setInterval(100);
  connect(killTimer, &QTimer::timeout, this, kill);

  connect(ui->killPushButton, &QPushButton::toggled, killTimer,
         [killTimer] (bool checked) {
      if (checked) killTimer->start();
      else killTimer->stop();
  });
  setUp();

}


MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::setUp() {
  setUpComboBox();
  setUpCoords();
}

void MainWindow::setUpComboBox() {
  for (sentence sentence_pack : appData.sentences) {
    QString sentence_pack_name = QString::fromStdString(sentence_pack.name);
    ui->sentence_selector_combobox->addItem(sentence_pack_name);
  }
}

void MainWindow::setUpCoords() {
  ui->originXSpinBox->setValue(appData.origin.x);
  ui->originYSpinBox->setValue(appData.origin.y);
  ui->displayXSpinBox->setValue(appData.display.x);
  ui->displayYSpinBox->setValue(appData.display.y);
  ui->crossXSpinBox->setValue(appData.rejoinCross.x);
  ui->crossYSpinBox->setValue(appData.rejoinCross.y);
  ui->tb1XSpinBox->setValue(appData.rejoinBox1.x);
  ui->tb1YSpinBox->setValue(appData.rejoinBox1.y);
  ui->tb2XSpinBox->setValue(appData.rejoinBox2.x);
  ui->tb2YSpinBox->setValue(appData.rejoinBox2.y);
  ui->arrowXSpinBox->setValue(appData.rejoinArrow.x);
  ui->arrowYSpinBox->setValue(appData.rejoinArrow.y);
}

void MainWindow::setUpThreads() {

}

void MainWindow::on_align_button_clicked() {
  doTask(appData, ALIGN);
}


void MainWindow::on_distributor_button_clicked() {
  doTask(appData, DISTRIBUTOR);
}


void MainWindow::on_course_button_clicked() {
  doTask(appData, COURSE);
}


void MainWindow::on_filter_button_clicked() {
  doTask(appData, FILTER);
}


void MainWindow::on_vent_button_clicked() {
  doTask(appData, VENT);
}


void MainWindow::on_asteroids_button_clicked() {
  doTask(appData, ASTEROIDS);
}


void MainWindow::on_divert1_button_clicked() {
  doTask(appData, DIVERT);
}


void MainWindow::on_divert2_button_clicked() {
  doTask(appData, CENTER);
}


void MainWindow::on_download_button_clicked() {
  doTask(appData, DOWNLOAD);
}


void MainWindow::on_trash_button_clicked() {
  doTask(appData, TRASH);
}


void MainWindow::on_wires_button_clicked() {
  doTask(appData, WIRES);
}


void MainWindow::on_fuel_button_clicked() {
  doTask(appData, FUEL);
}


void MainWindow::on_sample_button_clicked() {
  doTask(appData, SAMPLE);
}


void MainWindow::on_shields_button_clicked() {
   doTask(appData, SHIELDS);
}


void MainWindow::on_reactor_button_clicked() {
 doTask(appData, REACTOR);
}


void MainWindow::on_scan_button_clicked() {
 doTask(appData, SCAN);
}


void MainWindow::on_manifolds_button_clicked() {
  doTask(appData, MANIFOLDS);
}


void MainWindow::on_stabilize_button_clicked() {
  doTask(appData, STABILIZE);
}


void MainWindow::on_swipe_button_clicked() {
  doTask(appData, CARD);
}


void MainWindow::on_send_button_clicked() {
  QString text = ui->text_to_send_textEdit->toPlainText();
  //QStringList strList = text.split(QRegExp("[\n]"), QString::SkipEmptyParts);
  Qt::SplitBehavior behavior = Qt::SkipEmptyParts;
  QStringList strList = text.split("\n", behavior);
  std::vector<std::string> sentences = {};
  for (QString sentence : strList) {
      sentences.push_back(sentence.toStdString());
  }
  sendText(sentences);
}


void MainWindow::on_joinButton_clicked() {
  appData.code = ui->joinLineEdit->text().toStdString();
}


void MainWindow::on_joinButton_toggled(bool checked) {
  appData.code = ui->joinLineEdit->text().toStdString();
  if (checked) {
      joinLobby(appData);
  }
}


void MainWindow::on_detect_button_clicked() {
  detectTask(appData);
}

