/****************************************************************************
** Binary Search Tree Utility QT-4 Version 1.00
** Author:  Alexandre A. Barbosa
** Created: Fev-14-2010
** Updated: Apr-08-2015
** Name:    nodeitem.h
****************************************************************************/

#ifndef NODEITEM_H
#define NODEITEM_H
#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsSceneMouseEvent>
#include "treescene.h"

QT_BEGIN_NAMESPACE
     class TreeGraph;
     class NodeEllipseItem;
     class NodeEllipseGradient;
     class NodeLineItem;
     class NodeTextItem;
QT_END_NAMESPACE

class NodeGraphItemGroup: public QGraphicsItemGroup {
     public:
          enum Colors {BLACK = 0, RED = 1, BLUE = 2, GREEN = 3};
          NodeGraphItemGroup(TreeGraph *graph, QGraphicsItem *parent = NULL);
          NodeGraphItemGroup(NodeGraphItemGroup *source, TreeGraph *graph, QGraphicsItem *parent = NULL);
          virtual ~NodeGraphItemGroup();
          void setupGroup(QPointF point, QString value);
          void Initialize();
          NodeLineItem *createLine();
          NodeLineItem *copyLine(NodeLineItem *source);
          bool          destroyLine();
          void addLine(NodeLineItem *li);
          void removeLine();
          inline NodeEllipseItem   *getEllipse()         {return ellipse;}
          inline NodeLineItem       *getLine()              {return line;}
          inline NodeTextItem       *getText()              {return text;}
          NodeGraphItemGroup::Colors getColor()           {return color;}
          void setColor(NodeGraphItemGroup::Colors color) {this->color = color;}
     protected:
          inline TreeGraph *getTree()                      {return tree;}
          inline void setEllipse(NodeEllipseItem *ep)     {ellipse = ep;}
          inline void setLine(NodeLineItem *ln)              {line = ln;}
          inline void setText(NodeTextItem *tx)              {text = tx;}
          inline void setMovedSourcePoint(QPointF pt) {moved_source_point = pt;}
          inline void setMovedTargetPoint(QPointF pt) {moved_target_point = pt;}
          inline QPointF getMovedSourcePoint()      {return moved_source_point;}
          inline QPointF getMovedTargetPoint()      {return moved_target_point;}
          inline void setRestorePosition(QPointF pt) {restore_position = pt;}
          inline QPointF getRestorePosition()        {return restore_position;}
     private:
          void checkBounds();
          TreeGraph           *tree;
          NodeEllipseItem  *ellipse;
          NodeLineItem        *line;
          NodeTextItem        *text;
          QPointF moved_source_point;
          QPointF moved_target_point;
          QPointF   restore_position;
          NodeGraphItemGroup::Colors color;
};

