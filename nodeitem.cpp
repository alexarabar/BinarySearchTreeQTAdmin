/****************************************************************************
** Binary Search Tree Utility QT-4 Version 1.00
** Author:  Alexandre A. Barbosa
** Created: Fev-14-2010
** Updated: Apr-07-2015
** Name:    nodeitem.cpp
****************************************************************************/

#include <QtGui>
//#include <QtDebug>
//#include <QObject>
#include "mainwindow.h"
#include "nodeitem.h"

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

// ***************************************** NODE GRAPH ITEM GROUP (Base Class) ***************************************** //

/*
NodeGraphItemGroup::NodeGraphItemGroup() {
     Initialilize();
}
*/

NodeGraphItemGroup::NodeGraphItemGroup(TreeGraph *graph, QGraphicsItem *parent): QGraphicsItemGroup(parent), tree(graph) {

     qDebug("- New Node Graphic Item Group at: %p", this);

     Initialize();
     ellipse = new NodeEllipseItem(this);
     text    = new NodeTextItem(ellipse);
     line    = NULL;
     addToGroup(ellipse);
}

NodeGraphItemGroup::NodeGraphItemGroup(NodeGraphItemGroup *source, TreeGraph *graph, QGraphicsItem *parent): QGraphicsItemGroup(parent), tree(graph) {

     qDebug("- Copy of Node Graphic Item Group at: %p\n\t- New Node Graphic Item Group at: %p", source, this);

     setFlags(source->flags());
     setCacheMode(source->cacheMode());
     setAcceptDrops(source->acceptDrops());
     setAcceptHoverEvents(source->acceptHoverEvents());
     color = source->getColor();
     ellipse = new NodeEllipseItem(source->getEllipse(), this);
     text    = new NodeTextItem(source->getText(), ellipse);
     line = NULL;
     addToGroup(ellipse);
}

NodeGraphItemGroup::~NodeGraphItemGroup() {

     qDebug("- Delete Node Graphic Item Group at: %p", this);

     removeFromGroup(ellipse);
     delete text;
     text = NULL;
     delete ellipse;
     ellipse = NULL;

     qDebug("\t- Line at %p", line);

     if (line != NULL && destroyLine()) {
         removeFromGroup(line);
         delete line;
         line = NULL;
     }
}

void NodeGraphItemGroup::Initialize() {
     color = NodeGraph::BLACK;
     setFlags(ItemIsMovable | ItemIsSelectable);
     setCacheMode(DeviceCoordinateCache);
     setAcceptDrops(true);
     setAcceptHoverEvents(true);
     setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
}

void NodeGraphItemGroup::setupGroup(QPointF point, QString value) {

     qDebug("- Setup Group in Node Graphic Item Group at: %p\n\t- Ellipse Start Point is: (%5.3f, %5.3f)\n\t- Text Value is: %s", this, point.x(), point.y(), value.toStdString().c_str());

     qreal len = getTree()->getLengthOfNode();
     ellipse->setupEllipse(point.x(), point.y(), len, len);
     ellipse->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
     text->setupText(value);

}

NodeLineItem *NodeGraphItemGroup::createLine() {

      qDebug("- Create Line in Node Graphic Item Group!");

     line = new NodeLineItem(this);
     return line;
}

NodeLineItem *NodeGraphItemGroup::copyLine(NodeLineItem *source) {

     qDebug("- Copy Line from Source at: %p in Node Graphic Item Group!", source);

     line = new NodeLineItem(source, this);
     return line;
}

bool NodeGraphItemGroup::destroyLine() {

     qDebug("- Destroy Line of Node Graphic Item Group at: %p\n\t- Source at: %p\n\t- Target at: %p", line, line->getSourceNode(), line->getTargetNode());

     if (line->getSourceNode() != NULL && line->getTargetNode() != NULL) {
         line->setSourceNode(NULL);
         line->setTargetNode(NULL);
         return true;
     }
     return false;
}

void NodeGraphItemGroup::addLine(NodeLineItem *li) {

     qDebug("- Add Line at: %p in Node Graphic Item Group!", li);

     if (li != NULL) {
         addToGroup(li);
         line = li;
     }
}

void NodeGraphItemGroup::removeLine() {

     qDebug("- Remove Line at: %p in Node Graphic Item Group!", line);

     removeFromGroup(line);
}

/*
GraphViewer *NodeGraphItemGroup::getViewer() {

     qDebug("- Get Viewer in Node Graphic Item Group!");

     return getTree()->getGraphViewer();
}
*/

// ************************************************** NODE GRAPH (Derived Class) ************************************************* //

/*
NodeGraph::NodeGraph() {
     left_node = right_node = NULL;
}
*/

NodeGraph::NodeGraph(int value, TreeGraph *graph, NodeGraph **parentNode, QGraphicsItem *parent): NodeGraphItemGroup(graph, parent) {

     qDebug("- New Node Graphic at: %p", this);

     setIntegerValue(value);
     createNode(parentNode);
     identifyNode();
     if (parentNode != NULL) {
         createLine();
     }
     orderZValueToUp();
}

NodeGraph::NodeGraph(TreeGraph *graph, NodeGraph *source, NodeGraph **parentNode, QGraphicsItem *parent): NodeGraphItemGroup(source, graph, parent)  {

     qDebug("- Copy of Node Graphic at: %p\n\t- New Node Graphic at: %p", source, this);

     setIntegerValue(source->getIntegerValue());
     createNode(parentNode);
     identifyNode();
     if (parentNode != NULL) {
         copyLine(source->getLine());
     }
     orderZValueToUp();
}

NodeGraph::~NodeGraph() {

     qDebug("- Delete Node Graphic at: %p", this);

}

void NodeGraph::setupNode() {

     qDebug("- Setup Node in Node Graphic at: %p\n\t- Is root node? %d", this, is_root_node);

     if (is_root_node == true) {
         setupGroup(getTree()->getStartPoint(), QString::number(integer_value));
         return;
     }

     qDebug("\t- Integer Value: %d\n\t- Parent Node at: %p", integer_value, parent_node);

     setupGroup(getBottomOfParent(), QString::number(integer_value));
     if (parent_node != NULL) {
         NodeLineItem *li;
         if (getLine() == NULL) {
             li = createLine();
             addLine(li);
         }
         getLine()->setupLine(this, parent_node);
     } else {
         if (destroyLine() == true) {
             delete getLine();
         }
     }

     qDebug("- Setup Node Finished in Node Graphic!");

}

void NodeGraph::createNode(NodeGraph **parentNode) {

     qDebug("- Create Node at: %p in Node Graphic!", this);

     if (!parentNode) {
         setParentNode(NULL);
     } else {
         setParentNode((*parentNode));
         if ((*parentNode)->getIntegerValue() > getIntegerValue()) {
             (*parentNode)->setLeftNode(this);
         } else {
             (*parentNode)->setRightNode(this);
         }
     }
     setLeftNode(NULL);
     setRightNode(NULL);
     setSelectedNode(false);
     inverted_color = inverted_fixed = position_updated = false;
     factor =  0;

     qDebug("\t- This Node at: %p\n\t- Parent Node at: %p\n- Create Node Finished in Node Graphic!", this, getParentNode());

}

NodeGraph *NodeGraph::insertNode(int value, TreeGraph *graph, NodeGraph *curNode, NodeGraph **parentNode, QGraphicsItem *parent) {

     qDebug("- Insert Node in Node Graphic!\n\t- Tree Graphic at: %p\n\t- Current Node at: %p\n\t- Value is: %d: ", graph, curNode, value);

     if (curNode == NULL) {
         //return new NodeGraph(value, graph, parentNode, parent);
         NodeGraph *node = new NodeGraph(value, graph, parentNode, parent);
         node->getTree()->setLastNode(node);
         return node;
     } else {
         if (curNode->getIntegerValue() > value) {
             return insertNode(value, graph, curNode->getLeftNode(), &curNode, parent);
         } else if (curNode->getIntegerValue() < value) {
             return insertNode(value, graph, curNode->getRightNode(), &curNode, parent);
         } else {
             return NULL;
         }
    }
}

