#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <QScrollBar>
#include "subchild.h"
#include "mainwindow.h"
#include "ui_subchild.h"

SubChild::SubChild(QWidget *parent) : QWidget(parent), ui(new Ui::SubChild) {
     ui->setupUi(this);
     setAttribute(Qt::WA_DeleteOnClose);
     mainwindow = qobject_cast <QMainWindow *>  (parent);
     tree = NULL;
     is_saved = is_docked =  false;
     is_empty = is_untitled = true;
     connect(ui->groupBox, SIGNAL(toggled(bool)), this, SLOT(setBoxChecked(bool)));
     ui->graphicsView->horizontalScrollBar()->setStyleSheet("background-color:lightgray;");
     ui->graphicsView->verticalScrollBar()->setStyleSheet("background-color:lightgray;");
     ui->graphicsView->setStyleSheet("background-color:white;");
}

SubChild::~SubChild() {
     disconnect(ui->groupBox, SIGNAL(toggled(bool)));
     for (register int i = trees.count() -1; i >= 0; i--) {

          qDebug("- Delete Tree: %p", trees.at(i));

          if (trees.at(i) != NULL)
              delete trees.at(i);
              //trees.removeAt(i);
     }
     delete ui;
}

void SubChild::closeEvent(QCloseEvent *event) {
     if (maybeSave() == false) {
         event->ignore();
         return;
     }
     MainWindow *m_win = getMainWindow();
     m_win->removeSubChild();
     m_win->setVisibleDocks(false);
     if (is_docked == true) {
         if (m_win->getMode() == MainWindow::tabified)
             m_win->setVisibleTabWidget(false);
         else
             m_win->destroySplitter();
     } else {
         m_win->setVisibleMdiArea(false);
     }
     m_win->decreaseFilesOpen();
     m_win->updateActionsVisible(false);
     m_win->updateActionsEnabled(false);
}

void SubChild::resizeEvent(QResizeEvent *event) {
     bool flag = ui->groupBox->title().isEmpty() == false;
     int x = 0, y = 0, w, h;
     calculateSize(flag);
     w = ui->groupBox->width();
     h = ui->groupBox->height();
     if (flag == true) {
         x = 4;
         y = 16;
         w -= 8;
         h -= 24;
     }
     ui->graphicsView->setGeometry(x, y, w, h);
     ui->graphicsView->setFixedSize(w, h);
     event->accept();
}

void SubChild::setBoxChecked(bool checked) {
     if (checked == true) {
         MainWindow *m_win = getMainWindow();
         m_win->setActiveBoxToChild(this);
     }
}

QString SubChild::getShortFileName() {
    return getFileInfo(filename);
}

QString SubChild::getFileInfo(const QString &file) {
     return QFileInfo(file).fileName();
}

void SubChild::showBoxTitle(bool show, QString title) {
     ui->groupBox->setCheckable(show);
     if (show == true) {
         ui->groupBox->setChecked(false);
         ui->groupBox->setTitle(title);
     } else {
         ui->groupBox->setTitle("");
     }
     calculateSize(show);
}

void SubChild::setCheckedBox(bool checked) {
     ui->groupBox->setChecked(checked);
}

bool SubChild::insertTree(int value) {
     if (tree == NULL) {
         tree = new TreeGraph(value, ui->graphicsView, this);
         tree->addItem(tree->getLastNode());
         tree->setupTree(tree->getRootNode());
     } else {
         TreeGraph *tmp_tree = new TreeGraph(trees.last(), this);
         if (tmp_tree->addNode(value) == false) {
             delete tmp_tree;
             return false;
         }
         tmp_tree->setupTree(tmp_tree->getRootNode());
         tmp_tree->checkCollides(tmp_tree->getRootNode());
         tmp_tree->addNodesToGraph();
         tree = tmp_tree;
     }
     trees.append(tree);
     setMaximumForSlider();
     setUndoEnabled(true);
     clearBackupTree();
     ui->graphicsView->setScene(tree);
     return true;
}

bool SubChild::deleteTree(int value) {
     TreeGraph *tmp_tree = new TreeGraph(trees.last(), this);
     if (tmp_tree->deleteNode(value) == true) {
        if (tmp_tree->getRootNode() != NULL) {
            tmp_tree->getRootNode()->identifyNodesAll();
            tmp_tree->setupTree(tmp_tree->getRootNode());
            tmp_tree->checkCollides(tmp_tree->getRootNode());
            tmp_tree->addNodesToGraph();
            tree = tmp_tree;
            trees.append(tree);
            setMaximumForSlider();
            setUndoEnabled(true);
            clearBackupTree();
        } else {
            delete tmp_tree;
            tree = NULL;
            is_empty = true;
        }
        ui->graphicsView->setScene(tree);
        return true;
    }
    return false;
}

bool SubChild::searchTree(int value) {
     return trees.last()->searchNode(value);
}

void SubChild::clearBackupTree() {
     backup_trees.clear();
     setRedoEnabled(false);
}

