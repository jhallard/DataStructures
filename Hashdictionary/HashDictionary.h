#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H
/*  
*    @Author John H Allard. Written for CSIS 212 Advanced Data Structures at GCC, May 27th, 2014.
*    HashDictionary.h - Declaration of the HashDictionary class. This class represents a dictionary that uses hashing with chaining to store the items.
*    The dictionary size is defined as a constant below, which is because of a bug that I could not resolve involving the compiler rejecting a one arg constructor
*    which would have been the size of the dictionary that the user wants. 
*    ONLINE REPOSITORY -     http://github.com/jhallard/HashDictionary
*/
#include "DictionaryNode.h"
#include <vector>
#include <iostream>
#include <functional> // used for std::hash function

template <class keyType, class itemType> 
class HashDictionary
{
private:
    int dictionarySize; // max size of the dictionary slots, you can have more elements than this but they will nessearily have to be chained
    
    DictionaryNode<keyType, itemType> ** dictionary;               // our dictionary, an array of pointers to dictionary nodes. The array slots are the
                                                                   // slots of our dictionary, and the pointers will point to the next item in the list if
                                                                   // there is a collision between entries

    int numberOfEntries;    // current number of entries in our dictionary
    int hashEntry(keyType); // Hash utility function, takes a key and maps it via std::hash<int> to an index between {0, dictionarySize}

public:

    // constructor, takes one argument that determines the number of slots of the dictionary
     HashDictionary(int); 

     // Destructor, must delete the dynamically allocated hash map memory.
     ~HashDictionary();
    // returns true if the dictionary has no entries
    bool isEmpty();

    // simply a get for the numberOfEntries field
    int getNumberOfItems();

    // simply a get for the dictionarySize field
    int getDictionarySize();  

    // add an item to the dictionary by specifying the key and item, uses the hashEntry() utility function
    bool add(keyType, itemType); 

    // removes an item from the dictionary, returns true if it can find and remove the item, false otherwise.
    bool remove(keyType);       

    // query the dictionary for an item by key
    bool contains(keyType);        

    // THROWS logic_error if key doesn't exist. Gets the item for the item with the given key.
    itemType getItem(keyType);    

    // Kind of like a print function for now. You pass it a function that takes a node and does something with
    // that node. The example function in @function void visit(DictionaryNode &) in @file main.cpp takes the node passed to
    // it and prints out the key and item of that entry.
    // The function will traverse the dictionary in ascending order for its slots, and if a slot has multiple entries chained
    // together it will traverse the chain in order from front to back. 
    // TODO : Instead of having the function just print out the entries of the map, have the entries inserted into an array or vector 
    // and returned to the user for them to decide what to do with the information (don't hardcode the print statements into the class,
    // just give the user the data and let them choose how to format the print statements)
    void traverse(void visit(DictionaryNode<keyType, itemType>&));


    //returns a vector of the entries of the dictionary in order based on their key. If the keys map the the same index through std::Hash, then they will be 
    // in relative order of how they were inserted.
    std::vector<DictionaryNode<keyType, itemType>> toVector();


};

#include "HashDictionary.cpp"

#endif