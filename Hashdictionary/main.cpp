/*
*    @Author
*/

#include <iostream>
#include <string>
#include <fstream>
#include <exception>

#include "HashDictionary.h"
#include "DictionaryNode.h"

using namespace std;

template <class keyType, class itemType>
void visit(DictionaryNode<keyType, itemType> & name);


template <class keyType, class itemType>
bool fileToDictionary(HashDictionary<keyType, itemType> &, string filename);

template <class keyType, class itemType>
bool DictionaryToFile(std::vector<DictionaryNode<keyType, itemType>> vec, string filename);


int main()
{
    HashDictionary<int, string> dict(13);

    enum OPTIONS {QUIT, PRINT, RETRIEVE, DELETE, READ, ADD, SAVE};
    int menuop = -1;

    while(menuop != 0)
    {
        cout << "Please Choose One of the Following Options\n\n";
        cout << "1.) Print hash table\n";
        cout << "2.) Retrieve hash item\n";
        cout << "3.) Delete item\n";
        cout << "4.) Read names from file\n";
        cout << "5.) Add a name to the file\n";
        cout << "6.) Save dictionary to file\n";
        cout << "0.) Quit\n\n";

        cin >> menuop;
        int key = 0;
        int age = 0;
        string name;
        cin.ignore();
        switch(menuop)
        {
            case(PRINT):
                system("cls");
                void (*fptr)(DictionaryNode<int, string> &);
                fptr = visit;
                dict.traverse(fptr);    
                system("pause");
                system("cls");
            break;

            case(RETRIEVE):
                cout << "Please enter the key to the item you want to retrieve\n";
                cin >> key;

                if(dict.contains(key))
                {
                    string item = dict.getItem(key);
                    cout << "Item Located in Map, Key #" << key << " :: Item " << item << "\n\n";
                }
                else
                    cout << "\n\nItem not found in dictionary\n\n";
                system("pause");
                system("cls");
            break;


            case(DELETE):
                cout << "Please enter the key to the item you want to delete\n";
                cin >> key;
                if(dict.remove(key))
                {
                    cout << "\n\nItem with key #" << key << " has been removed\n\n";
                }
                else
                    cout << "\n\nItem not found in dictionary\n\n";
                system("pause");
                system("cls");
            break;


            case(READ):
                cout << "Please enter the name of the file to read from\n";
                cin >> name;
                if(fileToDictionary(dict, name))
                    cout << "\n\n File has been located\n\n";
                else
                    cout << "\n\n Could not find file\n\n";

                system("pause");
                system("cls");
            break;

            case(ADD):
                cout << "Please enter the name to add to the dictionary\n";
                getline(cin,name);
                cout << "Please enter the age that corresponds to that person\n";
                cin >> age;
                
                dict.add(age, name);

                cout << "\n\n\n  (" << name << ", " << age << ") has been added.\n\n\n";
                system("pause");
                system("cls");
            break;


            case(SAVE):
                std::vector<DictionaryNode<int, std::string>> entries = dict.toVector();
                cout << "Please enter the name of the file to save to\n";
                cin >> name;
                if(DictionaryToFile(dict.toVector(), name))
                    cout << "\n\n File Successfully Saved\n\n";
                else
                    cout << "\n\n Could not save file\n\n";

                system("pause");
                system("cls");
            break;
        }// end switch

    }// end main menu while loop
    
}


template <class keyType, class itemType>
bool fileToDictionary(HashDictionary<keyType, itemType>  &dic, string filename)
{
    ifstream infile;

    infile.open(filename);

    if(!infile)
        return false;

    std::vector<std::string> names;
    while(!infile.eof()) // To get you all the lines.
    {
        string str;
        char age[3];
        int numage = 0;
        int index = 0;
        getline(infile,str); 

        while(index < 3 && str[index] != ' ')
        {
            age[index] = str[index];
            index++;
        }

        while(str[index] == ' ')
        {
            index++;
        }

        str = str.substr(index, str.size());
        numage = atoi(age);

        dic.add(numage, str);
    }
    infile.close();
    return true;

}

template <class keyType, class itemType>
bool DictionaryToFile(std::vector<DictionaryNode<keyType, itemType>> vec, string filename)
{
     ofstream outfile;

    try
    {
        outfile.open(filename);
    }
    catch(exception e)
    {
        return false;
    }

    /*for(int i = 0; i < vec.size(); i++)
    {
        outfile << vec[i].getKey() << " " << vec[i].getItem() << "\n";
    }*/
    
}

template <class keyType, class itemType>
void visit(DictionaryNode<keyType, itemType> & name)
{
    cout << "  Age : " << name.getKey() << "    --   Name : " << name.getItem() << "\n\n";
}


