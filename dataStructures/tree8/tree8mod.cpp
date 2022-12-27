#include "tree8mod.hpp"

void createRoot(const tree &_tree)
{
    createRoot((tree *)&_tree);
}

void initTree(const tree &_tree, unsigned size)
{
    initTree((tree *)&_tree, size);
}

void writeDataTree(const tree &_tree, tree8BaseType E)
{
    writeDataTree((tree *)&_tree, E);
}

bool isLSon(const tree &_tree)
{
    return isLSon((tree *)&_tree);
}

bool isRSon(const tree &_tree)
{
    return isRSon((tree *)&_tree);
}

bool isEmptyTree(const tree &_tree)
{
    return isEmptyTree((tree *)&_tree);
}

void delTree(const tree &_tree)
{
    delTree((tree *)&_tree);
}

bool isLeafEmpty(const tree &_tree)
{
    return (const_cast<tree *>(&_tree)->pBuf[_tree.ptr - 1]->flag != 1);
}

tree getLSon(const tree &_tree)
{
    assert(!isLSon(_tree) && "ERROR: left son is empty");
    // FIXME: создается копия целого дерева, что не есть хорошо
    tree temp = _tree;
    moveToLSon(const_cast<tree *>(&temp), nullptr);
    return temp;
}

tree getRSon(const tree &_tree)
{
    assert(!isRSon(_tree) && "ERROR: right son is empty");
    // FIXME: создается копия целого дерева, что не есть хорошо
    tree temp = _tree;
    moveToRSon(const_cast<tree *>(&temp), nullptr);
    return temp;
}

bool isLSonEmpty(const tree &_tree)
{
    return (const_cast<tree *>(&_tree)->pBuf[_tree.ptr * 2 + 1 - 1]->flag != 1);
}

bool isRSonEmpty(const tree &_tree)
{
    return (const_cast<tree *>(&_tree)->pBuf[_tree.ptr * 2 + 2 - 1]->flag != 1);
}

bool isLSonFull(const tree &_tree)
{
    return (const_cast<tree *>(&_tree)->pBuf[_tree.ptr * 2 + 1 - 1]->flag == 1);
}

bool isRSonFull(const tree &_tree)
{
    return (const_cast<tree *>(&_tree)->pBuf[_tree.ptr * 2 + 2 - 1]->flag == 1);
}