#include <QtGui>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
     ui->setupUi(this);
     mapper    = new QSignalMapper(this);
     validator = new QIntValidator(-32767, 32767);
     clipboard = qApp->clipboard();
     clipboard_values = NULL;
     clipboard_count  = 0;
     selection_flag = clipboard_flag   = false;
     redo_flag = undo_flag = false;
     split = NULL;
     child = NULL;
     filesopen = 0;
     minimum = minimumSize();
     palette = ui->status_Bar->palette();
     font = ui->status_Bar->font();
     ui->lineEdit_value->setValidator(validator);
     ui->status_Bar->setAutoFillBackground(true);
     setCorner(Qt::TopLeftCorner,  Qt::TopDockWidgetArea);
     setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
     setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
     setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
     readSettings();
     startToolBar();
     setToolButtons();
     createConnections();
     setVisibleDocks(false);
     setVisibleMdiArea(false);
     setVisibleTabWidget(false);
     qApp->installEventFilter(this);
}

MainWindow::~MainWindow() {
     destroyConnections();
     delete mapper;
     delete validator;
     delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
     if (ui->mdiArea->isVisible() == true) {
         if (closeAllMdis() == false) {
             event->ignore();
             return;
         }
     } else {
         if (closeAllTabs() == false) {
             event->ignore();
             return;
         }
     }
     writeSettings();
}

void MainWindow::resizeEvent(QResizeEvent *event) {
     QSize size = sizeFreeArea();
     if (ui->mdiArea->isVisible() == true) {
         ui->mdiArea->setFixedWidth(size.width());
         ui->mdiArea->setFixedHeight(size.height());
     } else if (ui->tabWidget->isVisible()) {
         ui->tabWidget->setFixedWidth(size.width());
         ui->tabWidget->setFixedHeight(size.height());
     } else if (mode == MainWindow::horizontal || mode == MainWindow::vertical) {
         if (split != NULL) {
             split->setFixedWidth(size.width());
             split->setFixedHeight(size.height());
         }
     }
     if (event != NULL) event->accept();
}

void MainWindow::startToolBar() {
     QList <QAction *> list_tree;
     QList <QAction *> list_edit;
     list_tree.append(ui->action_New);
     list_tree.append(ui->action_Open);
     list_tree.append(ui->action_Save);
     list_tree.append(ui->action_Print);
     list_edit.append(ui->action_Undo);
     list_edit.append(ui->action_Redo);
     list_edit.append(ui->action_Copy);
     list_edit.append(ui->action_Cut);
     list_edit.append(ui->action_Paste);
     ui->tool_Bar->addActions(list_tree);
     ui->tool_Bar->addSeparator();
     ui->tool_Bar->addActions(list_edit);
}

void MainWindow::removeSubChild() {
     register int index = 0;
     if (ui->mdiArea->isVisible() == true) {
         for (register int i = 0; i < ui->mdiArea->subWindowList().count(); i++) {
              if (ui->mdiArea->activeSubWindow() == ui->mdiArea->subWindowList().at(i)) {
                  index = i;
                  break;
              }
         }
     } else if (ui->tabWidget->isVisible() == true) {
         index = ui->tabWidget->currentIndex();
     } else if (mode == MainWindow::horizontal || mode == MainWindow::vertical) {
         index = split->indexOf(child);
         split->widget(index)->setParent(NULL);
     }
     childs.removeAt(index);
     if (childs.count() == 0) {
         child = NULL;
     } else {
         for (register int i = 0; i < childs.count(); i++) {
              childs.at(i)->setIndex(i);
         }
     }
}

void MainWindow::setVisibleDocks(bool visible) {
     if (childs.count() == 0) {
         ui->dockWidget_Input->setVisible(visible);
         ui->dockWidget_toolButtons->setVisible(visible);
         ui->dockWidget_History->setVisible(visible);
     }
}

void MainWindow::setVisibleMdiArea(bool visible) {
     if (childs.count() == 0) {
         ui->mdiArea->setVisible(visible);
     }
}

void MainWindow::setVisibleTabWidget(bool visible) {
    if (childs.count() == 0) {
        ui->tabWidget->clear();
        ui->tabWidget->setVisible(visible);
    }
}

void MainWindow::updateActionsVisible(bool visible) {
     if (visible == true && ui->tool_Bar->actions().count() == 10) {
         ui->action_Undo->setVisible(true);
         ui->action_Redo->setVisible(true);
         ui->action_Undo->setEnabled(false);
         ui->action_Redo->setEnabled(false);
         ui->tool_Bar->addSeparator();
         ui->tool_Bar->addAction(ui->action_Zoom_In);
         ui->tool_Bar->addAction(ui->action_Zoom_Out);
     } else if (visible == false && ui->tool_Bar->actions().count() == 13) {
         if (childs.count() == 0) {
             ui->tool_Bar->clear();
             ui->action_Undo->setVisible(false);
             ui->action_Redo->setVisible(false);
             startToolBar();
         }
     }
}

void MainWindow::updateActionsEnabled(bool enabled) {
     ui->action_Save->setEnabled(enabled);
     ui->action_Save_As->setEnabled(enabled);
     ui->menu_Transaction->setEnabled(enabled);
     ui->action_Commit->setEnabled(enabled);
     ui->action_RollBack->setEnabled(enabled);
     ui->action_Print->setEnabled(enabled);
     ui->action_Normal->setEnabled(enabled);
     ui->action_Red_Black->setEnabled(enabled);
     ui->action_AVL->setEnabled(enabled);
     ui->action_Zoom_In->setEnabled(enabled);
     ui->action_Zoom_Out->setEnabled(enabled);
     ui->toolButton_Edge->setEnabled(enabled);
     ui->toolButton_Left_rotation->setEnabled(enabled);
     ui->toolButton_Right_rotation->setEnabled(enabled);
     ui->toolButton_Right_rotation->setEnabled(enabled);
     ui->toolButton_Balance->setEnabled(enabled);
     ui->pushButton_Delete->setEnabled(enabled);
     ui->pushButton_Search->setEnabled(enabled);
     updateEditActionsEnabled();
}

void MainWindow::updateEditActionsEnabled() {
    if (child != NULL && childs.count() > 0) {
        if (child->isEmpty() == false)
            ui->action_Select_All->setEnabled(true);
        else
            ui->action_Select_All->setEnabled(false);
        ui->action_Paste->setEnabled(clipboard_flag);
        TreeGraph *tree = child->getTree();
        if (tree != NULL && tree->getSelectedNodesCount() > 0) {
            ui->action_Copy->setEnabled(selection_flag);
            ui->action_Cut->setEnabled(selection_flag);
        } else {
            ui->action_Copy->setEnabled(false);
            ui->action_Cut->setEnabled(false);
        }
    } else {
        ui->action_Select_All->setEnabled(false);
        ui->action_Paste->setEnabled(false);
        ui->action_Copy->setEnabled(false);
        ui->action_Cut->setEnabled(false);
    }
    ui->action_Undo->setEnabled(undo_flag);
    ui->action_Redo->setEnabled(redo_flag);
}

void MainWindow::updateUndoActionEnabled(bool enabled) {
     ui->action_Undo->setEnabled(enabled);
     undo_flag = enabled;
}

void MainWindow::updateRedoActionEnabled(bool enabled) {
     ui->action_Redo->setEnabled(enabled);
     redo_flag = enabled;
}

void MainWindow::updateButtonsEnabled(bool enabled, bool flag) {
     ui->pushButton_Insert->setEnabled(enabled);
     ui->pushButton_Delete->setEnabled(flag);
     ui->pushButton_Search->setEnabled(flag);
}

void MainWindow::setTextForInput(char *str) {
     ui->lineEdit_value->setText(str);
}

void MainWindow::destroySplitter() {
     if (split != NULL && split->count() == 0) {
         delete split;
         split = NULL;
         child = NULL;
         mode = MainWindow::tabified;
     }
}

bool MainWindow::autoEdgeIsChecked() {
     return ui->toolButton_Edge->isChecked();
}

void MainWindow::setActiveBoxToChild(SubChild *child) {
     for (register int i = 0; i < childs.count(); i++) {
          if (childs.at(i) != child) {
              childs.at(i)->setCheckedBox(false);
          }
     }
     this->child = child;
}

void MainWindow::setMenuFromContext(QMenu &menu) {
     menu.addAction(ui->action_Copy);
     menu.addAction(ui->action_Cut);
     menu.addAction(ui->action_Paste);
}

void MainWindow::setSelectionFlag(bool selection) {
     selection_flag = selection;
     ui->action_Copy->setEnabled(selection);
     ui->action_Cut->setEnabled(selection);
}

void MainWindow::setSliderMaximum(int maximum) {
     ui->slider_History->setMaximum(maximum);
     ui->slider_History->setValue(maximum);
}

bool MainWindow::setMinimumSizeOfChilds() {
     int w, cw = 0, h, ch = 0;
     w = sizeFreeArea().width();
     h = sizeFreeArea().height();
     for (register int i = 0; i < childs.count(); i++) {
          cw += childs.at(i)->minimumWidth()  +30;
          ch += childs.at(i)->minimumHeight() +30;
     }
     if (cw > w || ch > h) {
         if (mode == MainWindow::horizontal && cw > w) {
             resize(cw, height());
             setMinimumSize(cw, height());
             return true;
         } else if (mode == MainWindow::vertical && ch > h) {
             resize(width(), ch);
             setMinimumSize(width(), ch);
             return true;
         }
     }
     return false;
}

QString MainWindow::stripAllTagsOfHtml(QString src) {
     if (src.isEmpty() == true)
         return "";
     QString result;
     bool tag  = false;
     bool mark = false;
     register int count = src.count();
     for (register int i = 0; i < count; i++) {
          if (src.at(i) == '<') {
              tag = true;
          } else if (src.at(i) == '>') {
              tag = false;
          } else if (src.at(i) == '&') {
              mark  = true;
          } else if (src.at(i) == ';') {
              mark = false;
          } else {
              if (tag == false && mark == false) {
                  result.append(src.at(i));
              }
          }
     }
     return result;
}

QString MainWindow::delimitedByComma(QString src, int &size) {
     if (src.isEmpty() == true)
         return "";
     QString result;
     const QChar ch_neg = '-';
     int register count = src.count();
     size = 1;
     for (register int i = 0; i < count; i++) {
          if (src.at(i).isDigit() == true) {
              result.append(src.at(i));
          } else if (src.at(i) == ch_neg) {
              if (i < count -1)
                  if (src.at(i +1).isDigit() == true)
                      result.append(src.at(i));
          } else {
              if (src.at(i).isPrint() == true) {
                  if (result.count() > 0 && i < count -1) {
                      if (result.at(result.count() - 1) != ',') {
                          result.append(',');
                          size++;
                      }
                  }
              }
          }
     }
     return result;
}

