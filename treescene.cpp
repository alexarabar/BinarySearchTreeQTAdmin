/****************************************************************************
** Binary Search Tree Utility QT-4 Version 1.00
** Author:  Alexandre A. Barbosa
** Created: Fev-14-2010
** Updated: Apr-04-2015
** Name: treescene.cpp
****************************************************************************/

#include <QtGui>
#include <QMenu>
#include <QList>
#include <QMessageBox>
//#include <QtDebug>
//#include <exception>
//#include <iostream>
#include "mainwindow.h"
#include "treescene.h"

//using namespace std;

// ******************************** TREE GRAPH SCENE (Base Class) ********************************* //

TreeGraphScene::TreeGraphScene(QGraphicsView *view, QWidget *parent): QGraphicsScene(parent), graph_view(view) {

    qDebug("- New Tree Graphic Scene at: %p", this);

     setItemIndexMethod(QGraphicsScene::NoIndex);
}

TreeGraphScene::TreeGraphScene(TreeGraphScene *source, QGraphicsView *view, QWidget *parent) : QGraphicsScene(parent), graph_view(view) {

    qDebug("- New Tree Graphic Scene at: %p\n\t- From Previous at: %p", this, source);

    setItemIndexMethod(QGraphicsScene::NoIndex);
}


TreeGraphScene::TreeGraphScene(TreeGraphScene *source, QWidget *parent): QGraphicsScene(parent) {

     qDebug("- Copy of Tree Graphic Scene at: %p\n\t- New Tree Graphic Scene at: %p", source, this);

     setItemIndexMethod(source->itemIndexMethod());
     length_of_node = source->getLengthOfNode();
     start_point    = source->getStartPoint();
     new_position   = source->getNewPosition();
     graph_view     = source->getGraphicsView();
}

TreeGraphScene::~TreeGraphScene() {

     qDebug("- Delete Tree Graphic Scene at %p", this);

}

void TreeGraphScene::setupScene(QPointF point) {

     qDebug("\t- Setup with point at: (%5.3f, %5.3f) in Tree Graphic Scene!",  point.x(), point.y());

     start_point = point;
     length_of_node = 40.0;
}

SubChild *TreeGraphScene::getSubChild() {

     qDebug("- Get Sub Child in Tree Graphic Scene!");

     if (parent() != NULL) {
         return qobject_cast <SubChild *> (parent());
     }
     qCritical("- ERROR: can not get a Sub Child in Tree Graphic Scene!");
     return NULL;
}


NodeTextItem *TreeGraphScene::getItemText(QPointF point) {

     qDebug("- Get Item Text with point at: (%5.3f, %5.3f) in Tree Graphic Scene!", point.x(), point.y());

     QTransform t;
     QGraphicsItem      *item = this->itemAt(point, t);
     NodeEllipseItem *ellipse;
     NodeTextItem       *text;
     if (!item || !item->isUnderMouse())
         return NULL;
     ellipse = qgraphicsitem_cast <NodeEllipseItem *> (item);
     if (ellipse) {
         text = qgraphicsitem_cast <NodeTextItem *> (ellipse->childItems().at(0));
         if (text && !text->text().isEmpty()) {
             return text;
         }
         return NULL;
     }
     text = qgraphicsitem_cast <NodeTextItem *> (item);
     if (text && !text->text().isEmpty())
         return text;
     return NULL;
}

NodeEllipseItem *TreeGraphScene::getItemEllipse(QPointF point, QString *value) {

     qDebug("- Get Item Ellipse with point at: (%5.3f, %5.3f) in Tree Graphic Scene!", point.x(), point.y());

     if (value)
         qDebug("\t- Value is: %s", value->toStdString().c_str());

     NodeTextItem  *text = getItemText(point);
     if (text) {
         if (value)
             (*value) = text->text();
         return qgraphicsitem_cast <NodeEllipseItem *> (text->parentItem());
     }
     return NULL;
}

