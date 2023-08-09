#include "../include/btree.h"

#include <iostream>

template <typename KeyType>
BTreeNode<KeyType>::BTreeNode(int t, bool leaf) : t{t}, leaf{leaf}
{
	keys = new KeyType[2 * t - 1];
	children = new BTreeNode*[2 * t];
	n = 0;
}

template <typename KeyType>
KeyType* BTreeNode<KeyType>::getKeys() const {
	return keys;
}

template <typename KeyType>
int BTreeNode<KeyType>::getT() const {
	return t;
}

template <typename KeyType>
BTreeNode<KeyType>** BTreeNode<KeyType>::getChildren() const {
	return children;
}

template <typename KeyType>
int BTreeNode<KeyType>::getN() const {
	return n;
}

template <typename KeyType>
bool BTreeNode<KeyType>::getLeaf() const {
	return leaf;
}

template <typename KeyType>
void BTreeNode<KeyType>::setKeys(KeyType* k) {
	keys = k;
}

template <typename KeyType>
void BTreeNode<KeyType>::setT(int _t) {
	t = _t;
}

template <typename KeyType>
void BTreeNode<KeyType>::setChildren(BTreeNode<KeyType>** ch) {
	children = ch;
}

template <typename KeyType>
void BTreeNode<KeyType>::setN(int _n) {
	n = _n;
}

template <typename KeyType>
void BTreeNode<KeyType>::setLeaf(bool l) {
	leaf = l;
}

template <typename KeyType>
void BTreeNode<KeyType>::traverse() {
	int i;
    	for (i = 0; i < n; ++i) {
        	if (!leaf) {
            		children[i]->traverse();
        	}
        	std::cout << " " << keys[i];
    	}
    	if (!leaf) {
        	children[i]->traverse();
    	}
}

template <typename KeyType>
BTreeNode<KeyType>* BTreeNode<KeyType>::search(const KeyType& k) {
	int i = 0;
	while (i < n && k > keys[i]) {
		++i;
	}
	if (keys[i] == k) {
		return this;
	}
	if (leaf == true) {
		return nullptr;
	}
	return children[i]->search(k);
}

template <typename KeyType>
BTreeNode<KeyType>::~BTreeNode() {
	delete[] keys;
	delete[] children;
}

template <typename KeyType>
BTree<KeyType>::BTree(int t) : t{t}
{
	root = nullptr;
}

template <typename KeyType>
void BTree<KeyType>::traverse() {
	if (root) {
		root->traverse();
	}
}

template <typename KeyType>
void BTreeNode<KeyType>::splitChild(int i) {
	BTreeNode<KeyType>* child = children[i];
    	BTreeNode<KeyType>* new_child = new BTreeNode<KeyType>(t, child->leaf);
    	new_child->n = t - 1;
    	for (int j = 0; j < t - 1; j++) {
        	new_child->keys[j] = child->keys[j + t];
    	}
    	if (!child->leaf) {
        	for (int j = 0; j < t; j++) {
            		new_child->children[j] = child->children[j + t];
        	}
    	}
    	child->n = t - 1;
    	for (int j = n; j >= i + 1; j--) {
        	children[j + 1] = children[j];
    	}
    	children[i + 1] = new_child;
    	for (int j = n - 1; j >= i; j--) {
        	keys[j + 1] = keys[j];
    	}
    	keys[i] = child->keys[t - 1];
    	n++;
}

template <typename KeyType>
void BTreeNode<KeyType>::insertNonFull(const KeyType& k) {
	int i = n - 1;
    	if (leaf) {
        	while (i >= 0 && keys[i] > k) {
            		keys[i + 1] = keys[i];
            		i--;
        	}
        	keys[i + 1] = k;
        	n++;
    	} else {
        	while (i >= 0 && keys[i] > k) {
            		i--;
        	}
        	if (children[i + 1]->n == 2 * t - 1) {
            		splitChild(i + 1);
            		if (keys[i + 1] < k) {
                		i++;
            		}
        	}
        	children[i + 1]->insertNonFull(k);
    	}
}

template <typename KeyType>
void BTree<KeyType>::insert(const KeyType& k) {
	if (!root) {
        	root = new BTreeNode<KeyType>(t, true);
        	root->getKeys()[0] = k;
        	root->setN(1);
    	} else {
        	if (root->getN() == 2 * t - 1) {
            		BTreeNode<KeyType>* new_root = new BTreeNode<KeyType>(t, false);
            		new_root->getChildren()[0] = root;
            		new_root->splitChild(0);
            		int i = 0;
            		if (new_root->getKeys()[0] < k) {
                		i++;
            		}
            		new_root->getChildren()[i]->insertNonFull(k);
            		root = new_root;
        	} else {
            		root->insertNonFull(k);
        	}
    	}
}

template <typename KeyType>
BTreeNode<KeyType>* BTree<KeyType>::search(const KeyType& k) {
	if (!root) {
		return nullptr;
	}
	return root->search(k);
}

template <typename KeyType>
int BTreeNode<KeyType>::findKey(const KeyType& k) {
    	int idx = 0;
    	while (idx < n && keys[idx] < k) {
        	idx++;
    	}
    	return idx;
}

