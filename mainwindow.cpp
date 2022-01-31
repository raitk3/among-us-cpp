#include <iostream>
#include <string>
#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"

data app_data;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
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


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUp()
{
    setUpComboBox();
    setUpCoords();
}

void MainWindow::setUpComboBox()
{
    for (sentence sentence_pack : app_data.sentences)
    {
        QString sentence_pack_name = QString::fromStdString(sentence_pack.name);
        ui->sentence_selector_combobox->addItem(sentence_pack_name);
    }
}

void MainWindow::setUpCoords()
{
    ui->originXSpinBox->setValue(app_data.origin.x);
    ui->originYSpinBox->setValue(app_data.origin.y);
    ui->displayXSpinBox->setValue(app_data.display.x);
    ui->displayYSpinBox->setValue(app_data.display.y);
    ui->crossXSpinBox->setValue(app_data.rejoin_cross.x);
    ui->crossYSpinBox->setValue(app_data.rejoin_cross.y);
    ui->tb1XSpinBox->setValue(app_data.rejoin_box_1.x);
    ui->tb1YSpinBox->setValue(app_data.rejoin_box_1.y);
    ui->tb2XSpinBox->setValue(app_data.rejoin_box_2.x);
    ui->tb2YSpinBox->setValue(app_data.rejoin_box_2.y);
    ui->arrowXSpinBox->setValue(app_data.rejoin_arrow.x);
    ui->arrowYSpinBox->setValue(app_data.rejoin_arrow.y);
}

void MainWindow::on_align_button_clicked()
{
    do_task(app_data, ALIGN);
}


void MainWindow::on_distributor_button_clicked()
{
    do_task(app_data, DISTRIBUTOR);
}


void MainWindow::on_course_button_clicked()
{

    do_task(app_data, COURSE);
}


void MainWindow::on_filter_button_clicked()
{
    do_task(app_data, FILTER);
}


void MainWindow::on_vent_button_clicked()
{
    do_task(app_data, VENT);
}


void MainWindow::on_asteroids_button_clicked()
{
    do_task(app_data, ASTEROIDS);
}


void MainWindow::on_divert1_button_clicked()
{
    do_task(app_data, DIVERT);
}


void MainWindow::on_divert2_button_clicked()
{
    do_task(app_data, CENTER);
}


void MainWindow::on_download_button_clicked()
{
    do_task(app_data, DOWNLOAD);
}


void MainWindow::on_trash_button_clicked()
{
    do_task(app_data, TRASH);
}


void MainWindow::on_wires_button_clicked()
{
    do_task(app_data, WIRES);
}


void MainWindow::on_fuel_button_clicked()
{
    do_task(app_data, FUEL);
}


void MainWindow::on_sample_button_clicked()
{
    do_task(app_data, SAMPLE);
}


void MainWindow::on_shields_button_clicked()
{
    do_task(app_data, SHIELDS);
}


void MainWindow::on_reactor_button_clicked()
{
    do_task(app_data, REACTOR);
}


void MainWindow::on_scan_button_clicked()
{
    do_task(app_data, SCAN);
}


void MainWindow::on_manifolds_button_clicked()
{
    do_task(app_data, MANIFOLDS);
}


void MainWindow::on_stabilize_button_clicked()
{
    do_task(app_data, STABILIZE);
}


void MainWindow::on_swipe_button_clicked()
{
    do_task(app_data, CARD);
}


void MainWindow::on_send_button_clicked()
{
    QString text = ui->text_to_send_textEdit->toPlainText();
    QStringList strList = text.split(QRegExp("[\n]"), QString::SkipEmptyParts);
    std::vector<std::string> sentences = {};
    for (QString sentence : strList) {
        sentences.push_back(sentence.toStdString());
    }
    send_text(sentences);
}


void MainWindow::on_joinButton_clicked()
{
    app_data.code = ui->joinLineEdit->text().toStdString();
}


void MainWindow::on_joinButton_toggled(bool checked)
{
    app_data.code = ui->joinLineEdit->text().toStdString();
    if (checked) {
        join_lobby(app_data);
    }
}


void MainWindow::on_detect_button_clicked()
{
    detect_task(app_data);
}

