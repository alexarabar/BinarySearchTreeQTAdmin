/****************************************************************************
** Binary Search Tree Utility QT-4 Version 1.00
** Author:  Alexandre A. Barbosa
** Created: Fev-14-2010
** Updated: Apr-08-2015
** Name:    treescene.h
****************************************************************************/

#ifndef TREESCENE_H
#define TREESCENE_H
#include <QGraphicsView>
#include <QGraphicsScene>
//#include <QGraphicsRectItem>
//#include <QGraphicsItem>
//#include <QTransform>
#include "subchild.h"
#include "nodeitem.h"

QT_BEGIN_NAMESPACE
     class SubChild;
     class NodeGraph;
     //class NodeEllipseItem;
     //class NodeLineItem;
     //class NodeTextItem;
QT_END_NAMESPACE


class TreeGraphScene: public QGraphicsScene {
     public:
          enum type {normal = 0, red_black = 1, avl = 2};
          TreeGraphScene(QGraphicsView *view, QWidget *parent = NULL);
          TreeGraphScene(TreeGraphScene *source, QGraphicsView *view, QWidget *parent = NULL);
          TreeGraphScene(TreeGraphScene *source, QWidget *parent = NULL);
          virtual ~TreeGraphScene();
          SubChild        *getSubChild();
          //inline int getNodeCounter()              {return node_counter;}
          inline qreal getLengthOfNode()         {return length_of_node;}
          inline QPointF getStartPoint()            {return start_point;}
          inline void setNewPosition(QPointF pos)   {new_position = pos;}
          inline QPointF getNewPosition()          {return new_position;}
          inline QGraphicsView *getGraphicsView()     {return graph_view;}
          inline void setTypeOfTree(TreeGraphScene::type type) {type_of_tree = type;}
          inline TreeGraphScene::type getTypeOfTree()          {return type_of_tree;}
     protected:
          void setupScene(QPointF point);
          NodeTextItem    *getItemText(QPointF point);
          NodeEllipseItem *getItemEllipse(QPointF point, QString *value = NULL);
          NodeGraph       *getNodeItem(QPointF point);
          /*
          inline void setNodeCounter(int count)        {node_counter = count;}
          inline void setLengthOfNode(qreal len)       {length_of_node = len;}
          inline void setStartPoint(QPointF point)      {start_point = point;}
          inline void startCounter(int value)          {node_counter = value;}
          inline void increaseCounter()                      {node_counter++;}
          inline void decreaseCounter()                      {node_counter--;}
          */
     private:
          //int                node_counter;
          qreal              length_of_node;
          QPointF               start_point;
          QPointF              new_position;
          QGraphicsView         *graph_view;
          TreeGraphScene::type type_of_tree;
};

class TreeGraph: public TreeGraphScene {
     public:
          TreeGraph(int value, QGraphicsView *view, QWidget *parent = NULL);
          TreeGraph(int value, TreeGraph *source, QGraphicsView *view, QWidget *parent = NULL);
          TreeGraph(TreeGraph *source, QWidget *parent = NULL);
          //TreeGraph(QGraphicsView *view, QWidget *parent = NULL);
          virtual ~TreeGraph();
          /*
          NodeGraph *hasParentNode(NodeGraph *curNode);
          NodeGraph   *hasLeftNode(NodeGraph *curNode);
          NodeGraph  *hasRightNode(NodeGraph *curNode);
          */
          void setupTree(NodeGraph *node);
          NodeGraph *getRootOf(NodeGraph *node);
          NodeGraph *copyNodes(NodeGraph *node, NodeGraph **parent = NULL);
          bool addNode(int value);
          bool deleteNode(int value);
          bool searchNode(int value);
          void addNodesToGraph();
          void checkCollides(NodeGraph *node, NodeGraph *other = NULL);
          void increaseDistance(NodeGraph *node, NodeGraph *other);
          void invertColorAll(NodeGraph *node, bool flag = false);
          void selectRectAll(QRectF rect, NodeGraph *node);
          void valuesPreOrder(QList <QString> &listNodes);
          void valuesInOrder(QList <QString> &listNodes);
          void valuesPosOrder(QList <QString> &listNodes);
          int  sizeOfTree();
          void setSelectedNodes(NodeGraph *node);
          int *getSelectedNodes();
          int  getSelectedNodesCount();
          void clearSelectedNodes();
          void selectNodesAll(NodeGraph *node);
          TreeGraph *convertToNormal();
          TreeGraph *convertToRedBlack(bool &flag);
          TreeGraph *convertToAVL();
          //void addNodesAllRedBlack(NodeGraph *root, NodeGraph *old);
          inline void setRootNode(NodeGraph *node) {rootNode = node;}
          inline void setLastNode(NodeGraph *node) {lastNode = node;}
          inline NodeGraph *getLastNode()          {return lastNode;}
          inline NodeGraph *getRootNode()          {return rootNode;}
          /*
          inline void setPreviousTree(TreeGraph *curTree) {previousTree = curTree;}
          inline void setNextTree(TreeGraph *curTree)         {nextTree = curTree;}
          inline TreeGraph *getPreviousTree()                {return previousTree;}
          inline TreeGraph *getNextTree()                        {return nextTree;}
          */
     protected:
          /*
          void  drawBackground (QPainter *painter, const QRectF &rect);
          void  drawForeground (QPainter *painter, const QRectF &rect);
          */
          void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
          /*
          void  dragEnterEvent    (QGraphicsSceneDragDropEvent *event);
          void  dragLeaveEvent    (QGraphicsSceneDragDropEvent *event);
          void  dragMoveEvent     (QGraphicsSceneDragDropEvent *event);
          void  dropEvent         (QGraphicsSceneDragDropEvent *event);
          void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);
          */
          void mousePressEvent       (QGraphicsSceneMouseEvent *event);
          void mouseMoveEvent        (QGraphicsSceneMouseEvent *event);
          void mouseReleaseEvent     (QGraphicsSceneMouseEvent *event);
     private:
          void fixBinaryTree(NodeGraph *node);
          bool isBinaryTree(NodeGraph *node, int min, int max);
          /*
          void correctBSTUtil(NodeGraph *root, NodeGraph **first, NodeGraph **middle, NodeGraph **last, NodeGraph **prev);
          void correctBST(NodeGraph *root);
          void recoverTree(NodeGraph *root);
          */
          NodeGraph *lastNode;
          NodeGraph *rootNode;
          QList <NodeGraph *> selectedNodes;
          QPointF    selectedPointToStart;
          //QPointF    restorePointToBack;
          QRectF     startToScene;
          //QRectF     backToScene;
          QGraphicsRectItem *selectedRect;
};


#endif // TREESCENE_H
