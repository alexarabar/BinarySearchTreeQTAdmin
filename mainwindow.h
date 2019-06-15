#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define MAX_FILES 24
#define CHILD_SIZE 282
#include <QMainWindow>
#include <QSignalMapper>
#include <QValidator>
#include <QSplitter>
#include "subchild.h"

namespace Ui {
     class MainWindow;
}

class MainWindow : public QMainWindow {
     Q_OBJECT
public:
     enum Modes {tabified = 0, horizontal = 1, vertical = 2};
     explicit MainWindow(QWidget *parent = NULL);
     virtual ~MainWindow();
     void removeSubChild();
     void setVisibleDocks(bool visible);
     void setVisibleMdiArea(bool visible);
     void setVisibleTabWidget(bool visible);
     void updateActionsVisible(bool visible);
     void updateActionsEnabled(bool enabled);
     void updateEditActionsEnabled();
     void updateUndoActionEnabled(bool enabled);
     void updateRedoActionEnabled(bool enabled);
     void updateButtonsEnabled(bool enabled, bool flag = false);
     void setTextForInput(char *str);
     void destroySplitter();
     bool autoEdgeIsChecked();
     void setActiveBoxToChild(SubChild *child);
     void setMenuFromContext(QMenu &menu);
     void setSelectionFlag(bool selection);
     void setSliderMaximum(int maximum);
     void alertOnStatusBar(const QString &message);
     inline MainWindow::Modes getMode() {return mode;}
     inline void decreaseFilesOpen()    {filesopen--;}
protected:
     void closeEvent(QCloseEvent *event);
     void resizeEvent(QResizeEvent *event);
private slots:
     void topLevelInput(bool top);
     void topLevelToolButtons(bool top);
     void topLevelHistory(bool top);
     void locationInput();
     void locationToolButtons(Qt::DockWidgetArea);
     void locationHistory(Qt::DockWidgetArea);
     void New();
     void Open();
     void Save();
     void SaveAs();
     void Insert();
     void Delete();
     void Search();
     void Cascade();
     void selectAll();
     void Cut();
     void Copy();
     void Paste();
     void rotateLeft();
     void rotateRight();
     void Balance();
     void Undo();
     void Redo();
     void RollBack();
     void Commit();
     void ZoomIn();
     void ZoomOut();
     void Normal();
     void RedBlack();
     void AVL();
     void setDocked();
     void closeOneMdi();
     void closeOneTab();
     bool closeOneMdi(int index);
     bool closeOneTab(int index);
     bool closeAllMdis();
     bool closeAllTabs();
     void setTabified();
     void splitHorizontal();
     void splitVertical();
     void setRotation(int dir);
     void updateWindowMenu();
     void setActiveSubWindow(QWidget *window);
     void alertOffStatusBar();
     void getClipBoardData();
     void setClipBoardData();
     void setSliderValue(int value);
private:
     SubChild *getSubChild();
     SubChild *addSubChild(QString title = NULL);
   //void alertOnStatusBar(const QString &message);
     void displayAlertNotFound();
     bool loadFile(const QString &fileName, int *array, int &size);
     QString saveFile();
     void setHtopLevel(QDockWidget *dock, bool top);
     void setVtopLevel(QDockWidget *dock, bool top);
     void setHlocation(QDockWidget *dock);
     void setVlocation(QDockWidget *dock);
     void widthToFitAll();
     void heightToFitAll();
     QSize sizeFreeArea();
     void startToolBar();
     void setToolButtons();
     void createConnections();
     void destroyConnections();
     void connectWindowMenu(bool flag);
     void disconnectWindowMenu(bool flag);
     bool keyPressedForChild(QKeyEvent *keyEvent);
     bool keyPressedForButton(QString q_str, QKeyEvent *keyEvent);
     bool keyPressedForInput(QKeyEvent *keyEvent);
     bool keyPressedForBox(QKeyEvent *keyEvent, QObject *object);
     bool keyPressedForTools(const QString &Name, QKeyEvent *keyEvent);
     bool focusInForInput();
     bool focusOutForInput();
     bool focusInForChild(QObject *object);
     bool focusOutForChild();
     bool focusInForSlider();
     bool focusOutForSlider();
     bool paintForChild();
     bool MouseReleaseForView(QObject *object);
     bool eventFilter(QObject *object, QEvent *event);
     void insertMdiChild();
     void insertTabChild();
     void removeMdiChild();
     void removeTabChild();
     void createSplitter();
     void removeSplitter();
     void readSettings();
     void writeSettings();
     SubChild *activeMdiChild();
     SubChild *activeTabChild();
     bool setMinimumSizeOfChilds();
     QString stripAllTagsOfHtml(QString src);
     QString delimitedByComma(QString src, int &size);
     QString *createArrayFromValues(QString src, int size);
     bool checkValuesInClipboard(QString *array, int &size);
     void updateGraphicsView(SubChild *child, TreeGraph *tree, NodeGraph *node);
     void balanceToVector(QList <QString> list, QVector <int> &vector, int start, int end);
     void updateMenuTypeChecked(int index);
     QSignalMapper *mapper;
     QClipboard *clipboard;
     QString    *clipboard_values;
     int         clipboard_count;
     bool        clipboard_flag;
     bool        selection_flag;
     bool  redo_flag, undo_flag;
     QIntValidator *validator;
     QList <SubChild *> childs;
     SubChild  *child;
     QSplitter *split;
     QSize    minimum;
     QPalette palette;
     QFont       font;
     Modes       mode;
     int filesopen;
     Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