NodeGraph *NodeGraph::insertNodeRedBlack(int value, TreeGraph *graph, NodeGraph *curNode, NodeGraph **parentNode, QGraphicsItem *parent) {

     qDebug("Insert Node Red-Black in Node Graphic!");

     NodeGraph *newNode = insertNode(value, graph, curNode, parentNode, parent);
     if (newNode != NULL) {
         newNode->setColor(NodeGraph::RED);

         qDebug("\t- New Node Red-Black at: %p, value is: %d", newNode, newNode->integer_value);

         NodeGraph *rootNode = newNode->getRoot();
         insertNodeRedBlackFix(&rootNode, newNode);

         //insertNodeRedBlackFix(newNode);
         //insertNodeRedBlackFixCase1(newNode);
         //return newNode->getRoot();

         rootNode->setParentNode(NULL);
         return rootNode;
         //return newNode;
    }
    return NULL;
}

NodeGraph *NodeGraph::getGrandParent(NodeGraph *n) {
     if (n != NULL && n->parent_node != NULL)
         return n->parent_node->parent_node;
     return NULL;
}

NodeGraph *NodeGraph::getUncle(NodeGraph *n) {
     NodeGraph *g = getGrandParent(n);
     if (g == NULL)
         return NULL;
     if (n->parent_node == g->left_node)
         return g->right_node;
     else
         return g->left_node;
}

void NodeGraph::insertNodeRedBlackFixCase1(NodeGraph *n) {
     if (n->parent_node == NULL)
         n->setColor(NodeGraphItemGroup::BLACK);
     else
         insertNodeRedBlackFixCase2(n);
}

void NodeGraph::insertNodeRedBlackFixCase2(NodeGraph *n) {
     if (n->parent_node->getColor() == NodeGraphItemGroup::BLACK)
         return;
     insertNodeRedBlackFixCase3(n);
}

void NodeGraph::insertNodeRedBlackFixCase3(NodeGraph *n) {
     NodeGraph *u = getUncle(n), *g;
     if (u != NULL && u->getColor() == NodeGraphItemGroup::RED) {
         n->parent_node->setColor(NodeGraphItemGroup::BLACK);
         u->setColor(NodeGraphItemGroup::BLACK);
         g = getGrandParent(n);
         g->setColor(NodeGraphItemGroup::RED);
         insertNodeRedBlackFixCase1(g);
     } else {
         insertNodeRedBlackFixCase4(n);
     }
}

void NodeGraph::insertNodeRedBlackFixCase4(NodeGraph *n) {
     NodeGraph *g = getGrandParent(n);
     if (n == n->parent_node->right_node && n->parent_node == g->left_node) {
         n->parent_node->rotationLeft(); //rotate_left(n->parent);

         /*
          * rotate_left can be the below because of already having *g =  grandparent(n)
          *
          * struct node *saved_p=g->left, *saved_left_n=n->left;
          * g->left=n;
          * n->left=saved_p;
          * saved_p->right=saved_left_n;
          *
          * and modify the parent's nodes properly
          */

          n = n->left_node;
     } else if (n == n->parent_node->left_node && n->parent_node == g->right_node) {
          n->parent_node->rotationRight(); //rotate_right(n->parent);

          /*
           * rotate_right can be the below to take advantage of already having *g =  grandparent(n)
           *
           * struct node *saved_p=g->right, *saved_right_n=n->right;
           * g->right=n;
           * n->right=saved_p;
           * saved_p->left=saved_right_n;
           *
           */

           n = n->right_node;
     }
     insertNodeRedBlackFixCase5(n);
}

void NodeGraph::insertNodeRedBlackFixCase5(NodeGraph *n) {
     NodeGraph *g = getGrandParent(n);
     n->parent_node->setColor(NodeGraphItemGroup::BLACK);
     g->setColor(NodeGraphItemGroup::RED);
     if (n == n->parent_node->left_node)
         g->rotationRight(); // rotate_right(g);
     else
         g->rotationLeft(); //rotate_left(g);
}

void NodeGraph::insertNodeRedBlackFix(NodeGraph *x) {
     NodeGraph *y;
     while ((x->getParentNode() != NULL && x->getParentNode()->getParentNode() != NULL) && x->getParentNode()->getColor() == NodeGraphItemGroup::RED) {
            if (x->getParentNode() == x->getParentNode()->getParentNode()->getLeftNode()) {
                y = x->getParentNode()->getParentNode()->getRightNode();
                if (y != NULL && y->getColor() == NodeGraphItemGroup::RED) {
                    x->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                    y->setColor(NodeGraphItemGroup::BLACK);
                    x->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                    x = x->getParentNode()->getParentNode();
                } else {
                    if (x == x->getParentNode()->getRightNode()) {
                        x = x->getParentNode();
                        rotationLeft(x);  // x->rotationLeft(); // x = x->rotationLeft();
                    }
                    x->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                    x->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                     rotationRight(x->getParentNode()->getParentNode()); // x->getParentNode()->getParentNode()->rotationRight(); // x = x->getParentNode()->getParentNode()->rotationRight(); // x->getParentNode()->setParentNode(x->getParentNode()->getParentNode()->rotationRight());
                }
            } else {
                y = x->getParentNode()->getParentNode()->getLeftNode();
                if (y != NULL && y->getColor() == NodeGraphItemGroup::RED) {
                    x->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                    y->setColor(NodeGraphItemGroup::BLACK);
                    x->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                    x = x->getParentNode()->getParentNode();
                } else {
                    if (x == x->getParentNode()->getLeftNode()) {
                        x = x->getParentNode();
                        rotationRight(x); // x->rotationRight(); // x = x->rotationRight();
                    }
                    x->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                    x->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                    rotationLeft(x->getParentNode()->getParentNode()); // x->getParentNode()->getParentNode()->rotationLeft(); // x->getParentNode()->setParentNode(x->getParentNode()->getParentNode()->rotationLeft()); // x = x->getParentNode()->getParentNode()->rotationLeft();
                }

            }
     }
     NodeGraph *z = x->getRoot();
     z->setColor(NodeGraphItemGroup::BLACK);
     z->setParentNode(NULL);
}

void NodeGraph::insertNodeRedBlackFix(NodeGraph **root, NodeGraph *z) {
     while (z != *root && z->parent_node->getColor() == NodeGraphItemGroup::RED && z->parent_node->parent_node != NULL) {
            NodeGraph *y;
            if (z->parent_node == z->parent_node->parent_node->left_node)
                y = z->parent_node->parent_node->right_node;
            else
                y = z->parent_node->parent_node->left_node;
            if (y != NULL && y->getColor() == NodeGraphItemGroup::RED) {
                y->setColor(NodeGraphItemGroup::BLACK);
                z->parent_node->setColor(NodeGraphItemGroup::BLACK);
                z->parent_node->parent_node->setColor(NodeGraphItemGroup::RED);
                z = z->parent_node->parent_node;
            } else {

                qDebug("-> FIX TEST");
                qDebug("\tParent Node: %p", z->parent_node);
                qDebug("\tParent of Parent: %p", z->parent_node->parent_node);
                qDebug("\tLeft of Parent of Parent: %p", z->parent_node->parent_node->left_node);
                qDebug("\tRight of Parent of Parent: %p", z->parent_node->parent_node->right_node);
                qDebug("\tLeft of Parent: %p", z->parent_node->left_node);
                qDebug("\tRight of Parent: %p", z->parent_node->right_node);

                NodeGraphItemGroup::Colors c;
                if (z->parent_node == z->parent_node->parent_node->left_node && z == z->parent_node->left_node) {
                    c = z->parent_node->getColor();
                    z->parent_node->setColor(z->parent_node->parent_node->getColor());
                    z->parent_node->parent_node->setColor(c);
                    rotationRight(root, z->parent_node->parent_node);
                } else if (z->parent_node == z->parent_node->parent_node->left_node && z == z->parent_node->right_node) {
                    c = z->getColor();
                    z->setColor(z->parent_node->parent_node->getColor());
                    z->parent_node->parent_node->setColor(c);
                    rotationLeft(root, z->parent_node);
                    rotationRight(root, z->parent_node->parent_node);
                } else if (z->parent_node == z->parent_node->parent_node->right_node && z == z->parent_node->right_node) {
                    c = z->parent_node->getColor();
                    z->parent_node->setColor(z->parent_node->parent_node->getColor());
                    z->parent_node->parent_node->setColor(c);
                    rotationLeft(root, z->parent_node->parent_node);
                } else if (z->parent_node == z->parent_node->parent_node->right_node && z == z->parent_node->left_node) {
                    c = z->getColor();
                    z->setColor(z->parent_node->parent_node->getColor());
                    z->parent_node->parent_node->setColor(c);
                    rotationRight(root, z->parent_node);
                    rotationLeft(root, z->parent_node->parent_node);
                } else {
                    break; //z = z->parent_node;
                }
            }
     }
     (*root)->setColor(NodeGraphItemGroup::BLACK);
}

