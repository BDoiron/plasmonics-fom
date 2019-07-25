#include "permplot.h"
#include "mieplot.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QTabWidget>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow w;
    QTabWidget *tabs = new QTabWidget();
    tabs->insertTab(0, new PermPlot(), "Permittivity Plot");
    tabs->insertTab(1, new MiePlot(), "Mie Theory");
    w.setCentralWidget(tabs);
    w.resize(900, 600);
    w.show();
    return a.exec();
}