QString *MainWindow::createArrayFromValues(QString src, int size) {
     register int j = 0, count = src.count();
     QString *result = new QString[size];
     for (register int i = 0; i < count; i++) {
          if (src.at(i) != ',') {
              result[j].append(src.at(i));
          } else {
              j++;
          }
     }
     return result;
}

bool MainWindow::checkValuesInClipboard(QString *string, int &size) {
     int pos = 0;
     for (register int i = 0; i < size; i++) {
          if (validator->validate(string[i], pos) == QValidator::Invalid) {
              for (register int j = i+1, k = i; k < size -1; j++, k++) {
                   if (string[k].isNull() == false && string[j].isNull() == false)
                       string[k] = string[j];
              }
              --i;
              --size;
          }
     }
     if (size > 0)
         return true;
     else
         return false;
}

void MainWindow::updateGraphicsView(SubChild *child, TreeGraph *tree, NodeGraph *node) {
     qApp->setOverrideCursor(Qt::WaitCursor);
     node->identifyNodesAll();
     tree->setRootNode(node);
     tree->setupTree(node);
     tree->checkCollides(node);
     tree->addNodesToGraph();
     child->appendTree(tree);
     child->getGraphicsView()->setScene(child->getTree());
     child->setSaved(false);
     qApp->restoreOverrideCursor();
}

void MainWindow::setToolButtons() {
     ui->toolButton_Normal->setDefaultAction(ui->action_Normal);
     ui->toolButton_RedBlack->setDefaultAction(ui->action_Red_Black);
     ui->toolButton_AVL->setDefaultAction(ui->action_AVL);
     ui->toolButton_Commit->setDefaultAction(ui->action_Commit);
     ui->toolButton_RollBack->setDefaultAction(ui->action_RollBack);
}

void MainWindow::createConnections() {
     connect(ui->dockWidget_Input, SIGNAL(topLevelChanged(bool)), this, SLOT(topLevelInput(bool)));
     connect(ui->dockWidget_Input, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(locationInput()));
     connect(ui->dockWidget_toolButtons, SIGNAL(topLevelChanged(bool)), this, SLOT(topLevelToolButtons(bool)));
     connect(ui->dockWidget_toolButtons, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(locationToolButtons(Qt::DockWidgetArea)));
     connect(ui->dockWidget_History, SIGNAL(topLevelChanged(bool)), this, SLOT(topLevelHistory(bool)));
     connect(ui->dockWidget_History, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(locationHistory(Qt::DockWidgetArea)));
     connect(ui->action_New, SIGNAL(triggered()), this, SLOT(New()));
     connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(Open()));
     connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(Save()));
     connect(ui->action_Save_As, SIGNAL(triggered()), this, SLOT(SaveAs()));
     connect(ui->menu_Window, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));
     connect(ui->action_All_Windows_Docked, SIGNAL(triggered()), this, SLOT(setDocked()));
     connect(ui->action_Exit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
     connect(ui->pushButton_Insert, SIGNAL (released()), this, SLOT (Insert()));
     connect(ui->pushButton_Delete, SIGNAL (released()), this, SLOT (Delete()));
     connect(ui->pushButton_Search, SIGNAL (released()), this, SLOT (Search()));
     connect(mapper, SIGNAL(mapped(QWidget *)), this, SLOT(setActiveSubWindow(QWidget *)));
     connect(clipboard, SIGNAL(dataChanged ()), this, SLOT(getClipBoardData()));
     connect(ui->action_Select_All, SIGNAL(triggered()), this, SLOT(selectAll()));
     connect(ui->action_Undo, SIGNAL(triggered()), this, SLOT(Undo()));
     connect(ui->action_Redo, SIGNAL(triggered()), this, SLOT(Redo()));
     connect(ui->action_Copy, SIGNAL(triggered()), this, SLOT(Copy()));
     connect(ui->action_Cut, SIGNAL(triggered()), this, SLOT(Cut()));
     connect(ui->action_Paste, SIGNAL(triggered()), this, SLOT(Paste()));
     connect(ui->toolButton_Left_rotation, SIGNAL(pressed()), this, SLOT(rotateLeft()));
     connect(ui->toolButton_Right_rotation, SIGNAL(pressed()), this, SLOT(rotateRight()));
     connect(ui->toolButton_Balance, SIGNAL(pressed()), this, SLOT(Balance()));
     connect(ui->action_Commit, SIGNAL(triggered()), this, SLOT(Commit()));
     connect(ui->action_RollBack, SIGNAL(triggered()), this, SLOT(RollBack()));
     connect(ui->action_Zoom_In, SIGNAL(triggered()), this, SLOT(ZoomIn()));
     connect(ui->action_Zoom_Out, SIGNAL(triggered()), this, SLOT(ZoomOut()));
     connect(ui->action_Normal, SIGNAL(triggered()), this, SLOT(Normal()));
     connect(ui->action_Red_Black, SIGNAL(triggered()), this, SLOT(RedBlack()));
     connect(ui->action_AVL, SIGNAL(triggered()), this, SLOT(AVL()));
     connect(ui->slider_History, SIGNAL(valueChanged(int)), this, SLOT(setSliderValue(int)));
     connectWindowMenu(false);
}

void MainWindow::destroyConnections() {
     disconnect(ui->dockWidget_Input, SIGNAL(topLevelChanged(bool)));
     disconnect(ui->dockWidget_Input, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)));
     disconnect(ui->dockWidget_toolButtons, SIGNAL(topLevelChanged(bool)));
     disconnect(ui->dockWidget_toolButtons, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)));
     disconnect(ui->dockWidget_History, SIGNAL(topLevelChanged(bool)));
     disconnect(ui->dockWidget_History, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)));
     disconnect(ui->action_New, SIGNAL(triggered()));
     disconnect(ui->action_Open, SIGNAL(triggered()));
     disconnect(ui->action_Save, SIGNAL(triggered()));
     disconnect(ui->action_Save_As, SIGNAL(triggered()));
     disconnect(ui->menu_Window, SIGNAL(aboutToShow()));
     disconnect(ui->action_All_Windows_Docked, SIGNAL(triggered()));
     disconnect(ui->action_Exit, SIGNAL(triggered()));
     disconnect(ui->pushButton_Insert, SIGNAL (released()));
     disconnect(ui->pushButton_Delete, SIGNAL (released()));
     disconnect(ui->pushButton_Search, SIGNAL (released()));
     disconnect(mapper, SIGNAL(mapped(QWidget *)));
     disconnect(clipboard, SIGNAL(dataChanged ()));
     disconnect(ui->action_Select_All, SIGNAL(triggered()));
     disconnect(ui->action_Copy, SIGNAL(triggered()));
     disconnect(ui->action_Cut, SIGNAL(triggered()));
     disconnect(ui->action_Paste, SIGNAL(triggered()));
     disconnect(ui->toolButton_Left_rotation, SIGNAL(pressed()));
     disconnect(ui->toolButton_Right_rotation, SIGNAL(pressed()));
     disconnect(ui->toolButton_Balance, SIGNAL(pressed()));
     disconnect(ui->action_Commit, SIGNAL(triggered()));
     disconnect(ui->action_RollBack, SIGNAL(triggered()));
     disconnect(ui->action_Zoom_In, SIGNAL(triggered()));
     disconnect(ui->action_Zoom_Out, SIGNAL(triggered()));
     disconnect(ui->action_Normal, SIGNAL(triggered()));
     disconnect(ui->action_Red_Black, SIGNAL(triggered()));
     disconnect(ui->action_AVL, SIGNAL(triggered()));
     disconnect(ui->slider_History, SIGNAL(valueChanged(int)));
     disconnectWindowMenu(ui->action_All_Windows_Docked->isChecked());
}

void MainWindow::connectWindowMenu(bool flag) {
     if (flag == true) {
         connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeOneTab(int)), Qt::UniqueConnection);
         connect(ui->action_Close, SIGNAL(triggered()), this, SLOT(closeOneTab()), Qt::UniqueConnection);
         connect(ui->action_Close_All, SIGNAL(triggered()), this, SLOT(closeAllTabs()), Qt::UniqueConnection);
         connect(ui->action_Split_horizontal, SIGNAL(triggered()), this, SLOT(splitHorizontal()), Qt::UniqueConnection);
         connect(ui->action_Split_vertical, SIGNAL(triggered()), this, SLOT(splitVertical()), Qt::UniqueConnection);
         connect(ui->action_Set_Tabified, SIGNAL(triggered()), this, SLOT(setTabified()), Qt::UniqueConnection);
     } else {
         connect(ui->action_Close, SIGNAL(triggered()), this, SLOT(closeOneMdi()), Qt::UniqueConnection);
         connect(ui->action_Close_All, SIGNAL(triggered()), this, SLOT(closeAllMdis()), Qt::UniqueConnection);
         connect(ui->action_Tile, SIGNAL(triggered()), ui->mdiArea, SLOT(tileSubWindows()), Qt::UniqueConnection);
         connect(ui->action_Cascade, SIGNAL(triggered()), this, SLOT(Cascade()), Qt::UniqueConnection);
         connect(ui->action_Next, SIGNAL(triggered()), ui->mdiArea, SLOT(activateNextSubWindow()), Qt::UniqueConnection);
         connect(ui->action_Previous, SIGNAL(triggered()), ui->mdiArea, SLOT(activatePreviousSubWindow()), Qt::UniqueConnection);
     }
}

void MainWindow::disconnectWindowMenu(bool flag) {
     if (flag == true) {
         disconnect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(closeOneTab(int)));
         disconnect(ui->action_Close, SIGNAL(triggered()), this, SLOT(closeOneTab()));
         disconnect(ui->action_Close_All, SIGNAL(triggered()), this, SLOT(closeAllTabs()));
         disconnect(ui->action_Split_horizontal, SIGNAL(triggered()), this, SLOT(splitHorizontal()));
         disconnect(ui->action_Split_vertical, SIGNAL(triggered()), this, SLOT(splitVertical()));
         disconnect(ui->action_Set_Tabified, SIGNAL(triggered()), this, SLOT(setTabified()));
     } else {
         disconnect(ui->action_Close, SIGNAL(triggered()), this, SLOT(closeOneMdi()));
         disconnect(ui->action_Close_All, SIGNAL(triggered()), this, SLOT(closeAllMdis()));
         disconnect(ui->action_Tile, SIGNAL(triggered()), ui->mdiArea, SLOT(tileSubWindows()));
         disconnect(ui->action_Cascade, SIGNAL(triggered()), this, SLOT(Cascade()));
         disconnect(ui->action_Next, SIGNAL(triggered()), ui->mdiArea, SLOT(activateNextSubWindow()));
         disconnect(ui->action_Previous, SIGNAL(triggered()), ui->mdiArea, SLOT(activatePreviousSubWindow()));
     }
}