NodeGraph *TreeGraphScene::getNodeItem(QPointF point) {

     qDebug("- Get Node Item with point at: (%5.3f, %5.3f) in Tree Graphic Scene!", point.x(), point.y());

     NodeEllipseItem *ellipse = getItemEllipse(point);
     if (ellipse)
         return qgraphicsitem_cast <NodeGraph *> (ellipse->parentItem());
     return NULL;
}

// ***************************** TREE GRAPH (Derived Class of Tree Graph SCene ) ***************************** //

TreeGraph::TreeGraph(int value, QGraphicsView *view, QWidget *parent): TreeGraphScene(view, parent) {

     qDebug("- New Tree Graphic at: %p, parent: %p", this, this->parent());

     rootNode = new NodeGraph(value, this);
     lastNode  = rootNode;
     setTypeOfTree(TreeGraphScene::normal);
}

TreeGraph::TreeGraph(int value, TreeGraph *source, QGraphicsView *view, QWidget *parent) : TreeGraphScene(source, view, parent) {

    qDebug("- New Tree Graphic at: %p\n\t- Source at %p", this, source);

    rootNode = new NodeGraph(value, this);
    lastNode  = rootNode;
    setTypeOfTree(source->getTypeOfTree());
}

TreeGraph::TreeGraph(TreeGraph *source, QWidget *parent): TreeGraphScene(source, parent) {

     qDebug("- Copy of Tree Graphic at: %p\n\t- New Tree Graphic at: %p", source, this);

     lastNode = copyNodes(source->getRootNode());
     rootNode = getRootOf(lastNode);
     setTypeOfTree(source->getTypeOfTree());
}

/*
TreeGraph::TreeGraph(QGraphicsView *view, QWidget *parent = NULL) : TreeGraphScene(view, parent) {
     rootNode = lastNode = NULL;
}
*/

TreeGraph::~TreeGraph() {

     qDebug("- Delete Tree Graphic at: %p\n\t- Root Node at: %p", this, rootNode);

     if (rootNode == NULL)
         return;
     rootNode->clearNodesAll();
     delete rootNode;
}
/*
NodeGraph *TreeGraph::hasParentNode(NodeGraph *curNode) {

     qDebug("- Has Parent Node in Tree Graphic!");

     return curNode->getParentNode();
}

NodeGraph *TreeGraph::hasLeftNode(NodeGraph *curNode) {

     qDebug("- Has Left Node in Tree Graphic!");

     return curNode->getLeftNode();
}

NodeGraph *TreeGraph::hasRightNode(NodeGraph *curNode) {

     qDebug("- Has Right Node in Tree Graphic!");

     return curNode->getRightNode();
}
*/
void TreeGraph::setupTree(NodeGraph *node) {

     qDebug("- Setup of Tree at: %p in Tree Graphic!\n\t- Setting Node at: %p", this, node);

     if (node == rootNode) {
         setupScene(QPointF(0.0, 0.0));
         selectedRect = addRect(0, 0, 0, 0, QPen(Qt::DotLine), QBrush(Qt::NoBrush));
     }
     node->setupNode();
     if (node->getLeftNode())
         setupTree(node->getLeftNode());
     if (node->getRightNode())
         setupTree(node->getRightNode());

     qDebug("- Setup of Tree finished in Tree Graphic!");

}

NodeGraph *TreeGraph::getRootOf(NodeGraph *node) {

     qDebug("- Get Root Of... in Tree Graphic!");

     NodeGraph *current = node;
     while (current->getParentNode() != NULL)
            current = current->getParentNode();
     return current;
}

NodeGraph *TreeGraph::copyNodes(NodeGraph *node, NodeGraph **parent) {

     qDebug("- Copy of Tree Graphic at: %p\n\t- Node at: %p\n\t- Parent Node at: %p", this, node, parent);

     NodeGraph *current = new NodeGraph(this, node, parent);
     if (node->getLeftNode() && node->getRightNode()) {
         current->setLeftNode(copyNodes(node->getLeftNode(), &current));
         current->setRightNode(copyNodes(node->getRightNode(), &current));
     } else if (node->getLeftNode()) {
         current->setLeftNode(copyNodes(node->getLeftNode(), &current));
     } else if (node->getRightNode()) {
         current->setRightNode(copyNodes(node->getRightNode(), &current));
     }
     return current;
}

