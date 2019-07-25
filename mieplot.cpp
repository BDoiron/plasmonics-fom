#include "mieplot.h"
#include "ui_mieplot.h"

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

#include <complex>
#include <cmath>

#include <python2.7/Python.h>



MiePlot::MiePlot(QWidget *parent) :   //Define Mie plot custom Widget class
    QWidget(parent),
    m_ui(new Ui_MiePlotForm)
{
    m_ui->setupUi(this);                //Setup UI
    populateMatBox();//Add materials to dropdown box
    populatePlotBox();
    updateUI();                         //Update UI when user makes changes
};

MiePlot::~MiePlot()
{
    delete m_ui;
}

void MiePlot::populatePlotBox()         //Add items to materials combobox
{
    m_ui->plotComboBox->addItem("Scattering");
    m_ui->plotComboBox->addItem("Absorption");
    m_ui->plotComboBox->addItem("Extinction");
}

void MiePlot::populateMatBox()         //Add items to materials combobox
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

void MiePlot::updateUI()
{
    QString str = m_ui->matComboBox->currentText();
    QString plotstr = m_ui->plotComboBox->currentText();
    int plot = m_ui->plotComboBox->currentIndex();
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

    for(int i=0; i<124; i++){
        series->append(hold[3*i].toDouble(),mieCalculator(hold[(3*i+1)].toDouble(), hold[(3*i+2)].toDouble(), 100.0, 1.0, hold[3*i].toDouble(),plot));
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("Normalized "+plotstr+" Cross-Section");
    chart->createDefaultAxes();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    m_ui->gridLayout->addWidget(chartView, 1, 0);

}


double MiePlot::mieCalculator (double n, double k, double size, double ns, double wav, int ref)
{
    using namespace std;
    double pi = 3.14159;

    complex<double> m(n/ns,k/ns);
    double x0 = 2*pi*ns*size/wav;
    complex<double> x(2*pi*ns*size/wav,0);

    //complex<double> A=(m*m*sph_Bessel(1,m*x)*(2.0*sph_Bessel(1,x)-x*sph_Bessel(0,x))-sph_Bessel(1,x)*(2.0*sph_Bessel(1,m*x)- m*x*sph_Bessel(0,m*x)))/(m*m*sph_Bessel(1,m*x)*0.5*(sph_hankel_1(0,x0)-sph_hankel_1(2,x0)-sph_hankel_1(1,x0)/x)-sph_hankel_1(1,x0)*(2.0*sph_Bessel(1,m*x)-m*x*sph_Bessel(0,m*x)));
    //complex<double> B=(sph_Bessel(1,m*x)*(2.0*sph_bessel(1,x)-x*sph_Bessel(0,x))-sph_Bessel(1,x)*(2.0*sph_Bessel(1,m*x)- m*x*sph_Bessel(0,m*x)))/(sph_Bessel(1,m*x)*0.5*(sph_hankel_1(0,x0)-sph_hankel_1(2,x0)-sph_hankel_1(1,x0)/x)-sph_hankel_1(1,x0)*(2.0*sph_Bessel(1,m*x)-m*x*sph_Bessel(0,m*x)));

    complex<double> A(1,1);
    complex<double> B(1,1);

    if(ref==0)
    {
        return 6*(norm(A)+norm(B))/(x0*x0);
    }
    else if (ref==1)
    {
        return -6*(A.real()+B.real())/(x0*x0);
    }
    else if (ref==2)
    {
        return -6*(norm(A)+norm(B)-A.real()-B.real())/(x0*x0);
    }
    else
    {
        return 0;
    }

}

std::complex <double> sph_Bessel(int,std::complex<double>)
{
    Py_Initialize();

    from scipy import

    Py_Finalize();

}

