#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "include/tasks.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  void setUp();

  void setUpComboBox();

  void setUpCoords();

  void setUpThreads();

  void on_align_button_clicked();

  void on_distributor_button_clicked();

  void on_course_button_clicked();

  void on_filter_button_clicked();

  void on_vent_button_clicked();

  void on_asteroids_button_clicked();

  void on_divert1_button_clicked();

  void on_divert2_button_clicked();

  void on_download_button_clicked();

  void on_trash_button_clicked();

  void on_wires_button_clicked();

  void on_fuel_button_clicked();

  void on_sample_button_clicked();

  void on_shields_button_clicked();

  void on_reactor_button_clicked();

  void on_scan_button_clicked();

  void on_manifolds_button_clicked();

  void on_stabilize_button_clicked();

  void on_swipe_button_clicked();

  void on_send_button_clicked();

  void on_joinButton_clicked();

  void on_joinButton_toggled(bool checked);

  void on_detect_button_clicked();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