bool TreeGraph::addNode(int value) {

     qDebug("- Add Node in Tree at: %p in Tree Graphic!", this);
     qDebug("\t- Value to be inserted is: %d", value);

     NodeGraph *root, *node = NULL;
     if (getTypeOfTree() == TreeGraphScene::normal) {
         node = rootNode->insertNode(value, this, rootNode);
     } else {
         if (getTypeOfTree() == TreeGraphScene::red_black) {
             root = rootNode->insertNodeRedBlack(value, this, rootNode);
         } else if (getTypeOfTree() == TreeGraphScene::avl) {
             root = rootNode->insertNodeAVL(value, this, rootNode);
         }
         node = lastNode;
         rootNode = root;
     }
     if (node != NULL) {
         //lastNode = node;
         sceneRect().setRect((sceneRect().x() - 5), (sceneRect().y() - 5), (sceneRect().width() + 5), (sceneRect().height() + 5));
         return true;
     }
     return false;
}

bool TreeGraph::deleteNode(int value) {

     qDebug("- Delete Node in Tree at: %p in Tree Graphic!", this);
     qDebug("\t- Value to be deleted is: %d", value);

     NodeGraph* node = rootNode->deleteNode(value, rootNode);
     if (node != NULL) {
         if (node == rootNode) {
             if (node->getLeftNode() != NULL && node->getRightNode() != NULL)
                 ; // Nothing To Do! (Never occurs)
             else if (node->getLeftNode() != NULL)
                 rootNode = node->getLeftNode();
             else if (node->getRightNode() != NULL)
                 rootNode = node->getRightNode();
             else
                 rootNode = lastNode = NULL;
         }
         delete node;
         return true;
     }
     return false;
}

bool TreeGraph::searchNode(int value) {

     qDebug("- Search Node in Tree at: %p in Tree Graphic!", this);
     qDebug("\t- Value to be search is: %d", value);

     NodeGraph *node = rootNode->searchNode(value);
     if (node == NULL)
         return false;

     SubChild *child = getSubChild();
     node->ensureVisible(child->contentsRect());
     return true;
}

void TreeGraph::addNodesToGraph() {

     qDebug("- Add Nodes To Graphic in Tree Graphic!");
     \
     QList <NodeGraph *> listNodes;
     rootNode->loadListNodesPreOrder(listNodes);
     foreach (NodeGraph *node, listNodes) {

          qDebug("\t- Add to Tree at: %p\n\t\t- Node in List at: %p", this, node);

          addItem(node);
     }

     qDebug("- Add Nodes To Graphic Finished in Tree Graphic!");

}

void TreeGraph::checkCollides(NodeGraph *node, NodeGraph *other) {

     qDebug("- Check Collides in Tree Graphic!\n\t- Node at: %p Value is: %d", node, node->getIntegerValue());
     if (other)
         qDebug("\t- Other at: %p Value is: %d", other, other->getIntegerValue());

     if (other ==  NULL) {
         if (node->getLeftNode() && node->getRightNode()) {
             checkCollides(node, node->getLeftNode());
             checkCollides(node, node->getRightNode());
         } else if (node->getLeftNode()) {
             checkCollides(node, node->getLeftNode());
         } else if (node->getRightNode()) {
             checkCollides(node, node->getRightNode());
         } else {
             return;
         }
     } else {
         NodeGraph *collided = node->hasCollision(other);
         if (collided != NULL) {
             increaseDistance(node, collided);
             checkCollides(getRootNode());  // back to begin!
         } else {
             if (node->getLeftNode() && node->getRightNode()) {
                 checkCollides(node->getLeftNode(), other);
                 checkCollides(node->getRightNode(), other);
             } else if (node->getLeftNode()) {
                 checkCollides(node->getLeftNode(), other);
             } else if (node->getRightNode()) {
                 checkCollides(node->getRightNode(), other);
             }
         }
     }
}

