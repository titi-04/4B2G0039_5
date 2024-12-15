
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>
using namespace std;

// AVL 樹的節點結構
struct AVLNode {
    int key; // 節點的鍵值
    AVLNode* left; // 左子節點指標
    AVLNode* right; // 右子節點指標
    int height; // 節點的高度

    // 節點的構造函數，初始化鍵值和指標
    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
public:
    AVLNode* root; // 樹的根節點

    AVLTree() : root(nullptr) {}

    // 獲取節點高度
    int height(AVLNode* node) {
        return node ? node->height : 0; // 如果節點為空，高度為 0
    }

    // 計算平衡因子
    int balanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    // 右旋操作
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // 執行旋轉
        x->right = y;
        y->left = T2;

        // 更新高度
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x; // 返回新的根節點
    }

    // 左旋操作
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // 執行旋轉
        y->left = x;
        x->right = T2;

        // 更新高度
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y; // 返回新的根節點
    }

    // 插入節點
    AVLNode* insert(AVLNode* node, int key) {
        // 1. 標準的二叉搜索樹插入
        if (!node)
            return new AVLNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // 不允許重複鍵值

        // 2. 更新節點高度
        node->height = 1 + max(height(node->left), height(node->right));

        // 3. 計算平衡因子並進行平衡
        int balance = balanceFactor(node);

        // LL 情況
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // RR 情況
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // LR 情況
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // RL 情況
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node; // 返回未平衡的節點
    }

    // 找到以給定節點為根的子樹中鍵值最小的節點
    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    // 刪除節點
    AVLNode* deleteNode(AVLNode* root, int key) {
        if (!root)
            return root;

        // 遍歷找到需要刪除的節點
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            // 節點有 0 或 1 個子節點
            if (!root->left || !root->right) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                }
                else {
                    *root = *temp;
                }
                delete temp;
            }
            else {
                // 節點有兩個子節點，找到中序後繼
                AVLNode* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root)
            return root;

        // 更新高度
        root->height = 1 + max(height(root->left), height(root->right));

        // 平衡樹
        int balance = balanceFactor(root);

        // LL 情況
        if (balance > 1 && balanceFactor(root->left) >= 0)
            return rotateRight(root);

        // LR 情況
        if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // RR 情況
        if (balance < -1 && balanceFactor(root->right) <= 0)
            return rotateLeft(root);

        // RL 情況
        if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    // 插入接口
    void insert(int key) {
        root = insert(root, key);
    }

    // 刪除接口
    void remove(int key) {
        root = deleteNode(root, key);
    }

    // 層次遍歷打印樹
    void printTreeByLevel(AVLNode* node) {
        if (!node) return;

        queue<AVLNode*> q;
        q.push(node);

        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                AVLNode* cur = q.front();
                q.pop();

                if (cur) {
                    cout << cur->key << " ";
                    q.push(cur->left);
                    q.push(cur->right);
                }
                else {
                    cout << "  ";
                }
            }
            cout << endl;
        }
    }

    // 打印樹結構
    void printTree() {
        printTreeByLevel(root);
    }
};
struct Node23 {
    vector<int> keys;  // 存放節點的鍵值（最多2個鍵）
    vector<Node23*> children;  // 存放子節點的指針（最多3個子節點）

    Node23() {}  // 建構子

    bool isLeaf() {  // 檢查當前節點是否為葉子節點
        return children.empty();  // 如果沒有子節點，則是葉子節點
    }
};

class Tree23 {
public:
    Node23* root;

    Tree23() : root(nullptr) {}

    void insert(int key) {
        if (!root) {
            root = new Node23();
            root->keys.push_back(key);
            return;
        }

        Node23* splitNode = nullptr;
        int midKey;

        root = insert(root, key, splitNode, midKey);

        if (splitNode) {
            Node23* newRoot = new Node23();
            newRoot->keys.push_back(midKey);
            newRoot->children.push_back(root);
            newRoot->children.push_back(splitNode);
            root = newRoot;
        }
    }

    Node23* insert(Node23* node, int key, Node23*& splitNode, int& midKey) {
        if (node->isLeaf()) {  // 如果是葉子節點
            node->keys.push_back(key);  // 插入鍵值
            sort(node->keys.begin(), node->keys.end());  // 排序鍵值

            if (node->keys.size() > 2) {  // 如果節點有超過2個鍵
                splitNode = split(node, midKey);  // 分割節點
            }

            return node;
        }

        int pos = findChildIndex(node, key);  // 找到應該插入的子節點

        Node23* childSplit = nullptr;
        int childMidKey;

        node->children[pos] = insert(node->children[pos], key, childSplit, childMidKey);  // 將鍵插入到子節點

        if (childSplit) {  // 如果子節點需要分割
            node->keys.insert(node->keys.begin() + pos, childMidKey);  // 插入中間鍵到當前節點
            node->children.insert(node->children.begin() + pos + 1, childSplit);  // 插入分割的子節點

            if (node->keys.size() > 2) {  // 如果當前節點超過2個鍵
                splitNode = split(node, midKey);  // 分割當前節點
            }
        }

        return node;
    }

