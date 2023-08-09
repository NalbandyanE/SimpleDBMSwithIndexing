#ifndef BTREE_H
#define BTREE_H

template <typename KeyType>
class BTreeNode {
public:
	BTreeNode(int, bool);
	void traverse();
	BTreeNode<KeyType>* search(const KeyType&);
	KeyType* getKeys() const;
	int getT() const;
	BTreeNode<KeyType>** getChildren() const;
	int getN() const;
	bool getLeaf() const;
	void setKeys(KeyType*);
	void setT(int);
	void setChildren(BTreeNode<KeyType>**);
	void setN(int);
	void setLeaf(bool);
	void splitChild(int);
	void insertNonFull(const KeyType&);
	int findKey(const KeyType&);
	void remove(const KeyType&);
	void removeFromLeaf(int);
	void removeFromNonLeaf(int);
	KeyType getPred(int);
	KeyType getSucc(int);
	void fill(int);
	void borrowFromPrev(int);
	void borrowFromNext(int);
	void merge(int);
	~BTreeNode();
private:
	KeyType* keys;
	int t;
	BTreeNode** children;
	int n;
	bool leaf;
};

template <typename KeyType>
class BTree {
public:
	BTree(int);
	void traverse();
	void insert(const KeyType&);
	BTreeNode<KeyType>* search(const KeyType&);
	void remove(const KeyType&);
	~BTree();
private:
	BTreeNode<KeyType>* root;
	int t;
};

#include "../src/btree.tpp"

#endif // BTREE_H