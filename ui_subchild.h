/********************************************************************************
** Form generated from reading UI file 'subchild.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBCHILD_H
#define UI_SUBCHILD_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SubChild
{
public:
    QGroupBox *groupBox;
    QGraphicsView *graphicsView;

    void setupUi(QWidget *SubChild)
    {
        if (SubChild->objectName().isEmpty())
            SubChild->setObjectName(QStringLiteral("SubChild"));
        SubChild->resize(385, 380);
        SubChild->setMinimumSize(QSize(80, 80));
        SubChild->setBaseSize(QSize(400, 400));
        SubChild->setFocusPolicy(Qt::StrongFocus);
        SubChild->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        groupBox = new QGroupBox(SubChild);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 361, 361));
        groupBox->setAlignment(Qt::AlignCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        groupBox->setChecked(false);
        graphicsView = new QGraphicsView(groupBox);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 20, 341, 331));
        graphicsView->setFocusPolicy(Qt::NoFocus);
        graphicsView->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        graphicsView->setRenderHints(QPainter::HighQualityAntialiasing);
        graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
        graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);
        graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
        graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemShape);
        graphicsView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);

        retranslateUi(SubChild);

        QMetaObject::connectSlotsByName(SubChild);
    } // setupUi

    void retranslateUi(QWidget *SubChild)
    {
        SubChild->setWindowTitle(QApplication::translate("SubChild", "SubChild", 0));
        groupBox->setTitle(QApplication::translate("SubChild", "GroupBox", 0));
    } // retranslateUi

};

namespace Ui {
    class SubChild: public Ui_SubChild {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBCHILD_H