NodeGraph *NodeGraph::insertNodeAVL(int value, TreeGraph *graph, NodeGraph *curNode, NodeGraph **parentNode, QGraphicsItem *parent) {

     return NULL;
}

void NodeGraph::insertNodeAVLFix(NodeGraph *node) {

}

NodeGraph *NodeGraph::deleteNode(int value, NodeGraph *root) {

     qDebug("- Delete Node in Node Graphic!");

     NodeGraph *node, *parent, *child, *predecessor;
     node = findNode(value, root);
     if (node == NULL)
         return NULL;
     // leaf node - just return to delete the node
     if (node->left_node == NULL && node->right_node == NULL) {
         if (node->parent_node != NULL) {
             parent = node->parent_node;
             if (node == parent->left_node)
                 parent->left_node = NULL;
             else
                 parent->right_node = NULL;
         }
         return node;
     }
     // two children - replace it with its predecessor and return to delete
     if (node->left_node != NULL && node->right_node != NULL) {
         int pred_value = getPredecessorValue(node);
         predecessor = findNode(pred_value, root);
         if (predecessor->parent_node->left_node == predecessor)
             predecessor->parent_node->left_node = NULL;
         else if(predecessor->parent_node->right_node == predecessor)
             predecessor->parent_node->right_node = NULL;
        node->integer_value = predecessor->integer_value;
        return predecessor;
     }
     // only one child - replace it with its child and return to delete
     if (node->left_node)
         child = node->left_node;
     else if(node->right_node)
         child = node->right_node;
     parent = node->parent_node;
     if (parent != NULL) {
         if (parent->left_node != NULL && parent->left_node == node)
             parent->left_node = child;
         else if (parent->right_node != NULL && parent->right_node == node)
             parent->right_node = child;
     }
     child->parent_node = parent;
     return node;
}

NodeGraph *NodeGraph::searchNode(int value) {

     qDebug("- Search Node in Node Graphic!");

     NodeGraph *node = findNode(value, this);
     if (node != NULL) {
         setDefaultColorsAll();
         if (node->isColorInverted() == false) {
             node->invertColor();
             getTree()->clearSelectedNodes();
             getTree()->setSelectedNodes(node);
         }
     }
     return node;
}

QPointF NodeGraph::getBottomOfParent() {

     qDebug("- Get Bottom of Parent in Node Graphic!");

     if (parent_node == NULL)
         return QPointF(0.0,0.0);
     QPointF result;
     QRectF rect = parent_node->getEllipse()->rect();
     if (is_left_node) {
         result = rect.bottomLeft();
         result.setX(result.x() - rect.width() - 2.5);
         result.setY(result.y() + 2.5);
     } else if (is_right_node) {
         result = rect.bottomRight() + QPointF(2.5, 2.5);;
     }

     qDebug("\t- Bottom of Ellipse Parent:\n\t\t- Rectangle: (%5.3f, %5.3f, %5.3f, %5.3f\n\t\t- Results is Point at: (%5.3f, %5.3f).\n- Get Bottom of Parent Finished in Node Graphic!", rect.x(), rect.y(), rect.width(), rect.height(), result.x(), result.y());

     return result;
}

void NodeGraph::clearNodesAll() {

     qDebug("- Clear Nodes All in Node Graphic!");

     if (left_node != NULL && right_node != NULL) {
        left_node->clearNodesAll();
        delete left_node;
        left_node = NULL;
        right_node->clearNodesAll();
        delete right_node;
        right_node = NULL;
    } else if (left_node != NULL) {
        left_node->clearNodesAll();
        delete left_node;
        left_node = NULL;
    } else if (right_node != NULL) {
        right_node->clearNodesAll();
        delete right_node;
        right_node = NULL;
    }
}

void NodeGraph::loadListValuesPreOrder(QList <QString> &listNodes) {

     qDebug("- Load List Values Pre Order in Node Graphic!");

     QString str = QString::number(integer_value);
     listNodes.append(str);
     if (left_node)
         left_node->loadListValuesPreOrder(listNodes);
     if (right_node)
         right_node->loadListValuesPreOrder(listNodes);
}

void NodeGraph::loadListValuesInOrder(QList <QString> &listNodes) {

     qDebug("- Load List Values In Order in Node Graphic!");

     if (left_node)
         left_node->loadListValuesInOrder(listNodes);
     QString str = QString::number(integer_value);
     listNodes.append(str);
     if (right_node)
         right_node->loadListValuesInOrder(listNodes);
}

void NodeGraph::loadListValuesPosOrder(QList <QString> &listNodes) {
    if (left_node)
        left_node->loadListValuesPosOrder(listNodes);
    if (right_node)
        right_node->loadListValuesPosOrder(listNodes);
    QString str = QString::number(integer_value);
    listNodes.append(str);
}

void NodeGraph::loadListNodesPreOrder(QList <NodeGraph *> &listNodes) {

     qDebug("- Load List Nodes Pre Order in Node Graphic!");

     listNodes.append(this);
     if (left_node)
         left_node->loadListNodesPreOrder(listNodes);
     if (right_node)
         right_node->loadListNodesPreOrder(listNodes);
}

NodeGraph *NodeGraph::hasCollision(NodeGraph *otherNode) {

     qDebug("- Has Collision in Node Graphic!");

     if (this == otherNode)
         return NULL;

     qDebug("\t- Has Collision?\n\t- With Node at: %p Value is: %d\n\t- With Other Node at: %p Value is: %d", this, this->getIntegerValue(), otherNode, otherNode->getIntegerValue());

     NodeGraph *result = NULL;
     if (getEllipse()->collidesWithItem(otherNode->getEllipse(), Qt::IntersectsItemShape)) {
         result = otherNode;
     } else {
         if (getParentNode() != NULL && otherNode != getLeftNode() && otherNode != getRightNode() && this != otherNode->getLeftNode() && this != otherNode->getRightNode()) {
             if (getLine()->collidesWithItem(otherNode->getEllipse(), Qt::IntersectsItemShape))
                 result = otherNode;;
         }
     }
     if (!result) {
         if (otherNode->getLeftNode()) {
             result = hasCollision(otherNode->getLeftNode());
         }
         if (!result) {
             if (otherNode->getRightNode()) {
                 result = hasCollision(otherNode->getRightNode());
             }
         }
     }

     if (result != NULL)
         qDebug("\t- Have Collision with Other Node at %p Value is %d", result, result->getIntegerValue());
     else
         qDebug("\t- No Have Collisions...");

     qDebug("- Has Collision is Finished in Node Graphic!");

     return result;
}

NodeGraph *NodeGraph::getAncestorOf(NodeGraph *otherNode) {

     qDebug("- Get Ancestor of... in Node Graphic!\n\t- This Node at: %p Value is: %d\n\t- Other Node at: %p Value is: %d", this, getIntegerValue(), otherNode, otherNode->getIntegerValue());

     NodeGraph *pThis  = this;
     NodeGraph *pOther = otherNode;
     while (pThis != NULL && pThis->isRootNode() == false) {
          while (pOther != NULL && pOther->isRootNode() == false) {
               if (pOther == pThis)
                   break;

               qDebug ("\t- Other Node Parent %p at: ", pOther->getParentNode());

               pOther = pOther->getParentNode();
          }
          if (pThis == pOther)
              break;

          qDebug ("\t- This Node Parent at: %p", pThis->getParentNode());

          pThis = pThis->getParentNode();
          pOther = otherNode;
     }

     qDebug("\t- Results Node at: %p Value is: %d\n- Get Ancestor Finished in Node Graphic!", pThis, pThis->getIntegerValue());

     return pThis;
}

void NodeGraph::adjust() {

     qDebug("- Adjust in Node Graphic!\n\t- This Node at: %p", this);

     NodeEllipseItem *e = getEllipse();
     qreal ex, ey;
     if (is_left_node) {
         ex = e->getX() - (e->getWidth() / 2.0);
     } else {
         ex = e->getX() + (e->getWidth() / 2.0);
     }
     ey = e->getY() + (e->getHeight() / 2.0);
     setupNodesAll(QPointF(ex, ey));

     qDebug("- Adjust Finished in Node Graphic!");

}