void MainWindow::alertOffStatusBar() {
     ui->status_Bar->setPalette(palette);
     ui->status_Bar->setFont(font);
     disconnect(ui->status_Bar, SIGNAL(messageChanged(QString)));
}

void MainWindow::getClipBoardData() {
     int count;
     QString data;
     QString text;
     const QMimeData *mime = clipboard->mimeData();
     if (mime->hasHtml()) {
         data = stripAllTagsOfHtml(mime->html());
         text = delimitedByComma(data, count);
     } else if (mime->hasText()) {
         text = delimitedByComma(mime->text(), count);
     } else {
         ui->action_Paste->setEnabled(false);
         clipboard_flag = false;
         return;
     }
     clipboard_values = createArrayFromValues(text, count);
     bool result = checkValuesInClipboard(clipboard_values, count);
     if (result == true) {
         if (childs.count() > 0)
             ui->action_Paste->setEnabled(true);
         else
             ui->action_Paste->setEnabled(false);
         clipboard_count = count;
         clipboard_flag  = true;
     } else {
         ui->action_Paste->setEnabled(false);
         clipboard_count = 0;
         clipboard_flag  = false;
     }
}

void MainWindow::setClipBoardData() {
     SubChild *s_child = getSubChild();
     QString q_str1;
     const int size = 7;
     int *values = s_child->getTree()->getSelectedNodes();
     int  count  = s_child->getTree()->getSelectedNodesCount();
     char c_str1[size];
     char c_str2[count][size];
     std::string c_str3;
     c_str3.reserve(count * size);
     for (register int i = 0; i < count; i++) {
          sprintf(c_str2[i], "%s,", itoa(values[i], c_str1, 10));
          c_str3.append(c_str2[i]);
          q_str1 = q_str1.fromStdString(c_str3);
     }
     clipboard->setText(q_str1);
}

void MainWindow::setSliderValue(int value) {
     SubChild  *s_child = getSubChild();
     if (s_child == NULL)
         return;
     if (value >= s_child->getTreeCount())
         return;
     TreeGraph *v_tree  = s_child->getTreeAt(value);
     s_child->getGraphicsView()->setScene(v_tree);
}

void MainWindow::alertOnStatusBar(const QString &message) {
     QPalette palette;
     QFont    font;
     palette.setColor(QPalette::Window, QColor(127, 0, 0));
     palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
     font.setFamily("Verdana");
     font.setBold(true);
     ui->status_Bar->setPalette(palette);
     ui->status_Bar->setFont(font);
     ui->status_Bar->showMessage(message, 2750);
     Beep(125, 260);
     QTimer::singleShot(2750, this, SLOT(alertOffStatusBar()));
     connect(ui->status_Bar, SIGNAL(messageChanged(QString)), this, SLOT(alertOffStatusBar()));
}

bool MainWindow::keyPressedForChild(QKeyEvent *keyEvent) {
    if (ui->mdiArea->isVisible() == true) {
        if (keyEvent->key() == Qt::Key_Tab)
            ui->mdiArea->activateNextSubWindow();
        else if (keyEvent->key() == Qt::Key_Backspace || keyEvent->key() == Qt::Key_Escape)
            ui->lineEdit_value->setFocus();
        return true;
    } else if (ui->tabWidget->isVisible() == true) {
        if (keyEvent->key() == Qt::Key_Tab) {
            if (ui->tabWidget->currentIndex() < ui->tabWidget->count() -1) {
                int i = ui->tabWidget->indexOf(ui->tabWidget->currentWidget()) ;
                ui->tabWidget->setCurrentWidget(childs.at(i +1));
            } else {
                ui->tabWidget->setCurrentWidget(childs.at(0));
            }
            return true;
        } else if (keyEvent->key() == Qt::Key_Backspace || keyEvent->key() == Qt::Key_Escape) {
            ui->lineEdit_value->setFocus();
            return true;
        }
    }
    return false;
}

bool MainWindow::keyPressedForInput(QKeyEvent *keyEvent) {
     if (keyEvent->text().isEmpty() == false) {
         int pos = 0;
         QChar ch = keyEvent->text().at(pos);
         QString txt = ui->lineEdit_value->text();
         if (ui->lineEdit_value->selectedText().isEmpty() == false)
             txt.remove(ui->lineEdit_value->cursorPosition(), ui->lineEdit_value->selectedText().count());
         txt.insert(ui->lineEdit_value->cursorPosition(), ch);
         if (ch.isPrint() == true) {
             if (ui->lineEdit_value->validator()->validate(txt, pos) != QValidator::Invalid) {
                 ui->lineEdit_value->setText(txt);
                 return true;
             } else {
                 bool flag = ui->pushButton_Delete->isEnabled();
                 updateButtonsEnabled(false);
                 alertOnStatusBar(tr("Cannot accept this character!"));
                 updateButtonsEnabled(true, flag);
             }
         } else if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
             if (ui->lineEdit_value->text().isEmpty() == false) {
                 emit ui->pushButton_Insert->click();
                 ui->pushButton_Insert->setFocus();
                 return true;
             }
         }
     }
     return false;
}

bool MainWindow::keyPressedForBox(QKeyEvent *keyEvent, QObject *object) {
     SubChild *s_child = qobject_cast <SubChild *> (object->parent());
     if (keyEvent->key() == Qt::Key_Tab) {
        int index = s_child->getIndex();
        if (index < childs.count() -1) {
            s_child = childs.at(index +1);
        } else {
            s_child = childs.at(0);
        }
        s_child->getGroupBox()->setFocus();
        return true;
    } else if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
        if (s_child->getGroupBox()->isChecked() == true) {
            s_child->getGroupBox()->setChecked(false);
        } else {
            s_child->getGroupBox()->setChecked(true);
        }
    } else if (keyEvent->key() == Qt::Key_Escape || keyEvent->key() == Qt::Key_Backspace) {
        ui->lineEdit_value->setFocus();
    }
    return false;
}

bool MainWindow::keyPressedForButton(QString q_str, QKeyEvent *keyEvent) {
     if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
         if (q_str.compare("Insert") == 0)
             emit ui->pushButton_Insert->click();
         else if (q_str.compare("Delete") == 0)
             emit ui->pushButton_Delete->click();
         else if (q_str.compare("Search") == 0)
             emit ui->pushButton_Search->click();
         else
             return false;
     } else if (keyEvent->key() == Qt::Key_Escape || keyEvent->key() == Qt::Key_Backspace) {
         ui->lineEdit_value->setFocus();
     } else {
         return false;
     }
     return true;
}

bool MainWindow::keyPressedForTools(const QString &Name, QKeyEvent *keyEvent) {
    if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
        if (Name.compare("toolButton_Edge") == 0)
            emit ui->toolButton_Edge->click();
        else if (Name.compare("toolButton_Left_rotation") == 0)
            emit ui->toolButton_Left_rotation->pressed();
        else if (Name.compare("toolButton_Right_rotation") == 0)
            emit ui->toolButton_Right_rotation->pressed();
        else if (Name.compare("toolButton_Balance") == 0)
            emit ui->toolButton_Balance->pressed();
        else
            return false;
        return true;
    } else if (keyEvent->key() == Qt::Key_Escape || keyEvent->key() == Qt::Key_Backspace) {
        ui->lineEdit_value->setFocus();
    } else {
        return false;
    }
    return true;
}

bool MainWindow::focusInForInput() {
     ui->lineEdit_value->setPalette(palette);
     if (ui->lineEdit_value->text().compare("00000") == 0) {
         ui->lineEdit_value->setText("");
         return true;
     }
     return false;
}

bool MainWindow::focusOutForInput() {
     if (ui->lineEdit_value->text().isEmpty() == true) {
         QPalette palette;
         palette.setColor(QPalette::Text, QColor(127, 127, 127));
         ui->lineEdit_value->setPalette(palette);
         ui->lineEdit_value->setText("00000");
         return true;
     }
     return false;
}

bool MainWindow::focusInForChild(QObject *object) {
     child = qobject_cast <SubChild *> (object);
     if (child == NULL)
         return false;
     if (child->isEmpty() == true || child->getTreeCount() < 2) {
         updateUndoActionEnabled(false);
         updateRedoActionEnabled(false);
     } else {
         updateUndoActionEnabled(true);
         if (child->getBackupTreeCount() > 0)
             updateRedoActionEnabled(true);
         else
             updateRedoActionEnabled(false);
     }
     return true;
}

bool MainWindow::focusOutForChild() {
     return false;
}

bool MainWindow::focusInForSlider() {
    if (child != NULL && child->isEmpty() == false) {
        setSliderMaximum(child->getTreeCount() -1);
        return true;
    }
    ui->slider_History->setMaximum(0);
    return false;
}

bool MainWindow::focusOutForSlider() {
     if (child != NULL && child->isEmpty() == false) {
         int count = child->getTreeCount();
         if (count > 0) {
             ui->slider_History->setValue(count -1);
             return true;
         }
     }
     return false;
}

bool MainWindow::paintForChild() {
     child = getSubChild();
     if (child != NULL && child->isEmpty() == false) {
         TreeGraph *tree = child->getTree();
         if (tree != NULL)
             updateMenuTypeChecked(tree->getTypeOfTree());
         updateActionsEnabled(true);
         return true;
     }
     updateActionsEnabled(false);
     return false;
}

