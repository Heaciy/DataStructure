#include <iostream>
#include <queue>

using namespace std;

typedef char DataType;

typedef struct BiTreeNode {
  BiTreeNode *lchild;
  DataType data;
  BiTreeNode *rchild;
} * BiTree;

typedef struct StaticBiTreeNode {
  int lchild;
  DataType data;
  int rchild;
} * StaticBiTree;

// 创建二叉树
BiTree createTree(void) {
  DataType data = 0;
  BiTree tmp = nullptr;
  cin >> data;
  cin.get();
  if (data == '.') return nullptr;
  tmp = new BiTreeNode;
  tmp->data = data;
  tmp->lchild = createTree();
  tmp->rchild = createTree();
  return tmp;
}

// 遍历过程的操作
void visit(DataType data) { cout << data << " "; }

// 先序遍历二叉树
BiTree preOrderTraverse(BiTree tree, void (*visit)(DataType)) {
  if (tree != nullptr) {
    visit(tree->data);
    preOrderTraverse(tree->lchild, visit);
    preOrderTraverse(tree->rchild, visit);
    return tree;
  }
  return nullptr;
}

// 中序遍历二叉树
BiTree InOrderTraverse(BiTree tree, void (*visit)(DataType)) {
  if (tree != nullptr) {
    preOrderTraverse(tree->lchild, visit);
    visit(tree->data);
    preOrderTraverse(tree->rchild, visit);
    return tree;
  }
  return nullptr;
}

// 后序遍历二叉树
BiTree PostOrderTraverse(BiTree tree, void (*visit)(DataType)) {
  if (tree != nullptr) {
    preOrderTraverse(tree->lchild, visit);
    preOrderTraverse(tree->rchild, visit);
    visit(tree->data);
    return tree;
  }
  return nullptr;
}

// 层次遍历二叉树
void DoHierarchicallyTraverse(queue<BiTree> visitQueue,
                              void (*visit)(DataType)) {
  if (!visitQueue.empty()) {
    BiTree tmp = visitQueue.front();
    visitQueue.pop();
    visit(tmp->data);
    if (tmp->lchild != nullptr) visitQueue.push(tmp->lchild);
    if (tmp->rchild != nullptr) visitQueue.push(tmp->rchild);
    DoHierarchicallyTraverse(visitQueue, visit);
  }
}

// 层次遍历二叉树
BiTree HierarchicallyTraverse(BiTree tree, void (*visit)(DataType)) {
  queue<BiTree> visitQueue;
  visitQueue.push(tree);
  DoHierarchicallyTraverse(visitQueue, visit);
  return tree;
}

// 销毁二叉树
void DestroyBiTree(BiTree tree) {
  if (tree != nullptr) {
    DestroyBiTree(tree->lchild);
    DestroyBiTree(tree->rchild);
    delete tree;
  }
}

// 获取二叉树大小
void GetSize(BiTree tree, int &size) {
  if (tree != nullptr) {
    size++;
    GetSize(tree->lchild, size);
    GetSize(tree->rchild, size);
  } else
    return;
}

// 动态二叉树转换静态二叉树
void DoDynamicConversion(BiTree tree, StaticBiTree stree, int pos, int &top) {
  if (tree != nullptr) {
    int lpos = tree->lchild == nullptr ? 0 : ++top;
    int rpos = tree->rchild == nullptr ? 0 : ++top;
    stree[pos] = {lpos, tree->data, rpos};
    DoDynamicConversion(tree->lchild, stree, stree[pos].lchild, top);
    DoDynamicConversion(tree->rchild, stree, stree[pos].rchild, top);
  }
}

// 动态二叉树转换静态二叉树
void DynamicConversion(BiTree tree, StaticBiTree &staticTree, int &size) {
  GetSize(tree, size);
  staticTree = new StaticBiTreeNode[size];
  int top = 0;
  DoDynamicConversion(tree, staticTree, 0, top);
}

// 打印静态二叉树
void printStaticTree(StaticBiTree stree, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d [%d %c %d]\n", i, stree[i].lchild, stree[i].data,
           stree[i].rchild);
  }
}

int main() {
  BiTree tree = createTree();
  preOrderTraverse(tree, visit);
  cout << endl;

  InOrderTraverse(tree, visit);
  cout << endl;

  PostOrderTraverse(tree, visit);
  cout << endl;

  HierarchicallyTraverse(tree, visit);
  cout << endl;

  StaticBiTree stree;
  int size = 0;

  DynamicConversion(tree, stree, size);
  printStaticTree(stree, size);

  DestroyBiTree(tree);
  return 0;
}