bool NodeGraph::advance() {

     qDebug("- Advance in Node Graphic!");

     TreeGraph *tree = getTree();
     if (tree == NULL ||  tree->getNewPosition() == pos())
         return false;
     setPos(tree->getNewPosition());
     return true;
}

QRectF NodeGraph::boundingRect() const {

     //qDebug("- Bounding Rectangle in Node Graphic!");

     qreal adjust = 2.0;
     return QRectF(-adjust, -adjust, 23.0 + adjust, 23.0 + adjust);
}

QPainterPath NodeGraph::shape() const {

     qDebug("- Shape in Node Graphic!");

     QPainterPath path;
     path.addEllipse(0.0, 0.0, 20.0, 20.0);
     return path;
}
void NodeGraph::identifyNodesAll() {

     qDebug("- Identify Nodes All in Node Graphic!");

     if (parent_node == NULL) {
         is_root_node  = true;
         is_left_node  = false;
         is_right_node = false;
     } else {
         if (parent_node->getLeftNode() == this) {
             is_root_node  = false;
             is_left_node =  true;
             is_right_node = false;
         } else if (parent_node->getRightNode() == this) {
             is_root_node  = false;
             is_left_node =  false;
             is_right_node = true;
         }
     }
     if (left_node != NULL)
         left_node->identifyNodesAll();
     if (right_node != NULL)
         right_node->identifyNodesAll();
}

NodeGraph *NodeGraph::rotationLeft() {

     qDebug("- Rotation Left in Node Graphic!");

     NodeGraph *newroot = right_node;
     if(newroot != NULL) {
        right_node = newroot->getLeftNode();
        if (newroot->getLeftNode() != NULL)
            newroot->getLeftNode()->setParentNode(this);
        newroot->setParentNode(parent_node);
     }
     if(parent_node != NULL) {
        if (this == parent_node->getLeftNode())
            parent_node->setLeftNode(newroot);
        else
            parent_node->setRightNode(newroot);
     }
     if(newroot != NULL)
        newroot->setLeftNode(this);
     parent_node = newroot;
     return newroot;
}

NodeGraph *NodeGraph::rotationRight() {

     qDebug("- Rotation Right in Node Graphic!");

     NodeGraph *newroot = left_node;
     if (newroot != NULL) {
         left_node = newroot->getRightNode();
         if (newroot->getRightNode() != NULL)
             newroot->getRightNode()->setParentNode(this);
         newroot->setParentNode(parent_node);
     }
     if (parent_node != NULL) {
         if (this == parent_node->getLeftNode())
             parent_node->setLeftNode(newroot);
         else
             parent_node->setRightNode(newroot);
     }
     if (newroot != NULL)
         newroot->setRightNode(this);
     parent_node = newroot;
     return newroot;
}

/*
void NodeGraph::rotationLeft(NodeGraph *node_x){
     NodeGraph *node_y;
     if (node_x->getRightNode() == NULL){
        return;
     }
     node_y = node_x->getRightNode();
     if (node_y->getLeftNode() != NULL){
        node_y->getLeftNode()->setParentNode(node_x);
        node_x->setRightNode(node_y->getLeftNode());
     }
     node_y->setParentNode(node_x->getParentNode());
     if (node_x->getParentNode() == NULL){
         node_y->IamRootNode(true);
     } else if (node_x == node_x->getParentNode()->getLeftNode()){
         node_x->getParentNode()->setLeftNode(node_y);
     } else{
         node_x->getParentNode()->setRightNode(node_y);
     }
     node_x->setRightNode(node_y->getLeftNode());
     node_y->setLeftNode(node_x);
     node_x->setParentNode(node_y);
}

void NodeGraph::rotationRight(NodeGraph *node_y){
     NodeGraph *node_x;
     if (node_y->getLeftNode() == NULL){
         return;
     }
     node_x = node_y->getLeftNode();
     if (node_x->getRightNode() != NULL){
         node_x->getRightNode()->setParentNode(node_y);
        node_y->setLeftNode(node_x->getRightNode());
     }
     node_x->setParentNode(node_y->getParentNode());
     if (node_y->getParentNode() == NULL){
         node_x->IamRootNode(true);
     } else if(node_y == node_y->getParentNode()->getLeftNode()){
         node_y->getParentNode()->setLeftNode(node_x);
     } else {
         node_y->getParentNode()->setRightNode(node_x);
     }
     node_y->setLeftNode(node_x->getRightNode());
     node_x->setRightNode(node_y);
     node_y->setParentNode(node_x);
}

NodeGraph* NodeGraph::rotationLeft(NodeGraph* a) {
     NodeGraph *b = a->right_node;
     b->parent_node = a->parent_node;
     a->right_node = b->left_node;
     if (a->right_node != NULL)
         a->right_node->parent_node = a;
     b->left_node   = a;
     a->parent_node = b;
     if (b->parent_node != NULL) {
         if (b->parent_node->right_node == a) {
             b->parent_node->right_node = b;
         } else {
             b->parent_node->left_node = b;
         }
     }
     return b;
}

NodeGraph* NodeGraph::rotationRight(NodeGraph *a) {
     NodeGraph *b = a->left_node;
     b->parent_node = a->parent_node;
     a->left_node = b->right_node;
     if (a->left_node != NULL)
         a->left_node->parent_node = a;
     b->right_node  = a;
     a->parent_node = b;
     if (b->parent_node != NULL) {
         if (b->parent_node->right_node == a) {
             b->parent_node->right_node = b;
         } else {
             b->parent_node->left_node = b;
         }
     }
     return b;
}
*/

void NodeGraph::rotationLeft(NodeGraph *n) {
     NodeGraph *temp = n->right_node;
     n->right_node = temp->left_node;
     if (temp->left_node != NULL)
         temp ->left_node->parent_node = n;
     if (n->parent_node == NULL) {
         temp->parent_node = NULL;
     } else if (n->parent_node->left_node == n) {
         n->parent_node->left_node = temp;
     } else {
         n->parent_node->right_node = temp;
     }
     temp->left_node = n;
     n->parent_node  = temp;
}

void NodeGraph::rotationRight(NodeGraph *n) {
     NodeGraph *temp = n->left_node;
     n->left_node = temp->right_node;
     if (temp->right_node != NULL)
         temp->right_node->parent_node = n;
     if (n->parent_node == NULL) {
         temp->parent_node = NULL;
     } else if (n->parent_node->left_node == n) {
         n->parent_node->left_node = temp;
     } else {
         n->parent_node->right_node = temp;
     }
     temp->right_node = n;
     n->parent_node = temp;
}

void NodeGraph::rotationLeft(NodeGraph **root, NodeGraph *x) {
     //y stored pointer of right child of x
     NodeGraph *y = x->right_node;

     //store y's left subtree's pointer as x's right child
     x->right_node = y->left_node;

     //update parent pointer of x's right
     if (x->right_node != NULL)
         x->right_node->parent_node = x;

     //update y's parent pointer
     y->parent_node = x->parent_node;

     // if x's parent is null make y as root of tree
     if (x->parent_node == NULL)
         (*root) = y;

     // store y at the place of x
     else if (x == x->parent_node->left_node)
         x->parent_node->left_node = y;
     else
         x->parent_node->right_node = y;

     // make x as left child of y
     y->left_node = x;

     //update parent pointer of x
     x->parent_node = y;
}

void NodeGraph::rotationRight(NodeGraph **root, NodeGraph *y) {
     NodeGraph *x = y->left_node;
     y->left_node = x->right_node;
     if (x->right_node != NULL)
         x->right_node->parent_node = y;
     x->parent_node = y->parent_node;
     if (x->parent_node == NULL)
         (*root) = x;
     else if (y == y->parent_node->left_node)
         y->parent_node->left_node = x;
     else
         y->parent_node->right_node = x;
    x->right_node = y;
    y->parent_node = x;
}

NodeGraph *NodeGraph::getRoot() {
     NodeGraph *t = this;
     while (t->getParentNode() != NULL)
            t = t->getParentNode();
     return t;
}

int NodeGraph::getSizeOfNodes(NodeGraph *node) {

    qDebug("- Get Size Of Nodes in Node Graphic!");

    if (node == NULL) {
        return 0;
      } else {
        return getSizeOfNodes(node->left_node) + 1 + getSizeOfNodes(node->right_node);
      }
}

