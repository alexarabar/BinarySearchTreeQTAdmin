#ifndef SUBCHILD_H
#define SUBCHILD_H
#include <QWidget>
#include <QMainWindow>
#include <QGroupBox>
#include "treescene.h"

QT_BEGIN_NAMESPACE
     class MainWindow;
     class TreeGraph;
QT_END_NAMESPACE

namespace Ui {
     class SubChild;
}

class SubChild : public QWidget {
     Q_OBJECT
public:
     explicit SubChild(QWidget *parent = NULL);
     virtual ~SubChild();
     QString getShortFileName();
     void showBoxTitle(bool show, QString title = NULL);
     void setCheckedBox(bool checked);
     bool insertTree(int value);
     bool deleteTree(int value);
     bool searchTree(int value);
     bool maybeSave();
     bool save(const bool message);
     bool saveAs(const QString &fileName, const bool message);
     MainWindow *getMainWindow();
     QGroupBox  *getGroupBox();
     QGraphicsView *getGraphicsView();
     void elidedBoxTitle();
     void appendTree(TreeGraph *tree);
     int getTreeCount();
     TreeGraph *getTreeAt(int index);
     TreeGraph *getLastTree();
     void removeLastTree();
     void clearTree();
     void appendBackupTree(TreeGraph *tree);
     int getBackupTreeCount();
     TreeGraph *getLastBackupTree();
     void removeLastBackupTree();
     void clearBackupTree();
     inline void setFileName(QString file) {filename = file;}
     inline QString getFileName()          {return filename;}
     inline void setIndex(int index)   {this->index = index;}
     inline int  getIndex()                   {return index;}
     inline void setDocked(bool docked) {is_docked = docked;}
     inline void setSaved(bool saved)   {is_saved = saved;}
     inline void setUntitled(bool untitled) {is_untitled = untitled;}
     inline bool isUntitled()               {return is_untitled;}
     inline void setEmpty(bool empty) {is_empty = empty;}
     inline bool isEmpty()             {return is_empty;}
     inline void setTree(TreeGraph *tree)  {this->tree = tree;}
     inline TreeGraph *getTree()           {return tree;}
protected:
     void closeEvent(QCloseEvent *event);
     void resizeEvent(QResizeEvent *event);
private slots:
     void setBoxChecked(bool checked);
private:
     bool saveFile(const QString &fileName);
     void calculateSize(bool flag);
     QString getFileInfo(const QString &file);
     void setMaximumForSlider();
     void setUndoEnabled(bool enabled);
     void setRedoEnabled(bool enabled);
     QString filename;
     QMainWindow *mainwindow;
     QList <TreeGraph *> trees;
     QList <TreeGraph *> backup_trees;
     TreeGraph  *tree;
     Ui::SubChild *ui;
     int index;
     bool is_docked;
     bool is_saved;
     bool is_untitled;
     bool is_empty;
};
#endif // SUBCHILD_H