    int findChildIndex(Node23* node, int key) {
        int i = 0;
        while (i < node->keys.size() && key > node->keys[i])
            i++;
        return i;
    }

    Node23* split(Node23* node, int& midKey) {
        Node23* newNode = new Node23();  // 創建一個新節點
        midKey = node->keys[1];  // 取出中間鍵作為分割鍵
        newNode->keys.push_back(node->keys[2]);  // 將右邊的鍵移到新節點

        if (!node->isLeaf()) {  // 如果不是葉子節點
            newNode->children.push_back(node->children[2]);
            newNode->children.push_back(node->children[3]);
        }

        node->keys.resize(1);  // 保留左邊的鍵
        if (!node->isLeaf()) {
            node->children.resize(2);  // 保留左邊的子節點
        }

        return newNode;
    }

    void remove(int key) {  // 刪除鍵值
        if (!root) return;
        remove(root, key);
        if (root && root->keys.empty() && !root->isLeaf()) {
            Node23* oldRoot = root;
            root = root->children[0];  // 如果根節點被刪空，將根指向其唯一的子節點
            delete oldRoot;
        }
    }

    void remove(Node23* node, int key) {  // 遞迴刪除
        int idx = 0;
        while (idx < node->keys.size() && key > node->keys[idx])
            idx++;

        if (idx < node->keys.size() && key == node->keys[idx]) {  // 找到鍵值
            if (node->isLeaf()) {  // 如果是葉子節點
                node->keys.erase(node->keys.begin() + idx);
            }
            else {  // 如果是內部節點，找繼承者來替換
                int successorKey = getSuccessor(node->children[idx + 1]);
                node->keys[idx] = successorKey;
                remove(node->children[idx + 1], successorKey);
            }
        }
        else if (!node->isLeaf()) {  // 如果不是葉子節點，繼續遞迴刪除
            remove(node->children[idx], key);

            if (node->children[idx]->keys.empty()) {
                rebalance(node, idx);  // 重平衡節點
            }
        }
    }

    int getSuccessor(Node23* node) {
        while (!node->isLeaf())
            node = node->children[0];
        return node->keys[0];
    }

    void rebalance(Node23* node, int idx) {  // 重平衡方法
        if (idx > 0 && node->children[idx - 1]->keys.size() > 1) {  // 左兄弟有多於1個鍵
            // 重平衡操作
        }
        else if (idx < node->children.size() - 1 && node->children[idx + 1]->keys.size() > 1) {  // 右兄弟有多於1個鍵
            // 重平衡操作
        }
        else {
            if (idx > 0) {
                merge(node, idx - 1);  // 合併左兄弟
            }
            else {
                merge(node, idx);  // 合併右兄弟
            }
        }
    }

    void merge(Node23* node, int idx) {  // 合併操作
        Node23* leftChild = node->children[idx];
        Node23* rightChild = node->children[idx + 1];

        leftChild->keys.push_back(node->keys[idx]);
        leftChild->keys.insert(leftChild->keys.end(), rightChild->keys.begin(), rightChild->keys.end());

        if (!rightChild->isLeaf()) {
            leftChild->children.insert(leftChild->children.end(), rightChild->children.begin(), rightChild->children.end());
        }

        node->keys.erase(node->keys.begin() + idx);
        node->children.erase(node->children.begin() + idx + 1);

        delete rightChild;
    }

    void printTreeByLevel(Node23* node) {  // 按層次顯示樹
        if (!node) return;

        queue<Node23*> q;
        q.push(node);

        while (!q.empty()) {
            int size = q.size();
            while (size--) {
                Node23* cur = q.front();
                q.pop();

                if (cur) {
                    for (int key : cur->keys) {
                        cout << key << " ";  // 顯示鍵值
                    }
                    cout << "  ";
                    for (Node23* child : cur->children) {
                        q.push(child);  // 把子節點加入隊列
                    }
                }
                else {
                    cout << "  ";
                }
            }
            cout << endl;
        }
    }

    void printTree() {  // 顯示整棵樹
        printTreeByLevel(root);
    }
};

// 主函數，執行樹的插入、刪除及顯示操作
int main() {
    AVLTree avl;
    Tree23 tree23;

    cout << "請輸入整數值 (以 -1 結束):\n";
    int val;
    while (cin >> val && val != -1) {
        avl.insert(val);
        tree23.insert(val);
    }

    while (true) {
        cout << "\n選擇操作: \n1. 插入\n2. 刪除\n3. 顯示 AVL 樹\n4. 顯示 2-3 樹\n5. 結束\n";
        int choice;
        cin >> choice;

        if (choice == 5) break;

        switch (choice) {
        case 1:
            cout << "輸入要插入的值: ";
            cin >> val;
            avl.insert(val);
            tree23.insert(val);
            break;
        case 2:
            cout << "輸入要刪除的值: ";
            cin >> val;
            avl.remove(val);
            tree23.remove(val);
            break;
        case 3:
            cout << "\nAVL 樹結構 (層次遍歷):\n";
            avl.printTree();
            break;
        case 4:
            cout << "\n2-3 樹結構 (層次遍歷):\n";
            tree23.printTree();
            break;
        default:
            cout << "無效選項。\n";
        }
    }

    return 0;
}
