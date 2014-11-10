/*
*    @author John H Allard. May 27, 2014. This is the implementation of the DictionaryNode class, defined of course in DictionaryNode.h
*    This class represents an entry on a hash table that uses chaining to avoid collisions. The reason it has node in the name is because
*    each object of this class also acts like a node in a linked list that links to a chain of other DictionaryNodes behind it in the hash table.
*    ONLINE REPOSITORY http://github.com/jhallard/HashDictionary
*/

#ifndef DICTIONARY_NODE_CPP
#define DICTIONARY_NODE_CPP

#include "DictionaryNode.h"

template <class keyType, class itemType>
DictionaryNode<keyType, itemType>::DictionaryNode(keyType key, itemType item)
{
    this->key = key;
    this->item = item;
    this->next = nullptr;
}

template <class keyType, class itemType>
void DictionaryNode<keyType, itemType>::setKey(keyType key)
{
    this->key = key;
}

template <class keyType, class itemType>
keyType DictionaryNode<keyType, itemType>::getKey()
{
    return this->key;
}

template <class keyType, class itemType>
void DictionaryNode<keyType, itemType>::setItem(itemType)
{
    this->item = item;
}

template <class keyType, class itemType>
itemType DictionaryNode<keyType, itemType>::getItem()
{
    return this->item;
}

template <class keyType, class itemType>
DictionaryNode<keyType, itemType> * DictionaryNode<keyType, itemType>::getNext()
{
    return this->next;
}

template <class keyType, class itemType>
void DictionaryNode<keyType, itemType>::setNext(DictionaryNode<keyType, itemType> * nextEntry)
{
    this->next = nextEntry;
}

#endif