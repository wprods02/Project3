#include <iostream>
#include <cstdlib>
#include <vector>
#include "song.h"

using namespace std;



class Hash {
private:

    struct songStruct {
        Song song;
        songStruct* next;
        songStruct* prev;
    };

    static const int tableSize = 100;
    songStruct* hashMap[tableSize];

public:
    Hash();
    int hash(string key);
    void AddSong(Song newSong);
    int NumberOfItemsInIndex(int index);
    void PrintTable();
    void PrintItemsInIndex(int index);
    Song* FindSong(string name, string artist);
    void RemoveItem(string title);
    int count = 0;
};

Hash::Hash(){
    for (int i = 0; i < tableSize; ++i) {
        hashMap[i] = new songStruct;
        hashMap[i]->next = nullptr;
        hashMap[i]->prev = nullptr;
    }

}

void Hash::AddSong(Song newSong) {

    int index = hash(newSong.name);


    if (hashMap[index]->song.name.empty())
    {
        hashMap[index]->song = newSong;
    }
    else
    {
        songStruct* Ptr = hashMap[index];
        songStruct* n = new songStruct;
        n->song = newSong;
        n->next = nullptr;

        while(Ptr->next != nullptr)
        {
            Ptr = Ptr->next;
        }
        Ptr->next = n;
    }
}

int Hash::hash(string key) {

    int hash = 0;
    int index;

    for (int i = 0; i < key.length(); i++) {
        hash = hash + (int) key[i];
    }

    index = hash % tableSize;

    if (index < 0) { index*=-1;}
    return index;
}


Song* Hash::FindSong(string name, string artist) {
    int index = hash(name);
    songStruct* Ptr = hashMap[index];
    while (Ptr != nullptr) {
        if (Ptr->song.name == name && Ptr->song.artists == artist) {
            return &(Ptr->song); // Return the address of the found song
        }
        Ptr = Ptr->next;
    }
    return nullptr; // Return nullptr if not found
}