NodeGraph *NodeGraph::getBrother() {

     qDebug("- Get Brother in Node Graphic!");

     NodeGraph *parent = getParentNode();
     if (parent == NULL)
        return NULL;
     if (is_left_node)
         return parent->getRightNode();
     if (is_right_node)
        return parent->getLeftNode();

    qCritical("- ERROR: can not identify a node in Node Graphic!");

    return NULL;
}

void NodeGraph::invertColor() {

     qDebug("- Invert Color is: %d at Node Graphic!", getEllipse()->getGradient()->getColor());

     switch (getEllipse()->getGradient()->getColor()) {
          case NodeEllipseGradient::black:
               getEllipse()->setGradient(NodeEllipseGradient::yellow);
               inverted_color = true;
          break;
          case NodeEllipseGradient::yellow:
               getEllipse()->setGradient(NodeEllipseGradient::black);
               inverted_color = false;
          break;
          case NodeEllipseGradient::red:
               getEllipse()->setGradient(NodeEllipseGradient::magenta);
               inverted_color = true;
          break;
          case NodeEllipseGradient::magenta:
               getEllipse()->setGradient(NodeEllipseGradient::red);
               inverted_color = false;
          break;
          case NodeEllipseGradient::blue:
               getEllipse()->setGradient(NodeEllipseGradient::cyan);
               inverted_color = true;
          break;
          case NodeEllipseGradient::cyan:
               getEllipse()->setGradient(NodeEllipseGradient::blue);
               inverted_color = false;
          break;
          case NodeEllipseGradient::green:
               getEllipse()->setGradient(NodeEllipseGradient::gray);
               inverted_color = true;
          break;
          case NodeEllipseGradient::gray:
               getEllipse()->setGradient(NodeEllipseGradient::green);
               inverted_color = false;
          break;
     }
     if (inverted_color == true) {
         getText()->setBrushOf(QColor(Qt::black));
         getText()->setPenOf(QColor(Qt::darkGray));
     } else {
         getText()->setBrushOf(QColor(Qt::white));
         getText()->setPenOf(QColor(Qt::yellow));
     }
}

void NodeGraph::identifyNode() {

     qDebug("- Identify Node in Node Graphic!");

     if (!parent_node) {
         IamRootNode(true);
         IamLeftNode(false);
         IamRightNode(false);
     } else {
         IamRootNode(false);
         if (parent_node->getIntegerValue() > integer_value) {
             IamLeftNode(true);
             IamRightNode(false);
         } else {
             IamLeftNode(false);
             IamRightNode(true);
         }
     }
}

void NodeGraph::orderZValueToUp() {

     qDebug("- Order Z Value to Up in Node Graphic!");

     NodeGraph *father, *brother;
     father = getParentNode();
     brother = getBrother();
     if (brother) {
         setZValue(brother->zValue());
         return;
     }
     if (father) {
         setZValue(father->zValue());
         while (!father->isRootNode()) {
              father->setZValue(father->zValue() + 1);
              father = father->getParentNode();
         }
         father->setZValue(father->zValue() + 1);
         return;
     }
     setZValue(1);
}

void NodeGraph::setupNodesAll(QPointF point) {

     qDebug("- Setup Nodes All in Node Graphic!");

     NodeEllipseItem *e = getEllipse();

     qDebug("\t- Ellipse at: %p\n\t- Line at: %p", e, getLine());

     e->setupEllipse(point.x(), point.y(), e->getWidth(), e->getHeight());
     getText()->updateToNode();
     if (getLine() != NULL)
         getLine()->updateToNode();
     if (left_node != NULL)
         left_node->setupNodesAll(left_node->getBottomOfParent());
     if (right_node != NULL)
         right_node->setupNodesAll(right_node->getBottomOfParent());

     qDebug("Setup Nodes All Finished in Node Graphic!");

}

QVariant NodeGraph::itemChange(GraphicsItemChange change, const QVariant &value) {

     qDebug("- Item Change in Node Graphic!");

     TreeGraph *tree = getTree();
     if (tree && getLine()) {
         switch (change) {
              case ItemPositionHasChanged:

                   qDebug("\t- Node Graph Item Position has changed...");

              break;
              default:
              break;
         }
     }
     return QGraphicsItem::itemChange(change, value);
}

/*
void NodeGraph::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {

     qDebug("- Drag Enter Event in Node Graphic!");

     QGraphicsItem::dragEnterEvent(event);
}

void NodeGraph::dragLeaveEvent(QGraphicsSceneDragDropEvent *event) {

     qDebug("- Drag Leave Event in Node Graphic!");

     QGraphicsItem::dragLeaveEvent(event);
}

void NodeGraph::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {

     qDebug("- Drag Move Event in Node Graphic!");

     QGraphicsItem::dragMoveEvent(event);
}

void NodeGraph::dropEvent(QGraphicsSceneDragDropEvent *event) {

     qDebug("- Drop Event in Node Graphic!");

     QGraphicsItem::dropEvent(event);
}

void NodeGraph::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {

     qDebug("- Hover Enter Event in Node Graphic!");

     QGraphicsItem::hoverEnterEvent(event);
}

void NodeGraph::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {

     qDebug("- Hover Leave Event in Node Graphic!");

     QGraphicsItem::hoverLeaveEvent(event);
}

void NodeGraph::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {

     qDebug("- Hover Move Event in Node Graphic!");

     QGraphicsItem::hoverMoveEvent(event);
}
*/

void NodeGraph::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {

     qDebug("- Mouse Double Click Event in Node Graphic!");

     setSelectedNode(selected_node == false);
     inverted_fixed = isColorInverted();
     SubChild   *child = getTree()->getSubChild();
     MainWindow *m_win = child->getMainWindow();
     char *str = new char[6];
     sprintf(str, "%d", integer_value);
     m_win->setTextForInput(str);
     m_win->updateButtonsEnabled(true, child->isEmpty() == false);
     QGraphicsItem::mouseDoubleClickEvent(event);
}

void NodeGraph::mousePressEvent(QGraphicsSceneMouseEvent *event) {

     qDebug("- Mouse Press Event in Node Graphic!");

     QPointF pt1, pt2;
     QRectF br = boundingRect();

     qDebug("\t- Bounds: \n\t\t- x: %5.3f\n\t\t- y: %5.3f\n\t\t- width: %5.3f\n\t\t- height: %5.3f", br.x(), br.y(), br.width(), br.height());
     qDebug("\t- Ellipse: (%5.3f, %5.3f, %5.3f, %5.3f)", getEllipse()->getX(), getEllipse()->getY(), getEllipse()->getWidth(), getEllipse()->getHeight());
     qDebug("\t- Position of Ellipse: (%5.3f, %5.3f)", getEllipse()->pos().x(), getEllipse()->pos().y());

     if (inverted_fixed == false) {
         setSelectedNode(true);
         invertColor();
     }
     if (getParentNode() != NULL && getLine() != NULL) {
         position_updated = false;
         pt1 = getLine()->getSourcePoint();
         pt2 = getLine()->getTargetPoint();

         qDebug("\t- Work with Line Source at point: (%5.3f, %5.3f)\n\t- And Line Target at point: (%5.3f, %5.3f)", pt1.x(), pt1.y(), pt2.x(), pt2.y());

         setMovedSourcePoint(pt1);
         setMovedTargetPoint(pt2);
     }
     setRestorePosition(QPointF(x(), y()));
     QGraphicsItem::mousePressEvent(event);
}

void NodeGraph::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {

     /*
     qDebug("- Mouse Move Event in Node Graphic!");
     qDebug("\t- Ellipse X is: %5.3f\n\t- Ellipse Y is: %5.3f", getEllipse()->getX(), getEllipse()->getY());
     */

     if (getParentNode() && getLine()) {

         /*
         qDebug("\t- Source Point of Line: (%5.3f, %5.3f)\n\t- Target Point of Line: (%5.3f, %5.3f)", getLine()->getSourcePoint().x(), getLine()->getSourcePoint().x(), getLine()->getTargetPoint().x(), getLine()->getTargetPoint().y());
         qDebug("\t\t- Line x: %5.3f, y: %5.3f", getLine()->x(), getLine()->y());
         */

         position_updated = getLine()->updateToNode(event->scenePos());
     } else {
         position_updated = true;
     }

     //qDebug("\t\t- Position Updated? %d", position_updated);

     QGraphicsItem::mouseMoveEvent(event);
}

