#include <bits/stdc++.h>
using namespace std;

class Node {
    private:
        int val, height;
        Node* left;
        Node* right;

    public:
        Node(int val, Node* left, Node* right): val(val), left(left), right(right), height(1) {}
        Node(int val): Node(val, nullptr, nullptr) {}

        // getters
        int getVal() { return this->val; }
        int getHeight() { return this->height; }
        Node* getLeftNode() { return this->left; }
        Node* getRightNode() { return this->right; }

        // setters
        void setHeight(int height) {
            this->height = height;
        }

        void setLeftNode(Node* left) {
            this->left = left;
        }

        void setRightNode(Node* right) {
            this->right = right;
        }

        void setVal(int val) {
            this->val = val;
        }
};

class AVLTree {
    public:
        void insert(int n) {
            if (head == nullptr) {
                head = new Node(n);
                return;
            }

            head = insert(n, head);
        }

        void remove(int n) {
            if (head == nullptr) {
                return;
            }

            head = remove(n, head);
        }

        void preOrder(Node* curNode, bool isStart) {
            if (head == nullptr) {
                cout << "EMPTY" << endl;
                return;
            }

            if (isStart) {
                preOrder(head, false);
                return;
            } 

            // normal preOrder
            if (curNode == nullptr) return;

            cout << curNode->getVal() << " ";
            preOrder(curNode->getLeftNode(), isStart);
            preOrder(curNode->getRightNode(), isStart);
        }

        void inOrder(Node *curNode, bool isStart) {
            if (head == nullptr) {
                cout << "EMPTY" << endl;
                return;
            }

            if (isStart) {
                inOrder(head, false);
                return;
            }

            // normal inOrder
            if (curNode == nullptr) return;

            inOrder(curNode->getLeftNode(), isStart);
            cout << curNode->getVal() << " ";
            inOrder(curNode->getRightNode(), isStart);
        }

        void postOrder(Node* curNode, bool isStart) {
            if (head == nullptr) {
                cout << "EMPTY" << endl;
                return;
            }

            if (isStart) {
                postOrder(head, false);
                return;
            } 

            // normal postOrder
            if (curNode == nullptr) return;

            postOrder(curNode->getLeftNode(), isStart);
            postOrder(curNode->getRightNode(), isStart);
            cout << curNode->getVal() << " ";
        }

        AVLTree(): head(nullptr) {}

    private:
        Node* head;

        int getHeight(Node *node) {
            return (node == nullptr ? 0 : node->getHeight());
        } 

        int getBalancingFactor(Node* node) {
            if (!node) return 0;

            Node* left = node->getLeftNode();
            Node* right = node->getRightNode();

            return getHeight(left) - getHeight(right);
        }

        Node* rightRotate(Node* y) {
            Node* x = y->getLeftNode();
            Node* temp = x->getRightNode();

            x->setRightNode(y);
            y->setLeftNode(temp);

            y->setHeight(max(getHeight(y->getLeftNode()), getHeight(y->getRightNode())) + 1);
            x->setHeight(max(getHeight(x->getLeftNode()), getHeight(x->getRightNode())) + 1);

            return x;
        }

        Node* leftRotate(Node* x) {
            Node* y = x->getRightNode();
            Node* temp = y->getLeftNode();

            y->setLeftNode(x);
            x->setRightNode(temp);

            x->setHeight(max(getHeight(x->getLeftNode()), getHeight(x->getRightNode())) + 1);
            y->setHeight(max(getHeight(y->getLeftNode()), getHeight(y->getRightNode())) + 1);

            return y;
        }

        Node* insert(int val, Node* curNode) {
            if (curNode == nullptr) {
                return new Node(val);
            }

            if (val < curNode->getVal()) {
                curNode->setLeftNode(insert(val, curNode->getLeftNode()));
            } else {
                curNode->setRightNode(insert(val, curNode->getRightNode()));
            }

            curNode->setHeight(max(getHeight(curNode->getLeftNode()), getHeight(curNode->getRightNode())) + 1);
            return rebalanceTree(curNode);
        }

        Node* remove(int val, Node* curNode) {
            if (!curNode) {
                return nullptr;
            }

            if (curNode->getVal() == val) {
                // node to delete
                if (!curNode->getLeftNode() || !curNode->getRightNode()) {
                    Node* temp = curNode->getLeftNode() ? curNode->getLeftNode() : curNode->getRightNode();
                    delete curNode;
                    return temp;
                } else {
                    Node* pred = getMax(curNode->getLeftNode());
                    curNode->setVal(pred->getVal());
                    curNode->setLeftNode(remove(pred->getVal(), curNode->getLeftNode()));
                }

            } else if (val < curNode->getVal()) {
                curNode->setLeftNode(remove(val, curNode->getLeftNode()));
            } else {
                curNode->setRightNode(remove(val, curNode->getRightNode()));
            }

            curNode->setHeight(max(getHeight(curNode->getLeftNode()), getHeight(curNode->getRightNode())) + 1);
            return rebalanceTree(curNode);
        }

        Node* getMax(Node* curNode) {
            if (!curNode) return nullptr;
            while (curNode->getRightNode()) curNode = curNode->getRightNode();
            return curNode;
        }

        Node* rebalanceTree(Node* node) {
            int bf = getBalancingFactor(node);

            if (bf > 1) {
                // left-left
                if (getBalancingFactor(node->getLeftNode()) >= 0) {
                    return rightRotate(node);
                } else { // left-right
                    node->setLeftNode(leftRotate(node->getLeftNode()));
                    return rightRotate(node);
                }
            }

            if (bf < -1) {
                // right-right
                if (getBalancingFactor(node->getRightNode()) <= 0) {
                    return leftRotate(node);
                } else { // right-left
                    node->setRightNode(rightRotate(node->getRightNode()));
                    return leftRotate(node);
                }
            }
            
            return node;
        } 
};

int main() {
    AVLTree tree;
    int n; cin >> n;
    while (n--) {
        string comand;
        cin >> comand;

        if (comand[0] == 'A') {
            tree.insert(stoi(comand.substr(1)));
        } else{
            tree.remove(stoi(comand.substr(1)));
        }
    }

    string fin; cin >> fin;
    if (fin == "PRE") {
        tree.preOrder(nullptr, true);
    } else if (fin == "POST") {
        tree.postOrder(nullptr, true);
    } else {
        tree.inOrder(nullptr, true);
    }

    cout << endl;
}