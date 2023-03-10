#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QInputDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    ui->label->setFrameStyle(QFrame::StyledPanel);
    ui->label->resize(width(), height());
    QPixmap pix(ui->label->size());
    QPen pen;
    pen.setWidth(2);
    pix.fill(Qt::white);
    QPainter p(&pix);
    p.setPen(pen);
    cx = pix.width()/2.0;
    cy = pix.height()/2.0;
    p.drawLine(cx, 0, cx, pix.height());
    p.drawLine(0, cy, pix.width(), cy);
    pen.setWidth(1);
    p.setPen(pen);
    int k = 0;
    QFont serifFont("Times", 8, QFont::Bold);
    p.setFont(serifFont);
    for(double i = cx; i < pix.width(); i += one, k++){
        p.drawLine(i, 0, i, pix.height());
        p.drawText(i, cy + 10, QString::number(k));
    }
    k = -1;
    for(double i = cx - one; i > 0; i -= one, k--){
        p.drawLine(i, 0, i, pix.height());
        p.drawText(i, cy + 10, QString::number(k));
    }
    k = -1;
    for(double i = cy + one; i < pix.height(); i += one, k--){
        p.drawLine(0, i, pix.width(), i);
        p.drawText(cx + 7, i, QString::number(k));
    }
    k = 1;
    for(double i = cy - one; i > 0; i -= one, k++){
        p.drawLine(0, i, pix.width(), i);
        p.drawText(cx + 7, i, QString::number(k));
    }
    pen.setColor(Qt::green);
    pen.setWidth(2);
    p.setPen(pen);

    for(auto to:added){
        p.drawLine(to.first.x()*one+cx, -to.first.y()*one+cy, to.second.x()*one+cx, -to.second.y()*one+cy);
    }
    if(haveRect){
        pen.setColor(Qt::red);
        pen.setWidth(2);
        p.setPen(pen);
        p.drawRect(QRect(QPoint(xmin*one+cx, -ymax*one+cy), QPoint(xmax*one+cx, -ymin*one+cy)));

    }
    pen.setColor(Qt::blue);
    pen.setWidth(2);
    p.setPen(pen);
    for(auto to:lines4){
        p.drawLine(to.first.first*one+cx, -to.first.second*one+cy, to.second.first*one+cx, -to.second.second*one+cy);
    }
    pen.setColor(Qt::yellow);
    pen.setWidth(3);
    p.setPen(pen);
    for(int i = 0; i < poly.size() - 1; i++){
        p.drawLine(poly[i].x()*one + cx, -poly[i].y()*one+cy, poly[i + 1].x()*one+cx, -poly[i+1].y()*one+cy);
    }

    pen.setColor(QColorConstants::Svg::brown);
    pen.setWidth(3);
    p.setPen(pen);
    for(int i = 0; i < otsecPoly.size() - 1; i++){
        p.drawLine(otsecPoly[i].x()*one + cx, -otsecPoly[i].y()*one+cy, otsecPoly[i + 1].x()*one+cx, -otsecPoly[i+1].y()*one+cy);
    }
    pen.setColor(QColorConstants::Svg::purple);
    pen.setWidth(3);
    p.setPen(pen);
    for(int i = 0; i < cuttedPoly.size() - 1; i++){
        p.drawLine(cuttedPoly[i].x()*one + cx, -cuttedPoly[i].y()*one+cy, cuttedPoly[i + 1].x()*one+cx, -cuttedPoly[i+1].y()*one+cy);
    }
    ui->label->setPixmap(pix);
}

void MainWindow::otsech(double x1, double y1, double x2, double y2){
    qDebug() << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2;
    double len = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2)*(y1 - y2));
    qDebug() << "len " << len;
    if(len < 0.05){
        qDebug() << "3";
        return;
    }
    if(x1 > x2){
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    if(x1 > xmax){
        qDebug() << "4";
        return;
    }
    if(x2 < xmin){
        qDebug() << "5";
        return;
    }
    if(std::min(y1, y2) > ymax){
        qDebug() << "6";
        return;
    }
    if(std::max(y1, y2) < ymin){
        qDebug() << "7";
        return;
    }
    if(x1 >= xmin*1.0 && x2 <= xmax*1.0 && std::min(y1, y2) >= ymin*1.0 && std::max(y1, y2) <= ymax*1.0){
        lines4.push_back({{x1, y1}, {x2, y2}});
        qDebug() << "8";
        return;
    }
    otsech(x1, y1, (x1 + x2)/2, (y1+y2)/2);
    otsech((x1 + x2)/2, (y1+y2)/2, x2, y2);
}