void TreeGraph::increaseDistance(NodeGraph *node, NodeGraph *other) {

     qDebug("- Increase Distance in Tree Graphic!");

     if (node == NULL || other == NULL)
         return;
     NodeGraph *ancestor = node->getAncestorOf(other);

     if (ancestor != NULL)
         qDebug("\t- Increase Distance Between Value: %d and Value: %d\n\t- Ancestor value: %d", node->getIntegerValue(), other->getIntegerValue(), ancestor->getIntegerValue());
     else
         return;

     if (ancestor->getLeftNode() != NULL)
         ancestor->getLeftNode()->adjust();
     if (ancestor->getRightNode() != NULL)
         ancestor->getRightNode()->adjust();

     qDebug("- Increase Distance Finished in Tree Graphic!");

}

TreeGraph *TreeGraph::convertToNormal() {

     return NULL;
}

TreeGraph *TreeGraph::convertToRedBlack(bool &corrupted) {

     qDebug("- Convert To Red-Black in Tree Graphic!");

     register int count;
     bool flag_null = false;
     QList <QString>  q_str;
     TreeGraph *tree = NULL;
     valuesPreOrder(q_str);
     corrupted = false;
     count = q_str.count();
     if (count > 0) {
         int value = atoi(q_str.at(0).toStdString().c_str());
         tree = new TreeGraph(value, getGraphicsView(), qobject_cast <QWidget *> (parent()));
         NodeGraph *oldroot = tree->getRootNode();
         NodeGraph *newroot = NULL;
         //NodeGraph *newnode = NULL;
         oldroot->setColor(NodeGraphItemGroup::RED);

         qDebug("- Old Root Node at: %p, value is: %d", oldroot, oldroot->getIntegerValue());

         for (register int i = 1; i < count; i++) {
              value = atoi(q_str.at(i).toStdString().c_str());
              newroot = oldroot->insertNodeRedBlack(value, tree, oldroot);
              //newnode = oldroot->insertNodeRedBlack(value, tree, oldroot);
              if (newroot == NULL) {
              //if (newnode == NULL) {
                  flag_null = true;
                  break;
              }
         }
         if (flag_null == false && newroot == newroot->getRoot()) {
         //if (flag_null == false && newnode == newnode->getRoot()) {
             tree->setRootNode(newroot);
             //tree->setRootNode(newnode);
             if (tree->getRootNode()->getLine() != NULL)
                 tree->getRootNode()->destroyLine();

             tree->fixBinaryTree(tree->getRootNode());
             if (tree->isBinaryTree(tree->getRootNode(), -32767, 32767) == false) {
                 corrupted = true;
                 getSubChild()->getMainWindow()->alertOnStatusBar(tr("This Tree was corrupted!"));
             }
         }

         qDebug("- New Root at: %p, value is: %d", newroot, newroot->getIntegerValue());
         //qDebug("- New Root at: %p, value is: %d", newnode, newnode->getIntegerValue());

     } else {
         return NULL;
     }

     qDebug("- Convert To Red-Black Finished in Tree Graphic!");

     if (flag_null == false) {
         return tree;
     }
     delete tree;
     return NULL;
}

TreeGraph *TreeGraph::convertToAVL() {

     return NULL;
}


void TreeGraph::selectNodesAll(NodeGraph *node) {
    NodeGraph *left, *right;
    if (node == NULL)
       return;
    node->setSelectedNode(true);
    left  = node->getLeftNode();
    right = node->getRightNode();
    if (left != NULL && right != NULL) {
        selectNodesAll(left);
        selectNodesAll(right);
    } else if (left!= NULL) {
        selectNodesAll(left);
    } else if (right != NULL) {
        selectNodesAll(right);
    }
}