bool MainWindow::MouseReleaseForView(QObject *object) {
     if (split != NULL && (mode == MainWindow::horizontal || mode == MainWindow::vertical)) {
         QGroupBox *box = qobject_cast <QGroupBox *> (object->parent());
         box->setChecked(true);
         return true;
     }
     return false;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
     if (event->type() == QEvent::KeyPress) {
         QKeyEvent *keyEvent = static_cast <QKeyEvent *> (event);
         if (object->objectName().toStdString().compare("SubChild") == 0) {
             return keyPressedForChild(keyEvent);
         } else if (object->objectName().toStdString().compare("lineEdit_value") == 0) {
             return keyPressedForInput(keyEvent);
         } else if (object->objectName().toStdString().compare("groupBox") == 0) {
             return keyPressedForBox(keyEvent, object);
         } else {
             QString q_str1(object->objectName().left(10));
             if (q_str1.toStdString().compare("pushButton") == 0) {
                 QString q_str2(object->objectName().right(6));
                 return keyPressedForButton(q_str2, keyEvent);
             } else if (q_str1.toStdString().compare("toolButton") == 0) {
                 return keyPressedForTools(object->objectName(), keyEvent);\
             }\
         }
     } else if (event->type() == QEvent::FocusIn) {
         if (object->objectName().toStdString().compare("SubChild") == 0) {
             return focusInForChild(object);
         } else if (object->objectName().toStdString().compare("lineEdit_value") == 0) {
             return focusInForInput();
         } else if  (object->objectName().toStdString().compare("slider_History") == 0) {
             return focusInForSlider();
         }
     } else if (event->type() == QEvent::FocusOut) {
         if (object->objectName().toStdString().compare("SubChild") == 0) {
             return focusOutForChild();
         } else if (object->objectName().toStdString().compare("lineEdit_value") == 0) {
             return focusOutForInput();
         } else if  (object->objectName().toStdString().compare("slider_History") == 0) {
             return focusOutForSlider();
         }
     } else if (event->type() == QEvent::Paint) {
         if (object->objectName().toStdString().compare("SubChild") == 0) {
             return paintForChild();
         }
     } else if (event->type() == QEvent::MouseButtonRelease) {
         if (object->objectName().toStdString().compare("graphicsView") == 0) {
             return MouseReleaseForView(object);
         }
     }
     return QWidget::eventFilter(object, event);
}

void MainWindow::topLevelInput(bool top) {
     setHtopLevel(ui->dockWidget_Input, top);
}

void MainWindow::topLevelToolButtons(bool top) {
     if (ui->dockWidget_toolButtons->width() != 80 && ui->dockWidget_toolButtons->height() != 400) {
         setHtopLevel(ui->dockWidget_toolButtons, top);
     } else {
         setVtopLevel(ui->dockWidget_toolButtons, top);
     }
}

void MainWindow::topLevelHistory(bool top) {
     if (ui->slider_History->orientation() == Qt::Horizontal) {
         setHtopLevel(ui->dockWidget_History, top);
     } else {
         setVtopLevel(ui->dockWidget_History, top);
     }
}

void MainWindow::locationInput() {
     widthToFitAll();
     heightToFitAll();
}

void MainWindow::locationToolButtons(Qt::DockWidgetArea area) {
     if (area == Qt::TopDockWidgetArea || area == Qt::BottomDockWidgetArea) {
         setHlocation(ui->dockWidget_toolButtons);
         ui->toolButton_Edge->setGeometry(10, 10, 30, 30);
         ui->toolButton_Left_rotation->setGeometry(50, 10, 30, 30);
         ui->toolButton_Right_rotation->setGeometry(90, 10, 30, 30);
         ui->toolButton_Balance->setGeometry(130, 10, 30, 30);
         ui->toolButton_Normal->setGeometry(180, 10, 30, 30);
         ui->toolButton_RedBlack->setGeometry(220, 10, 30, 30);
         ui->toolButton_AVL->setGeometry(260, 10, 30, 30);
         ui->toolButton_Commit->setGeometry(310, 10, 30, 30);
         ui->toolButton_RollBack->setGeometry(350, 10, 30, 30);
     } else {
         setVlocation(ui->dockWidget_toolButtons);
         ui->toolButton_Edge->setGeometry(25, 10, 30, 30);
         ui->toolButton_Left_rotation->setGeometry(25, 60, 30, 30);
         ui->toolButton_Right_rotation->setGeometry(25, 100, 30, 30);
         ui->toolButton_Balance->setGeometry(25, 140, 30, 30);
         ui->toolButton_Normal->setGeometry(25, 190, 30, 30);
         ui->toolButton_RedBlack->setGeometry(25, 230, 30, 30);
         ui->toolButton_AVL->setGeometry(25, 270, 30, 30);
         ui->toolButton_Commit->setGeometry(25, 320, 30, 30);
         ui->toolButton_RollBack->setGeometry(25, 360, 30, 30);
     }
     if (dockWidgetArea(ui->dockWidget_Input) == area && ui->dockWidget_Input->isFloating() == false) {
         ui->dockWidgetContents_Input->updateGeometry();
     }
     if (dockWidgetArea(ui->dockWidget_History) == area && ui->dockWidget_History->isFloating() == false) {
         ui->dockWidgetContents_History->updateGeometry();
     }
     ui->dockWidgetContents_toolButtons->updateGeometry();
     widthToFitAll();
     heightToFitAll();
}

void MainWindow::locationHistory(Qt::DockWidgetArea area) {
     if (area == Qt::TopDockWidgetArea || area == Qt::BottomDockWidgetArea) {
         setHlocation(ui->dockWidget_History);
         ui->slider_History->setOrientation(Qt::Horizontal);
         ui->slider_History->setGeometry(25, 20, 360, 19);
         ui->slider_History->setFixedWidth(360);
         ui->slider_History->setFixedHeight(22);
     } else {
         setVlocation(ui->dockWidget_History);
         ui->slider_History->setOrientation(Qt::Vertical);
         ui->slider_History->setGeometry(30, 20, 19, 360);
         ui->slider_History->setFixedWidth(22);
         ui->slider_History->setFixedHeight(360);
     }
     if (dockWidgetArea(ui->dockWidget_Input) == area && ui->dockWidget_Input->isFloating() == false) {
         ui->dockWidgetContents_Input->updateGeometry();
     }
     if (dockWidgetArea(ui->dockWidget_toolButtons) == area && ui->dockWidget_toolButtons->isFloating() == false) {
         ui->dockWidgetContents_toolButtons->updateGeometry();
     }
     ui->dockWidgetContents_History->updateGeometry();
     widthToFitAll();
     heightToFitAll();
}

SubChild *MainWindow::getSubChild() {
    if (ui->mdiArea->isVisible() == true)
        child = activeMdiChild();
    else
        child = activeTabChild();
    return child;
}

SubChild *MainWindow::addSubChild(QString title) {
     if (filesopen == MAX_FILES) {
         QMessageBox::critical(this, tr("BST Utility"), tr("Canot open more files...\n limit researched (%1) found!").arg(MAX_FILES));
         return NULL;
     }
     static int sequenceNumber = 1;
     if (title.isNull() == true)
         title = tr("untitled%1.bst").arg(sequenceNumber++);
     setVisibleDocks(true);
     updateMenuTypeChecked(0);
     childs.append(new SubChild(this));
     childs.last()->setIndex(childs.indexOf(childs.last()));
     childs.last()->setFileName(title);
     childs.last()->setWindowTitle(childs.last()->getShortFileName());
     if (ui->action_All_Windows_Docked->isChecked() == true) {
         ui->mdiArea->setVisible(false);
         if (mode == MainWindow::tabified) {
             ui->tabWidget->setVisible(true);
             ui->tabWidget->addTab(childs.last(), childs.last()->windowTitle());
             ui->tabWidget->setGeometry(1, 1, CHILD_SIZE, CHILD_SIZE);
             childs.last()->showBoxTitle(false);
             childs.last()->show();
         } else {
             childs.last()->showBoxTitle(true, childs.last()->windowTitle());
             childs.last()->getGroupBox()->setChecked(true);
             split->insertWidget(childs.count() -1, childs.last());
             split->widget(childs.count() -1)->setVisible(true);
             split->show();
             childs.last()->elidedBoxTitle();
             if (setMinimumSizeOfChilds() == false)
                 setMinimumSize(minimum);
         }
         childs.last()->setDocked(true);
         disconnectWindowMenu(false);
         connectWindowMenu(true);
     } else {
         ui->tabWidget->setVisible(false);
         ui->mdiArea->setVisible(true);
         ui->mdiArea->addSubWindow(childs.last());
         ui->mdiArea->subWindowList().last()->resize(CHILD_SIZE, CHILD_SIZE);
         childs.last()->setDocked(false);
         childs.last()->showBoxTitle(false);
         disconnectWindowMenu(true);
         connectWindowMenu(false);
         childs.last()->show();
     }
     filesopen++;
     updateActionsVisible(true);
     resizeEvent(NULL);
     child = childs.last();
     return child;
}

bool MainWindow::loadFile(const QString &fileName, int *array, int &size) {
     bool flag;
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         flag = false;
     } else {
         QTextStream *datafile = new QTextStream(&file);
         register int index = 0;
         if (datafile->readLine().toStdString() == "!BST") {
             int value;
             while (!datafile->atEnd()) {
                    value = std::atoi(datafile->readLine().toStdString().c_str());
                    if (value < -32767 || value > 32767) {
                        QMessageBox::critical(this, tr("BST Utility"), tr("Canot read a value out of range in Binary Search Tree file!"));
                        flag = false;
                        break;
                    } else {
                        if (index >= 99) {
                            QMessageBox::critical(this, tr("BST Utility"), tr("Your file is too large to be opened for this program!"));
                            flag = false;
                            break;
                        } else {
                           array[index] = value;
                           index++;
                           flag = true;
                        }
                    }
             }
         } else {
             QMessageBox::critical(this, tr("BST Utility"), tr("This is not a Binary Search Tree file!"));
             flag = false;
         }
         file.close();
         size = index;
     }
     return flag;
}

QString MainWindow::saveFile() {
     SubChild *s_child = child;
     qApp->setOverrideCursor(Qt::WaitCursor);
     QString filename = QFileDialog::getSaveFileName(this, tr("Save As Binary Search Tree"), child->getFileName(), tr("Binary Search Tree files (*.bst);;All files (*.*)"));
     qApp->restoreOverrideCursor();
     child = s_child;
     return  filename;
}

void MainWindow::New() {
     if (addSubChild() != NULL) {
         child->setUntitled(true);
         child->setEmpty(true);
         child->setSaved(false);
         ui->lineEdit_value->setText("");
         ui->lineEdit_value->setFocus();
     }
}

void MainWindow::Open() {
     qApp->setOverrideCursor(Qt::WaitCursor);
     QString filename = QFileDialog::getOpenFileName(this, tr("Open Binary Search Tree"), QDir::currentPath(), tr("Binary Search Tree files (*.bst);;All files (*.*)"));
     int i, size = 100;
     int line[size];
     if (loadFile(filename, line, size) == true) {
         if (addSubChild(filename) != NULL) {
             for (i = 0; i < size; i++)
                 child->insertTree(line[i]);
             if (i > 0)
                 updateActionsEnabled(true);
             child->setSaved(true);
             child->setEmpty(false);
             child->setUntitled(false);
         }
     }
     qApp->restoreOverrideCursor();
}