void NodeGraph::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {

     qDebug("- Mouse Release Event in Node Graphic!");

     if (!inverted_fixed) {
         setSelectedNode(false);
         invertColor();
     }
     if (position_updated) {
         //if (getTree()->isAutoEdge()) {
         if (getTree()->getSubChild()->getMainWindow()->autoEdgeIsChecked() == true) {

             qDebug("\t- YES! is auto edge...");

             edge();
         } else {

             qDebug("\t- Not is Auto Edge!");

        }
     }
     QGraphicsItem::mouseReleaseEvent(event);
}

void NodeGraph::edge() {

     qDebug("- Edge in Node Graphic!");

     QRectF br = boundingRect();

     qDebug("\t- Bounds: \n\t\t- x: %5.3f\n\t\t- y: %5.3f\n\t\t- width: %5.3f\n\t\t- height: %5.3f", br.x(), br.y(), br.width(), br.height());
     qDebug("\t- Position of Ellipse is: (%5.3f, %5.3f)\n\t\t- Ellipse X is: %5.3f\n\t\t- Ellipse Y is: %5.3f", getEllipse()->pos().x(), getEllipse()->pos().y(), getEllipse()->getX(), getEllipse()->getY());
     qDebug("\t- This X is: %5.3f\n\t- This Y is: %5.3f", x(), y());

     setX(getRestorePosition().x());
     setY(getRestorePosition().y());
     getEllipse()->setGradient(NodeEllipseGradient::black);
     getEllipse()->update();
     getText()->updateToNode();
     getText()->update();
     if (getParentNode() != NULL && getLine() != NULL) {
         getLine()->updateToNode();
         getLine()->update();
     }
     update();
}

void NodeGraph::setDefaultColorsAll() {

     qDebug("- Set Default Colors All in Node Graphic!");

     if (isColorInverted() == true) {
         invertColor();
     }
     if (left_node != NULL)
         left_node->setDefaultColorsAll();
     if (right_node != NULL)
         right_node->setDefaultColorsAll();
}

int NodeGraph::maximumNodeValue(NodeGraph *root) {

     qDebug("- Maximum Node Value in Node Graphic!");

     while(root->right_node) {
           root = root->right_node;
     }
     return root->integer_value;
}

int NodeGraph::getPredecessorValue(NodeGraph *root) {

     qDebug("- Get Predecessor Value in Node Graphic!");

     if (root->left_node)
         return maximumNodeValue(root->left_node);
     NodeGraph *aux = root->parent_node;
     while(root == aux->left_node) {
           root = aux;
           aux = aux->parent_node;
     }
     return aux->integer_value;
}

NodeGraph *NodeGraph::findNode(int value, NodeGraph *root) {

     qDebug("- Find Node in Node Graphic!");

     if (root == NULL )
         return NULL;
     else if (value == root->integer_value)
         return root;
     else if (value < root->integer_value)
         return findNode(value, root->left_node);
     else if (value > root->integer_value)
         return findNode(value, root->right_node);
     else
         return NULL;
}


/*
// ********************************** NODE GRAPH RED BLACK (Derived Class of Node Graph) ********************* //

NodeGraphRedBlack::NodeGraphRedBlack(int value, TreeGraph *graph, NodeGraph **parentNode, QGraphicsItem *parent) : NodeGraph(value, graph, parentNode, parent) {

}

NodeGraphRedBlack::NodeGraphRedBlack(TreeGraph *graph, NodeGraph *source, NodeGraph **parentNode, QGraphicsItem *parent) : NodeGraph(graph, source, parentNode, parent) {

}

// ********************************** NODE GRAPH AVL (Derived Class of Node Graph) *************************** //

NodeGraphAVL::NodeGraphAVL(int value, TreeGraph *graph, NodeGraph **parentNode, QGraphicsItem *parent) : NodeGraph(value, graph, parentNode, parent) {

}

NodeGraphAVL::NodeGraphAVL(TreeGraph *graph, NodeGraph *source, NodeGraph **parentNode, QGraphicsItem *parent) : NodeGraph(graph, source, parentNode, parent) {

}
*/

// ********************** NODE ELLIPSE ITEM (Friend of Base Class Node Graph Item Group) ********************** //

NodeEllipseItem::NodeEllipseItem(QGraphicsItem *parent): QGraphicsEllipseItem(parent) {

     qDebug("- New Ellipse at: %p", this);

     createGradient();
}

NodeEllipseItem::NodeEllipseItem(NodeEllipseItem *source, QGraphicsItem *parent): QGraphicsEllipseItem(parent) {

     qDebug("- Copy of Ellipse at: %p\n\t- New Ellipse at: %p", source, this);

     copyGradient(source->getGradient());
}

NodeEllipseItem::~NodeEllipseItem() {

     qDebug("- Delete ellipse at: %p", this);

     delete this->gradient;
}

void NodeEllipseItem::setupEllipse(qreal x, qreal y, qreal width, qreal height) {

     qDebug("- Setup of Ellipse at: %p in Node Ellipse Item\n\t- Rectangle: (%5.3f, %5.3f, %5.3f, %5.3f)\n\t- Gradient at: %p", this, x, y, width, height, gradient);

     setRect(x, y, width, height);
     this->x = x;
     this->y = y;
     this->width  = width;
     this->height = height;

     NodeGraphItemGroup *grp = qgraphicsitem_cast <NodeGraphItemGroup *> (this->parentItem());

     qDebug("Group at: %p", grp);

     switch (grp->getColor()) {
             case NodeGraphItemGroup::BLACK:
                  setGradient(NodeEllipseGradient::black);
                  break;
             case NodeGraphItemGroup::RED:
                  setGradient(NodeEllipseGradient::red);
                  break;
             case NodeGraphItemGroup::BLUE:
                  setGradient(NodeEllipseGradient::blue);
                  break;
             case NodeGraphItemGroup::GREEN:
                  setGradient(NodeEllipseGradient::green);
                  break;
     }

     qDebug("- Setup of Ellipse Finished in Node Ellipse Item!");

}

void NodeEllipseItem::createGradient() {

     qDebug("- Create Gradient in Node Ellipse Item!");

     gradient = new NodeEllipseGradient(this);
}

void NodeEllipseItem::setGradient(int color) {

     qDebug("- Set Gradient in Node Ellipse Item!");

     const qreal half  = width / 2.0;
     const qreal quart = half  / 2.0;
     const qreal eight = quart / 2.0;

     qDebug("\t- Base Color is: %d and Width is: %5.3f", color, width);

     NodeGraph *srcNode = qgraphicsitem_cast <NodeGraph *> (this->parentItem());
     NodeEllipseGradient::colors base = (NodeEllipseGradient::colors) color;
     NodeEllipseGradient &radial = *gradient;
     gradient->setColorsOf(base);
     gradient->setRadiusIn(half);
     if (srcNode->isLeftNode()) {
         gradient->setCenterIn(QPointF(x + half + eight, y + quart));
         gradient->setFocalIn(QPointF(x + half + eight, y + quart));
     } else if (srcNode->isRightNode()) {
         gradient->setCenterIn(QPointF(x + quart, y + quart));
         gradient->setFocalIn(QPointF(x + quart, y + quart));
     } else {
         gradient->setCenterIn(QPointF(half, quart));
         gradient->setFocalIn(QPointF(half, quart));
     }
     setBrush(radial);

     qDebug("- Set Gradient Finished in Node Ellipse Item!");

}

void NodeEllipseItem::copyGradient(NodeEllipseGradient *srcGradient) {

     qDebug("- Copy Gradient at: %p in Node Ellipse Item!", srcGradient);

     gradient = new NodeEllipseGradient(srcGradient, this);
}

// ************************** NODE ELLIPSE GRADIENT (Friend of Class Node Ellipse Item) *********************** //

NodeEllipseGradient::NodeEllipseGradient(NodeEllipseItem *node) {

     qDebug("- New Gradient at: %p in Node Ellipse Gradient!", this);

     setSpread(QGradient::PadSpread);
     setCoordinateMode(QGradient::LogicalMode);
     source_node = node;
}

NodeEllipseGradient::NodeEllipseGradient(NodeEllipseGradient *source, NodeEllipseItem *node) {

     qDebug("- Copy of Gradient at: %p in Node Ellipse Gradient!\n\t- New Gradient at: %p\n\t- Node Ellipse Item at: %p", source, this, node);

     setSpread(source->spread());
     setCoordinateMode(source->coordinateMode());
     source_node = node;
     setColorsOf(source->getColor());
     setCenterIn(source->getCenter());
     setFocalIn(source->getFocal());
     setRadiusIn(source->getRadius());
}