void MainWindow::on_actionadd_triggered()
{
    bool ok = false;
    int x1, y1, x2, y2;
    QString text;
    while(!ok){
        text = QInputDialog::getText(this, "x1", "print x1 from -10 to 10", QLineEdit::Normal, "", &ok);
    }

    ok = false;
    x1 = text.toInt();
    while(!ok){
        text = QInputDialog::getText(this, "y1", "print y1 from -10 to 10", QLineEdit::Normal, "", &ok);
    }

    ok = false;
    y1 = text.toInt();
    while(!ok){
        text = QInputDialog::getText(this, "x2", "print x2 from -10 to 10", QLineEdit::Normal, "", &ok);
    }

    ok = false;
    x2 = text.toInt();
    while(!ok){
        text = QInputDialog::getText(this, "y2", "print y2 from -10 to 10", QLineEdit::Normal, "", &ok);
    }
    y2 = text.toInt();
    added.push_back({QPoint(x1, y1), QPoint(x2, y2)});
    repaint();
}


void MainWindow::on_actionadd_Rectangle_triggered()
{
    lines4.clear();
    bool ok = false;
    int x1, y1, x2, y2;
    QString text;
    while(!ok){
        text = QInputDialog::getText(this, "xmin", "print xmin from -10 to 10", QLineEdit::Normal, "", &ok);
    }

    ok = false;
    x1 = text.toInt();
    while(!ok){
        text = QInputDialog::getText(this, "ymin", "print ymin from -10 to 10", QLineEdit::Normal, "", &ok);
    }

    ok = false;
    y1 = text.toInt();
    while(!ok){
        text = QInputDialog::getText(this, "xmax", "print xmax from -10 to 10", QLineEdit::Normal, "", &ok);
    }

    ok = false;
    x2 = text.toInt();
    while(!ok){
        text = QInputDialog::getText(this, "ymax", "print ymax from -10 to 10", QLineEdit::Normal, "", &ok);
    }
    y2 = text.toInt();
    pmin = QPoint(x1, y1);
    pmax = QPoint(x2, y2);
    xmin = x1;
    ymin = y1;
    xmax = x2;
    ymax = y2;
    haveRect = true;
    repaint();
}


void MainWindow::on_actioncut_off_triggered()
{

    lines4.clear();
    for(auto to:added){
        otsech(to.first.x(), to.first.y(), to.second.x(), to.second.y());
    }
    repaint();
}


void MainWindow::on_actionadd_polygon_triggered()
{
    poly.clear();
    bool ok = false;
    QString text;
    text = QInputDialog::getText(this, "count", "enter count of dots", QLineEdit::Normal, "", &ok);
    if(!ok)return;
    int k = text.toInt();
    if(k <= 0)return;
    while(k--){
        int x, y;
        ok = false;
        while(!ok){
            text = QInputDialog::getText(this, "x", "print x", QLineEdit::Normal, "", &ok);
        }
        x = text.toInt();
        ok = false;
        while(!ok){
            text = QInputDialog::getText(this, "y", "print y", QLineEdit::Normal, "", &ok);
        }
        y = text.toInt();
        Xmin = std::min(Xmin, x);
        Ymin = std::min(Ymin, y);
        Xmax = std::max(Xmax, x);
        Ymax = std::max(Ymax, y);
        poly.push_back(QPoint(x, y));
    }
    poly.push_back(poly[0]);
    repaint();
}


void MainWindow::on_actionpolygon_cut_off_triggered()
{
    cuttedPoly.clear();
    QVector < QPointF > fir = poly;
    fir.pop_back();
    QVector < QPointF > sec = otsecPoly;
    sec.pop_back();
    suthHodgClip(fir, sec);
}