void MainWindow::Save() {
    child = getSubChild();
    if (child->isUntitled() == true) {
        SaveAs();
    } else {
        QString filename = child->getFileName();
        if (filename.isNull() == false && filename.isEmpty() == false)
             child->save(false);
    }
}

void MainWindow::SaveAs() {
     child = getSubChild();
     QString filename = saveFile();
     if (filename.isNull() == false && filename.isEmpty() == false) {
         child->saveAs(filename, false);
     }
}

void MainWindow::Insert() {
     if (ui->lineEdit_value->text().isEmpty() == false && ui->lineEdit_value->text().compare("00000") != 0) {
         qApp->setOverrideCursor(Qt::WaitCursor);
         child = getSubChild();
         if (child->insertTree(atoi(ui->lineEdit_value->text().toStdString().c_str())) == true) {
             updateActionsEnabled(true);
             child->setEmpty(false);
             child->setSaved(false);
         } else {
             bool flag = ui->pushButton_Delete->isEnabled();
             updateButtonsEnabled(false);
             alertOnStatusBar(tr("This value already exist!"));
             updateButtonsEnabled(true, flag);
         }
         qApp->restoreOverrideCursor();
     }
}

void MainWindow::Delete() {
     if (ui->lineEdit_value->text().isEmpty() == false && ui->lineEdit_value->text().compare("00000") != 0) {
         qApp->setOverrideCursor(Qt::WaitCursor);
         child = getSubChild();
         if (child->deleteTree(atoi(ui->lineEdit_value->text().toStdString().c_str())) == true) {
             if (child->isEmpty() == true)
                 updateActionsEnabled(false);
         } else {
             displayAlertNotFound();
         }
         qApp->restoreOverrideCursor();
     }
}

void MainWindow::Search() {
     if (ui->lineEdit_value->text().isEmpty() == false && ui->lineEdit_value->text().compare("00000") != 0) {
         qApp->setOverrideCursor(Qt::WaitCursor);
         child = getSubChild();
         if (child->searchTree(atoi(ui->lineEdit_value->text().toStdString().c_str())) == true) {
             Beep(870,220);
             ui->status_Bar->showMessage(tr("The value was found on this tree"));
         } else {
             displayAlertNotFound();
         }
         qApp->restoreOverrideCursor();
     }
}

void MainWindow::Cascade() {
     ui->mdiArea->cascadeSubWindows();
     for (register int i = 0; i < childs.count(); i++) {
          ui->mdiArea->subWindowList().at(i)->resize(CHILD_SIZE, CHILD_SIZE);
     }
}

void MainWindow::selectAll() {
     if (child != NULL) {
         TreeGraph *tree = child->getTree();
         if (tree != NULL) {
             tree->selectNodesAll(tree->getRootNode());
             tree->invertColorAll(tree->getRootNode());
             tree->setSelectedNodes(tree->getRootNode());
             if (tree->getSelectedNodesCount() > 0)
                 setSelectionFlag(true);
             else
                 setSelectionFlag(false);
         }
     }
}

void MainWindow::Cut() {
     SubChild *s_child = getSubChild();
     TreeGraph *tree = s_child->getTree();
     if (tree == NULL)
         return;
     qApp->setOverrideCursor(Qt::WaitCursor);
     setClipBoardData();
     int count   = tree->getSelectedNodesCount();
     int *values = tree->getSelectedNodes();
     for (register int i = 0; i < count; i++)
          s_child->deleteTree(values[i]);
     if (s_child->isEmpty() == true)
         updateActionsEnabled(false);
     else
         s_child->setSaved(false);
     qApp->restoreOverrideCursor();
}

void MainWindow::Copy() {
     if (getSubChild()->getTree() != NULL)
         setClipBoardData();

}

void MainWindow::Paste() {
     child = getSubChild();
     qApp->setOverrideCursor(Qt::WaitCursor);
     for (register int i = 0; i < clipboard_count; i++) {
          if (child->insertTree(atoi(clipboard_values[i].toStdString().c_str())) == true) {
              updateActionsEnabled(true);
              child->setEmpty(false);
              child->setSaved(false);
          }
     }
     qApp->restoreOverrideCursor();
}

void MainWindow::rotateLeft() {
     setRotation(-1);
}

void MainWindow::rotateRight() {
     setRotation(1);
}

void MainWindow::Balance() {
     SubChild *s_child = getSubChild();
     if (s_child == NULL || s_child->isEmpty() == true)
         return;
     TreeGraph *tree = s_child->getTree();
     if (tree != NULL) {
         int size_of_tree = tree->sizeOfTree();
         if (size_of_tree == 1)
             return;
         QVector <int> *vt = new QVector <int>;
         QList <QString> lst;
         vt->reserve(size_of_tree);
         tree->valuesInOrder(lst);
         balanceToVector(lst, *vt, 0, size_of_tree);
         TreeGraph *newTree = new TreeGraph(vt->at(0), tree, s_child->getGraphicsView(), s_child);
         qApp->setOverrideCursor(Qt::WaitCursor);
         for (int i = 1; i < size_of_tree; i++) {
              newTree->addNode(vt->at(i));
         }
         qApp->restoreOverrideCursor();
         delete(vt);
         NodeGraph *newRoot = newTree->getRootNode();
         if (newRoot->getLine() != NULL) {
             newRoot->destroyLine();
         }
         updateGraphicsView(s_child, newTree, newRoot);
         s_child->clearBackupTree();
     }
}

void MainWindow::Undo() {
     SubChild *s_child = getSubChild();
     if (s_child != NULL) {
         if (s_child->isEmpty() == false) {
             TreeGraph *tree = s_child->getLastTree();
             if (tree != NULL) {
                 if (tree == s_child->getTree()) {
                     s_child->appendBackupTree(tree);
                     s_child->removeLastTree();
                     s_child->setTree(s_child->getLastTree());
                     s_child->getGraphicsView()->setScene(s_child->getTree());
                     setSliderMaximum(s_child->getTreeCount() -1);
                     if (s_child->getTreeCount() < 2) {
                         updateUndoActionEnabled(false);
                     }
                     updateRedoActionEnabled(true);
                 }
             }
         }
     }
}

void MainWindow::Redo() {
     SubChild *s_child = getSubChild();
     if (s_child != NULL) {
         if (s_child->isEmpty() == false) {
             TreeGraph *back = s_child->getLastBackupTree();
             if (back != NULL) {
                 s_child->appendTree(back);
                 s_child->removeLastBackupTree();
                 s_child->setTree(s_child->getLastTree());
                 s_child->getGraphicsView()->setScene(s_child->getTree());
                 setSliderMaximum(s_child->getTreeCount() -1);
                 if (s_child->getBackupTreeCount() < 1) {
                     updateRedoActionEnabled(false);
                 }
             }
         }
     }
}

void MainWindow::RollBack() {
     SubChild *s_child = getSubChild();
     if (s_child != NULL) {
         if (s_child->isEmpty() == false) {
             if (s_child->getBackupTreeCount() > 0) {
                 QMessageBox::StandardButton message;
                 message = QMessageBox::question(this, tr("BST Utility"), tr("This will delete all the history at this point.\n- Confirm?"), QMessageBox::Yes | QMessageBox::No);
                 if (message == QMessageBox::Yes)
                     s_child->clearBackupTree();
             }
         }
     }
}

void MainWindow::Commit() {
     SubChild *s_child = getSubChild();
     if (s_child != NULL) {
         if (s_child->isEmpty() == false) {
             TreeGraph *tree = s_child->getLastTree();
             if (tree != NULL && s_child->getTreeCount() > 1) {
                 QMessageBox::StandardButton message;
                 message = QMessageBox::question(this, tr("BST Utility"), tr("This will delete all the history before this point.\n- Confirm?"), QMessageBox::Yes | QMessageBox::No);
                 if (message == QMessageBox::Yes) {
                     s_child->clearTree();
                     s_child->appendTree(tree);
                     s_child->setTree(tree);
                     updateUndoActionEnabled(false);
                 }
             }
         }
     }

}

void MainWindow::ZoomIn() {
    SubChild *s_child = getSubChild();
    if (s_child != NULL) {
        if (s_child->isEmpty() == false) {
            QGraphicsView *view = s_child->getGraphicsView();
            view->scale(1.2, 1.2);
        }
    }
}

void MainWindow::ZoomOut() {
    SubChild *s_child = getSubChild();
    if (s_child != NULL) {
        if (s_child->isEmpty() == false) {
            QGraphicsView *view = s_child->getGraphicsView();
            view->scale(1 / 1.2, 1 / 1.2);
        }
    }
}
void MainWindow::Normal() {
     updateMenuTypeChecked(0);
     child = getSubChild();
     if (child != NULL) {
         TreeGraph *tree = child->getTree();
         if (tree != NULL) {
             tree->convertToNormal();
             tree->setTypeOfTree(TreeGraph::normal);
         }
     }

}

void MainWindow::RedBlack() {
     updateMenuTypeChecked(1);
     child = getSubChild();
     if (child != NULL) {
         TreeGraph *old_tree = child->getTree(), *new_tree = NULL;
         bool flag = false;
         if (old_tree != NULL) {
             new_tree = old_tree->convertToRedBlack(flag);
             if (new_tree != NULL) {
                 new_tree->setTypeOfTree(TreeGraph::red_black);

                 qDebug("- New Red-Black Tree at: %p", new_tree);

                 updateGraphicsView(child, new_tree, new_tree->getRootNode());
                 if (flag == true) {
                     QMessageBox::StandardButton message;
                     message = QMessageBox::critical(this, tr("BST Utility"), tr("This tree was corrupted!\nDo you want to retry the operation?"), QMessageBox::Retry | QMessageBox::Cancel);
                     if (message == QMessageBox::Retry)
                         emit ui->action_Red_Black->triggered(true);
                     else
                         emit ui->action_Undo->triggered(true);
                 }
                 return;
             }
         }
     }
     updateMenuTypeChecked(0);
     QMessageBox::critical(this, tr("BST Utility"), tr("Canot convert to Red Black Tree!"));
}

void MainWindow::AVL() {
     QMessageBox::information(this, tr("BST Utility"), tr("Not yet implemented!"));
}