void TreeGraph::invertColorAll(NodeGraph *node, bool flag) {

     qDebug("- Invert Color All with Node at: %p and Flag is: %d in Tree Graphic!", node, flag);

     NodeGraph *left, *right;
     if (node == NULL)
        return;
     if (node->isSelectedNode() == true) {
         if (flag == true) {
             node->setSelectedNode(false);
             if (node->isColorInverted() == true)
                 node->invertColor();
         } else {
             if (node->isColorInverted() == false)
                 node->invertColor();
         }
     } else {
         if (node->isColorInverted())
             node->invertColor();
     }
     left  = node->getLeftNode();
     right = node->getRightNode();
     if (left != NULL && right != NULL) {
         invertColorAll(left, flag);
         invertColorAll(right, flag);
     } else if (left!= NULL) {
         invertColorAll(left, flag);
     } else if (right != NULL) {
         invertColorAll(right, flag);
     }
}

void TreeGraph::selectRectAll(QRectF rect, NodeGraph *node) {

     qDebug("- Select Rectangle All in Tree Graphic!");

     NodeGraph *left, *right;
     if (!node)
         return;
     if (rect.contains(node->getEllipse()->rect()))
         node->setSelectedNode(true);
     left  = node->getLeftNode();
     right = node->getRightNode();
     if (left && right) {
         selectRectAll(rect, left);
         selectRectAll(rect, right);
     } else if (left) {
         selectRectAll(rect, left);
     } else if (right) {
         selectRectAll(rect, right);
     }
}

void TreeGraph::valuesPreOrder(QList <QString> &listNodes) {

     qDebug("- Values Pre Order in Tree Graphic!");

     rootNode->loadListValuesPreOrder(listNodes);
}

void TreeGraph::valuesInOrder(QList <QString> &listNodes) {

     qDebug("- Values In Order in Tree Graphic!");

     rootNode->loadListValuesInOrder(listNodes);
}

void TreeGraph::valuesPosOrder(QList <QString> &listNodes) {

     rootNode->loadListValuesPosOrder(listNodes);
}

int TreeGraph::sizeOfTree() {

    qDebug("- Size of Tree in Tree Graphic!");

    return rootNode->getSizeOfNodes(rootNode);
}

/*
void TreeGraph::drawBackground (QPainter *painter, const QRectF &rect) {

     qDebug("- Draw Background in Tree Graphic!");

}

void TreeGraph::drawForeground (QPainter *painter, const QRectF &rect) {

     qDebug("- Draw Foreground in Tree Graphic!");

}
*/

void TreeGraph::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
     QMenu menu;
     MainWindow *m_win = getSubChild()->getMainWindow();
     m_win->setMenuFromContext(menu);
     menu.exec(event->screenPos());

     /* TO DO: emit text to child from copy and cut!
     NodeTextItem *item  = getItemText(event->scenePos());
     qDebug("\t- Value of Text is: %s", item->text().toStdString().c_str());
     */
}

/*
void TreeGraph::dragEnterEvent(QGraphicsSceneDragDropEvent *event){

     qDebug("- Drag Enter Event in Tree Graphic!");

}

void TreeGraph::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {

     qDebug("- Drag Leave Event in Tree Graphic!");

}

void TreeGraph::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {

     qDebug("- Drag Move Event in Tree Graphic!");

}

void TreeGraph::dropEvent(QGraphicsSceneDragDropEvent *event) {

     qDebug("- Drop EVent in Tree Graphic!");

}

void TreeGraph::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

    qDebug("- Double Click Event in Tree Graphic!");

    QGraphicsScene::mouseDoubleClickEvent(event);
}
*/

void TreeGraph::mousePressEvent(QGraphicsSceneMouseEvent *event) {

     qDebug("- Mouse Press Event in Tree Graphic!");

     if (event->buttons() == Qt::LeftButton) {
         NodeGraph *node  = getNodeItem(event->scenePos());
         if (node == NULL) {

             qDebug("\t- Left Button.\n\t- Point Selected: (%5.3f, %5.3f).", event->scenePos().x(), event->scenePos().y());

             selectedPointToStart.setX(event->scenePos().x());
             selectedPointToStart.setY(event->scenePos().y());
             startToScene = sceneRect();
             invertColorAll(getRootNode(), true);
         }
     }
     QGraphicsScene::mousePressEvent(event);
}

