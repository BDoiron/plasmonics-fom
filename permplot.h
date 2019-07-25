#ifndef PERMPLOT_H
#define PERMPLOT_H

#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>

QT_BEGIN_NAMESPACE
class QComboBox;
class QCheckBox;
class Ui_PermPlotForm;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
class QChart;
QT_CHARTS_END_NAMESPACE

typedef QPair<QPointF, QString> Data;
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;

QT_CHARTS_USE_NAMESPACE

class PermPlot: public QWidget
{
    Q_OBJECT
public:
    explicit PermPlot(QWidget *parent = 0);
    ~PermPlot();

private Q_SLOTS:
    void updateUI();

private:
    void populateMatBox();
    void connectSignals();
    QChart *createSplineChart() const;

private:
    //int m_listCount;
    //int m_valueMax;
    //int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;

    Ui_PermPlotForm *m_ui;
};

#endif // PERMPLOT_H
