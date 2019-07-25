#include "permplot.h"
#include "ui_permplot.h"

#include <QApplication>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QtDebug>
#include <iostream>
#include <cmath>
#include <QWidget>
#include <QPen>
#include <QRgb>

PermPlot::PermPlot(QWidget *parent) :   //Define permittivity plot custom Widget class
    QWidget(parent),
    m_ui(new Ui_PermPlotForm)
{
    m_ui->setupUi(this);                //Setup UI
    populateMatBox();                   //Add materials to dropdown box

    updateUI();                         //Update UI when user makes changes
};

PermPlot::~PermPlot()
{
    delete m_ui;
}

void PermPlot::populateMatBox()         //Add items to materials combobox
{
    m_ui->matComboBox->addItem("Ag");
    m_ui->matComboBox->addItem("Al");
    m_ui->matComboBox->addItem("Au");
    m_ui->matComboBox->addItem("Cu");
    m_ui->matComboBox->addItem("Pd");
    m_ui->matComboBox->addItem("Rh");
    m_ui->matComboBox->addItem("Mo");
    m_ui->matComboBox->addItem("Ni");
    m_ui->matComboBox->addItem("W");
    m_ui->matComboBox->addItem("Ti");
    m_ui->matComboBox->addItem("NbN");
    m_ui->matComboBox->addItem("TiN");
    m_ui->matComboBox->addItem("TiON");
    m_ui->matComboBox->addItem("SMO");
    m_ui->matComboBox->addItem("SNO");
    m_ui->matComboBox->addItem("SRO");
    m_ui->matComboBox->addItem("CuO");
}

void PermPlot::updateUI()
{
    QString str = m_ui->matComboBox->currentText();     //Read current value of ComboBox

    QFile file("/Users/Home/Desktop/DeviceDesign/OpticalData/"+str+"_nk.txt");      //Create file object

    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);
    QVector<QString> hold;

    while(!in.atEnd()) {
        QString line = in.readAll();
        QRegExp rx("(\t|\n|\r)");
        QStringList fields = line.split(rx,QString::SkipEmptyParts);
        hold = fields.toVector();
    }

    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");

    QSplineSeries *series2 = new QSplineSeries();
    series2->setName("spline");

    QSplineSeries *series0 = new QSplineSeries();
    series0->setName("spline");
    series0->append(300,0);
    series0->append(1600,0);

    QPen pen(QRgb(000000));
    series0->setPen(pen);

    for(int i=0; i<124; i++){
        series->append(hold[3*i].toInt(),pow((hold[(3*i+1)].toDouble()),2)-pow((hold[(3*i+2)].toDouble()),2));
        series2->append(hold[3*i].toInt(),2*(hold[(3*i+1)].toDouble())*(hold[(3*i+2)].toDouble()));
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(series0);
    chart->setTitle("Real Permittivity - " + str);
    chart->createDefaultAxes();
    chart->axisY()->setRange(-120,20);

    QChart *chart2 = new QChart();
    chart2->legend()->hide();
    chart2->addSeries(series2);
    chart2->setTitle("Imginary Permittivity - " + str);
    chart2->createDefaultAxes();
    chart2->axisY()->setRange(0,50);

    QChartView *chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    m_ui->gridLayout->addWidget(chartView2, 1, 1);
    m_ui->gridLayout->addWidget(chartView, 1, 0);

}