void TreeGraph::mouseMoveEvent (QGraphicsSceneMouseEvent *event) {

     //qDebug("- Mouse Move Event in Tree Graphic!");

     if (event->buttons() == Qt::LeftButton) {
         NodeGraph *node  = getNodeItem(event->scenePos());
         if (node != NULL) {
             node->setSelectedNode(true);
         } else {
             QPointF pt1(selectedPointToStart);
             QPointF pt2(event->scenePos());
             QRectF  rt1(pt1, pt2);
             QRectF  rt2(sceneRect());
             rt1 = rt1.normalized();
             rt2.setX(rt2.x()- 250.0);
             rt2.setY(rt2.y()- 250.0);
             rt2.setWidth(rt2.width()+ 250.0);
             rt2.setHeight(rt2.height()+ 250.0);
             if (rt2.contains(rt1)) {

                 //qDebug("\t- Rectangle Selected: (%5.3f, %5.3f, %5.3f, %5.3f)", rt1.x(), rt1.y(), rt1.width(), rt1.height());

                 selectedRect->setRect(rt1);
                 selectRectAll(rt1, getRootNode());
                 update();
             }
         }
     }
     QGraphicsScene::mouseMoveEvent(event);
}

void TreeGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

     qDebug("- Mouse Release Event in Tree Graphic!");

     selectedRect->setRect(0, 0, 0, 0);
     if (startToScene.isNull() == false) {
         setSceneRect(startToScene);
         startToScene.setCoords(0,0,0,0);
         selectedNodes.clear();
         invertColorAll(getRootNode());
         setSelectedNodes(getRootNode());
         update();
         if (selectedNodes.count() > 0)
             getSubChild()->getMainWindow()->setSelectionFlag(true);
         else
             getSubChild()->getMainWindow()->setSelectionFlag(false);
     }
     QGraphicsScene::mouseReleaseEvent(event);
}

int *TreeGraph::getSelectedNodes() {
     int   count = selectedNodes.count();
     int *result = new int[count];
     for (register int i = 0; i < count; i++) {
          result[i] = selectedNodes.at(i)->getIntegerValue();
     }
     return result;
}

int TreeGraph::getSelectedNodesCount() {
    return selectedNodes.count();
}

void TreeGraph::clearSelectedNodes() {
     selectedNodes.clear();
}

void TreeGraph::setSelectedNodes(NodeGraph *node) {
     if (node->isColorInverted() == true)
         selectedNodes.append(node);
     NodeGraph *left  = node->getLeftNode();
     NodeGraph *right = node->getRightNode();
     if (left != NULL && right != NULL) {
         setSelectedNodes(left);
         setSelectedNodes(right);
     } else if (left != NULL) {
         setSelectedNodes(left);
     } else if (right != NULL) {
         setSelectedNodes(right);
     }
}


bool TreeGraph::isBinaryTree(NodeGraph *temp, int min, int max) {
     if(temp == NULL)
        return true;
     if (temp->getIntegerValue() > min && temp->getIntegerValue() < max) {
         if (isBinaryTree(temp->getLeftNode(), min, temp->getIntegerValue()) && isBinaryTree(temp->getRightNode(), temp->getIntegerValue(), max))
            return true;
    }
    return false;
}

void TreeGraph::fixBinaryTree(NodeGraph *n) {
     bool flag = false;
     if (n != NULL) {
         if (n->getParentNode() != NULL) {
             if (n == n->getParentNode()->getLeftNode() && n->getIntegerValue() > n->getParentNode()->getIntegerValue()) {
                 flag = true;
             } else if (n == n->getParentNode()->getRightNode() && n->getIntegerValue() < n->getParentNode()->getIntegerValue()) {
                 flag = true;
             }
         }
         if (flag == true) {
             int a, b;
             a = n->getIntegerValue();
             b = n->getParentNode()->getIntegerValue();
             n->setIntegerValue(b);
             n->getParentNode()->setIntegerValue(a);
             fixBinaryTree(n->getParentNode());
         }
         fixBinaryTree(n->getLeftNode());
         fixBinaryTree(n->getRightNode());
     }

}