template <typename KeyType>
void BTreeNode<KeyType>::remove(const KeyType& k) {
	int idx = findKey(k);
    	if (idx < n && keys[idx] == k) {
        	if (leaf) {
            		removeFromLeaf(idx);
        	} else {
            		removeFromNonLeaf(idx);
        	}
    	} else {
        	if (leaf) {
            		return;
        	}
        	bool flag = (idx == n);
        	if (children[idx]->n < t) {
            		fill(idx);
        	}
        	if (flag && idx > n) {
            		children[idx - 1]->remove(k);
        	} else {
            		children[idx]->remove(k);
        	}
    	}
}

template <typename KeyType>
void BTreeNode<KeyType>::removeFromLeaf(int idx) {
	for (int i = idx + 1; i < n; ++i) {
        	keys[i - 1] = keys[i];
    	}
    	n--;
}

template <typename KeyType>
void BTreeNode<KeyType>::removeFromNonLeaf(int idx) {
	KeyType k = keys[idx];
    	if (children[idx]->n >= t) {
        	KeyType pred = getPred(idx);
        	keys[idx] = pred;
        	children[idx]->remove(pred);
    	} else if (children[idx + 1]->n >= t) {
        	KeyType succ = getSucc(idx);
        	keys[idx] = succ;
        	children[idx + 1]->remove(succ);
    	} else {
        	merge(idx);
        	children[idx]->remove(k);
    	}
}	

template <typename KeyType>
KeyType BTreeNode<KeyType>::getPred(int idx) {
	BTreeNode<KeyType>* curr = children[idx];
    	while (!curr->leaf) {
        	curr = curr->children[curr->n];
    	}
    	return curr->keys[curr->n - 1];
}

template <typename KeyType>
KeyType BTreeNode<KeyType>::getSucc(int idx) {
	BTreeNode<KeyType>* curr = children[idx + 1];
    	while (!curr->leaf) {
        	curr = curr->children[0];
    	}
    	return curr->keys[0];
}

template <typename KeyType>
void BTreeNode<KeyType>::fill(int idx) {
	if (idx != 0 && children[idx - 1]->n >= t) {
        	borrowFromPrev(idx);
    	} else if (idx != n && children[idx + 1]->n >= t) {
        	borrowFromNext(idx);
    	} else {
        	if (idx != n) {
            		merge(idx);
        	} else {
            		merge(idx - 1);
      	  	}
    	}
}

template <typename KeyType>
void BTreeNode<KeyType>::borrowFromPrev(int idx) {
	BTreeNode<KeyType>* child = children[idx];
    	BTreeNode<KeyType>* sibling = children[idx - 1];

    	for (int i = child->n - 1; i >= 0; --i) {
        	child->keys[i + 1] = child->keys[i];
    	}

    	if (!child->leaf) {
        	for (int i = child->n; i >= 0; --i) {
            		child->children[i + 1] = child->children[i];
        	}
    	}

    	child->keys[0] = keys[idx - 1];

    	if (!child->leaf) {
        	child->children[0] = sibling->children[sibling->n];
    	}

    	keys[idx - 1] = sibling->keys[sibling->n - 1];

    	child->n += 1;
    	sibling->n -= 1;
}

template <typename KeyType>
void BTreeNode<KeyType>::borrowFromNext(int idx) {
	 BTreeNode<KeyType>* child = children[idx];
    	BTreeNode<KeyType>* sibling = children[idx + 1];

    	child->keys[child->n] = keys[idx];

    	if (!child->leaf) {
        	child->children[child->n + 1] = sibling->children[0];
    	}

    	keys[idx] = sibling->keys[0];

    	for (int i = 1; i < sibling->n; ++i) {
        	sibling->keys[i - 1] = sibling->keys[i];
    	}

    	if (!sibling->leaf) {
        	for (int i = 1; i <= sibling->n; ++i) {
            		sibling->children[i - 1] = sibling->children[i];
        	}
    	}

    	child->n += 1;
    	sibling->n -= 1;
}

template <typename KeyType>
void BTreeNode<KeyType>::merge(int idx) {
	BTreeNode<KeyType>* child = children[idx];
    	BTreeNode<KeyType>* sibling = children[idx + 1];

    	child->keys[t - 1] = keys[idx];

    	for (int i = 0; i < sibling->n; ++i) {
        	child->keys[i + t] = sibling->keys[i];
    	}

    	if (!child->leaf) {
        	for (int i = 0; i <= sibling->n; ++i) {
            		child->children[i + t] = sibling->children[i];
        	}
    	}

    	for (int i = idx + 1; i < n; ++i) {
        	keys[i - 1] = keys[i];
    	}

    	for (int i = idx + 2; i <= n; ++i) {
        	children[i - 1] = children[i];
    	}

    	child->n += sibling->n + 1;
    	n--;

    	delete sibling;
}

template <typename KeyType>
void BTree<KeyType>::remove(const KeyType& k) {
	if (!root) {
        	return;
    	}
    	root->remove(k);
    	if (root->getN() == 0) {
        	BTreeNode<KeyType>* old_root = root;
        	if (root->getLeaf()) {
            		root = nullptr;
        	} else {
            		root = root->getChildren()[0];
        	}
        	delete old_root;
    	}
}

template <typename KeyType>
BTree<KeyType>::~BTree() {
	delete root;
}