void NodeEllipseGradient::setColorsOf(NodeEllipseGradient::colors color) {

     qDebug("- Set Colors Of... in Node Ellipse Gradient!");

     int max = 255, mid = 79, min = 47;
     switch (color) {
          case NodeEllipseGradient::black:
               color1 = Qt::black;
               color2 = Qt::darkGray;
               color3 = Qt::gray;
               color4 = Qt::lightGray;
          break;
          case NodeEllipseGradient::red:
               color1 = Qt::darkRed;
               color2 = Qt::red;
               color3 = QColor(max, min, min);
               color4 = QColor(max, mid, mid);
          break;
          case NodeEllipseGradient::green:
               color1 = Qt::darkGreen;
               color2 = Qt::green;
               color3 = QColor(min, max, min);
               color4 = QColor(mid, max, mid);
          break;
          case NodeEllipseGradient::blue:
               color1 = Qt::darkBlue;
               color2 = Qt::blue;
               color3 = QColor(min, min, max);
               color4 = QColor(mid, mid, max);
          break;
          case NodeEllipseGradient::cyan:
               color1 = Qt::darkCyan;
               color2 = Qt::cyan;
               color3 = QColor(min, max, max);
               color4 = QColor(mid, max, max);
          break;
          case NodeEllipseGradient::magenta:
               color1 = Qt::darkMagenta;
               color2 = Qt::magenta;
               color3 = QColor(max, min, max);
               color4 = QColor(max, mid, max);
          break;
          case NodeEllipseGradient::yellow:
               color1 = Qt::darkYellow;
               color2 = Qt::yellow;
               color3 = QColor(max, max, min);
               color4 = QColor(max, max, mid);
          break;
          case NodeEllipseGradient::gray:
               color1 = QColor(min, min, min);
               color2 = Qt::darkGray;
               color3 = Qt::gray;
               color4 = Qt::lightGray ;
          break;
          default:
               color1 = QColor(max, max, max);
               color2 = QColor(mid, mid, mid);
               color3 = QColor(min, min, min);
               color4 = Qt::black;
     }
     setColorAt(0.00, color4);
     setColorAt(0.25, color3);
     setColorAt(0.50, color2);
     setColorAt(1.00, color1);
     default_color = color;
}

void NodeEllipseGradient::setCenterIn(QPointF c) {

     qDebug("- Set Center In... at: %p in Node Ellipse Gradient!\n\t- Center at point: (%5.3f, %5.3f", this, c.x(), c.y());

     setCenter(c);
     center_point = c;
}

void NodeEllipseGradient::setFocalIn(QPointF f) {

     qDebug("- Set Focal In... at: %p in Node Ellipse Gradient!\n\t- Focal at point: (%5.3f, %5.3f", this, f.x(), f.y());

     setFocalPoint(f);
     focal_point = f;
}

void NodeEllipseGradient::setRadiusIn(qreal rad) {

     qDebug("- Set Radius In... at: %p in Node Ellipse Gradient\n\t- Radius is: %5.3f", this, rad);

     setRadius(rad);
     radius_real = rad;
}

// ************************* NODE LINE ITEM (Friend of Base Class Node Graph Item Group) ************************ //

NodeLineItem::NodeLineItem(QGraphicsItem *parent): QGraphicsLineItem(parent), arrow_size(6.0) {

     qDebug("- New Line at: %p in Node Line Item!", this);

     arrow_up = arrow_down =  NULL;
     setAcceptedMouseButtons(false);
}

NodeLineItem::NodeLineItem(NodeLineItem *source, QGraphicsItem *parent): QGraphicsLineItem(parent), arrow_size(6.0) {

     qDebug("- Copy of Line at: %p in Node Line Item!\n\t- New Line at: %p", source, this);

     arrow_up = arrow_down =  NULL;

     if (source != NULL)
         setAcceptedMouseButtons(source->acceptedMouseButtons());
}

NodeLineItem::~NodeLineItem() {

     qDebug("- Delete Line at: %p in Node Line Item!\n\t- Delete Arrow Up at: %p\n\t- Delete Arrow Down at: %p", this, arrow_up, arrow_down);

     if (this->arrow_up != NULL)
         delete this->arrow_up;
     if (this->arrow_down != NULL)
         delete this->arrow_down;
}

void NodeLineItem::setSourceNode(NodeGraph *node) {

     qDebug("- Set Source Node in Node Line Item!");

     source = node;
     adjust();
}

void NodeLineItem::setTargetNode(NodeGraph *node) {

     qDebug("- Set Target Node in Node Line Item!");

     target = node;
     adjust();
}

void NodeLineItem::setupLine(NodeGraph *sourceNode, NodeGraph *targetNode) {

     qDebug("- Setup of Line at: %p in Node Line Item!\n\t- Node Source at: %p\n\t- Node Target at: %p", this, sourceNode, targetNode);

     source = sourceNode;
     target = targetNode;
     source->addLine(this);
     arrow_up   = new QGraphicsPolygonItem(this);
     arrow_down = new QGraphicsPolygonItem(this);
     adjust();
     setPositionOf();
     setPenOf();
     setArrowsOf();
}

bool NodeLineItem::stretch(QPointF pos) {

     qDebug("- Stretch in Node Line Item!");

     if (source == NULL || target == NULL)
         return false;
     NodeEllipseItem *es = source->getEllipse();
     NodeEllipseItem *et = target->getEllipse();
     QRectF rs, rt, ru = QRectF(source_point, target_point);
     QPointF ps, pt, bk1, bk2, nw1, nw2;
     QLineF line;
     qreal sex, sey, tex, tey;
     bk1 = line.p1();
     bk2 = line.p2();
     rs = es->boundingRect();
     rt = et->boundingRect();
     rs = rs.normalized();
     rt = rt.normalized();
     ru = ru.normalized();

     qDebug("\t- Stretch Line:\n\t- Source Point: (%5.3f, %5.3f)\n\t- Target Point: (%5.3f, %5.3f)", source_point.x(), source_point.y(), target_point.x(), target_point.y());
     qDebug("\t\t- Position:  (%5.3f, %5.3f)", pos.x(), pos.y());
     qDebug("\t\t- Rectangle: (%5.f, %5.f, %5.f, %5.f", ru.x(), ru.y(), ru.width(), ru.height());
     qDebug("\t\t\t- Rectangle Right Point X: %5.3f\n\t\t\t- Rectangle Bottom Point Y: %5.3f", ru.right(), ru.bottom());

     if (pos.x() > ru.right()) {

         qDebug("\t\t- X position after rectangle right point!");

         sex = rs.right();
         tex = rt.left();
     } else {
         if (pos.x() > ru.left()) {

             qDebug("\t\t- X position after rectangle left point!");

             sex = rs.center().x();
             tex = rt.center().x();
         } else {

             qDebug("\t\t- X position before rectangle left point!");

             sex = rs.left();
             tex = rt.right();
         }
     }
     if (pos.y() > ru.bottom()) {

         qDebug("\t\t- Y position after retangle bottom point!");

         sey = rs.bottom();
         tey = rt.top();
     } else {

         qDebug("\t\t- Y position before retangle bottom point!");

         if (pos.y() > ru.top()) {

             qDebug("\t\t- Y position after rectangle top point!");

             sey = rs.center().y();
             tey = rt.center().y();
         } else {

             qDebug("\t\t- Y position before rectangle top point!");

             sey = rs.top();
             tey = rt.bottom();
         }
     }

     qDebug("\t\t- Source X: %5.3f\n\t\t- Source Y: %5.3f\n\t\t- Target X: %5.3f\n\t\t- Target Y: %5.3f", sex, sey, tex, tey);

     ps = mapFromItem(source, sex, sey);
     pt = mapFromItem(target, tex, tey);
     if (source->isLeftNode()) {
         nw1 = ps;
         nw2 = pt;
     } else {
         nw1 = pt;
         nw2 = ps;
     }
     if (nw1 != bk1 && nw2 != bk2) {
         line.setPoints(nw1, nw2);
         setGeometryOf(line);
         return true;
     }
     return false;
}