void MainWindow::balanceToVector(QList <QString> list, QVector <int> &vector, int start, int end) {
     int middle;
     if (start < end) {
        middle = (start + end) / 2;
        vector.append(atoi(list.at(middle).toStdString().c_str()));
        balanceToVector(list, vector, start, middle);
        balanceToVector(list, vector, middle +1, end);
    }
}

void MainWindow::updateMenuTypeChecked(int index) {
     for (register int i = 0; i < ui->menu_Type->actions().count(); i++) {
         if (i == index)
             ui->menu_Type->actions().at(i)->setChecked(true);
         else
             ui->menu_Type->actions().at(i)->setChecked(false);
     }
}

void MainWindow::setDocked() {
     mode  = MainWindow::tabified;
     if (childs.count() > 0) {
         if (ui->action_All_Windows_Docked->isChecked() == true) {
             removeMdiChild();
             insertTabChild();
         } else {
             removeTabChild();
             insertMdiChild();
         }
         resizeEvent(NULL);
     }
     removeSplitter();
}

void MainWindow::displayAlertNotFound() {
     bool flag = ui->pushButton_Delete->isEnabled();
     updateButtonsEnabled(false);
     alertOnStatusBar(tr("This value not found!"));
     updateButtonsEnabled(true, flag);
}

void MainWindow::closeOneMdi() {
     for (register int i = 0; i < ui->mdiArea->subWindowList().count(); i++) {
          if (ui->mdiArea->subWindowList().at(i) == ui->mdiArea->activeSubWindow()) {
              closeOneMdi(i);
              break;
          }
     }
}

void MainWindow::closeOneTab() {
     if (mode == MainWindow::tabified) {
         closeOneTab(ui->tabWidget->currentIndex());
     } else {
          register int i = 0;
          if (child != NULL) {
              for (register int j = 0; j < childs.count(); j++) {
                   if (child == childs.at(j)) {
                       i = j;
                       break;
                   }
              }
          } else {
              i = childs.count() -1;
          }
          closeOneTab(i);
     }
}

bool MainWindow::closeOneMdi(int index) {
     return ui->mdiArea->subWindowList().at(index)->close() == true;
}

bool MainWindow::closeOneTab(int index) {
     if (mode == MainWindow::tabified) {
         if (ui->tabWidget->widget(index)->close() == true) {
             ui->tabWidget->removeTab(index);
             return true;
         }
     } else {
         if (split->widget(index)->close() == true) {
             if (split != NULL)
                 child = qobject_cast <SubChild *> (split->widget(split->count() -1));
             return true;
         }
     }
     return false;
}

bool MainWindow::closeAllMdis() {
    while (childs.isEmpty() == false) {
           if (closeOneMdi(0) == false)
               return false;
    }
    return true;
}

bool MainWindow::closeAllTabs() {
    register int count;
    if (mode == MainWindow::tabified)
        count = ui->tabWidget->count();
    else
        count = split->count();
    while (count > 0) {
           if (split != NULL  && (mode == MainWindow::horizontal || mode == MainWindow::vertical))
               child = qobject_cast <SubChild *> (split->widget(0));
           if (closeOneTab(0) == false)
               return false;
           count--;
    }
    return true;
}

void MainWindow::setTabified() {
     insertTabChild();
     removeSplitter();
     mode = MainWindow::tabified;
     resizeEvent(NULL);
}

void MainWindow::removeSplitter() {
    if (split != NULL) {
        for (register int i = 0; i < split->count(); i++)
             split->widget(i)->hide();
        if (setMinimumSizeOfChilds() == false)
            setMinimumSize(minimum);
        delete split;
        split = NULL;
        child = NULL;
    }
}

void MainWindow::splitHorizontal() {
     if (split == NULL) {
         split = new QSplitter(Qt::Horizontal, ui->central_Widget);
     } else {
         split->setOrientation(Qt::Horizontal);
     }
     mode = MainWindow::horizontal;
     createSplitter();
}

void MainWindow::splitVertical() {
     if (split == NULL) {
         split = new QSplitter(Qt::Vertical, ui->central_Widget);
     } else {
         split->setOrientation(Qt::Vertical);
     }
     mode = MainWindow::vertical;
     createSplitter();
}

void MainWindow::createSplitter() {
     ui->tabWidget->setVisible(false);
     QList <int> sizes;
     for (register int i = 0; i < childs.count(); i++) {
          split->insertWidget(i, childs.at(i));
          split->widget(i)->setVisible(true);
          childs.at(i)->showBoxTitle(true, childs.at(i)->windowTitle());
          if (split->orientation() == Qt::Horizontal)
              sizes.append(sizeFreeArea().width() / childs.count());
          else
              sizes.append(sizeFreeArea().height() / childs.count());
     }
     split->setSizes(sizes);
     ui->tabWidget->clear();
     split->setGeometry(1, 1, CHILD_SIZE, CHILD_SIZE);
     split->show();
     split->setFocus();
     if (setMinimumSizeOfChilds() == false)
         setMinimumSize(minimum);
     resizeEvent(NULL);
}

void MainWindow::insertMdiChild() {
      ui->mdiArea->setVisible(true);
      ui->mdiArea->subWindowList().clear();
      for (register int i = 0; i < childs.count(); i++) {
           ui->mdiArea->addSubWindow(childs.at(i));
           ui->mdiArea->subWindowList().at(i)->resize(CHILD_SIZE, CHILD_SIZE);
           childs.at(i)->showBoxTitle(false);
           childs.at(i)->setDocked(false);
           childs.at(i)->show();
           childs.at(i)->raise();
      }
      connectWindowMenu(false);
}

void MainWindow::insertTabChild() {
     ui->tabWidget->setVisible(true);
     ui->tabWidget->clear();
     for (register int i = 0; i < childs.count(); i++) {
          ui->tabWidget->addTab(childs.at(i), childs.at(i)->windowTitle());
          childs.at(i)->showBoxTitle(false);
          childs.at(i)->setDocked(true);
          childs.at(i)->show();
          childs.at(i)->setFocus();
     }
     ui->tabWidget->setGeometry(1, 1, CHILD_SIZE, CHILD_SIZE);
     connectWindowMenu(true);
}

void MainWindow::removeMdiChild() {
     ui->mdiArea->setVisible(false);
     for (register int i = childs.count() -1; i >= 0; i--) {
          ui->mdiArea->removeSubWindow(childs.at(i));
          ui->mdiArea->removeSubWindow(ui->mdiArea->subWindowList().at(i));
          childs.at(i)->hide();
     }
     disconnectWindowMenu(false);
}

void MainWindow::removeTabChild() {
     ui->tabWidget->setVisible(false);
     for (register int i = childs.count() -1; i >= 0; i--) {
          ui->tabWidget->removeTab(i);
          childs.at(i)->hide();
     }
     disconnectWindowMenu(true);
}

void MainWindow::setRotation(int dir) {
     SubChild *s_child = getSubChild();
     if (s_child == NULL || s_child->isEmpty() == true || s_child->getTree() == NULL)
         return;
     TreeGraph *curtree = new TreeGraph(s_child->getTree(), s_child);
     NodeGraph *oldroot = curtree->getRootNode();
     NodeGraph *newroot =  NULL;
     if (dir == -1) {
         newroot = oldroot->rotationLeft();
     } else if (dir == 1) {
         newroot = oldroot->rotationRight();
     }
     if (newroot != NULL) {
         if (newroot->getLine() != NULL)
             newroot->destroyLine();
         updateGraphicsView(s_child, curtree, newroot);
         s_child->clearBackupTree();
     } else {
         delete curtree;
     }
}

void MainWindow::updateWindowMenu() {
     bool flag;
     ui->menu_Window->clear();
     ui->menu_Window->addAction(ui->action_Close);
     ui->menu_Window->addAction(ui->action_Close_All);
     ui->menu_Window->addSeparator();
     if (ui->action_All_Windows_Docked->isChecked() == true) {
         ui->menu_Window->addAction(ui->action_Split_horizontal);
         ui->menu_Window->addAction(ui->action_Split_vertical);
         ui->menu_Window->addAction(ui->action_Set_Tabified);
         ui->menu_Window->addSeparator();
         ui->menu_Window->addAction(ui->action_All_Windows_Docked);
         ui->action_Split_horizontal->setVisible(true);
         ui->action_Split_vertical->setVisible(true);
         ui->action_Set_Tabified->setVisible(true);
         if (split != NULL && (mode == MainWindow::horizontal || mode == MainWindow::vertical))
             flag = split->count() > 0;
         else
             flag = ui->tabWidget->count() > 0;
         ui->action_Close->setEnabled(flag);
         ui->action_Close_All->setEnabled(flag);
         ui->action_Split_horizontal->setEnabled(flag);
         ui->action_Split_vertical->setEnabled(flag);
         ui->action_Set_Tabified->setEnabled(flag);
         if (mode  == MainWindow::tabified)
             ui->action_Set_Tabified->setEnabled(false);
         else if (mode  == MainWindow::horizontal)
             ui->action_Split_horizontal->setEnabled(false);
         else if (mode  == MainWindow::vertical)
             ui->action_Split_vertical->setEnabled(false);
     } else {
         ui->menu_Window->addAction(ui->action_Tile);
         ui->menu_Window->addAction(ui->action_Cascade);
         ui->menu_Window->addSeparator();
         ui->menu_Window->addAction(ui->action_Next);
         ui->menu_Window->addAction(ui->action_Previous);
         ui->menu_Window->addSeparator();
         ui->menu_Window->addAction(ui->action_All_Windows_Docked);
         QList <QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
         flag = (windows.isEmpty() == false);
         if (flag == true)
             ui->menu_Window->addSeparator();
         ui->action_Close->setEnabled(flag);
         ui->action_Close_All->setEnabled(flag);
         ui->action_Tile->setEnabled(flag);
         ui->action_Cascade->setEnabled(flag);
         ui->action_Next->setEnabled(flag);
         ui->action_Previous->setEnabled(flag);
         for (register int i = 0; i < windows.count(); ++i) {
              SubChild *child = qobject_cast <SubChild *> (windows.at(i)->widget());
              QString text = tr("%1 %2").arg(i + 1).arg(child->getShortFileName());
              QAction *action  = ui->menu_Window->addAction(text);
              action->setCheckable(true);
              action ->setChecked(child == activeMdiChild());
              connect(action, SIGNAL(triggered()), mapper, SLOT(map()));
              mapper->setMapping(action, windows.at(i));
         }
     }
}

void MainWindow::setActiveSubWindow(QWidget *window) {
    if (window == NULL)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast <QMdiSubWindow *> (window));
}