bool SubChild::maybeSave() {
     if (is_saved == false && is_empty == false) {
         QMessageBox::StandardButton message;
         message = QMessageBox::warning(this, tr("BST Utility"), tr("'%1' has been modified.\nDo you want to save your changes?").arg(getShortFileName()), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
         if (message == QMessageBox::Save)
             return save(true);
         else if (message == QMessageBox::Cancel)
             return false;
     }
     return true;
}

bool SubChild::save(const bool message) {
     if (is_untitled == true) {
         return saveAs(filename, message);
     }
     return saveFile(filename);
}

bool SubChild::saveAs(const QString &fileName, const bool message) {
     bool flag = false;
     if (message == true) {
         qApp->setOverrideCursor(Qt::WaitCursor);
         QString dialog = QFileDialog::getSaveFileName(this, tr("Save As Binary Search Tree"), fileName, tr("Binary Search Tree files (*.bst);;All files (*.*)"));
         qApp->restoreOverrideCursor();
         if (dialog.isNull() == false && dialog.isEmpty() == false) {
             if (saveFile(dialog) == true){
                 setFileName(dialog);
                 flag = true;;
             }
         }
     } else {
         if (fileName.isNull() == false && fileName.isEmpty() == false) {
             if (saveFile(fileName) == true){
                 setFileName(fileName);
                 flag = true;;
             }
         }
     }
     if (flag == true) {
         MainWindow *m_win = getMainWindow();
         setWindowTitle(getShortFileName());
         if (m_win->getMode() == MainWindow::horizontal || m_win->getMode() == MainWindow::vertical)
             ui->groupBox->setTitle(getShortFileName());
     }
     return flag;
}

bool SubChild::saveFile(const QString &fileName) {
     QFile file(fileName);
     if (!file.open(QFile::WriteOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("BST Utility"), tr("Canot write file %1:\n%2.").arg(fileName).arg(file.errorString()));
         return false;
     }
     if (trees.count() > 0) {
         file.write("!BST\n");
         QList <QString> list;
         trees.last()->valuesPreOrder(list);
         register int count = list.count();
         for (register int i = 0; i < count; i++) {
              file.write(list.at(i).toStdString().c_str());
              file.write("\n");
         }
     }
     file.close();
     is_saved    = true;
     is_untitled = false;
     return true;
}

MainWindow *SubChild::getMainWindow() {
     return qobject_cast <MainWindow *>  (mainwindow);
}

QGroupBox *SubChild::getGroupBox() {
     return ui->groupBox;
}

QGraphicsView *SubChild::getGraphicsView() {
     return ui->graphicsView;
}

void SubChild::calculateSize(bool flag) {
    if (flag == true) {
        ui->groupBox->setGeometry(0, 20, width(), height() -20);
        ui->groupBox->setFixedSize(width(), height() -20);
        elidedBoxTitle();
    } else {
        ui->groupBox->setGeometry(0, 0, width(), height());
        ui->groupBox->setFixedSize(size());
    }
}

void SubChild::elidedBoxTitle() {
     int w = ui->groupBox->width() -25;
     QFontMetrics metrics(ui->groupBox->font());
     if (w <= metrics.width(ui->groupBox->title()) +25) {
         QString text(ui->groupBox->title());
         QString elided = metrics.elidedText(text, Qt::ElideRight, w, Qt::TextSingleLine);
         ui->groupBox->setTitle(elided);
     } else {
         if (ui->groupBox->title().compare(getShortFileName()) != 0) {
             ui->groupBox->setTitle(getShortFileName());
         }
     }
}

void SubChild::appendTree(TreeGraph *tree) {
     trees.append(tree);
     this->tree = tree;
     setMaximumForSlider();
     setUndoEnabled(true);
}

int SubChild::getTreeCount() {
     return trees.count();
}

TreeGraph *SubChild::getTreeAt(int index) {
     return trees.at(index);
}

TreeGraph *SubChild::getLastTree() {
     return trees.last();
}

void SubChild::removeLastTree() {
     trees.removeLast();
}

void SubChild::clearTree() {
     trees.clear();
     tree = NULL;
}

void SubChild::appendBackupTree(TreeGraph *tree) {
     backup_trees.append(tree);
}

int SubChild::getBackupTreeCount() {
     return backup_trees.count();
}

TreeGraph *SubChild::getLastBackupTree() {
     return backup_trees.last();
}

void SubChild::removeLastBackupTree() {
     backup_trees.removeLast();
}

void SubChild::setMaximumForSlider() {
     MainWindow *m_win = getMainWindow();
     m_win->setSliderMaximum(trees.count() -1);
}

void SubChild::setUndoEnabled(bool enabled) {
     if (enabled == true && trees.count() < 2)
         return;
     MainWindow *m_win = getMainWindow();
     m_win->updateUndoActionEnabled(enabled);
}

void SubChild::setRedoEnabled(bool enabled) {
     if (enabled == true && backup_trees.count() < 1)
         return;
     MainWindow *m_win = getMainWindow();
     m_win->updateRedoActionEnabled(enabled);
}

