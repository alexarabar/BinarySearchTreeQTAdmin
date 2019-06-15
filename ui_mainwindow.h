/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_New;
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_Save_As;
    QAction *action_Commit;
    QAction *action_RollBack;
    QAction *action_Print;
    QAction *action_Exit;
    QAction *action_Normal;
    QAction *action_Red_Black;
    QAction *action_AVL;
    QAction *action_Select_All;
    QAction *action_Undo;
    QAction *action_Redo;
    QAction *action_Cut;
    QAction *action_Copy;
    QAction *action_Paste;
    QAction *action_Zoom_In;
    QAction *action_Zoom_Out;
    QAction *action_Close;
    QAction *action_Close_All;
    QAction *action_Tile;
    QAction *action_Cascade;
    QAction *action_Next;
    QAction *action_All_Windows_Docked;
    QAction *action_About;
    QAction *action_About_Qt;
    QAction *action_Split_horizontal;
    QAction *action_Split_vertical;
    QAction *action_Set_Tabified;
    QAction *action_Previous;
    QWidget *central_Widget;
    QMdiArea *mdiArea;
    QTabWidget *tabWidget;
    QWidget *widget_ghost_1;
    QWidget *widget_ghost_2;
    QMenuBar *menu_Bar;
    QMenu *menu_Tree;
    QMenu *menu_Transaction;
    QMenu *menu_Type;
    QMenu *menu_Edit;
    QMenu *menu_Zoom;
    QMenu *menu_Window;
    QMenu *menu_Help;
    QStatusBar *status_Bar;
    QToolBar *tool_Bar;
    QDockWidget *dockWidget_Input;
    QWidget *dockWidgetContents_Input;
    QLabel *label_value;
    QLineEdit *lineEdit_value;
    QPushButton *pushButton_Insert;
    QPushButton *pushButton_Delete;
    QPushButton *pushButton_Search;
    QDockWidget *dockWidget_toolButtons;
    QWidget *dockWidgetContents_toolButtons;
    QToolButton *toolButton_Normal;
    QToolButton *toolButton_AVL;
    QToolButton *toolButton_Edge;
    QToolButton *toolButton_Left_rotation;
    QToolButton *toolButton_RedBlack;
    QToolButton *toolButton_Right_rotation;
    QToolButton *toolButton_Balance;
    QToolButton *toolButton_Commit;
    QToolButton *toolButton_RollBack;
    QDockWidget *dockWidget_History;
    QWidget *dockWidgetContents_History;
    QSlider *slider_History;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(880, 480);
        MainWindow->setMinimumSize(QSize(880, 480));
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        MainWindow->setDocumentMode(false);
        MainWindow->setDockNestingEnabled(false);
        MainWindow->setDockOptions(QMainWindow::AnimatedDocks);
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QStringLiteral("action_New"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new"), QSize(), QIcon::Normal, QIcon::Off);
        action_New->setIcon(icon);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/open"), QSize(), QIcon::Normal, QIcon::Off);
        action_Open->setIcon(icon1);
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        action_Save->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/save"), QSize(), QIcon::Normal, QIcon::Off);
        action_Save->setIcon(icon2);
        action_Save_As = new QAction(MainWindow);
        action_Save_As->setObjectName(QStringLiteral("action_Save_As"));
        action_Save_As->setEnabled(false);
        action_Commit = new QAction(MainWindow);
        action_Commit->setObjectName(QStringLiteral("action_Commit"));
        action_Commit->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/commit"), QSize(), QIcon::Normal, QIcon::Off);
        action_Commit->setIcon(icon3);
        action_RollBack = new QAction(MainWindow);
        action_RollBack->setObjectName(QStringLiteral("action_RollBack"));
        action_RollBack->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/rollback"), QSize(), QIcon::Normal, QIcon::Off);
        action_RollBack->setIcon(icon4);
        action_Print = new QAction(MainWindow);
        action_Print->setObjectName(QStringLiteral("action_Print"));
        action_Print->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/print"), QSize(), QIcon::Normal, QIcon::Off);
        action_Print->setIcon(icon5);
        action_Exit = new QAction(MainWindow);
        action_Exit->setObjectName(QStringLiteral("action_Exit"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/exit"), QSize(), QIcon::Normal, QIcon::Off);
        action_Exit->setIcon(icon6);
        action_Normal = new QAction(MainWindow);
        action_Normal->setObjectName(QStringLiteral("action_Normal"));
        action_Normal->setCheckable(true);
        action_Normal->setChecked(true);
        action_Normal->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/bin"), QSize(), QIcon::Normal, QIcon::Off);
        action_Normal->setIcon(icon7);
        action_Red_Black = new QAction(MainWindow);
        action_Red_Black->setObjectName(QStringLiteral("action_Red_Black"));
        action_Red_Black->setCheckable(true);
        action_Red_Black->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/rb"), QSize(), QIcon::Normal, QIcon::Off);
        action_Red_Black->setIcon(icon8);
        action_AVL = new QAction(MainWindow);
        action_AVL->setObjectName(QStringLiteral("action_AVL"));
        action_AVL->setCheckable(true);
        action_AVL->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/avl"), QSize(), QIcon::Normal, QIcon::Off);
        action_AVL->setIcon(icon9);
        action_Select_All = new QAction(MainWindow);
        action_Select_All->setObjectName(QStringLiteral("action_Select_All"));
        action_Select_All->setEnabled(false);
        action_Undo = new QAction(MainWindow);
        action_Undo->setObjectName(QStringLiteral("action_Undo"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/undo"), QSize(), QIcon::Normal, QIcon::Off);
        action_Undo->setIcon(icon10);
        action_Undo->setVisible(false);
        action_Redo = new QAction(MainWindow);
        action_Redo->setObjectName(QStringLiteral("action_Redo"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/redo"), QSize(), QIcon::Normal, QIcon::Off);
        action_Redo->setIcon(icon11);
        action_Redo->setVisible(false);
        action_Cut = new QAction(MainWindow);
        action_Cut->setObjectName(QStringLiteral("action_Cut"));
        action_Cut->setEnabled(false);
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/cut"), QSize(), QIcon::Normal, QIcon::Off);
        action_Cut->setIcon(icon12);
        action_Copy = new QAction(MainWindow);
        action_Copy->setObjectName(QStringLiteral("action_Copy"));
        action_Copy->setEnabled(false);
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/copy"), QSize(), QIcon::Normal, QIcon::Off);
        action_Copy->setIcon(icon13);
        action_Paste = new QAction(MainWindow);
        action_Paste->setObjectName(QStringLiteral("action_Paste"));
        action_Paste->setEnabled(false);
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/paste"), QSize(), QIcon::Normal, QIcon::Off);
        action_Paste->setIcon(icon14);
        action_Zoom_In = new QAction(MainWindow);
        action_Zoom_In->setObjectName(QStringLiteral("action_Zoom_In"));
        action_Zoom_In->setEnabled(false);
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/zoomin"), QSize(), QIcon::Normal, QIcon::Off);
        action_Zoom_In->setIcon(icon15);
        action_Zoom_Out = new QAction(MainWindow);
        action_Zoom_Out->setObjectName(QStringLiteral("action_Zoom_Out"));
        action_Zoom_Out->setEnabled(false);
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/zoomout"), QSize(), QIcon::Normal, QIcon::Off);
        action_Zoom_Out->setIcon(icon16);
        action_Close = new QAction(MainWindow);
        action_Close->setObjectName(QStringLiteral("action_Close"));
        action_Close->setEnabled(false);
        action_Close_All = new QAction(MainWindow);
        action_Close_All->setObjectName(QStringLiteral("action_Close_All"));
        action_Close_All->setEnabled(false);
        action_Tile = new QAction(MainWindow);
        action_Tile->setObjectName(QStringLiteral("action_Tile"));
        action_Tile->setEnabled(false);
        action_Cascade = new QAction(MainWindow);
        action_Cascade->setObjectName(QStringLiteral("action_Cascade"));
        action_Cascade->setEnabled(false);
        action_Next = new QAction(MainWindow);
        action_Next->setObjectName(QStringLiteral("action_Next"));
        action_Next->setEnabled(false);
        action_All_Windows_Docked = new QAction(MainWindow);
        action_All_Windows_Docked->setObjectName(QStringLiteral("action_All_Windows_Docked"));
        action_All_Windows_Docked->setCheckable(true);
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QStringLiteral("action_About"));
        action_About_Qt = new QAction(MainWindow);
        action_About_Qt->setObjectName(QStringLiteral("action_About_Qt"));
        action_Split_horizontal = new QAction(MainWindow);
        action_Split_horizontal->setObjectName(QStringLiteral("action_Split_horizontal"));
        action_Split_horizontal->setEnabled(false);
        action_Split_horizontal->setVisible(false);
        action_Split_vertical = new QAction(MainWindow);
        action_Split_vertical->setObjectName(QStringLiteral("action_Split_vertical"));
        action_Split_vertical->setEnabled(false);
        action_Split_vertical->setVisible(false);
        action_Set_Tabified = new QAction(MainWindow);
        action_Set_Tabified->setObjectName(QStringLiteral("action_Set_Tabified"));
        action_Set_Tabified->setEnabled(false);
        action_Set_Tabified->setVisible(false);
        action_Previous = new QAction(MainWindow);
        action_Previous->setObjectName(QStringLiteral("action_Previous"));
        action_Previous->setEnabled(false);
        central_Widget = new QWidget(MainWindow);
        central_Widget->setObjectName(QStringLiteral("central_Widget"));
        mdiArea = new QMdiArea(central_Widget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setGeometry(QRect(1, 0, 630, 330));
        mdiArea->setFocusPolicy(Qt::WheelFocus);
        mdiArea->setFrameShape(QFrame::NoFrame);
        mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        mdiArea->setActivationOrder(QMdiArea::CreationOrder);
        tabWidget = new QTabWidget(central_Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(650, 0, 141, 141));
        tabWidget->setFocusPolicy(Qt::StrongFocus);
        tabWidget->setTabsClosable(true);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        widget_ghost_1 = new QWidget();
        widget_ghost_1->setObjectName(QStringLiteral("widget_ghost_1"));
        tabWidget->addTab(widget_ghost_1, QString());
        widget_ghost_2 = new QWidget();
        widget_ghost_2->setObjectName(QStringLiteral("widget_ghost_2"));
        tabWidget->addTab(widget_ghost_2, QString());
        MainWindow->setCentralWidget(central_Widget);
        menu_Bar = new QMenuBar(MainWindow);
        menu_Bar->setObjectName(QStringLiteral("menu_Bar"));
        menu_Bar->setGeometry(QRect(0, 0, 880, 21));
        menu_Bar->setFocusPolicy(Qt::NoFocus);
        menu_Tree = new QMenu(menu_Bar);
        menu_Tree->setObjectName(QStringLiteral("menu_Tree"));
        menu_Tree->setFocusPolicy(Qt::NoFocus);
        menu_Transaction = new QMenu(menu_Tree);
        menu_Transaction->setObjectName(QStringLiteral("menu_Transaction"));
        menu_Transaction->setEnabled(false);
        menu_Type = new QMenu(menu_Bar);
        menu_Type->setObjectName(QStringLiteral("menu_Type"));
        menu_Type->setFocusPolicy(Qt::NoFocus);
        menu_Edit = new QMenu(menu_Bar);
        menu_Edit->setObjectName(QStringLiteral("menu_Edit"));
        menu_Edit->setFocusPolicy(Qt::NoFocus);
        menu_Zoom = new QMenu(menu_Bar);
        menu_Zoom->setObjectName(QStringLiteral("menu_Zoom"));
        menu_Zoom->setFocusPolicy(Qt::NoFocus);
        menu_Window = new QMenu(menu_Bar);
        menu_Window->setObjectName(QStringLiteral("menu_Window"));
        menu_Window->setFocusPolicy(Qt::NoFocus);
        menu_Help = new QMenu(menu_Bar);
        menu_Help->setObjectName(QStringLiteral("menu_Help"));
        menu_Help->setFocusPolicy(Qt::NoFocus);
        MainWindow->setMenuBar(menu_Bar);
        status_Bar = new QStatusBar(MainWindow);
        status_Bar->setObjectName(QStringLiteral("status_Bar"));
        MainWindow->setStatusBar(status_Bar);
        tool_Bar = new QToolBar(MainWindow);
        tool_Bar->setObjectName(QStringLiteral("tool_Bar"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tool_Bar->sizePolicy().hasHeightForWidth());
        tool_Bar->setSizePolicy(sizePolicy);
        tool_Bar->setFocusPolicy(Qt::NoFocus);
        tool_Bar->setMovable(false);
        tool_Bar->setAllowedAreas(Qt::NoToolBarArea);
        tool_Bar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, tool_Bar);
        dockWidget_Input = new QDockWidget(MainWindow);
        dockWidget_Input->setObjectName(QStringLiteral("dockWidget_Input"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dockWidget_Input->sizePolicy().hasHeightForWidth());
        dockWidget_Input->setSizePolicy(sizePolicy1);
        dockWidget_Input->setMinimumSize(QSize(400, 102));
        dockWidget_Input->setBaseSize(QSize(400, 80));
        dockWidget_Input->setFeatures(QDockWidget::DockWidgetFloatable);
        dockWidget_Input->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents_Input = new QWidget();
        dockWidgetContents_Input->setObjectName(QStringLiteral("dockWidgetContents_Input"));
        sizePolicy1.setHeightForWidth(dockWidgetContents_Input->sizePolicy().hasHeightForWidth());
        dockWidgetContents_Input->setSizePolicy(sizePolicy1);
        dockWidgetContents_Input->setMinimumSize(QSize(400, 80));
        dockWidgetContents_Input->setBaseSize(QSize(400, 80));
        label_value = new QLabel(dockWidgetContents_Input);
        label_value->setObjectName(QStringLiteral("label_value"));
        label_value->setGeometry(QRect(10, 16, 41, 16));
        lineEdit_value = new QLineEdit(dockWidgetContents_Input);
        lineEdit_value->setObjectName(QStringLiteral("lineEdit_value"));
        lineEdit_value->setGeometry(QRect(50, 16, 61, 21));
        lineEdit_value->setFocusPolicy(Qt::StrongFocus);
        lineEdit_value->setInputMethodHints(Qt::ImhNone);
        lineEdit_value->setMaxLength(6);
        lineEdit_value->setEchoMode(QLineEdit::Normal);
        lineEdit_value->setCursorMoveStyle(Qt::LogicalMoveStyle);
        lineEdit_value->setClearButtonEnabled(false);
        pushButton_Insert = new QPushButton(dockWidgetContents_Input);
        pushButton_Insert->setObjectName(QStringLiteral("pushButton_Insert"));
        pushButton_Insert->setGeometry(QRect(120, 10, 81, 31));
        pushButton_Insert->setFocusPolicy(Qt::StrongFocus);
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/insert"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Insert->setIcon(icon17);
        pushButton_Insert->setIconSize(QSize(20, 20));
        pushButton_Delete = new QPushButton(dockWidgetContents_Input);
        pushButton_Delete->setObjectName(QStringLiteral("pushButton_Delete"));
        pushButton_Delete->setEnabled(false);
        pushButton_Delete->setGeometry(QRect(210, 10, 81, 31));
        pushButton_Delete->setFocusPolicy(Qt::StrongFocus);
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/delete"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Delete->setIcon(icon18);
        pushButton_Delete->setIconSize(QSize(20, 20));
        pushButton_Search = new QPushButton(dockWidgetContents_Input);
        pushButton_Search->setObjectName(QStringLiteral("pushButton_Search"));
        pushButton_Search->setEnabled(false);
        pushButton_Search->setGeometry(QRect(300, 10, 81, 31));
        pushButton_Search->setFocusPolicy(Qt::StrongFocus);
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/search"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Search->setIcon(icon19);
        pushButton_Search->setIconSize(QSize(20, 20));
        dockWidget_Input->setWidget(dockWidgetContents_Input);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockWidget_Input);
        dockWidget_toolButtons = new QDockWidget(MainWindow);
        dockWidget_toolButtons->setObjectName(QStringLiteral("dockWidget_toolButtons"));
        sizePolicy1.setHeightForWidth(dockWidget_toolButtons->sizePolicy().hasHeightForWidth());
        dockWidget_toolButtons->setSizePolicy(sizePolicy1);
        dockWidget_toolButtons->setMinimumSize(QSize(400, 102));
        dockWidget_toolButtons->setBaseSize(QSize(400, 80));
        dockWidget_toolButtons->setFeatures(QDockWidget::DockWidgetFloatable);
        dockWidget_toolButtons->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_toolButtons = new QWidget();
        dockWidgetContents_toolButtons->setObjectName(QStringLiteral("dockWidgetContents_toolButtons"));
        sizePolicy1.setHeightForWidth(dockWidgetContents_toolButtons->sizePolicy().hasHeightForWidth());
        dockWidgetContents_toolButtons->setSizePolicy(sizePolicy1);
        dockWidgetContents_toolButtons->setMinimumSize(QSize(400, 80));
        dockWidgetContents_toolButtons->setBaseSize(QSize(400, 80));
        toolButton_Normal = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_Normal->setObjectName(QStringLiteral("toolButton_Normal"));
        toolButton_Normal->setGeometry(QRect(180, 10, 30, 30));
        toolButton_Normal->setMinimumSize(QSize(30, 30));
        toolButton_Normal->setFocusPolicy(Qt::NoFocus);
        toolButton_Normal->setIconSize(QSize(20, 20));
        toolButton_AVL = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_AVL->setObjectName(QStringLiteral("toolButton_AVL"));
        toolButton_AVL->setGeometry(QRect(260, 10, 30, 30));
        toolButton_AVL->setMinimumSize(QSize(30, 30));
        toolButton_AVL->setFocusPolicy(Qt::NoFocus);
        toolButton_AVL->setIconSize(QSize(20, 20));
        toolButton_Edge = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_Edge->setObjectName(QStringLiteral("toolButton_Edge"));
        toolButton_Edge->setEnabled(false);
        toolButton_Edge->setGeometry(QRect(10, 10, 30, 30));
        toolButton_Edge->setMinimumSize(QSize(30, 30));
        toolButton_Edge->setBaseSize(QSize(0, 0));
        toolButton_Edge->setFocusPolicy(Qt::StrongFocus);
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/edge"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Edge->setIcon(icon20);
        toolButton_Edge->setIconSize(QSize(20, 20));
        toolButton_Edge->setCheckable(true);
        toolButton_Left_rotation = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_Left_rotation->setObjectName(QStringLiteral("toolButton_Left_rotation"));
        toolButton_Left_rotation->setEnabled(false);
        toolButton_Left_rotation->setGeometry(QRect(50, 10, 30, 30));
        toolButton_Left_rotation->setMinimumSize(QSize(30, 30));
        toolButton_Left_rotation->setFocusPolicy(Qt::StrongFocus);
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/rotleft"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Left_rotation->setIcon(icon21);
        toolButton_Left_rotation->setIconSize(QSize(20, 20));
        toolButton_RedBlack = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_RedBlack->setObjectName(QStringLiteral("toolButton_RedBlack"));
        toolButton_RedBlack->setGeometry(QRect(220, 10, 30, 30));
        toolButton_RedBlack->setMinimumSize(QSize(30, 30));
        toolButton_RedBlack->setFocusPolicy(Qt::NoFocus);
        toolButton_RedBlack->setIconSize(QSize(20, 20));
        toolButton_Right_rotation = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_Right_rotation->setObjectName(QStringLiteral("toolButton_Right_rotation"));
        toolButton_Right_rotation->setEnabled(false);
        toolButton_Right_rotation->setGeometry(QRect(90, 10, 30, 30));
        toolButton_Right_rotation->setMinimumSize(QSize(30, 30));
        toolButton_Right_rotation->setFocusPolicy(Qt::StrongFocus);
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/rotright"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Right_rotation->setIcon(icon22);
        toolButton_Right_rotation->setIconSize(QSize(20, 20));
        toolButton_Balance = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_Balance->setObjectName(QStringLiteral("toolButton_Balance"));
        toolButton_Balance->setEnabled(false);
        toolButton_Balance->setGeometry(QRect(130, 10, 30, 30));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(toolButton_Balance->sizePolicy().hasHeightForWidth());
        toolButton_Balance->setSizePolicy(sizePolicy2);
        toolButton_Balance->setMinimumSize(QSize(30, 30));
        toolButton_Balance->setFocusPolicy(Qt::StrongFocus);
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/balance"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_Balance->setIcon(icon23);
        toolButton_Balance->setIconSize(QSize(20, 20));
        toolButton_Commit = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_Commit->setObjectName(QStringLiteral("toolButton_Commit"));
        toolButton_Commit->setEnabled(true);
        toolButton_Commit->setGeometry(QRect(310, 10, 30, 30));
        toolButton_Commit->setMinimumSize(QSize(30, 30));
        toolButton_Commit->setFocusPolicy(Qt::NoFocus);
        toolButton_Commit->setIconSize(QSize(20, 20));
        toolButton_RollBack = new QToolButton(dockWidgetContents_toolButtons);
        toolButton_RollBack->setObjectName(QStringLiteral("toolButton_RollBack"));
        toolButton_RollBack->setEnabled(true);
        toolButton_RollBack->setGeometry(QRect(350, 10, 30, 30));
        toolButton_RollBack->setMinimumSize(QSize(30, 30));
        toolButton_RollBack->setFocusPolicy(Qt::NoFocus);
        toolButton_RollBack->setIconSize(QSize(20, 20));
        dockWidget_toolButtons->setWidget(dockWidgetContents_toolButtons);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockWidget_toolButtons);
        dockWidget_History = new QDockWidget(MainWindow);
        dockWidget_History->setObjectName(QStringLiteral("dockWidget_History"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(dockWidget_History->sizePolicy().hasHeightForWidth());
        dockWidget_History->setSizePolicy(sizePolicy3);
        dockWidget_History->setMinimumSize(QSize(80, 422));
        dockWidget_History->setBaseSize(QSize(80, 400));
        dockWidget_History->setFeatures(QDockWidget::DockWidgetFloatable);
        dockWidgetContents_History = new QWidget();
        dockWidgetContents_History->setObjectName(QStringLiteral("dockWidgetContents_History"));
        sizePolicy3.setHeightForWidth(dockWidgetContents_History->sizePolicy().hasHeightForWidth());
        dockWidgetContents_History->setSizePolicy(sizePolicy3);
        dockWidgetContents_History->setMinimumSize(QSize(80, 400));
        dockWidgetContents_History->setBaseSize(QSize(80, 400));
        slider_History = new QSlider(dockWidgetContents_History);
        slider_History->setObjectName(QStringLiteral("slider_History"));
        slider_History->setGeometry(QRect(30, 20, 19, 340));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(slider_History->sizePolicy().hasHeightForWidth());
        slider_History->setSizePolicy(sizePolicy4);
        slider_History->setMinimumSize(QSize(10, 340));
        slider_History->setFocusPolicy(Qt::StrongFocus);
        slider_History->setMaximum(0);
        slider_History->setPageStep(0);
        slider_History->setTracking(false);
        slider_History->setOrientation(Qt::Vertical);
        slider_History->setInvertedControls(false);
        slider_History->setTickPosition(QSlider::NoTicks);
        dockWidget_History->setWidget(dockWidgetContents_History);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_History);

        menu_Bar->addAction(menu_Tree->menuAction());
        menu_Bar->addAction(menu_Type->menuAction());
        menu_Bar->addAction(menu_Edit->menuAction());
        menu_Bar->addAction(menu_Zoom->menuAction());
        menu_Bar->addAction(menu_Window->menuAction());
        menu_Bar->addAction(menu_Help->menuAction());
        menu_Tree->addAction(action_New);
        menu_Tree->addAction(action_Open);
        menu_Tree->addAction(action_Save);
        menu_Tree->addAction(action_Save_As);
        menu_Tree->addAction(menu_Transaction->menuAction());
        menu_Tree->addAction(action_Print);
        menu_Tree->addAction(action_Exit);
        menu_Transaction->addAction(action_Commit);
        menu_Transaction->addAction(action_RollBack);
        menu_Type->addAction(action_Normal);
        menu_Type->addAction(action_Red_Black);
        menu_Type->addAction(action_AVL);
        menu_Edit->addAction(action_Select_All);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Undo);
        menu_Edit->addAction(action_Redo);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_Copy);
        menu_Edit->addAction(action_Cut);
        menu_Edit->addAction(action_Paste);
        menu_Zoom->addAction(action_Zoom_In);
        menu_Zoom->addAction(action_Zoom_Out);
        menu_Window->addAction(action_Close);
        menu_Window->addAction(action_Close_All);
        menu_Window->addSeparator();
        menu_Window->addAction(action_Split_horizontal);
        menu_Window->addAction(action_Split_vertical);
        menu_Window->addAction(action_Set_Tabified);
        menu_Window->addSeparator();
        menu_Window->addAction(action_Tile);
        menu_Window->addAction(action_Cascade);
        menu_Window->addSeparator();
        menu_Window->addAction(action_Next);
        menu_Window->addAction(action_Previous);
        menu_Window->addSeparator();
        menu_Window->addAction(action_All_Windows_Docked);
        menu_Help->addAction(action_About);
        menu_Help->addAction(action_About_Qt);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Binary Search Tree - ADMIN", 0));
        action_New->setText(QApplication::translate("MainWindow", "New", 0));
#ifndef QT_NO_TOOLTIP
        action_New->setToolTip(QApplication::translate("MainWindow", "New Tree", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        action_New->setStatusTip(QApplication::translate("MainWindow", "Create a new tree", 0));
#endif // QT_NO_STATUSTIP
        action_New->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        action_Open->setText(QApplication::translate("MainWindow", "Open", 0));
#ifndef QT_NO_STATUSTIP
        action_Open->setStatusTip(QApplication::translate("MainWindow", "Open an existing tree", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        action_Open->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        action_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        action_Save->setText(QApplication::translate("MainWindow", "Save", 0));
#ifndef QT_NO_STATUSTIP
        action_Save->setStatusTip(QApplication::translate("MainWindow", "Save the tree to disk", 0));
#endif // QT_NO_STATUSTIP
        action_Save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        action_Save_As->setText(QApplication::translate("MainWindow", "Save As...", 0));
#ifndef QT_NO_STATUSTIP
        action_Save_As->setStatusTip(QApplication::translate("MainWindow", "Save the tree under a new name", 0));
#endif // QT_NO_STATUSTIP
        action_Commit->setText(QApplication::translate("MainWindow", "Commit", 0));
#ifndef QT_NO_STATUSTIP
        action_Commit->setStatusTip(QApplication::translate("MainWindow", "Commit all transactions of current tree and clean the history", 0));
#endif // QT_NO_STATUSTIP
        action_Commit->setShortcut(QApplication::translate("MainWindow", "Ctrl+End", 0));
        action_RollBack->setText(QApplication::translate("MainWindow", "RollBack", 0));
#ifndef QT_NO_STATUSTIP
        action_RollBack->setStatusTip(QApplication::translate("MainWindow", "Rollback all transactions from current tree and undo all", 0));
#endif // QT_NO_STATUSTIP
        action_RollBack->setShortcut(QApplication::translate("MainWindow", "Ctrl+Home", 0));
        action_Print->setText(QApplication::translate("MainWindow", "Print", 0));
#ifndef QT_NO_STATUSTIP
        action_Print->setStatusTip(QApplication::translate("MainWindow", "Prints the content of active tree", 0));
#endif // QT_NO_STATUSTIP
        action_Print->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", 0));
        action_Exit->setText(QApplication::translate("MainWindow", "Exit", 0));
#ifndef QT_NO_STATUSTIP
        action_Exit->setStatusTip(QApplication::translate("MainWindow", "Exit the application", 0));
#endif // QT_NO_STATUSTIP
        action_Exit->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", 0));
        action_Normal->setText(QApplication::translate("MainWindow", "Normal", 0));
#ifndef QT_NO_STATUSTIP
        action_Normal->setStatusTip(QApplication::translate("MainWindow", "Convert this tree for a non-balance tree", 0));
#endif // QT_NO_STATUSTIP
        action_Red_Black->setText(QApplication::translate("MainWindow", "Red Black", 0));
#ifndef QT_NO_STATUSTIP
        action_Red_Black->setStatusTip(QApplication::translate("MainWindow", "Convert this tree for a red/black balanced tree", 0));
#endif // QT_NO_STATUSTIP
        action_AVL->setText(QApplication::translate("MainWindow", "AVL", 0));
#ifndef QT_NO_STATUSTIP
        action_AVL->setStatusTip(QApplication::translate("MainWindow", "Convert this tree for a AVL balanced tree", 0));
#endif // QT_NO_STATUSTIP
        action_Select_All->setText(QApplication::translate("MainWindow", "Select All", 0));
#ifndef QT_NO_STATUSTIP
        action_Select_All->setStatusTip(QApplication::translate("MainWindow", "Select all nodes from this tree", 0));
#endif // QT_NO_STATUSTIP
        action_Select_All->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", 0));
        action_Undo->setText(QApplication::translate("MainWindow", "Undo", 0));
#ifndef QT_NO_STATUSTIP
        action_Undo->setStatusTip(QApplication::translate("MainWindow", "Undo the last operation in the active tree", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        action_Undo->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        action_Undo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        action_Redo->setText(QApplication::translate("MainWindow", "Redo", 0));
#ifndef QT_NO_STATUSTIP
        action_Redo->setStatusTip(QApplication::translate("MainWindow", "Redo the last operation in the active tree", 0));
#endif // QT_NO_STATUSTIP
        action_Redo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", 0));
        action_Cut->setText(QApplication::translate("MainWindow", "Cut", 0));
#ifndef QT_NO_STATUSTIP
        action_Cut->setStatusTip(QApplication::translate("MainWindow", "Cut the current selection's contents to the clipboard", 0));
#endif // QT_NO_STATUSTIP
        action_Cut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0));
        action_Copy->setText(QApplication::translate("MainWindow", "Copy", 0));
#ifndef QT_NO_STATUSTIP
        action_Copy->setStatusTip(QApplication::translate("MainWindow", "Copy the current selection's contents to the clipboard", 0));
#endif // QT_NO_STATUSTIP
        action_Copy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        action_Paste->setText(QApplication::translate("MainWindow", "Paste", 0));
#ifndef QT_NO_STATUSTIP
        action_Paste->setStatusTip(QApplication::translate("MainWindow", "Paste the clipboard's contents into the current selection", 0));
#endif // QT_NO_STATUSTIP
        action_Paste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0));
        action_Zoom_In->setText(QApplication::translate("MainWindow", "Zoom In", 0));
#ifndef QT_NO_STATUSTIP
        action_Zoom_In->setStatusTip(QApplication::translate("MainWindow", "Increase the size of current tree", 0));
#endif // QT_NO_STATUSTIP
        action_Zoom_In->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0));
        action_Zoom_Out->setText(QApplication::translate("MainWindow", "Zoom Out", 0));
#ifndef QT_NO_STATUSTIP
        action_Zoom_Out->setStatusTip(QApplication::translate("MainWindow", "Decrease the size of current tree", 0));
#endif // QT_NO_STATUSTIP
        action_Zoom_Out->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0));
        action_Close->setText(QApplication::translate("MainWindow", "Close", 0));
#ifndef QT_NO_STATUSTIP
        action_Close->setStatusTip(QApplication::translate("MainWindow", "Close the active window", 0));
#endif // QT_NO_STATUSTIP
        action_Close->setShortcut(QApplication::translate("MainWindow", "Ctrl+F4", 0));
        action_Close_All->setText(QApplication::translate("MainWindow", "Close All", 0));
#ifndef QT_NO_STATUSTIP
        action_Close_All->setStatusTip(QApplication::translate("MainWindow", "Close all the windows", 0));
#endif // QT_NO_STATUSTIP
        action_Tile->setText(QApplication::translate("MainWindow", "Tile", 0));
#ifndef QT_NO_STATUSTIP
        action_Tile->setStatusTip(QApplication::translate("MainWindow", "Tile the windows", 0));
#endif // QT_NO_STATUSTIP
        action_Cascade->setText(QApplication::translate("MainWindow", "Cascade", 0));
#ifndef QT_NO_STATUSTIP
        action_Cascade->setStatusTip(QApplication::translate("MainWindow", "Cascade the windows", 0));
#endif // QT_NO_STATUSTIP
        action_Next->setText(QApplication::translate("MainWindow", "Next", 0));
#ifndef QT_NO_STATUSTIP
        action_Next->setStatusTip(QApplication::translate("MainWindow", "Move the focus to the next window", 0));
#endif // QT_NO_STATUSTIP
        action_Next->setShortcut(QApplication::translate("MainWindow", "Ctrl+Tab", 0));
        action_All_Windows_Docked->setText(QApplication::translate("MainWindow", "All windows docked", 0));
#ifndef QT_NO_STATUSTIP
        action_All_Windows_Docked->setStatusTip(QApplication::translate("MainWindow", "All sub windows are display docked at main frame", 0));
#endif // QT_NO_STATUSTIP
        action_All_Windows_Docked->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
        action_About->setText(QApplication::translate("MainWindow", "About", 0));
#ifndef QT_NO_STATUSTIP
        action_About->setStatusTip(QApplication::translate("MainWindow", "Show the application's About box", 0));
#endif // QT_NO_STATUSTIP
        action_About_Qt->setText(QApplication::translate("MainWindow", "About Qt", 0));
#ifndef QT_NO_STATUSTIP
        action_About_Qt->setStatusTip(QApplication::translate("MainWindow", "Show the Qt library's About box", 0));
#endif // QT_NO_STATUSTIP
        action_Split_horizontal->setText(QApplication::translate("MainWindow", "Split Horizontal", 0));
#ifndef QT_NO_STATUSTIP
        action_Split_horizontal->setStatusTip(QApplication::translate("MainWindow", "Split all docks side by side", 0));
#endif // QT_NO_STATUSTIP
        action_Split_horizontal->setShortcut(QApplication::translate("MainWindow", "Ctrl+Right", 0));
        action_Split_vertical->setText(QApplication::translate("MainWindow", "Split Vertical", 0));
#ifndef QT_NO_STATUSTIP
        action_Split_vertical->setStatusTip(QApplication::translate("MainWindow", "Split all docks at top and botom", 0));
#endif // QT_NO_STATUSTIP
        action_Split_vertical->setShortcut(QApplication::translate("MainWindow", "Ctrl+Down", 0));
        action_Set_Tabified->setText(QApplication::translate("MainWindow", "Set Tabified", 0));
#ifndef QT_NO_STATUSTIP
        action_Set_Tabified->setStatusTip(QApplication::translate("MainWindow", "Tabify all docks at default position", 0));
#endif // QT_NO_STATUSTIP
        action_Set_Tabified->setShortcut(QApplication::translate("MainWindow", "Ctrl+Up", 0));
        action_Previous->setText(QApplication::translate("MainWindow", "Previous", 0));
#ifndef QT_NO_STATUSTIP
        action_Previous->setStatusTip(QApplication::translate("MainWindow", "Move the focus to the previous window", 0));
#endif // QT_NO_STATUSTIP
        action_Previous->setShortcut(QApplication::translate("MainWindow", "Ctrl+Backspace", 0));
        tabWidget->setTabText(tabWidget->indexOf(widget_ghost_1), QString());
        tabWidget->setTabText(tabWidget->indexOf(widget_ghost_2), QString());
        menu_Tree->setTitle(QApplication::translate("MainWindow", "Tree", 0));
        menu_Transaction->setTitle(QApplication::translate("MainWindow", "Transaction", 0));
        menu_Type->setTitle(QApplication::translate("MainWindow", "Type", 0));
        menu_Edit->setTitle(QApplication::translate("MainWindow", "Edit", 0));
        menu_Zoom->setTitle(QApplication::translate("MainWindow", "Zoom", 0));
        menu_Window->setTitle(QApplication::translate("MainWindow", "Window", 0));
        menu_Help->setTitle(QApplication::translate("MainWindow", "Help", 0));
        tool_Bar->setWindowTitle(QString());
        dockWidget_Input->setWindowTitle(QApplication::translate("MainWindow", "Nodes", 0));
        label_value->setText(QApplication::translate("MainWindow", "Value:", 0));
#ifndef QT_NO_STATUSTIP
        lineEdit_value->setStatusTip(QApplication::translate("MainWindow", "input a integer value here", 0));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_STATUSTIP
        pushButton_Insert->setStatusTip(QApplication::translate("MainWindow", "Insert a value for tree", 0));
#endif // QT_NO_STATUSTIP
        pushButton_Insert->setText(QApplication::translate("MainWindow", "Insert", 0));
#ifndef QT_NO_STATUSTIP
        pushButton_Delete->setStatusTip(QApplication::translate("MainWindow", "delete a value of tree", 0));
#endif // QT_NO_STATUSTIP
        pushButton_Delete->setText(QApplication::translate("MainWindow", "Delete", 0));
#ifndef QT_NO_STATUSTIP
        pushButton_Search->setStatusTip(QApplication::translate("MainWindow", "search a value in tree", 0));
#endif // QT_NO_STATUSTIP
        pushButton_Search->setText(QApplication::translate("MainWindow", "Search", 0));
        dockWidget_toolButtons->setWindowTitle(QApplication::translate("MainWindow", "Tools", 0));
        toolButton_Normal->setText(QString());
        toolButton_AVL->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_Edge->setToolTip(QApplication::translate("MainWindow", "Edge", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolButton_Edge->setStatusTip(QApplication::translate("MainWindow", "Auto edge nodes", 0));
#endif // QT_NO_STATUSTIP
        toolButton_Edge->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_Left_rotation->setToolTip(QApplication::translate("MainWindow", "Left", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolButton_Left_rotation->setStatusTip(QApplication::translate("MainWindow", "Left rotation tree", 0));
#endif // QT_NO_STATUSTIP
        toolButton_Left_rotation->setText(QString());
        toolButton_RedBlack->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_Right_rotation->setToolTip(QApplication::translate("MainWindow", "Right", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolButton_Right_rotation->setStatusTip(QApplication::translate("MainWindow", "Right rotation tree", 0));
#endif // QT_NO_STATUSTIP
        toolButton_Right_rotation->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButton_Balance->setToolTip(QApplication::translate("MainWindow", "Balance", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        toolButton_Balance->setStatusTip(QApplication::translate("MainWindow", "Balanced tree", 0));
#endif // QT_NO_STATUSTIP
        toolButton_Balance->setText(QString());
        toolButton_Commit->setText(QString());
        toolButton_RollBack->setText(QString());
        dockWidget_History->setWindowTitle(QApplication::translate("MainWindow", "HIstory", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