SubChild *MainWindow::activeMdiChild() {
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast <SubChild *> (activeSubWindow->widget());
    return NULL;
}

SubChild *MainWindow::activeTabChild() {
    if (ui->tabWidget->isVisible() == true) {
        return qobject_cast <SubChild *> (ui->tabWidget->currentWidget());
    } else {
        if (split != NULL) {
            if (child != NULL)
                return child;
            else
                return qobject_cast <SubChild *> (split->widget(split->count() -1));
        }
        return NULL;
    }
}

void MainWindow::setHtopLevel(QDockWidget *dock, bool top) {
    if (top == true) {
        dock->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        dock->setFixedWidth(400);
        dock->setFixedHeight(60);
    } else {
        dock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        dock->setMaximumWidth(QWIDGETSIZE_MAX);
        dock->setMinimumHeight(80);
    }
    resizeEvent(NULL);
}

void MainWindow::setVtopLevel(QDockWidget *dock, bool top) {
    if (top == true) {
        dock->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        dock->setFixedWidth(80);
        dock->setFixedHeight(400);
    } else {
        dock->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        dock->setMaximumWidth(80);
        dock->setMinimumHeight(400);
    }
    resizeEvent(NULL);
}

void MainWindow::setHlocation(QDockWidget *dock) {
     dock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
     dock->setFixedHeight(80);
     dock->setMinimumWidth(400);
     dock->setMaximumWidth(QWIDGETSIZE_MAX);
}

void MainWindow::setVlocation(QDockWidget *dock) {
    dock->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    dock->setFixedWidth(80);
    dock->setMinimumHeight(420);
}

void MainWindow::widthToFitAll() {
     int w = 0;
     if (ui->dockWidget_Input->isFloating() == false) {
         if (dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea) {
             w += ui->dockWidget_Input->minimumWidth();
             if (ui->dockWidget_toolButtons->isFloating() == false) {
                 if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea) {
                     w += ui->dockWidget_toolButtons->minimumWidth();
                     if (ui->dockWidget_History->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
                             w += ui->dockWidget_History->minimumWidth();
                         }
                     }
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
                     w += ui->dockWidget_toolButtons->minimumWidth();
                     if (ui->dockWidget_History->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea) {
                             w += ui->dockWidget_History->minimumWidth();
                         }
                     }
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) {
                     if (ui->dockWidget_History->isFloating() == false) {
                         w += ui->dockWidget_History->minimumWidth();
                     }
                 } else { // Tool Buttons at Left Dock Widget Area
                     if (ui->dockWidget_History->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
                             w += ui->dockWidget_History->minimumWidth();
                         } else if (dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) {
                             w += ui->dockWidget_toolButtons->minimumWidth();
                         }
                     }
                 }
             } else { // Tool Buttons is floating
                 if (ui->dockWidget_History->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
                         w += ui->dockWidget_History->minimumWidth();
                     }
                 }
             }
         } else { // Input at Bottom Dock Widget Area
             w += ui->dockWidget_Input->minimumWidth();
             if (ui->dockWidget_toolButtons->isFloating() == false) {
                 if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) {
                     w += ui->dockWidget_toolButtons->minimumWidth();
                     if (ui->dockWidget_History->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea) {
                             w += ui->dockWidget_History->minimumWidth();
                         }
                     }
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea) {
                     w += ui->dockWidget_toolButtons->minimumWidth();
                     if (ui->dockWidget_History->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) {
                             w += ui->dockWidget_History->minimumWidth();
                         }
                     }
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea) {
                     if (ui->dockWidget_History->isFloating() == false) {
                         w += ui->dockWidget_History->minimumWidth();
                     }
                 } else { // Tool Buttons at Right Dock Widget Area
                     if (ui->dockWidget_History->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea) {
                             w += ui->dockWidget_History->minimumWidth();
                         } else if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea) {
                             w += ui->dockWidget_toolButtons->minimumWidth();
                         }
                     }
                 }
             } else { // Tool Buttons is floating
                 if (ui->dockWidget_History->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea) {
                         w += ui->dockWidget_History->minimumWidth();
                     }
                 }
             }
         }
     } else { // Input is floating
         if (ui->dockWidget_toolButtons->isFloating() == false) {
             if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea) {
                 w += ui->dockWidget_toolButtons->minimumWidth();
                 if (ui->dockWidget_History->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
                         w += ui->dockWidget_History->minimumWidth();
                     }
                 }
             } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) {
                 w += ui->dockWidget_toolButtons->minimumWidth();
                 if (ui->dockWidget_History->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea) {
                         w += ui->dockWidget_History->minimumWidth();
                     }
                 }
             } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea) {
                 if (ui->dockWidget_History->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) {
                         w += ui->dockWidget_toolButtons->minimumWidth();
                         w += ui->dockWidget_History->minimumWidth();
                     }
                 }
             } else { // Tool Buttons at Right Dock Widget Area
                 if (ui->dockWidget_History->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea) {
                         w += ui->dockWidget_toolButtons->minimumWidth();
                         w += ui->dockWidget_History->minimumWidth();
                     }
                 }
             }
         }
     }
     if (w < 400) w = 400;
     if (width() < w) {
         resize(w, height());
     } else {
         resizeEvent(NULL);
     }
     setMinimumWidth(w);
     minimum = minimumSize();
     setMinimumSizeOfChilds();
}

void MainWindow::heightToFitAll() {
     int h = 33;
     if (ui->dockWidget_History->isFloating() == false) {
         if (dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
             h += ui->dockWidget_History->minimumHeight() +10;
             if (ui->dockWidget_toolButtons->isFloating() == false) {
                 if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
                     h += ui->dockWidget_toolButtons->minimumHeight() +25;
                     if (ui->dockWidget_Input->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea) {
                             h += ui->dockWidget_Input->minimumHeight() +5;
                         }
                     }
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) {
                     h += ui->dockWidget_toolButtons->minimumHeight() +25;
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea) {
                     if (ui->dockWidget_Input->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea) {
                             h += ui->dockWidget_Input->minimumHeight() +5;
                         }
                     }
                 } else { // Tool Buttons at Left Dock Widget Area
                     if (ui->dockWidget_Input->isFloating() == false) {
                         h += ui->dockWidget_Input->minimumHeight() +25;
                     }
                 }
             } else {  // Tool Buttons is floating
                 if (ui->dockWidget_Input->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea) {
                         h += ui->dockWidget_Input->minimumHeight() +20;
                     }
                 }
             }
         } else if (dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea) {
             h += ui->dockWidget_History->minimumHeight() +10;
             if (ui->dockWidget_toolButtons->isFloating() == false) {
                 if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea) {
                     h += ui->dockWidget_toolButtons->minimumHeight() +25;
                     if (ui->dockWidget_Input->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea) {
                             h += ui->dockWidget_Input->minimumHeight() +5;
                         }
                     }
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea) {
                     h += ui->dockWidget_toolButtons->minimumHeight() +25;
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) {
                     if (ui->dockWidget_Input->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea) {
                             h += ui->dockWidget_Input->minimumHeight() +5;
                         }
                     }
                 } else { // Tool Buttons at Right Dock Widget Area
                     if (ui->dockWidget_Input->isFloating() == false) {
                         h += ui->dockWidget_Input->minimumHeight() +30;
                     }
                 }
             } else {  // Tool Buttons is floating
                 if (ui->dockWidget_Input->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea) {
                         h += ui->dockWidget_Input->minimumHeight() +20;
                     }
                 }
             }
         } else if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea) {
             if (ui->dockWidget_toolButtons->isFloating() == false) {
                 if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea) {
                     h += ui->dockWidget_History->minimumHeight() +10;
                     h += ui->dockWidget_toolButtons->minimumHeight() +25;
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
                     h += ui->dockWidget_toolButtons->minimumHeight() +25;
                     if (ui->dockWidget_Input->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea) {
                             h += ui->dockWidget_Input->minimumHeight() +20;
                         }
                     }
                 }
             }
         } else { // History at Bottom Dock Widget Area
             if (ui->dockWidget_toolButtons->isFloating() == false) {
                 if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
                     h += ui->dockWidget_History->minimumHeight() +10;
                     h += ui->dockWidget_toolButtons->minimumHeight() +30;
                 } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea) {
                     h += ui->dockWidget_toolButtons->minimumHeight() +25;
                     if (ui->dockWidget_Input->isFloating() == false) {
                         if (dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea) {
                             h += ui->dockWidget_Input->minimumHeight() +20;
                         }
                     }
                 }
             }
         }
     } else { // History is floating
         if (ui->dockWidget_toolButtons->isFloating() == false) {
             if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea) {
                 h += ui->dockWidget_toolButtons->minimumHeight() +25;
                 if (ui->dockWidget_Input->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea) {
                         h += ui->dockWidget_Input->minimumHeight() +5;
                     }
                 }
             } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
                 h += ui->dockWidget_toolButtons->minimumHeight() +25;
                 if (ui->dockWidget_Input->isFloating() == false) {
                     if (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea) {
                         h += ui->dockWidget_Input->minimumHeight() +20;
                     }
                 }
             }
         }
     }
     if (h < 400) h = 400;
     if (height() < h) {
         resize(width(), h);
     } else {
         resizeEvent(NULL);
     }
     setMinimumHeight(h);
     minimum = minimumSize();
     setMinimumSizeOfChilds();
}

