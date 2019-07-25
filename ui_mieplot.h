#ifndef UI_MIEPLOT_H
#define UI_MIEPLOT_H


#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE
class Ui_MiePlotForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *matLabel;
    QComboBox *matComboBox;
    QComboBox *plotComboBox;
    QSpinBox *sizeSpinBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MiePlotForm)
    {
        if (MiePlotForm->objectName().isEmpty())
            MiePlotForm->setObjectName(QString::fromUtf8("MiePlotForm"));
        MiePlotForm->resize(900, 600);

        gridLayout = new QGridLayout(MiePlotForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        matLabel = new QLabel(MiePlotForm);
        matLabel->setObjectName(QString::fromUtf8("matLabel"));
        horizontalLayout->addWidget(matLabel);
        matComboBox = new QComboBox(MiePlotForm);
        matComboBox->setObjectName(QString::fromUtf8("matComboBox"));
        horizontalLayout->addWidget(matComboBox);
        plotComboBox = new QComboBox(MiePlotForm);
        plotComboBox->setObjectName(QString::fromUtf8("plotComboBox"));
        horizontalLayout->addWidget(plotComboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);
        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);
        retranslateUi(MiePlotForm);

        QObject::connect(matComboBox, SIGNAL(currentIndexChanged(int)), MiePlotForm, SLOT(updateUI()));
        QMetaObject::connectSlotsByName(MiePlotForm);
        QObject::connect(plotComboBox, SIGNAL(currentIndexChanged(int)), MiePlotForm, SLOT(updateUI()));
        QMetaObject::connectSlotsByName(MiePlotForm);
    } // setupUi

    void retranslateUi(QWidget *MiePlotForm)
    {
        matLabel->setText(QApplication::translate("MiePlotForm", "Material:", nullptr));
        Q_UNUSED(MiePlotForm);
    } // retranslateUi
};
namespace Ui {
    class MiePlotForm: public Ui_MiePlotForm {};
} // namespace Ui
QT_END_NAMESPACE





#endif // UI_MIEPLOT_H