double MainWindow::x_intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    double num = (x1*y2 - y1*x2) * (x3-x4) -
            (x1-x2) * (x3*y4 - y3*x4);
    double den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

double MainWindow::y_intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    double num = (x1*y2 - y1*x2) * (y3-y4) -
            (y1-y2) * (x3*y4 - y3*x4);
    double den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    return num/den;
}

void MainWindow::clip(QVector < QPointF >& poly_points, double x1, double y1, double x2, double y2)
{
    QVector < QPointF > new_points(20);
    int new_poly_size = 0;
    int poly_size = poly_points.size();
    for (int i = 0; i < poly_points.size(); i++)
    {
        int k = (i+1) % poly_points.size();
        double ix = poly_points[i].x(), iy = poly_points[i].y();
        double kx = poly_points[k].x(), ky = poly_points[k].y();
        double i_pos = (x2-x1) * (iy-y1) - (y2-y1) * (ix-x1);
        double k_pos = (x2-x1) * (ky-y1) - (y2-y1) * (kx-x1);

        if (i_pos < 0 && k_pos < 0)
        {
            new_points[new_poly_size].setX(kx);
            new_points[new_poly_size].setY(ky);
            new_poly_size++;
        }

        else if (i_pos >= 0 && k_pos < 0)
        {
            new_points[new_poly_size].setX(x_intersect(x1, y1, x2, y2, ix, iy, kx, ky));
            new_points[new_poly_size].setY(y_intersect(x1, y1, x2, y2, ix, iy, kx, ky));
            new_poly_size++;

            new_points[new_poly_size].setX(kx);
            new_points[new_poly_size].setY(ky);
            new_poly_size++;
        }

        else if (i_pos < 0 && k_pos >= 0)
        {
            new_points[new_poly_size].setX(x_intersect(x1,y1, x2, y2, ix, iy, kx, ky));
            new_points[new_poly_size].setY(y_intersect(x1,y1, x2, y2, ix, iy, kx, ky));
            new_poly_size++;
        }

        else
        {
            //No points are added
        }
    }
    poly_size = new_poly_size;
    poly_points.resize(new_poly_size);
    for (int i = 0; i < new_poly_size; i++)
    {
        poly_points[i].setX(new_points[i].x());
        poly_points[i].setY(new_points[i].y());
    }
}

void MainWindow::suthHodgClip(QVector < QPointF > &poly_points, QVector < QPointF >& clipper_points)
{
     int poly_size = poly_points.size();
     int clipper_size = clipper_points.size();
    for (int i=0; i < clipper_points.size(); i++)
    {
        int k = (i+1) % clipper_points.size();

        clip(poly_points, clipper_points[i].x(), clipper_points[i].y(), clipper_points[k].x(), clipper_points[k].y());
    }
    for(int i = 0; i < poly_points.size(); i++){
        qDebug() << poly_points[i];
        cuttedPoly.push_back(poly_points[i]);
    }
    cuttedPoly.push_back(cuttedPoly[0]);
}




void MainWindow::on_actionadd_cutting_polynom_triggered()
{
    otsecPoly.clear();
    bool ok = false;
    QString text;
    text = QInputDialog::getText(this, "count", "enter count of dots", QLineEdit::Normal, "", &ok);
    if(!ok)return;
    int k = text.toInt();
    if(k <= 0)return;
    while(k--){
        int x, y;
        ok = false;
        while(!ok){
            text = QInputDialog::getText(this, "x", "print x", QLineEdit::Normal, "", &ok);
        }
        x = text.toInt();
        ok = false;
        while(!ok){
            text = QInputDialog::getText(this, "y", "print y", QLineEdit::Normal, "", &ok);
        }
        y = text.toInt();
        Xmin = std::min(Xmin, x);
        Ymin = std::min(Ymin, y);
        Xmax = std::max(Xmax, x);
        Ymax = std::max(Ymax, y);
        otsecPoly.push_back(QPoint(x, y));
    }
    otsecPoly.push_back(otsecPoly[0]);
    repaint();
}


void MainWindow::on_actionclear_polygons_triggered()
{
    poly.clear();
    otsecPoly.clear();
    cuttedPoly.clear();
}