QSize MainWindow::sizeFreeArea() {
    int w = width(), h = height();
    if (ui->dockWidget_Input->isFloating() == false && ui->dockWidget_toolButtons->isFloating() == false && ui->dockWidget_History->isFloating() == false) {
        if ((dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea && dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) || (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea && dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea)) {
            h -= ui->dockWidget_Input->height();
            h -= ui->dockWidget_toolButtons->height();
            if (dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
                w -= ui->dockWidget_History->width();
            }
        } else if ((dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) || (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea)) {
            h -= ui->dockWidget_Input->height();
            h -= ui->dockWidget_History->height();
            if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea || dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
                w -= ui->dockWidget_toolButtons->width();
            }
        } else if ((dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) || (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea)) {
            h -= ui->dockWidget_toolButtons->height();
            h -= ui->dockWidget_History->height();
        } else {
            h -= ui->dockWidget_Input->height();
            if ((dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) || (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea)) {
                w -= ui->dockWidget_toolButtons->width();
                w -= ui->dockWidget_History->width();
            } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea || dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
                w -= ui->dockWidget_toolButtons->width();
            } else if (dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
                w -= ui->dockWidget_History->width();
            }
        }
    } else if (ui->dockWidget_Input->isFloating() == false && ui->dockWidget_toolButtons->isFloating() == false) {
        if ((dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea && dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) || (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea && dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea)) {
            h -= ui->dockWidget_Input->height();
            h -= ui->dockWidget_toolButtons->height();
        } else {
            h -= ui->dockWidget_Input->height();
            if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea || dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
                w -= ui->dockWidget_toolButtons->width();
            }
        }
    } else if (ui->dockWidget_Input->isFloating() == false && ui->dockWidget_History->isFloating() == false) {
        if ((dockWidgetArea(ui->dockWidget_Input) == Qt::TopDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) || (dockWidgetArea(ui->dockWidget_Input) == Qt::BottomDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea)) {
            h -= ui->dockWidget_Input->height();
            h -= ui->dockWidget_History->height();
        } else {
            h -= ui->dockWidget_Input->height();
            if (dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
                w -= ui->dockWidget_History->width();
            }
        }
    } else if (ui->dockWidget_toolButtons->isFloating() == false && ui->dockWidget_History->isFloating() == false) {
        if ((dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) || (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea)) {
            h -= ui->dockWidget_toolButtons->height();
            h -= ui->dockWidget_History->height();
        } else if ((dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) || (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea && dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea)) {
            w -= ui->dockWidget_toolButtons->width();
            w -= ui->dockWidget_History->width();
        } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::LeftDockWidgetArea || dockWidgetArea(ui->dockWidget_toolButtons) == Qt::RightDockWidgetArea) {
            w -= ui->dockWidget_toolButtons->width();
            if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) {
                h -= ui->dockWidget_History->height();
            }
        } else if (dockWidgetArea(ui->dockWidget_History) == Qt::LeftDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::RightDockWidgetArea) {
            w -= ui->dockWidget_History->width();
            if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) {
                h -= ui->dockWidget_toolButtons->height();
            }
        } else if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) {
            h -= ui->dockWidget_toolButtons->height();
        } else if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) {
            h -= ui->dockWidget_History->height();
        }
    } else if (ui->dockWidget_Input->isFloating() == false) {
        h -= ui->dockWidget_Input->height();
    } else if (ui->dockWidget_toolButtons->isFloating() == false) {
        if (dockWidgetArea(ui->dockWidget_toolButtons) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_toolButtons) == Qt::BottomDockWidgetArea) {
            h -= ui->dockWidget_toolButtons->height();
        } else {
            w -= ui->dockWidget_toolButtons->width();
        }
    } else if (ui->dockWidget_History->isFloating() == false) {
        if (dockWidgetArea(ui->dockWidget_History) == Qt::TopDockWidgetArea || dockWidgetArea(ui->dockWidget_History) == Qt::BottomDockWidgetArea) {
            h -= ui->dockWidget_History->height();
        } else {
            w -= ui->dockWidget_History->width();
        }
    }
    return QSize(w -20, h -82);
}

void MainWindow::readSettings() {
     QSettings settings("bstu.ini", QSettings::IniFormat);
     settings.beginGroup("MainWindow");
     if (settings.contains("state/window") == false){
         ui->dockWidget_Input->setGeometry(0, 33, 400, 80);
         ui->dockWidget_toolButtons->setGeometry(400, 33, 400, 80);
         ui->dockWidget_History->setGeometry(800, 33, 80, 400);
         setHlocation(ui->dockWidget_Input);
         setHlocation(ui->dockWidget_toolButtons);
         setVlocation(ui->dockWidget_History);
         return;
     }
     restoreState(settings.value("state/window").toByteArray());
     setMinimumSize(settings.value("minimum/size/window").toSize());
     resize(settings.value("size/window", QSize(minimumWidth(), minimumHeight())).toSize());
     move(settings.value("position/window", QPoint(minimumWidth() /2, minimumHeight() /2)).toPoint());
     settings.endGroup();
     settings.beginGroup("Input");
     ui->dockWidget_Input->setSizePolicy(static_cast <QSizePolicy::Policy> (settings.value("horizontal/policy/input").toInt()), static_cast <QSizePolicy::Policy> (settings.value("vertical/policy/input").toInt()));
     if (ui->dockWidget_Input->isFloating() == false) {
         ui->dockWidget_Input->setMinimumSize(settings.value("minimum/size/input").toSize());
         ui->dockWidget_Input->setMaximumSize(settings.value("maximum/size/input").toSize());
     } else {
         ui->dockWidget_Input->setFixedSize(settings.value("fixed/size/input").toSize());
     }
     settings.endGroup();
     settings.beginGroup("toolButtons");
     ui->toolButton_Edge->restoreGeometry(settings.value("geometry/tool/button/edge").toByteArray());
     ui->toolButton_Left_rotation->restoreGeometry(settings.value("geometry/tool/button/left").toByteArray());
     ui->toolButton_Right_rotation->restoreGeometry(settings.value("geometry/tool/button/right").toByteArray());
     ui->toolButton_Balance->restoreGeometry(settings.value("geometry/tool/button/balance").toByteArray());
     ui->toolButton_Normal->restoreGeometry(settings.value("geometry/tool/button/normal").toByteArray());
     ui->toolButton_RedBlack->restoreGeometry(settings.value("geometry/tool/button/redblack").toByteArray());
     ui->toolButton_AVL->restoreGeometry(settings.value("geometry/tool/button/avl").toByteArray());
     ui->toolButton_Commit->restoreGeometry(settings.value("geometry/tool/button/commit").toByteArray());
     ui->toolButton_RollBack->restoreGeometry(settings.value("geometry/tool/button/rollback").toByteArray());
     ui->dockWidget_toolButtons->setSizePolicy(static_cast <QSizePolicy::Policy> (settings.value("horizontal/policy/tool/buttons").toInt()), static_cast <QSizePolicy::Policy> (settings.value("vertical/policy/tool/buttons").toInt()));
     if (ui->dockWidget_toolButtons->isFloating() == false) {
         ui->dockWidget_toolButtons->setMinimumSize(settings.value("minimum/size/tool/buttons").toSize());
         ui->dockWidget_toolButtons->setMaximumSize(settings.value("maximum/size/tool/buttons").toSize());
     } else {
         ui->dockWidget_toolButtons->setFixedSize(settings.value("fixed/size/tool/buttons").toSize());
     }
     settings.endGroup();
     settings.beginGroup("History");
     ui->slider_History->setOrientation(static_cast <Qt::Orientation> (settings.value("orientation/slider/history").toInt()));
     ui->slider_History->restoreGeometry(settings.value("geometry/slider/history").toByteArray());
     ui->slider_History->setFixedSize(settings.value("fixed/size/slider/history").toSize());
     ui->dockWidget_History->setSizePolicy(static_cast <QSizePolicy::Policy> (settings.value("horizontal/policy/history").toInt()), static_cast <QSizePolicy::Policy> (settings.value("vertical/policy/history").toInt()));
     if (ui->dockWidget_History->isFloating() == false) {
         ui->dockWidget_History->setMinimumSize(settings.value("minimum/size/history").toSize());
         ui->dockWidget_History->setMaximumSize(settings.value("maximum/size/history").toSize());
     } else {
         ui->dockWidget_History->setFixedSize(settings.value("fixed/size/history").toSize());
     }
     settings.endGroup();
}

void MainWindow::writeSettings() {
     QSettings settings("bstu.ini", QSettings::IniFormat);
     settings.beginGroup("MainWindow");
     settings.setValue("state/window", saveState());
     settings.setValue("size/window", size());
     settings.setValue("position/window", pos());
     settings.setValue("minimum/size/window", minimumSize());
     settings.endGroup();
     settings.beginGroup("Input");
     settings.setValue("horizontal/policy/input", ui->dockWidget_Input->sizePolicy().horizontalPolicy());
     settings.setValue("vertical/policy/input", ui->dockWidget_Input->sizePolicy().verticalPolicy());
     settings.setValue("minimum/size/input", ui->dockWidget_Input->minimumSize());
     settings.setValue("maximum/size/input", ui->dockWidget_Input->maximumSize());
     settings.setValue("fixed/size/input", ui->dockWidget_Input->size());
     settings.endGroup();
     settings.beginGroup("toolButtons");
     settings.setValue("horizontal/policy/tool/buttons", ui->dockWidget_toolButtons->sizePolicy().horizontalPolicy());
     settings.setValue("vertical/policy/tool/buttons", ui->dockWidget_toolButtons->sizePolicy().verticalPolicy());
     settings.setValue("minimum/size/tool/buttons", ui->dockWidget_toolButtons->minimumSize());
     settings.setValue("maximum/size/tool/buttons", ui->dockWidget_toolButtons->maximumSize());
     settings.setValue("fixed/size/tool/buttons", ui->dockWidget_toolButtons->size());
     settings.setValue("geometry/tool/button/edge", ui->toolButton_Edge->saveGeometry());
     settings.setValue("geometry/tool/button/left", ui->toolButton_Left_rotation->saveGeometry());
     settings.setValue("geometry/tool/button/right", ui->toolButton_Right_rotation->saveGeometry());
     settings.setValue("geometry/tool/button/balance", ui->toolButton_Balance->saveGeometry());
     settings.setValue("geometry/tool/button/normal", ui->toolButton_Normal->saveGeometry());
     settings.setValue("geometry/tool/button/redblack", ui->toolButton_RedBlack->saveGeometry());
     settings.setValue("geometry/tool/button/avl", ui->toolButton_AVL->saveGeometry());
     settings.setValue("geometry/tool/button/commit", ui->toolButton_Commit->saveGeometry());
     settings.setValue("geometry/tool/button/rollback", ui->toolButton_RollBack->saveGeometry());
     settings.endGroup();
     settings.beginGroup("History");
     settings.setValue("horizontal/policy/history", ui->dockWidget_History->sizePolicy().horizontalPolicy());
     settings.setValue("vertical/policy/history", ui->dockWidget_History->sizePolicy().verticalPolicy());
     settings.setValue("minimum/size/history", ui->dockWidget_History->minimumSize());
     settings.setValue("maximum/size/history", ui->dockWidget_History->maximumSize());
     settings.setValue("fixed/size/history", ui->dockWidget_History->size());
     settings.setValue("orientation/slider/history", ui->slider_History->orientation());
     settings.setValue("geometry/slider/history", ui->slider_History->saveGeometry());
     settings.setValue("fixed/size/slider/history", ui->slider_History->size());
     settings.endGroup();
}
