/*
*    @author John H Allard. Made for GCC CSIS 212 lab #5. 
*    This is the declaration of the DictionaryNode class. This class is used in the HashDictionary class. A DictioinaryNode object
*    represents a single entry in a HashDictionary hash table. It has fields for a key, an item, and also acts as a node in a linked
*    list by having a pointer to the next item and get/set functions for the next item. This allows us to successfully create a dictionary that
*    uses hashing with chaining. 
*   ONLINE REPOSITORY http://github.com/jhallard/HashDictionary
*/

#ifndef DICTIONARY_NODE_H
#define DICTIONARY_NODE_H

template <class keyType, class itemType>
class DictionaryNode
{
private:
    keyType key;  // key associated with the entry
    itemType item;// value of the entry
    DictionaryNode<keyType, itemType> * next; // pointer to the next DictionaryNode, used to deal with collisions by chaining

public:
    // creates a DictionaryNode with a key and a value
    DictionaryNode(keyType, itemType);

    // set and get the key for this node
    void setKey(keyType);
    keyType getKey();

    // set and get the value (item) for this node
    void setItem(itemType);
    itemType getItem();

    // get a pointer to the next item in the chain. Returns nullptr if there is no next pointer
    DictionaryNode<keyType, itemType> * getNext();

    //set the next pointer in the chain
    void setNext(DictionaryNode<keyType, itemType> *);

};

#include "DictionaryNode.cpp"

#endif
