#include "./bplus.hpp"

Node::Node() {
  info = new TagData[MAX];
  info->rating = -1;
  info->tag = "";
  ptr = new Node *[MAX + 1];
}

BPTree::BPTree() {
  root = NULL;
}

// Search operation
int BPTree::search(int x) {
  if (root == NULL) {
    return 0;
  } else {
    Node *cursor = root;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        if (x < cursor->info[i].user_id) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    for (int i = 0; i < cursor->size; i++) {
      if (cursor->info[i].user_id == x) {
        return 1;
      }
    }
    return 0;
  }
}

int BPTree::update(TagData x)
{
  if (root == NULL) {
    return 0;
  } else {
    Node *cursor = root;
    while (cursor->IS_LEAF == false) {
      for (int i = 0; i < cursor->size; i++) {
        if (x.user_id < cursor->info[i].user_id) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    for (int i = 0; i < cursor->size; i++) {
      if (cursor->info[i].user_id == x.user_id) 
      {
        if(x.rating == -1)
          cursor->info[i].tag = x.tag;
        else
          cursor->info[i].rating = x.rating;
        return 1;
      }
    }
    return 0;
  }
}

// Insert Operation
void BPTree::insert(TagData x) {
  if (root == NULL) {
    root = new Node();
    root->info[0] = x;
    root->IS_LEAF = true;
    root->size = 1;
  } else {
    Node *cursor = root;
    Node *parent;
    while (cursor->IS_LEAF == false) {
      parent = cursor;
      for (int i = 0; i < cursor->size; i++) {
        if (x.user_id < cursor->info[i].user_id) {
          cursor = cursor->ptr[i];
          break;
        }
        if (i == cursor->size - 1) {
          cursor = cursor->ptr[i + 1];
          break;
        }
      }
    }
    if (cursor->size < MAX) {
      int i = 0;
      while (x.user_id > cursor->info[i].user_id && i < cursor->size)
        i++;
      for (int j = cursor->size; j > i; j--) {
        cursor->info[j] = cursor->info[j - 1];
      }
      cursor->info[i] = x;
      cursor->size++;
      cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
      cursor->ptr[cursor->size - 1] = NULL;
    } else {
      Node *newLeaf = new Node();
      TagData virtualNode[MAX + 1];
      for (int i = 0; i < MAX; i++) {
        virtualNode[i] = cursor->info[i];
      }
      int i = 0, j;
      while (x.user_id > virtualNode[i].user_id && i < MAX)
        i++;
      for (int j = MAX + 1; j > i; j--) {
        virtualNode[j] = virtualNode[j - 1];
      }
      virtualNode[i] = x;
      newLeaf->IS_LEAF = true;
      cursor->size = (MAX + 1) / 2;
      newLeaf->size = MAX + 1 - (MAX + 1) / 2;
      cursor->ptr[cursor->size] = newLeaf;
      newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
      cursor->ptr[MAX] = NULL;
      for (i = 0; i < cursor->size; i++) {
        cursor->info[i] = virtualNode[i];
      }
      for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
        newLeaf->info[i] = virtualNode[j];
      }
      if (cursor == root) {
        Node *newRoot = new Node();
        newRoot->info[0] = newLeaf->info[0];
        newRoot->ptr[0] = cursor;
        newRoot->ptr[1] = newLeaf;
        newRoot->IS_LEAF = false;
        newRoot->size = 1;
        root = newRoot;
      } else {
        insertInternal(newLeaf->info[0], parent, newLeaf);
      }
    }
  }
}

// Insert Operation
void BPTree::insertInternal(TagData x, Node *cursor, Node *child) {
  if (cursor->size < MAX) {
    int i = 0;
    while (x.user_id > cursor->info[i].user_id && i < cursor->size)
      i++;
    for (int j = cursor->size; j > i; j--) {
      cursor->info[j] = cursor->info[j - 1];
    }
    for (int j = cursor->size + 1; j > i + 1; j--) {
      cursor->ptr[j] = cursor->ptr[j - 1];
    }
    cursor->info[i] = x;
    cursor->size++;
    cursor->ptr[i + 1] = child;
  } else {
    Node *newInternal = new Node();
    TagData virtualKey[MAX + 1];
    Node *virtualPtr[MAX + 2];
    for (int i = 0; i < MAX; i++) {
      virtualKey[i] = cursor->info[i];
    }
    for (int i = 0; i < MAX + 1; i++) {
      virtualPtr[i] = cursor->ptr[i];
    }
    int i = 0, j;
    while (x.user_id > virtualKey[i].user_id && i < MAX)
      i++;
    for (int j = MAX + 1; j > i; j--) {
      virtualKey[j] = virtualKey[j - 1];
    }
    virtualKey[i] = x;
    for (int j = MAX + 2; j > i + 1; j--) {
      virtualPtr[j] = virtualPtr[j - 1];
    }
    virtualPtr[i + 1] = child;
    newInternal->IS_LEAF = false;
    cursor->size = (MAX + 1) / 2;
    newInternal->size = MAX - (MAX + 1) / 2;
    for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
      newInternal->info[i] = virtualKey[j];
    }
    for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
      newInternal->ptr[i] = virtualPtr[j];
    }
    if (cursor == root) {
      Node *newRoot = new Node();
      newRoot->info[0] = cursor->info[cursor->size];
      newRoot->ptr[0] = cursor;
      newRoot->ptr[1] = newInternal;
      newRoot->IS_LEAF = false;
      newRoot->size = 1;
      root = newRoot;
    } else {
      insertInternal(cursor->info[cursor->size], findParent(root, cursor),
                     newInternal);
    }
  }
}

// Find the parent
Node *BPTree::findParent(Node *cursor, Node *child) {
  Node *parent;
  if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
    return NULL;
  }
  for (int i = 0; i < cursor->size + 1; i++) {
    if (cursor->ptr[i] == child) {
      parent = cursor;
      return parent;
    } else {
      parent = findParent(cursor->ptr[i], child);
      if (parent != NULL)
        return parent;
    }
  }
  return parent;
}

void BPTree::display(Node *cursor) {
  if (cursor != NULL) {
    for (int i = 0; i < cursor->size; i++) {
      cout << cursor->info[i].user_id << " " << cursor->info[i].rating << " ";
    }
    cout << "\n";
    if (cursor->IS_LEAF != true) {
      for (int i = 0; i < cursor->size + 1; i++) {
        display(cursor->ptr[i]);
      }
    }
  }
}

// Get the root
Node *BPTree::getRoot() { return root; }
