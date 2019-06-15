void NodeGraph::insertNodeRedBlackFix(NodeGraph *x, TreeGraph *t) {
     // NodeGraph *root = getRoot();
     while (x != NULL) { //if (x != root) {
            NodeGraph *p = x; { //for (BT *p = x->parentOf(); p != root && colorOf(p) == RED; p = x->parentOf()) {

            qDebug("Node: %p, Value: %d", p, p->getIntegerValue());

            if (p->getParentNode() != NULL) {

                if (p != p->getParentNode()->getRightNode()) { //if (p->isRightNode() == false) { // if (!isRightChild(p)) {
                    NodeGraph *pp = p->getParentNode(); //BT *pp = p->parentOf();     // Left case: x's parent is a left child
                    if (pp != NULL) {
                        NodeGraph *uncle = pp->getRightNode(); // BT *uncle = pp->rightOf();
                        if (uncle != NULL) {

                            qDebug("- Uncle: %p, Value: %d", uncle, uncle->getIntegerValue());

                            if (uncle->getColor() == NodeGraph::RED) { // if (colorOf(uncle)==RED) {
                                // case 1: x's uncle is red: recolor
                                // (or symmetrical case where x is a right child)
                                p->setColor(NodeGraph::BLACK); //setColor(p, BLACK);
                                uncle->setColor(NodeGraph::BLACK); //setColor(uncle, BLACK);
                                pp->setColor(NodeGraph::RED); // setColor(pp, RED);
                                x = pp;
                            } else {
                                if (x == x->getParentNode()->getRightNode()) { //if (isRightChild(x)) {
                                    // case 2: x is a right child: rotate to get to case 3
                                    x = p;
                                    rotationLeft(p, t); // rotateLeft(p);
                                    p = x->getParentNode();// p = x->parentOf();
                                    // now x is a left child
                                }
                                // case 3: x is a left child: recolor and rotate grandparent
                                p->setColor(NodeGraph::BLACK); //setColor(p, BLACK);
                                pp = p->getParentNode(); //pp = p->parentOf();
                                pp->setColor(NodeGraph::RED); //setColor(pp, RED);
                                p = rotationRight(pp, t); //p = rotateRight(pp);
                            }
                        } else {
                            x = x->getParentNode();

                            qDebug("Case 1 - Node X: %p, Value: %d", x, x->getIntegerValue());

                        }
                    } else {
                        x = x->getParentNode();

                        qDebug("Case 1A - Node X: %p, Value: %d", x, x->getIntegerValue());

                    }
                } else {
                    // Right case: x's parent is a right child
                    // symmetric with left case
                    NodeGraph *pp = p->getParentNode(); //BT *pp = p->parentOf();
                    if (pp != NULL) {
                        NodeGraph *uncle = pp->getLeftNode(); //BT *uncle = pp->leftOf();
                        if (uncle != NULL) {

                            qDebug("- Uncle: %p, Value: %d", uncle, uncle->getIntegerValue());

                            if (uncle->getColor() == NodeGraph::RED) { //if (colorOf(uncle)==RED) {
                               // case 1: x's uncle is red: recolor
                                p->setColor(NodeGraph::BLACK); //setColor(p, BLACK);
                                uncle->setColor(NodeGraph::BLACK);//setColor(uncle, BLACK);
                                pp->setColor(NodeGraph::RED); //setColor(pp, RED);
                                x = pp;
                            } else {
                                // case 2: x is a left child: rotate to get to case 3
                                if (x != x->getParentNode()->getRightNode()) { //if (!isRightChild(x)) {
                                    x = p;
                                    rotationRight(p, t); //rotateRight(p);
                                    p = x->getParentNode();//p = x->parentOf();
                                }
                                // case 3: x is a right child: recolor and rotate grandparent
                                p->setColor(NodeGraph::BLACK); //setColor(p, BLACK);
                                pp = p->getParentNode(); //pp = p->parentOf();
                                pp->setColor(NodeGraph::RED); //setColor(pp, RED);
                                p = rotationLeft(pp, t); //p = rotateLeft(pp);
                            }
                        } else {
                            x = x->getParentNode();

                            qDebug("Case 2 - Node X: %p, Value: %d", x, x->getIntegerValue());

                        }
                    } else {

                        x = x->getParentNode();

                        qDebug("Case 2A - Node X: %p, Value: %d", x, x->getIntegerValue());

                    }
                }
            } else {

                qDebug("Case 3 - Node X: %p, Value: %d", x, x->getIntegerValue());

            }
     }
     root->setColor(NodeGraph::BLACK);
}

     void NodeGraph::insertNodeRedBlackAux(NodeGraph* curNode) {
          NodeGraph *x;
          NodeGraph *aux;
          curNode->setLeftNode(NULL);
          curNode->setRightNode(NULL);     //curNode->left=curNode->right=nil;
          aux = curNode->getRoot();     //aux=root;
          x = curNode->getRoot()->getLeftNode();     //x=root->left;
          while(x != NULL) {
                aux = x;
                if (x->getIntegerValue() > curNode->getIntegerValue()) { //if (x->keaux > curNode->keaux) {
                    x = x->getLeftNode(); // x = x->left;
                } else {
                    x = x->getRightNode(); // x = x->right;
                }
          }
          curNode->setParentNode(aux); // curNode->parent=aux;
          if (aux == curNode->getRoot() || aux->getIntegerValue() > curNode->getIntegerValue()) { // if ( (aux == root) || (aux->keaux > curNode->keaux)) {
              aux->setLeftNode(curNode); // aux->left=curNode;
          } else {
              aux->setRightNode(curNode); // aux->right=curNode;
          }
     }



     void NodeGraph::redFlip(NodeGraph *root) {

          //p->color        = !p->color;
          //p->left->color  = !p->left->color;
          //p->right->color = !p->right->color;

         root->setRed(root->isRed() == false);
         root->getLeftNode()->setRed(root->getLeftNode()->isRed() == false);
         root->getRightNode()->setRed(root->getRightNode()->isRed() == false);

     }


     void NodeGraph::debugPrintTMP() {
          qDebug("- Node: %p, Value: %d", this, getIntegerValue());
          if (left_node != NULL)
              left_node->debugPrintTMP();
          if (right_node != NULL)
              right_node->debugPrintTMP();
     }


     void NodeGraph::InsertNodeRedBlackFixUp(NodeGraph *curNode) {
          NodeGraph *aux;
          while (curNode->parent_node != NULL && curNode->parent_node->isRed() == true) {
                 if (curNode->parent_node == curNode->parent_node->parent_node->left_node) {
                     aux = curNode->parent_node->parent_node->right_node;
                     if (aux->isRed() == true) {
                         curNode->parent_node->setRed(false);
                         aux->setRed(false);
                         curNode->parent_node->parent_node->setRed(true);
                         curNode = curNode->parent_node->parent_node;
                     } else if((curNode = curNode->parent_node->right_node)) {
                         curNode = curNode->parent_node;
                         curNode->rotationLeft();
                     }
                     curNode->parent_node->setRed(false);
                     curNode->parent_node->parent_node->setRed(true);
                     curNode->parent_node->parent_node->rotationRight();
                 } else {
                     aux = curNode->parent_node->parent_node->left_node;
                     if (aux->isRed() == true) {
                         curNode->parent_node->setRed(false);
                         aux->setRed(false);
                         curNode->parent_node->parent_node->setRed(true);
                         curNode = curNode->parent_node->parent_node;
                     } else if ((curNode = curNode->parent_node->left_node)) {
                         curNode = curNode->parent_node;
                         curNode->rotationLeft();
                     }
                     curNode->parent_node->setRed(false);
                     curNode->parent_node->parent_node->setRed(true);
                     curNode->parent_node->parent_node->rotationRight();
                 }
          }
     }



     void NodeGraph::insertNodeRedBlackFix(NodeGraph **node) {
          NodeGraph *aux;



          while ((*node)->parent_node->isRed() == true) {



                 if ((*node)->parent_node == (*node)->parent_node->parent_node->left_node) {
                     aux = (*node)->parent_node->parent_node->right_node;
                     if (aux->red == true) {
                         (*node)->parent_node->red = false;
                         aux->red = false;
                         (*node)->parent_node->parent_node->red = true;
                         (*node) = (*node)->parent_node->parent_node;
                     } else if (((*node) = (*node)->parent_node->right_node)) {
                         (*node) = (*node)->parent_node;
                         (*node) = (*node)->rotationLeft();
                     }
                     (*node)->parent_node->red = false;
                     (*node)->parent_node->parent_node->red = true;
                     (*node)->parent_node->parent_node = (*node)->parent_node->parent_node->rotationRight();
                 } else {
                     aux = (*node)->parent_node->parent_node->left_node;
                     if (aux != NULL) {
                         if (aux->red == true) {
                             (*node)->parent_node->red = false;
                             aux->red = false;
                             (*node)->parent_node->parent_node->red = true;
                             (*node) = (*node)->parent_node->parent_node;
                         } else if (((*node) = (*node)->parent_node->left_node)) {
                             (*node) = (*node)->parent_node;
                             (*node) = (*node)->rotationLeft();
                         }
                         (*node)->parent_node->red = false;
                         (*node)->parent_node->parent_node->red = true;
                         (*node)->parent_node->parent_node = (*node)->parent_node->parent_node->rotationRight();
                     } else {


                     }
                 }
         }


     }



     void Insert(node * &tree, node *&curNode) {
         node* nil=tree->nil;
         node* root=tree->root;
         node *aux;
         node *x;
         aux=tree->nil;
         x=tree->root;
         while(x!=tree->nil)
         {
             aux=x;
             if((curNode->keaux)<(x->keaux))
                 x=x->left;
             else
                 x=x->right;
         }
         aux=curNode->parent;
         if(aux=tree->nil)
             curNode=tree->root;
         else if((curNode->keaux)<(aux->keaux))
             curNode=aux->left;
         else
             curNode=aux->right;
         curNode->left=tree->nil;
         curNode->right=tree->nil;
         curNode->color=RED;
         InsertFixUp(tree,curNode);
     }


     void NodeGraph::rotationLeft(NodeGraph *x, TreeGraph *t) {
          NodeGraph *y = NULL;
          NodeGraph *root = x->getRoot();
          if (x != NULL) {
              y = x->getRightNode();
              if (y != NULL) {
                  NodeGraph *beta = y->getLeftNode();
                  if (x == root) {
                      NodeGraph *gamma = y->getRightNode();
                      root = new NodeGraph(y->getIntegerValue(), t);
                      root->setLeftNode(x);
                      root->setRightNode(gamma);
                      t->setRootNode(root);
                      x->setRightNode(beta);
                      y->setLeftNode(NULL);
                      y->setRightNode(NULL);
                      delete y;
                      y = root;
                  } else {
                      NodeGraph *p = x->getParentNode();
                      if (x->isRightNode() == true)
                          p->setRightNode(y);
                      else
                          p->setLeftNode(y);
                      y->setLeftNode(x);
                      x->setRightNode(beta);
                  }
              }
          }
     }

     void NodeGraph::rotationRight(NodeGraph *y, TreeGraph *t) {
          NodeGraph *x = NULL;
          NodeGraph *root = y->getRoot();
          if (y != NULL)   {
              x = y->getLeftNode();
              if (x != NULL) {
                  NodeGraph *beta = x->getRightNode();
                  if (y == root) {
                      NodeGraph *alpha = x->getLeftNode();
                      root = new NodeGraph(x->getIntegerValue(), t);
                      root->setRightNode(y);
                      root->setLeftNode(alpha);
                      t->setRootNode(root);
                      y->setLeftNode(beta);
                      x->setLeftNode(NULL);
                      x->setRightNode(NULL);
                      delete x;
                      x = root;
                  } else {
                      NodeGraph *p = y->getParentNode();
                      if (y->isRightNode() == true)
                          p->setRightNode(x);
                      else
                          p->setLeftNode(x);
                      x->setRightNode(y);
                      y->setLeftNode(beta);
                  }
              }
          }
     }

     void NodeGraph::rotationLeft(NodeGraph *x) {
          NodeGraph *y;
          y = x->getRightNode();                // y = x->right;
          if (y == NULL || y->getLeftNode() == NULL)
              return;
          x->setRightNode(y->getLeftNode());    // x->right = y->left;
          y->getLeftNode()->setParentNode(x);   // y->left->parent = x;
          y->setParentNode(x->getParentNode()); // y->parent = x->parent;
          if (x->getParentNode() == NULL) // if ( x->parent == Nil )
              y->IamRootNode(true);       //Root = y;
         else if (x == x->getParentNode()->getLeftNode()) // else if ( x == x->parent->left )
              x->getParentNode()->setLeftNode(y); // x->parent->left = y;
         else
              x->getParentNode()->setRightNode(y); // x->parent->right = y;
         y->setLeftNode(x);   // y->left = x;
         x->setParentNode(y); // x->parent = y;
     }

     void NodeGraph::rotationRight(NodeGraph *x) {
          NodeGraph *y;
          y = x->getLeftNode();                // y = x->left;
          if (y == NULL || y->getRightNode() == NULL)
              return;
          x->setLeftNode(y->getRightNode());   // x->left = y->right;
          y->getRightNode()->setParentNode(x); // y->right->parent = x;
          y->setParentNode(x->getParentNode()); // y->parent = x->parent;
          if (x->getParentNode() == NULL) // if ( x->parent == Nil )
              y->IamRootNode(true);       // Root = y;
          else if (x == x->getParentNode()->getRightNode()) // else if ( x == x->parent->right )
              x->getParentNode()->setRightNode(y); // x->parent->right = y;
          else
              x->getParentNode()->setLeftNode(y);// x->parent->left = y;
          y->setRightNode(x);  // y->right = x;
          x->setParentNode(y); // x->parent = y;
     }

     void NodeGraph::rotationLeft(NodeGraph *n) {
          NodeGraph *right = n->right_node;
          swapNodes(n, right);
          n->right_node = right->left_node;
         if(right->left_node != NULL)
             right->left_node->parent_node = n;
         right->left_node = n;
         n->parent_node = right;
     }

     void NodeGraph::rotationRight(NodeGraph *n) {
         NodeGraph *left = n->left_node;
         swapNodes(n, left);
         n->left_node = left->right_node;
         if(left->right_node != NULL)
             left->right_node->parent_node = n;
         left->right_node = n;
         n->parent_node = left;
     }

     void NodeGraph::swapNodes(NodeGraph *oldNode, NodeGraph *newNode) {
          if (oldNode->parent_node != NULL) {
              if(oldNode == oldNode->parent_node->left_node)
                 oldNode->parent_node->left_node = newNode;
             else
                 oldNode->parent_node->right_node = newNode;
         }
         if(newNode != NULL)
             newNode->parent_node = oldNode->parent_node;
     }


     void NodeGraph::swapIntegers(int *a, int *b) {
          int t = *a;
          *a = *b;
          *b = t;
     }

     void NodeGraph::setCorrectBinTree (NodeGraph *root, NodeGraph **first, NodeGraph **middle, NodeGraph **last, NodeGraph **prev) {
          if(root != NULL) {
             if (*prev != NULL && root->getIntegerValue() < (*prev)->getIntegerValue()) {
                 if (*first == NULL) {
                     *first = *prev;
                     *middle = root;
                 } else {
                     *last = root;
                 }
             } else if (*last != NULL && root->getIntegerValue() > (*last)->getIntegerValue()) {
                 if (*first == NULL) {
                     *first = *prev;
                     *middle = root;
                 }
             }
             *prev = root;
             setCorrectBinTree(root->getLeftNode(), first, middle, last, prev );
             setCorrectBinTree(root->getRightNode(), first, middle, last, prev );
          }
     }

     void NodeGraph::updateCorrectBinTree(NodeGraph *root) {
          int a, b;
          NodeGraph *first, *middle, *last, *prev;
          first = middle = last = prev = NULL;
          setCorrectBinTree(root, &first, &middle, &last, &prev );

         if(first != NULL && last != NULL) {
             a = first->getIntegerValue();
             b = last->getIntegerValue();
             swapIntegers(&a, &b);
             first->setIntegerValue(a);
             last->setIntegerValue(b);
         } else if(first != NULL && middle != NULL) {
             a = first->getIntegerValue();
             b = middle->getIntegerValue();
             swapIntegers(&a, &b);
             first->setIntegerValue(a);
             middle->setIntegerValue(b);
         }
     }
     return NULL;

     NodeGraph *root = graph->getRootNode();
     NodeGraph *aux;
     NodeGraph  *x;
     aux = graph->getLastNode();
     x = root;
     while (x != NULL) {
            aux = x;
            if (curNode->integer_value < x->integer_value)
                x = x->left_node;
            else
                x = x->right_node;
     }
     aux = curNode->parent_node;
     if (aux == NULL)
        curNode = root;
     else if (curNode->integer_value < aux->integer_value)
        curNode = aux->left_node;
    else
        curNode = aux->right_node;
    curNode->left_node  = NULL;
    curNode->right_node = NULL;


    NodeGraph *newNode = insertNode(value, graph, curNode, &curNode->parent_node);
    if (newNode != NULL) {
         newNode->red = true;
         insertNodeRedBlackFix(&newNode);
         return newNode;
     }

     qDebug("Current Node at: %p and value is: %d", curNode, value);

     if (curNode == NULL)
         return new NodeGraph(value, graph, parentNode, parent);

     qDebug("Current Value is: %d", curNode->getIntegerValue());


     if ((curNode->left_node != NULL && curNode->left_node->isRed() == true) && (curNode->right_node != NULL && curNode->right_node->isRed() == true)) {
         curNode->setRed(curNode->isRed() == false);
         curNode->getLeftNode()->setRed(curNode->getLeftNode()->isRed() == false);
         curNode->getLeftNode()->setRed(curNode->getLeftNode()->isRed() == false);
     }

    if (value < curNode->integer_value)
        curNode->left_node = insertNodeRedBlack(value, graph, curNode->left_node, &curNode, parent);
    else if (value > curNode->integer_value)
        curNode->right_node = insertNodeRedBlack(value, graph, curNode->right_node, &curNode, parent);
    else {

        qDebug("Already Exists!");

        return NULL;
    }
    if (curNode->right_node != NULL && curNode->right_node->isRed() == true)
        curNode = curNode->rotationLeft();

    if ((curNode->left_node != NULL && curNode->left_node->isRed() == true) && (curNode->left_node->left_node != NULL && curNode->left_node->left_node->isRed() == true))
        curNode = curNode->rotationRight();

    return curNode;

     NodeGraph *auxNode = NULL, *newNode = insertNode(value, graph, curNode, &curNode->parent_node);
     newNode->setRed(true);
     while (newNode != graph->getRootNode() && newNode->parent_node->isRed() == true) {

            qDebug("Node: %p, Value: %d", newNode, newNode->getIntegerValue());

            if (newNode->parent_node != NULL && newNode->parent_node->parent_node != NULL) {
                if (newNode->parent_node == newNode->parent_node->parent_node->left_node) {
                    auxNode = newNode->parent_node->parent_node->right_node;
                    if (auxNode != NULL) {
                        if (auxNode->isRed() == true) {
                            newNode->parent_node->setRed(false);;
                            auxNode->setRed(false);
                            newNode->parent_node->parent_node->setRed(true);
                            newNode = newNode->parent_node->parent_node;
                        } else {
                            if (newNode == newNode->parent_node->right_node) {
                                newNode = newNode->parent_node;
                                newNode = newNode->rotationLeft();
                            }
                            newNode->parent_node->setRed(false);
                            newNode->parent_node->parent_node->setRed(true);
                            newNode->parent_node->parent_node = newNode->parent_node->parent_node->rotationRight();
                        }
                    } else {
                        newNode = newNode->parent_node;
                    }
                } else if (newNode->parent_node == newNode->parent_node->parent_node->right_node) {
                    auxNode = newNode->parent_node->parent_node->left_node;
                    if (auxNode != NULL) {
                        if (auxNode->isRed() == true) {
                            newNode->parent_node->setRed(false);;
                            auxNode->setRed(false);
                            newNode->parent_node->parent_node->setRed(true);
                            newNode = newNode->parent_node->parent_node;
                        } else {
                            if (newNode == newNode->parent_node->left_node) {
                                newNode = newNode->parent_node;
                                newNode = newNode->rotationRight();
                            }
                            newNode->parent_node->setRed(false);
                            newNode->parent_node->parent_node->setRed(true);
                            newNode->parent_node->parent_node = newNode->parent_node->parent_node->rotationLeft();
                        }
                    } else {
                        newNode = newNode->parent_node;
                    }
                }
            } else {
                newNode = newNode->parent_node;
            }
     }
     graph->getRootNode()->setRed(false);
     return newNode;


     NodeGraph *aux, *curNode;
     curNode = newNode;

     while (curNode->getParentNode() != NULL) { // && curNode->getParentNode()->isRed() == true) {

         qDebug("Node: %p, Value: %d", curNode, curNode->getIntegerValue());

         if (curNode->getParentNode()->getParentNode() != NULL) {
             if (curNode->getParentNode() == curNode->getParentNode()->getParentNode()->getLeftNode()) {
                 aux = curNode->getParentNode()->getParentNode()->getRightNode();
                 if (aux != NULL && aux->isRed() == true){
                     curNode->getParentNode()->setRed(false);
                     aux->setRed(false);
                     curNode->getParentNode()->getParentNode()->setRed(true);
                     curNode = curNode->getParentNode()->getParentNode();
                 } else if (curNode == curNode->getParentNode()->getRightNode()){
                     curNode = curNode->getParentNode();
                     curNode = curNode->rotationLeft();
                 }
                 if (curNode->getParentNode() != NULL){
                     curNode->getParentNode()->setRed(false);
                     if (curNode->getParentNode()->getParentNode() != NULL){
                         curNode->getParentNode()->getParentNode()->setRed(true);;
                         curNode->parent_node->parent_node = curNode->getParentNode()->getParentNode()->rotationRight();
                     }
                 }
             } else if (curNode->getParentNode() == curNode->getParentNode()->getParentNode()->getRightNode()){
                 aux = curNode->getParentNode()->getParentNode()->getLeftNode();
                 if (aux != NULL && aux->isRed() == true) {
                     curNode->getParentNode()->setRed(false);;
                     aux->setRed(false);
                     curNode->getParentNode()->getParentNode()->setRed(true);;
                     curNode = curNode->getParentNode()->getParentNode();
                 } else if (curNode == curNode->getParentNode()->getLeftNode()) {
                     curNode = curNode->getParentNode();
                     curNode = curNode->rotationRight();
                 }
                 if (curNode->getParentNode() != NULL){
                     curNode->getParentNode()->setRed(false);
                     if (curNode->getParentNode()->getParentNode() != NULL){
                         curNode->getParentNode()->getParentNode()->setRed(true);
                         curNode->parent_node->parent_node = curNode->getParentNode()->getParentNode()->rotationLeft();
                     }
                 }
             }

         } else {
             curNode = curNode->getParentNode();
         }
     }
     return curNode;
     newNode->setRed(true);
     while (newNode != graph->getRootNode() && newNode->parent_node->isRed() == true) {

            qDebug("Node: %p, Value: %d", newNode, newNode->getIntegerValue());

            if (newNode->parent_node != NULL && newNode->parent_node->parent_node != NULL) {
                if (newNode->parent_node == newNode->parent_node->parent_node->left_node) {
                    auxNode = newNode->parent_node->parent_node->right_node;
                    if (auxNode != NULL) {
                        if (auxNode->isRed() == true) {
                            newNode->parent_node->setRed(false);;
                            auxNode->setRed(false);
                            newNode->parent_node->parent_node->setRed(true);
                            newNode = newNode->parent_node->parent_node;
                        } else {
                            if (newNode == newNode->parent_node->right_node) {
                                newNode = newNode->parent_node;
                                newNode = newNode->rotationLeft();
                            }
                            newNode->parent_node->setRed(false);
                            newNode->parent_node->parent_node->setRed(true);
                            newNode->parent_node->parent_node = newNode->parent_node->parent_node->rotationRight();
                        }
                    } else {
                        newNode = newNode->parent_node;
                    }
                } else if (newNode->parent_node == newNode->parent_node->parent_node->right_node) {
                    auxNode = newNode->parent_node->parent_node->left_node;
                    if (auxNode != NULL) {
                        if (auxNode->isRed() == true) {
                            newNode->parent_node->setRed(false);;
                            auxNode->setRed(false);
                            newNode->parent_node->parent_node->setRed(true);
                            newNode = newNode->parent_node->parent_node;
                        } else {
                            if (newNode == newNode->parent_node->left_node) {
                                newNode = newNode->parent_node;
                                newNode = newNode->rotationRight();
                            }
                            newNode->parent_node->setRed(false);
                            newNode->parent_node->parent_node->setRed(true);
                            newNode->parent_node->parent_node = newNode->parent_node->parent_node->rotationLeft();
                        }
                    } else {
                        newNode = newNode->parent_node;
                    }
                }
            } else {
                newNode = newNode->parent_node;
            }
     }
     graph->getRootNode()->setRed(false);
     return newNode;

     return NULL;

     NodeGraph *newNode = new NodeGraph(value, graph);
     if(curNode == NULL)
        curNode = newNode;
     else if(value < curNode->integer_value) {
        insertNodeRedBlack(value, graph, curNode->left_node);
        curNode = curNode->rotationRight();
     } else if(value > curNode->integer_value) {
        insertNodeRedBlack(value, graph, curNode->right_node);
        curNode = curNode->rotationLeft();
     } else {
         delete newNode;
         return NULL;
     }
     graph->getRootNode()->setRed(false);
     return newNode;



     NodeGraph *aux;
     NodeGraph *x;
     aux = NULL;
     x = graph->getRootNode();
     while(x != NULL) {
           aux = x;
           if (value < curNode->integer_value)
               x = x->left_node;
           else if (value > x->integer_value)
               x = x->right_node;
           else
               return NULL;
     }
     aux = curNode->parent_node;
     if (aux == NULL)
         curNode = graph->getRootNode();
     else if(curNode->integer_value < x->integer_value)
         curNode = aux->left_node;
     else if (curNode->integer_value > x->integer_value)
         curNode = aux->right_node;

     curNode->left_node  = NULL;
     curNode->right_node = NULL;
     curNode->setRed(true);
     InsertNodeRedBlackFixUp(curNode);
     return curNode;



     if (curNode == NULL)
        return new NodeGraph(value, graph, parentNode, parent);
     if (curNode->getLeftNode() != NULL && curNode->getLeftNode()->isRed() && curNode->getRightNode() != NULL && curNode->getRightNode()->isRed())
         redFlip(curNode);
     if (value < curNode->getIntegerValue())
         curNode->setLeftNode(insertNodeRedBlack(value, graph, curNode->getLeftNode(), &curNode, parent));
     else if (value > curNode->getIntegerValue())
         curNode->setRightNode(insertNodeRedBlack(value, graph, curNode->getRightNode(), &curNode, parent));
     else
         return NULL;
     if (curNode->getRightNode() != NULL && curNode->getRightNode()->isRed() == true)
         curNode = curNode->rotationLeft();
     if (curNode->getLeftNode() != NULL && curNode->getLeftNode()->isRed() == true && curNode->getLeftNode()->getLeftNode() != NULL && curNode->getLeftNode()->getLeftNode()->isRed() == true)
         curNode = curNode->rotationRight();
     return curNode;


     qDebug("- Insert Node Red-Black Fix in Node Graphic!");
      if (node != NULL)
          qDebug("\t- Node %p, Value: %d", node, node->getIntegerValue());

      NodeGraph *y, *z;
      z = node;
      while (z->getParentNode() != NULL && z->getParentNode()->getColor() == NodeGraphItemGroup::RED) {

             qDebug("\t- Z(1) Node: %p, Value: %d", z, z->getIntegerValue());

             if (z->getParentNode()->getParentNode() != NULL) {

                 qDebug("\t- Parent Of Parent(1) found!");

                 if (z->getParentNode() == z->getParentNode()->getParentNode()->getLeftNode()) {

                     qDebug("\t- is Left Node!");

                     y = z->getParentNode()->getParentNode()->getRightNode();

                     if (y != NULL && y->getColor() == NodeGraphItemGroup::RED) {

                         qDebug("\t- Node Y(1): %p, Value: %d", y, y->getIntegerValue());

                         z->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                         y->setColor(NodeGraphItemGroup::BLACK);
                         z->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                         z = z->getParentNode()->getParentNode();
                     } else if (z == z->getParentNode()->getRightNode()) {
                         z = z->getParentNode();
                         rotationLeft(z); //z->rotationLeft(); //rotationLeft(z);

                         qDebug("\t- Rotation Left - Node Z(1): %p, Value: %d", z, z->getIntegerValue());

                     } else if (z->getParentNode() != NULL) {

                         qDebug("\t- Parent of Node Z(1): %p, Value: %d", z->getParentNode(), z->getParentNode()->getIntegerValue());

                         z->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                         if (z->getParentNode()->getParentNode() != NULL) {

                             qDebug("\t- Parent of Parent of Node Z(1): %p, Value: %d", z->getParentNode()->getParentNode(), z->getParentNode()->getParentNode()->getIntegerValue());

                             z->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                             rotationRight(z->getParentNode()->getParentNode()); //z->getParentNode()->getParentNode()->rotationRight(); // rotationRight(z->getParentNode()->getParentNode());
                         }
                     }
                 } else if (z->getParentNode() == z->getParentNode()->getParentNode()->getRightNode()) {

                     qDebug("\t- is Right Node!");

                     y = z->getParentNode()->getParentNode()->getLeftNode();
                     if (y != NULL && y->getColor() == NodeGraphItemGroup::RED) {

                         qDebug("\t- Node Y(2): %p, Value: %d", y, y->getIntegerValue());

                         z->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                         y->setColor(NodeGraphItemGroup::BLACK);
                         z->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                         z = z->getParentNode()->getParentNode();
                     } else if (z == z->getParentNode()->getLeftNode()) {
                         z = z->getParentNode();
                         rotationRight(z); // z->rotationRight(); //rotationRight(z);

                         qDebug("\t- Rotation Right - Node Z(2): %p, Value: %d", z, z->getIntegerValue());

                     } else if (z->getParentNode() != NULL){

                         qDebug("\t- Parent of Node Z(2): %p, Value: %d", z->getParentNode(), z->getParentNode()->getIntegerValue());

                         z->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                         NodeGraph *k = z->getParentNode()->getParentNode();
                         if (k != NULL){

                             qDebug("\t- Parent of Parent of Node Z(2): %p, Value: %d", z->getParentNode()->getParentNode(), z->getParentNode()->getParentNode()->getIntegerValue());

                             k->setColor(NodeGraphItemGroup::RED);
                             NodeGraph *x = k->rotationLeft(); //rotationLeft(z->getParentNode()->getParentNode());
                             if (x == getRoot()) {

                                 qDebug("\t- New Root!");

                                 //x->destroyLine();
                                 //z->getParentNode()->getParentNode()->setLine(x->getLine());
                                 //k->setLine(x->getLine());

                                 if (x->getParentNode() != NULL)
                                     qDebug("\t- Parent at: %p, Value: %d", x->getParentNode(), x->getParentNode()->getIntegerValue());

                                 //x->identifyNodesAll();
                             }



                         }
                     }
                 }
             } else {

                 qDebug("\t- Parent Of Parent NOT found!");

                 break;
             }

      }
      getRoot()->setColor(NodeGraphItemGroup::BLACK);

      qDebug("- Insert Node Red-Black Fix Finished in Node Graphic!");

 }



 void NodeGraph::insertNodeRedBlackFix(NodeGraph *x, TreeGraph *t) {
      // NodeGraph *root = getRoot();
      while (x != NULL) { //if (x != root) {
             NodeGraph *p = x; //for (BT *p = x->parentOf(); p != root && colorOf(p) == RED; p = x->parentOf()) {

             qDebug("Node: %p, Value: %d", p, p->getIntegerValue());

             if (p->getParentNode() != NULL) {

                 if (p != p->getParentNode()->getRightNode()) { //if (p->isRightNode() == false) { // if (!isRightChild(p)) {
                     NodeGraph *pp = p->getParentNode(); //BT *pp = p->parentOf();     // Left case: x's parent is a left child
                     if (pp != NULL) {
                         NodeGraph *uncle = pp->getRightNode(); // BT *uncle = pp->rightOf();
                         if (uncle != NULL) {

                             qDebug("- Uncle: %p, Value: %d", uncle, uncle->getIntegerValue());

                             if (uncle->getColor() == NodeGraph::RED) { // if (colorOf(uncle)==RED) {
                                 // case 1: x's uncle is red: recolor
                                 // (or symmetrical case where x is a right child)
                                 p->setColor(NodeGraph::BLACK); //setColor(p, BLACK);
                                 uncle->setColor(NodeGraph::BLACK); //setColor(uncle, BLACK);
                                 pp->setColor(NodeGraph::RED); // setColor(pp, RED);
                                 x = pp;
                             } else {
                                 if (x == x->getParentNode()->getRightNode()) { //if (isRightChild(x)) {
                                     // case 2: x is a right child: rotate to get to case 3
                                     x = p;
                                     rotationLeft(p, t); // rotateLeft(p);
                                     p = x->getParentNode();// p = x->parentOf();
                                     // now x is a left child
                                 }
                                 // case 3: x is a left child: recolor and rotate grandparent
                                 p->setColor(NodeGraph::BLACK); //setColor(p, BLACK);
                                 pp = p->getParentNode(); //pp = p->parentOf();
                                 pp->setColor(NodeGraph::RED); //setColor(pp, RED);
                                 p = rotationRight(pp, t); //p = rotateRight(pp);
                             }
                         } else {
                             x = x->getParentNode();

                             qDebug("Case 1 - Node X: %p, Value: %d", x, x->getIntegerValue());

                         }
                     } else {
                         x = x->getParentNode();

                         qDebug("Case 1A - Node X: %p, Value: %d", x, x->getIntegerValue());

                     }
                 } else {
                     // Right case: x's parent is a right child
                     // symmetric with left case
                     NodeGraph *pp = p->getParentNode(); //BT *pp = p->parentOf();
                     if (pp != NULL) {
                         NodeGraph *uncle = pp->getLeftNode(); //BT *uncle = pp->leftOf();
                         if (uncle != NULL) {

                             qDebug("- Uncle: %p, Value: %d", uncle, uncle->getIntegerValue());

                             if (uncle->getColor() == NodeGraph::RED) { //if (colorOf(uncle)==RED) {
                                // case 1: x's uncle is red: recolor
                                 p->setColor(NodeGraph::BLACK); //setColor(p, BLACK);
                                 uncle->setColor(NodeGraph::BLACK);//setColor(uncle, BLACK);
                                 pp->setColor(NodeGraph::RED); //setColor(pp, RED);
                                 x = pp;
                             } else {
                                 // case 2: x is a left child: rotate to get to case 3
                                 if (x != x->getParentNode()->getRightNode()) { //if (!isRightChild(x)) {
                                     x = p;
                                     rotationRight(p, t); //rotateRight(p);
                                     p = x->getParentNode();//p = x->parentOf();
                                 }
                                 // case 3: x is a right child: recolor and rotate grandparent
                                 p->setColor(NodeGraph::BLACK); //setColor(p, BLACK);
                                 pp = p->getParentNode(); //pp = p->parentOf();
                                 pp->setColor(NodeGraph::RED); //setColor(pp, RED);
                                 p = rotationLeft(pp, t); //p = rotateLeft(pp);
                             }
                         } else {
                             x = x->getParentNode();

                             qDebug("Case 2 - Node X: %p, Value: %d", x, x->getIntegerValue());

                         }
                     } else {
                         x = x->getParentNode();

                         qDebug("Case 2A - Node X: %p, Value: %d", x, x->getIntegerValue());

                     }
                 }
             } else {
                 x = x->getParentNode();

                 //qDebug("Case 3 - Node X: %p, Value: %d", x, x->getIntegerValue());

             }
      }
      getRoot()->setColor(NodeGraph::BLACK);
 }
  NodeGraph *y;
  while (z != NULL) { //&& z->parent_node->color == NodeGraph::RED) {

         qDebug("Node: %p, Value: %d", z, z->integer_value);

         if (z->parent_node != NULL && z->parent_node->parent_node != NULL) {
             if (z->parent_node == z->parent_node->parent_node->left_node) {
                 y = z->parent_node->parent_node->right_node;
                 if (y->color == NodeGraph::RED) {
                     z->parent_node->color = NodeGraph::BLACK;
                     y->color = NodeGraph::BLACK;
                     z->parent_node->parent_node->color = NodeGraph::RED;
                     z = z->parent_node->parent_node;
                 } else if (z == z->parent_node->right_node) {
                     z = z->parent_node;
                     z->rotationLeft();
                 }
                 z->parent_node->color = NodeGraph::BLACK;
                 z->parent_node->parent_node->color = NodeGraph::RED;
                 z->parent_node->parent_node->rotationRight();
             } else {
                 z = z->parent_node;
                 z->rotationRight();
             }
             if (z != NULL && z->parent_node != NULL) {
                 z->parent_node->color = NodeGraph::BLACK;
                 if (z->parent_node->parent_node != NULL) {
                     z->parent_node->parent_node->color = NodeGraph::RED;
                     z->parent_node->parent_node->rotationLeft();
                 }
             }
         } else {
             z = z->parent_node;
         }
  }



 void NodeGraph::insertNodeRedBlackFix(NodeGraph *n) {
      NodeGraph * y;
      while (n->getParentNode() != NULL && n->getParentNode()->getColor() == NodeGraphItemGroup::RED) {
             if (n->getParentNode()->getParentNode() != NULL) {
                 if (n->getParentNode() == n->getParentNode()->getParentNode()->getLeftNode()) {
                     y = n->getParentNode()->getParentNode()->getRightNode();
                     if (y != NULL && y->getColor() == NodeGraphItemGroup::RED) {
                         n->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                         y->setColor(NodeGraphItemGroup::BLACK);
                         n->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                         n = n->getParentNode()->getParentNode();
                     } else {
                         if (n == n->getParentNode()->getRightNode()) {
                             n = n->getParentNode();
                             rotationLeft(n);
                         }
                         n->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                         n->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                     }
                 } else {
                     y = n->getParentNode()->getParentNode()->getLeftNode();
                     if (y != NULL && y->getColor() == NodeGraphItemGroup::RED) {
                         n->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                         y->setColor(NodeGraphItemGroup::BLACK);
                         n->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                         n = n->getParentNode()->getParentNode();
                     } else {
                         if (n == n->getParentNode()->getLeftNode()) {
                             n = n->getParentNode();
                             rotationRight(n);
                         }
                         n->getParentNode()->setColor(NodeGraphItemGroup::BLACK);
                         n->getParentNode()->getParentNode()->setColor(NodeGraphItemGroup::RED);
                     }
                 }
             } else {
                 break;
             }
     }
     getRoot()->setColor(NodeGraphItemGroup::BLACK);

      NodeGraph *x;
      NodeGraph *y;
      while (n->parent_node != NULL && n->parent_node->getColor() == NodeGraphItemGroup::RED) {

             qDebug("- Node: %p, Value: %d", n, n->getIntegerValue());

             x = n->parent_node->parent_node;
             if (x != NULL) {
                 if (n->parent_node == x->left_node) { // (n->isLeftNode() == true) { //(n == n->parent_node->left_node) {

                     qDebug("- Left...");

                     y = x->right_node;
                     if (y != NULL) {

                         qDebug("- Y Node: %p, Value: %d", y, y->getIntegerValue());

                         if (y->getColor() == NodeGraphItemGroup::RED) {
                             n->parent_node->setColor(NodeGraphItemGroup::BLACK);
                             y->setColor(NodeGraphItemGroup::BLACK);
                             x->setColor(NodeGraphItemGroup::RED);
                             n = x;
                         } else {
                             if (n == n->parent_node->right_node) {

                                 qDebug("Left Rotation!");

                                 n = n->parent_node;
                                 rotationLeft(n);
                             }
                             n->parent_node->setColor(NodeGraphItemGroup::BLACK);
                             n->parent_node->parent_node->setColor(NodeGraphItemGroup::RED);
                         }
                     } else {
                         n = n->parent_node;

                         qDebug("- Node: %p, Value: %d", n, n->getIntegerValue());

                     }
                 } else { // (n->isRightNode() == true) {

                     qDebug("- Right...");

                     y = x->left_node;
                     if (y != NULL) {

                         qDebug("- Y Node: %p, Value: %d", y, y->getIntegerValue());

                         if (y->getColor() == NodeGraphItemGroup::RED) {
                             n->parent_node->setColor(NodeGraphItemGroup::BLACK);
                             y->setColor(NodeGraphItemGroup::BLACK);
                             x->setColor(NodeGraphItemGroup::RED);
                             n = x;
                         } else {
                             if (n == n->parent_node->left_node) {

                                 qDebug("Right Rotation!");

                                 n = n->parent_node;
                                 rotationRight(n);
                             }
                             n->parent_node->setColor(NodeGraphItemGroup::BLACK);
                             n->parent_node->parent_node->setColor(NodeGraphItemGroup::RED);
                         }
                     } else {
                         n = n->parent_node;

                         qDebug("- Node: %p, Value: %d", n, n->getIntegerValue());

                     }
                 }
             } else {
                 // X = NULL (parent of parent)
                 break;
             }
      }

      getRoot()->setColor(NodeGraphItemGroup::BLACK);


 NodeGraph *NodeGraph::getGrandParent(NodeGraph *n) {
      if (n != NULL && n->parent_node != NULL)
          return n->parent_node->parent_node;
      else
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

 void NodeGraph::insertNodeRedBlackFixcase1(NodeGraph *n) {
      if (n->parent_node == NULL)
          n->setColor(NodeGraphItemGroup::BLACK);
      else
          insertNodeRedBlackFixcase2(n);
 }

 void NodeGraph::insertNodeRedBlackFixcase2(NodeGraph *n) {
      if (n->parent_node->getColor() == NodeGraphItemGroup::BLACK)
          return;
      else
          insertNodeRedBlackFixcase3(n);
 }

 void NodeGraph::insertNodeRedBlackFixcase3(NodeGraph *n) {
      NodeGraph *u = getUncle(n), *g;
      if (u != NULL && u->getColor() == NodeGraphItemGroup::RED) {
          n->parent_node->setColor(NodeGraphItemGroup::BLACK);
          u->setColor(NodeGraphItemGroup::BLACK);
          g = getGrandParent(n);
          g->setColor(NodeGraphItemGroup::RED);
          insertNodeRedBlackFixcase1(g);
      } else {
          insertNodeRedBlackFixcase4(n);
      }
 }

 void NodeGraph::insertNodeRedBlackFixcase4(NodeGraph *n) {
      NodeGraph *g = getGrandParent(n);
      if (g == NULL || n->parent_node == NULL)
          return;
      if (n == n->parent_node->right_node && n->parent_node == g->left_node) {
          rotationLeft(n->parent_node);
          n = n->left_node;
      } else if ((n == n->parent_node->left_node) && (n->parent_node == g->right_node)) {
          rotationRight(n->parent_node);
          n = n->right_node;
      }
      insertNodeRedBlackFixcase5(n);
 }

 void NodeGraph::insertNodeRedBlackFixcase5(NodeGraph *n) {
      NodeGraph *g = getGrandParent(n);
      n->parent_node->setColor(NodeGraphItemGroup::BLACK);
      g->setColor(NodeGraphItemGroup::RED);
      if (n == n->parent_node->left_node)
          rotationRight(g);
      else
          rotationLeft(g);
 }

 /*
  void swapNodes(NodeGraph *oldNode, NodeGraph *newNode);
  void swapIntegers(int *a, int *b);
  void setCorrectBinTree(NodeGraph *root, NodeGraph **first, NodeGraph **middle, NodeGraph **last, NodeGraph **prev);

 NodeGraph *getGrandParent(NodeGraph *node);
 NodeGraph *getUncle(NodeGraph *node);
 void insertNodeRedBlackFixcase1(NodeGraph *node);
 void insertNodeRedBlackFixcase2(NodeGraph *node);
 void insertNodeRedBlackFixcase3(NodeGraph *node);
 void insertNodeRedBlackFixcase4(NodeGraph *node);
 void insertNodeRedBlackFixcase5(NodeGraph *node);
 void redFlip(NodeGraph *root);
 void insertNodeRedBlackAux(NodeGraph *root);
 NodeGraph *rotationLeft(NodeGraph *node, TreeGraph *tree);
 NodeGraph *rotationRight(NodeGraph *node, TreeGraph *tree);
 void insertNodeRedBlackFix(NodeGraph *node, TreeGraph *tree);
 void swapNodes(NodeGraph* oldNode, NodeGraph* newNode);
 */


 void TreeGraph::addNodesAllRedBlack(NodeGraph *root, NodeGraph *old) {
      root->insertNodeRedBlack(old->getIntegerValue(), this, root);
      if (old->getLeftNode() != NULL && old->getRightNode() != NULL) {
          addNodesAllRedBlack(root, old->getLeftNode());
          addNodesAllRedBlack(root, old->getRightNode());
      } else if (old->getLeftNode() != NULL) {
          addNodesAllRedBlack(root, old->getLeftNode());
      } else if (old->getRightNode() != NULL) {
          addNodesAllRedBlack(root, old->getRightNode());
      }
 }



 bool validate_bst(tnode *temp, int min, int max)
 {
     if(temp == NULL)
         return true;

     if(temp->data > min && temp->data < max)
     {
         if( validate_bst(temp->left, min, temp->data) &&
             validate_bst(temp->right, temp->data, max) )
             return true;
     }

     return false;
 }

 bool isBinary(root) {
         if (root == NULL)
           return true;
        else if( root.left == NULL and root.right == NULL)
           return true;
        else if(root.left == NULL)
            if(root.right.element > root.element)
                rerturn isBInary(root.right);
         else if (root.left.element < root.element)
               return isBinary(root.left);
         else
               return isBInary(root.left) and isBinary(root.right);

 }


 void TreeGraph::reBuild(NodeGraph *root) {
      if (root == NULL)
          return;
      int a, b;
      if (root->getParentNode() != NULL) {
          if (root->isRightNode() == true && root->getParentNode()->getIntegerValue() > root->getIntegerValue()) {
              if (root->getParentNode()->getLeftNode() != NULL) {
                  a = root->getIntegerValue();
                  b = root->getParentNode()->getLeftNode()->getIntegerValue();
                  root->swapIntegers(&a, &b);
                  root->setIntegerValue(a);
                  root->getParentNode()->getLeftNode()->setIntegerValue(b);
                  //reBuild(root->getParentNode());
              }
          } else if (root->isLeftNode() == true && root->getParentNode()->getIntegerValue() < root->getIntegerValue()) {
              if (root->getParentNode()->getRightNode() != NULL) {
                  a = root->getIntegerValue();
                  b = root->getParentNode()->getRightNode()->getIntegerValue();
                  root->swapIntegers(&a, &b);
                  root->setIntegerValue(a);
                  root->getParentNode()->getRightNode()->setIntegerValue(b);
                  //reBuild(root->getParentNode());
              }
          }
      }

      reBuild(root->getLeftNode());
      reBuild(root->getRightNode());

 }

 void TreeGraph::swapIntegers(int *a, int *b) {
      int t = *a;
      *a = *b;
      *b = t;
 }

 void TreeGraph::setCorrectBinTree(NodeGraph *root, NodeGraph **first, NodeGraph **middle, NodeGraph **last, NodeGraph **prev) {
      if (root != NULL) {
          setCorrectBinTree(root->getLeftNode(), first, middle, last, prev );
          if (*prev != NULL && root->getIntegerValue() < (*prev)->getIntegerValue()) {
             if (*first == NULL) {
                 *first = *prev;
                 *middle = root;
             } else {
                 *last = root;
             }
         } else if (*last != NULL && root->getIntegerValue() > (*last)->getIntegerValue()) {
             if (*first == NULL) {
                 *first = *prev;
                 *middle = root;
             }
         }
         *prev = root;
         setCorrectBinTree(root->getRightNode(), first, middle, last, prev );
      }
 }

 void TreeGraph::updateCorrectBinTree(NodeGraph *root) {
      int a, b;
      NodeGraph *first, *middle, *last, *prev;
      first = middle = last = prev = NULL;
      setCorrectBinTree(root, &first, &middle, &last, &prev );
      if (first != NULL && last != NULL) {
          a = first->getIntegerValue();
          b = last->getIntegerValue();
          swapIntegers(&a, &b);
          first->setIntegerValue(a);
          last->setIntegerValue(b);
      } else if(first != NULL && middle != NULL) {
          a = first->getIntegerValue();
          b = middle->getIntegerValue();
          swapIntegers(&a, &b);
          first->setIntegerValue(a);
          middle->setIntegerValue(b);
      }
 }

 void TreeGraph::recoverTree(NodeGraph *root) {
      int a, b;
      NodeGraph *curr = root;
      NodeGraph *ptr1 = NULL;
      NodeGraph *ptr2 = NULL;
      NodeGraph *prev = NULL;
      NodeGraph *predecessor = NULL;
      while (curr) {
             if (curr->getLeftNode() == NULL) {
                 if (prev != NULL && prev->getIntegerValue() > curr->getIntegerValue()) {
                     ptr2 = curr;
                     if (ptr1 == NULL)
                         ptr1 = curr;
                 }
                 prev = curr;
                 curr = curr->getRightNode();
             } else {
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
             if (ptr1 != NULL && ptr2 != NULL) {
                 a = ptr1->getIntegerValue();
                 b = ptr2->getIntegerValue();
                 swapIntegers(&a, &b);
                 ptr1->setIntegerValue(a);
                 ptr2->setIntegerValue(b);
             }
         }

 }

 //void reBuild(NodeGraph *root);
 //void swapIntegers(int *a, int *b);
 //void setCorrectBinTree(NodeGraph *root, NodeGraph **first, NodeGraph **middle, NodeGraph **last, NodeGraph **prev);
 //void updateCorrectBinTree(NodeGraph *root);
 //void recoverTree(NodeGraph *root);



