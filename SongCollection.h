#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>

#include "Song.h"

class SongCollection
{
public:
	
	void heapifyDown(int index,string attribute, int size); // Heap Sort Heapify Down
	void heapSort(string attribute); // Heap Sort Method
	void testPrint(string attribute); // Print the attributes of the Song including name and artist
};
