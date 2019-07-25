#ifndef MIEPLOT_H
#define MIEPLOT_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <complex>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_MiePlotForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

class MiePlot: public QWidget
{
    Q_OBJECT
public:
    explicit MiePlot(QWidget *parent = 0);
    ~MiePlot();

private Q_SLOTS:
    void updateUI();

private:
    void populateMatBox();
    void populatePlotBox();
    double mieCalculator(double, double, double, double, double, int);
    std::complex <double> sph_Bessel(int,std::complex<double>);
    std::complex <double> sph_Hankel(int,std::complex<double>);
    QChart *createSplineChart() const;

private:
    //int m_listCount;
    //int m_valueMax;
    //int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;

    Ui_MiePlotForm *m_ui;
};


#endif // MIEPLOT_H
