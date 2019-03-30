#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GrahamScan.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Enable panning (translation of axes)
    ui->plot->setInteraction(QCP::iRangeDrag, true);

    // Enable zoon on scroll
    ui->plot->setInteraction(QCP::iRangeZoom, true);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsNone);

    // Add points on double click
    connect(ui->plot, SIGNAL(mouseDoubleClick(QMouseEvent*)), SLOT(clickedGraph(QMouseEvent*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
}

void MainWindow::plot()
{

    int i;
    QCPItemLine *line[qv_x.size()];
    for(i = 0; i < (qv_x.size() - 1); i++){
        line[i] = new QCPItemLine(ui->plot);
        line[i]->start->setCoords(qv_x[i], qv_y[i]);
        line[i]->end->setCoords(qv_x[i+1], qv_y[i+1]);
        ui->plot->addItem(line[i]);
    }

//    QCPItemLine *line = new QCPItemLine(ui->plot);
//    line->start->setCoords(0.0, 1.0);
//    line->end->setCoords(3.0, 0.0);
//    ui->plot->addItem(line);
//    qDebug()<<ui->plot->itemCount();

    ui->plot->graph(0)->setData(qv_x, qv_y);
    ui->plot->replot();
    ui->plot->update();

}

void MainWindow::on_btn_add_clicked()
{
    addPoint(ui->bx_x->value(), ui->bx_y->value());
    plot();
}

void MainWindow::on_btn_clear_clicked()
{
    ui->plot->clearItems();
    clearData();
    plot();
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint point = event->pos();
    addPoint(ui->plot->xAxis->pixelToCoord(point.x()), ui->plot->yAxis->pixelToCoord(point.y()));
    plot();
}

void MainWindow::on_btn_zoomFull_clicked()
{
    //Zoom to display all points comfortably
    ui->plot->xAxis->setRange(*std::min_element(qv_x.begin(), qv_x.end()) - 1.0, *std::max_element(qv_x.begin(), qv_x.end()) + 1.0);
    ui->plot->yAxis->setRange(*std::min_element(qv_y.begin(), qv_y.end()) - 1.0, *std::max_element(qv_y.begin(), qv_y.end()) + 1.0);
    plot();
}

void MainWindow::on_btn_GrahamScan_clicked()
{
    std::vector<point> points;
    for(int i = 0; i < (qv_x.size() - 1); i++){
        struct point p;
            p.x = qv_x[i];
            p.y = qv_y[i];
            points.push_back(p);
    }
    GrahamScan *obj = new GrahamScan(points);
    obj->runGrahamScan(points, this);
}