class NodeGraph: public NodeGraphItemGroup {
     public:
          NodeGraph(int value, TreeGraph *graph, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
          NodeGraph(TreeGraph *graph, NodeGraph *source, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
          virtual ~NodeGraph();
          void setupNode();
          void createNode(NodeGraph **parentNode);
          void clearNodesAll();
          void loadListValuesPreOrder(QList <QString> &listNodes);
          void loadListValuesInOrder(QList <QString> &listNodes);
          void loadListValuesPosOrder(QList <QString> &listNodes);
          void loadListNodesPreOrder(QList <NodeGraph *> &listnodes);
          void adjust();
          void invertColor();
          void identifyNodesAll();
          bool advance();
          QPointF getBottomOfParent();
          QRectF boundingRect() const;
          QPainterPath  shape() const;
          NodeGraph *insertNode(int value, TreeGraph *graph, NodeGraph *curNode, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
          NodeGraph *insertNodeRedBlack(int value, TreeGraph *graph, NodeGraph *curNode, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
          NodeGraph *insertNodeAVL(int value, TreeGraph *graph, NodeGraph *curNode, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
          NodeGraph *deleteNode(int value, NodeGraph *root);
          NodeGraph *searchNode(int value);
          NodeGraph *hasCollision(NodeGraph *otherNode);
          NodeGraph *getAncestorOf(NodeGraph *otherNode);
          NodeGraph *rotationLeft();
          NodeGraph *rotationRight();
          NodeGraph *getRoot();
          int getSizeOfNodes(NodeGraph *node);
          inline NodeGraph *getLeftNode()     {return left_node;}
          inline NodeGraph *getRightNode()   {return right_node;}
          inline NodeGraph *getParentNode() {return parent_node;}
          inline int getIntegerValue()    {return integer_value;}
          inline bool isSelectedNode()    {return selected_node;}
          inline bool isLeftNode()         {return is_left_node;}
          inline bool isRightNode()       {return is_right_node;}
          inline bool isRootNode()         {return is_root_node;}
          inline bool isColorInverted()  {return inverted_color;}
          inline void setLeftNode(NodeGraph *curNode)       {left_node = curNode;}
          inline void setRightNode(NodeGraph *curNode)     {right_node = curNode;}
          inline void setParentNode(NodeGraph *curNode)   {parent_node = curNode;}
          inline void setIntegerValue(int value)          {integer_value = value;}
          inline void setSelectedNode(bool selected)   {selected_node = selected;}
          void debugPrintTMP();
     protected:
          void identifyNode();
          void orderZValueToUp();
          void setupNodesAll(QPointF point);
          /*
          void dragEnterEvent     (QGraphicsSceneDragDropEvent *event);
          void dragLeaveEvent     (QGraphicsSceneDragDropEvent *event);
          void dragMoveEvent      (QGraphicsSceneDragDropEvent *event);
          void dropEvent          (QGraphicsSceneDragDropEvent *event);
          void hoverEnterEvent       (QGraphicsSceneHoverEvent *event);
          void hoverLeaveEvent       (QGraphicsSceneHoverEvent *event);
          void hoverMoveEvent        (QGraphicsSceneHoverEvent *event);
          */
          void mouseDoubleClickEvent (QGraphicsSceneMouseEvent *event);
          void mousePressEvent       (QGraphicsSceneMouseEvent *event);
          void mouseMoveEvent        (QGraphicsSceneMouseEvent *event);
          void mouseReleaseEvent     (QGraphicsSceneMouseEvent *event);
          QVariant itemChange(GraphicsItemChange change, const QVariant &value);
          NodeGraph *getBrother();
          inline void IamRootNode(bool on)                  {is_root_node = on;}
          inline void IamLeftNode(bool on)                  {is_left_node = on;}
          inline void IamRightNode(bool on)                {is_right_node = on;}
     private:
          void edge();
          void setDefaultColorsAll();
          int maximumNodeValue(NodeGraph *root);
          int getPredecessorValue(NodeGraph *root);
          NodeGraph *findNode(int value, NodeGraph *root);
          /*
          NodeGraph *rotationLeft(NodeGraph *node);
          NodeGraph *rotationRight(NodeGraph *node);
          */
          void rotationLeft(NodeGraph *node);
          void rotationRight(NodeGraph *node);
          void rotationLeft(NodeGraph **root, NodeGraph *node);
          void rotationRight(NodeGraph **root, NodeGraph *node);

          NodeGraph *getGrandParent(NodeGraph *node);
          NodeGraph *getUncle(NodeGraph *node);
          void insertNodeRedBlackFixCase1(NodeGraph *node);
          void insertNodeRedBlackFixCase2(NodeGraph *node);
          void insertNodeRedBlackFixCase3(NodeGraph *node);
          void insertNodeRedBlackFixCase4(NodeGraph *node);
          void insertNodeRedBlackFixCase5(NodeGraph *node);

          void insertNodeRedBlackFix(NodeGraph *node);
          void insertNodeRedBlackFix(NodeGraph **root, NodeGraph *node);

          void insertNodeAVLFix(NodeGraph *node);
          int  factor;
          bool is_left_node;
          bool is_right_node;
          bool is_root_node;
          bool is_red_black;
          bool is_avl;
          bool selected_node;
          bool inverted_color;
          bool inverted_fixed;
          bool position_updated;
          int  integer_value;
          NodeGraph *parent_node;
          NodeGraph   *left_node;
          NodeGraph  *right_node;
};

/*
class NodeGraphRedBlack: public NodeGraph {
     public:
          NodeGraphRedBlack(int value, TreeGraph *graph, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
          NodeGraphRedBlack(TreeGraph *graph, NodeGraph *source, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
     private:
          bool red;
};

class NodeGraphAVL: public NodeGraph {
     public:
          NodeGraphAVL(int value, TreeGraph *graph, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
          NodeGraphAVL(TreeGraph *graph, NodeGraph *source, NodeGraph **parentNode = NULL, QGraphicsItem *parent = NULL);
     private:
          int factor;
};
*/

class NodeEllipseItem: public QGraphicsEllipseItem {
     friend class NodeGraphItemGroup;
     public:
          NodeEllipseItem(QGraphicsItem *parent = NULL);
          NodeEllipseItem(NodeEllipseItem *source, QGraphicsItem *parent = NULL);
          virtual ~NodeEllipseItem();
          void setupEllipse(qreal x, qreal y, qreal width, qreal height);
          void setGradient(int color);
          inline qreal getX()                              {return x;}
          inline void  setX(qreal xValue)                {x = xValue;}
          inline qreal getY()                              {return y;}
          inline void  setY(qreal yValue)                {y = yValue;}
          inline qreal getWidth()                      {return width;}
          inline void  setWidth(qreal wValue)        {width = wValue;}
          inline qreal getHeight()                    {return height;}
          inline void  setHeight(qreal hValue)      {height = hValue;}
          inline NodeEllipseGradient *getGradient() {return gradient;}
     protected:
          void createGradient();
          void copyGradient(NodeEllipseGradient *srcGradient);
     private:
          qreal     x, y, width, height;
          NodeEllipseGradient *gradient;
};

class NodeEllipseGradient: public QRadialGradient {
     friend class NodeEllipseItem;
     public:
          enum colors {black = 0, red = 1, green = 2, blue = 3, cyan = 4, magenta = 5, yellow = 6, gray = 7};
          NodeEllipseGradient(NodeEllipseItem *node);
          NodeEllipseGradient(NodeEllipseGradient *source, NodeEllipseItem *node);
          inline NodeEllipseGradient::colors getColor()   {return default_color;}
          inline NodeEllipseItem *getNode()               {return source_node;}
          inline QPointF getCenter() {return center_point;}
          inline QPointF getFocal()   {return focal_point;}
          inline qreal   getRadius()  {return radius_real;}
     protected:
          void setColorsOf(NodeEllipseGradient::colors color);
          void setCenterIn(QPointF c);
          void  setFocalIn(QPointF f);
          void setRadiusIn(qreal rad);
     private:
          colors default_color;
          NodeEllipseItem *source_node;
          QColor color1, color2, color3, color4;
          QPointF center_point, focal_point;
          qreal radius_real;
};

class NodeLineItem: public QGraphicsLineItem {
     friend class NodeGraphItemGroup;
     public:
          NodeLineItem(QGraphicsItem *parent = NULL);
          NodeLineItem(NodeLineItem *source, QGraphicsItem *parent = NULL);
          virtual ~NodeLineItem();
          void setSourceNode(NodeGraph *node);
          void setTargetNode(NodeGraph *node);
          void setupLine(NodeGraph *sourceNode, NodeGraph *targetNode);
          void adjust();
          void updateToNode();
          bool stretch(QPointF pos);
          bool updateToNode(QPointF pos);
          inline NodeGraph *getSourceNode() {return source;}
          inline NodeGraph *getTargetNode() {return target;}
          inline QPointF getSourcePoint() {return source_point;}
          inline QPointF getTargetPoint() {return target_point;}
     protected:
          void setPositionOf();
          void setArrowsOf();
          void setGeometryOf(QLineF line);
          void setPenOf();
          QRectF boundingRect() const;
          QPointF *arrayOfPoints(QRectF rect);
     private:
          QGraphicsPolygonItem *arrow_up, *arrow_down;
          NodeGraph         *source, *target;
          QPointF source_point, target_point;
          qreal   arrow_size;
};

class NodeTextItem: public QGraphicsSimpleTextItem {
     friend class NodeGraphItemGroup;
     public:
          NodeTextItem(QGraphicsItem *parent = NULL);
          NodeTextItem(NodeTextItem *source, QGraphicsItem *parent = NULL);
          void setArea();
          void setupText(QString text);
          void updateToNode();
          void setBrushOf(QColor in);
          void setPenOf(QColor out);
          inline QFont  getFont()         {return font;}
          inline QBrush getBrush()       {return brush;}
          inline QPen   getPen()           {return pen;}
          inline QColor getColorOut() {return colorOut;}
          inline QColor getColorIn()   {return colorIn;}
     protected:
          void setFontOf();
          void setPositionOf();
     private:
          QRectF  area;
          QString string;
          QFont   font;
          QBrush  brush;
          QPen    pen;
          QColor  colorOut, colorIn;
};

#endif // NODEITEM_H
