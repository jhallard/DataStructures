//  Created by Frank M. Carrano and Tim Henry.
//  Copyright (c) 2013 __Pearson Education__. All rights reserved.

// PARITALLY COMPLETE.

/** @file BinaryTree.cpp */

#ifndef BINARY_NODE_TREE_CPP
#define BINARY_NODE_TREE_CPP

#include "BinaryNodeTree.h" 
#include "BinaryNode.h" 
#include <iostream>


//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
{
   if (subTreePtr == nullptr)
      return 0;
   else
      return 1 + max(getHeightHelper(subTreePtr->getLeftChildPtr()), 
                     getHeightHelper(subTreePtr->getRightChildPtr()));
}  // end getHeightHelper

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const
{
	static int count = 0;
   if (subTreePtr != nullptr)
   {
      getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
      getNumberOfNodesHelper(subTreePtr->getRightChildPtr());
      count++;
   }  // end if
   return count;
}  // end getHeightHelper


template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr,
                                                            BinaryNode<ItemType>* newNodePtr)
{
   if (subTreePtr == nullptr)
      return newNodePtr;
   else
   {
      BinaryNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
      BinaryNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();
      
      if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
      {
         rightPtr = balancedAdd(rightPtr , newNodePtr);
         subTreePtr->setRightChildPtr(rightPtr );
      }
      else
      {
         leftPtr = balancedAdd(leftPtr, newNodePtr);
         subTreePtr->setLeftChildPtr(leftPtr);
      }  // end if
      
      return subTreePtr;
   }  // end if
}  // end balancedAdd

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
   BinaryNode<ItemType>* newTreePtr = nullptr;
   
   // Copy tree nodes during a preorder traversal
   if (treePtr != nullptr)
   {
      // Copy node
	   newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
	   newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
      newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
   }  // end if
   
   return newTreePtr;
}  // end copyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
   if (subTreePtr != nullptr)
   {
      destroyTree(subTreePtr->getLeftChildPtr());
      destroyTree(subTreePtr->getRightChildPtr());
      delete subTreePtr;
   }  // end if
}  // end destroyTree

//////////////////////////////////////////////////////////////
//      Protected Tree Traversal Sub-Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
   if (treePtr != nullptr)
   {
      inorder(visit, treePtr->getLeftChildPtr());
      ItemType theItem = treePtr->getItem();
      visit(theItem);
      inorder(visit, treePtr->getRightChildPtr());
   }  // end if
}  // end inorder

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
   if (treePtr != nullptr)
   {
	  ItemType theItem = treePtr->getItem();
      visit(theItem);
      preorder(visit, treePtr->getLeftChildPtr());
      preorder(visit, treePtr->getRightChildPtr());
   }  // end if
}  // end inorder

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
   if (treePtr != nullptr)
   {
      postorder(visit, treePtr->getLeftChildPtr());
      postorder(visit, treePtr->getRightChildPtr());
	  ItemType theItem = treePtr->getItem();
      visit(theItem);
   }  // end if
}  // end inorder
//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
}  // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
   rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
}  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
                                         const BinaryNodeTree<ItemType>* leftTreePtr,
                                         const BinaryNodeTree<ItemType>* rightTreePtr)
{
    rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr->rootPtr), 
                                                 copyTree(rightTreePtr->rootPtr));
}  // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr)
{
   rootPtr = copyTree(treePtr.rootPtr);
}  // end copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
   destroyTree(rootPtr);
}  // end destructor

//////////////////////////////////////////////////////////////
//      Public BinaryTreeInterface Methods Section
//////////////////////////////////////////////////////////////

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
   BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
   rootPtr = balancedAdd(rootPtr, newNodePtr);
   return true;
}  // end add

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const
{
   if (isEmpty())
      throw logic_error("getRootData() called with empty tree."); 
   
   return rootPtr->getItem();
}  // end getRootData

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	BinaryNode<ItemType> * temp = rootPtr;
	return getNumberOfNodesHelper(temp);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	BinaryNode<ItemType> * temp = rootPtr;
	return !getNumberOfNodesHelper(temp);
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const
{
	ItemType temp;
	return temp;
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	BinaryNode<ItemType> * temp = rootPtr;
	return getHeightHelper(temp);
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData) 
{
	this->rootPtr->setItem(newData);
}

//////////////////////////////////////////////////////////////
//      Public Traversals Section
//////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
   inorder(visit, rootPtr);
}  // end inorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
   preorder(visit, rootPtr);
}  // end inorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
   postorder(visit, rootPtr);
}  // end inorderTraverse

#endif