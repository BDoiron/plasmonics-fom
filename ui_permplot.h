#ifndef UI_PERMPLOT_H
#define UI_PERMPLOT_H


#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class Ui_PermPlotForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *matLabel;
    QComboBox *matComboBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *PermPlotForm)
    {
        if (PermPlotForm->objectName().isEmpty())
            PermPlotForm->setObjectName(QString::fromUtf8("PermPlotForm"));
        PermPlotForm->resize(900, 600);

        gridLayout = new QGridLayout(PermPlotForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        matLabel = new QLabel(PermPlotForm);
        matLabel->setObjectName(QString::fromUtf8("matLabel"));
        horizontalLayout->addWidget(matLabel);
        matComboBox = new QComboBox(PermPlotForm);
        matComboBox->setObjectName(QString::fromUtf8("matComboBox"));
        horizontalLayout->addWidget(matComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);
        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);
        retranslateUi(PermPlotForm);

        QObject::connect(matComboBox, SIGNAL(currentIndexChanged(int)), PermPlotForm, SLOT(updateUI()));
        QMetaObject::connectSlotsByName(PermPlotForm);
    } // setupUi

    void retranslateUi(QWidget *PermPlotForm)
    {
        matLabel->setText(QApplication::translate("PermPlotForm", "Material:", nullptr));
        Q_UNUSED(PermPlotForm);
    } // retranslateUi
};
namespace Ui {
    class PermPlotForm: public Ui_PermPlotForm {};
} // namespace Ui
QT_END_NAMESPACE


#endif // UI_PERMPLOT_H