void NodeLineItem::adjust() {

     qDebug("- Adjust Line in Node Line Item!");

     if (source == NULL || target == NULL)
         return;
     qDebug("\t- Source Point: (%5.3f, %5.3f)\n\t- Target Point: (%5.3f, %5.3f)", source_point.x(), source_point.y(), target_point.x(), target_point.y());

     NodeEllipseItem *es = source->getEllipse();
     NodeEllipseItem *et = target->getEllipse();
     QRectF rs, rt;
     qreal sex, sey, tex, tey;
     QPointF ps, pt;
     QLineF line;
     rs = es->boundingRect();
     rt = et->boundingRect();
     if (source->isRightNode()) {
         sex = rs.bottomRight().x();
         sey = rs.bottomRight().y();
         tex = rt.topLeft().x();
         tey = rt.topLeft().y();
     } else if (source->isLeftNode()) {
         tex = rt.topRight().x();
         tey = rt.topRight().y();
         sex = rs.bottomLeft().x();
         sey = rs.bottomLeft().y();
     } else {
         return;
     }
     ps = mapFromItem(source, sex, sey);
     pt = mapFromItem(target, tex, tey);
     if (source->isLeftNode()) {
         line.setPoints(ps, pt);
     } else {
         line.setPoints(pt, ps);
     }
     setGeometryOf(line);

     qDebug("- Adjust Line Finished in Node Line Item!");

}

void NodeLineItem::updateToNode() {

     qDebug("- Update To Node in Node Line Item!");

     adjust();
     setPositionOf();
     setArrowsOf();
}

bool NodeLineItem::updateToNode(QPointF pos) {

     qDebug("- Update To Node with point at: (%5.3f, %5.3f) in Node Line Item!", pos.x(), pos.y());

     if (stretch(pos)) {;
         setPositionOf();
         setArrowsOf();
         return true;
     }
     return false;
}

QRectF NodeLineItem::boundingRect() const {

     //qDebug("- Bounding Rectangle in Node Line Item!");

     if (source == NULL || target == NULL) {
         return QRectF();
     }
     qreal pen_width = 1.0;
     qreal extra = (pen_width + arrow_size) / 2.0;
     return QRectF(source_point, QSizeF(target_point.x() - source_point.x(), target_point.y() - source_point.y())).normalized().adjusted(-extra, -extra, extra, extra);
}

QPointF *NodeLineItem::arrayOfPoints(QRectF rect) {

     qDebug("- Array Of Points in Node Line Item!");

     QPointF *pts = new QPointF[8];
     pts[0].setX(rect.center().x());
     pts[0].setY(rect.top());
     pts[1].setX(rect.topRight().x());
     pts[1].setY(rect.topRight().y());
     pts[2].setX(rect.right());
     pts[2].setY(rect.center().y());
     pts[3].setX(rect.bottomRight().x());
     pts[3].setY(rect.bottomRight().y());
     pts[4].setX(rect.center().x());
     pts[4].setY(rect.bottom());
     pts[5].setX(rect.bottomLeft().x());
     pts[5].setY(rect.bottomLeft().y());
     pts[6].setX(rect.left());
     pts[6].setY(rect.center().y());
     pts[7].setX(rect.topLeft().x());
     pts[7].setY(rect.topLeft().y());
    return pts;
}

void NodeLineItem::setPositionOf() {

     qDebug("- Set Position Of... in Node Line Item!");

     if (source == NULL || target == NULL)
         return;
     QLineF line(source_point, target_point);
     this->setLine(line);
}

void NodeLineItem::setArrowsOf() {

     qDebug("- Set Arrows Of... in Node Line Item!");

     double angle = ::acos(line().dx() / line().length());
     if (line().dy() >= 0) {
         angle = TwoPi - angle;
     }
     QPointF sourceArrowP1 = source_point + QPointF(sin(angle + Pi / 3) * arrow_size, cos(angle + Pi / 3) * arrow_size);
     QPointF sourceArrowP2 = source_point + QPointF(sin(angle + Pi - Pi / 3) * arrow_size, cos(angle + Pi - Pi / 3) * arrow_size);
     QPointF targetArrowP1 = target_point + QPointF(sin(angle - Pi / 3) * arrow_size, cos(angle - Pi / 3) * arrow_size);
     QPointF targetArrowP2 = target_point + QPointF(sin(angle - Pi + Pi / 3) * arrow_size, cos(angle - Pi + Pi / 3) * arrow_size);
     QVector <QPointF> v_points_source;
     QVector <QPointF> v_points_target;
     v_points_source.append(line().p1());
     v_points_source.append(sourceArrowP1);
     v_points_source.append(sourceArrowP2);
     v_points_target.append(line().p2());
     v_points_target.append(targetArrowP1);
     v_points_target.append(targetArrowP2);
     QPolygonF polygon_source(v_points_source);
     QPolygonF polygon_target(v_points_target);
     arrow_up->setBrush(Qt::black);
     arrow_down->setBrush(Qt::black);
     arrow_up->setPolygon(polygon_source);
     arrow_down->setPolygon(polygon_target);
}

void NodeLineItem::setGeometryOf(QLineF line) {

     qDebug("- Set Geometry Of... in Node Line Item!");

     //line.setLength(100);

     //exit(2);

     qreal length = line.length();
     prepareGeometryChange();
     if (length > qreal(40.0)) {
         QPointF edgeOffset((line.dx() * 50.0) / length, (line.dy() * 50.0) / length);
         source_point = line.p1() + edgeOffset;
         target_point = line.p2() - edgeOffset;
     } else {
         source_point = target_point = line.p1();
     }
}

void NodeLineItem::setPenOf() {

     qDebug("- Set Pen Of... in Node Line Item!");

     setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
}

// ******************************** NODE TEXT ITEM (Friend of Base) ******************************* //

NodeTextItem::NodeTextItem(QGraphicsItem *parent): QGraphicsSimpleTextItem(parent) {

     qDebug("- New Node Text Item at: %p", this);

     setZValue(1);
     font.setFamily("");
}

NodeTextItem::NodeTextItem(NodeTextItem *source, QGraphicsItem *parent): QGraphicsSimpleTextItem(parent) {

     qDebug("- Copy of Node Text Item at: %p\n\t- New Text at: %p", source, this);

     setZValue(1);
     font.setFamily("");
}

void NodeTextItem::setArea() {

     qDebug("- Set Area in Node Text Item!");

     NodeEllipseItem *e = qgraphicsitem_cast <NodeEllipseItem *> (parentItem());
     area.setX(e->getX());
     area.setY(e->getY());
     area.setWidth(e->getWidth());
     area.setHeight(e->getHeight());
}

void NodeTextItem::setupText(QString text) {

     qDebug("- Setup of Text at: %p in Node Text Item!\n\t- Text Value: %s", this, text.toStdString().c_str());

     string = text;
     setText(text);
     updateToNode();
}

void NodeTextItem::updateToNode() {

     qDebug("- Update To Node in Node Text Item!");

     setArea();
     if (font.family().isEmpty()) {
         setFontOf();
     }
     setPositionOf();
     setBrushOf(QColor(Qt::white));
     setPenOf(QColor(Qt::yellow));
}

void NodeTextItem::setFontOf() {

     qDebug("- Set Font Of... in Node Text Item!");

     int len = text().count();
     qreal a = area.width(), b = len + 1.0, c = len + 2.5, d = len * 10.0;
     qreal fs = a - ((a / c) * b) + (a / d);
     font.setFamily("Courier");
     font.setBold(true);
     font.setPointSizeF(fs);
     setFont(font);
}

void NodeTextItem::setPositionOf() {

     qDebug("- Set Position Of... in Node Text Item!");

     QRectF inner = boundingRect();
     qreal w = (area.width() - inner.width()) / 2.0;
     qreal h = ((area.height() - inner.height()) / 2.0);
     qreal x = area.x() + w;
     qreal y = area.y() + h;
     setPos(x, y);
}

void NodeTextItem::setBrushOf(QColor in) {

     qDebug("- Set Brush Of... in Node Text Item!\n\t-Color is: %s", in.name().toStdString().c_str());

     QBrush brush(in);
     setBrush(brush);
     this->brush = brush;
}

void NodeTextItem::setPenOf(QColor out) {

     qDebug("- Set Pen Of... in Node Text Item!\n\t-Color is: %s", out.name().toStdString().c_str());

     qreal size = font.pointSizeF() / (static_cast <NodeEllipseItem *> (parentItem())->getWidth());
     QPen  pen(out, size, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
     setPen(pen);
     this->pen = pen;
}

