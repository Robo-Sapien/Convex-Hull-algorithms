#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "convex_hull_utility.h"
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addPoint(double x, double y);
    void clearData();
    void plot();
    void drawLines(std::vector<point> points);
    void clearLines();

private slots:
    void on_btn_add_clicked();

    void on_btn_clear_clicked();

    void clickedGraph(QMouseEvent *event);

    void on_btn_zoomFull_clicked();

    void on_btn_GrahamScan_clicked();

    void on_btn_KPS_clicked();

    void on_btn_JarvisMarch_clicked();

private:
    Ui::MainWindow *ui;

    QVector<double> qv_x, qv_y;
};

#endif // MAINWINDOW_H