/*
// This function does inorder traversal to find out the two swapped nodes.
// It sets three pointers, first, middle and last.  If the swapped nodes are
// adjacent to each other, then first and middle contain the resultant nodes
// Else, first and last contain the resultant nodes
void TreeGraph::correctBSTUtil(NodeGraph *root, NodeGraph **first, NodeGraph **middle, NodeGraph **last, NodeGraph **prev) {
     if(root != NULL) {
        // Recur for the left subtree
        correctBSTUtil(root->getLeftNode(), first, middle, last, prev );
        // If this node is smaller than the previous node, it's violating
        // the BST rule.
        if (*prev != NULL && root->getIntegerValue() < (*prev)->getIntegerValue()) {
            // If this is first violation, mark these two nodes as
            // 'first' and 'middle'
            if (*first == NULL) {
                *first = *prev;
                *middle = root;
            } else { // If this is second violation, mark this node as last
                *last = root;
            }
        }
        // Mark this node as previous
        *prev = root;
        // Recur for the right subtree
        correctBSTUtil( root->getRightNode(), first, middle, last, prev );
     }
}

// A function to fix a given BST where two nodes are swapped.  This
// function uses correctBSTUtil() to find out two nodes and swaps the
// nodes to fix the BST
void TreeGraph::correctBST(NodeGraph *root) {
     // Initialize pointers needed for correctBSTUtil()
     int a, b;
     NodeGraph *first, *middle, *last, *prev;
     first = middle = last = prev = NULL;
     // Set the poiters to find out two nodes
     correctBSTUtil(root, &first, &middle, &last, &prev);
     // Fix (or correct) the tree
     if(first != NULL && last != NULL) {
        //swap( &(first->data), &(last->data) );
        a = first->getIntegerValue();
        b = last->getIntegerValue();
        first->setIntegerValue(b);
        last->setIntegerValue(a);
     } else if( first && middle ) {// Adjacent nodes swapped
        //swap( &(first->data), &(middle->data) );
         a = first->getIntegerValue();
         b = middle->getIntegerValue();
         first->setIntegerValue(b);
         middle->setIntegerValue(a);
     } // else nodes have not been swapped, passed tree is really BST.
}

void TreeGraph::recoverTree(NodeGraph *root) {
        NodeGraph *curr = root;
        NodeGraph *ptr1 = NULL;
        NodeGraph *ptr2 = NULL;
        NodeGraph *prev = NULL;
        NodeGraph *predecessor = NULL;
        while (curr) {
            if (curr->getLeftNode() == NULL) {
                if (prev && prev->getIntegerValue() > curr->getIntegerValue()) {
                    ptr2 = curr;
                    if (ptr1 == NULL)
                        ptr1 = curr;
                }
                prev = curr;
                curr = curr->getRightNode();
            }
            else {
                predecessor = curr->getLeftNode();
                while (predecessor->getRightNode() != NULL && predecessor->getRightNode() != curr)
                    predecessor = predecessor->getRightNode();
                if (predecessor->getRightNode() == NULL) {
                    predecessor->setRightNode(curr);
                    curr = curr->getLeftNode();
                } else {
                    if (prev && prev->getIntegerValue() > curr->getIntegerValue()) {
                        ptr2 = curr;
                        if (ptr1 == NULL)
                            ptr1 = prev;
                    }
                    predecessor->setRightNode(NULL);
                    prev = curr;
                    curr = curr->getRightNode();
                }
            }
        }
        int a = ptr1->getIntegerValue();
        int b = ptr2->getIntegerValue();
        ptr1->setIntegerValue(b);
        ptr2->setIntegerValue(a);
}
*/
