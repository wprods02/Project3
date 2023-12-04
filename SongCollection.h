#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <exception>

#include "Song.h"

class SongCollection
{
public:
	
	void importSongs(); // Read in all files from CSV

	void quickSort(string attribute, int low, int high); // Quick Sort 
	int partition(string attribute, int low, int high); // Quick Sort Partition Method
	void swap(int index1, int index2); // Swaps elements of Song Vector based on Input
	void heapifyDown(int index,string attribute, int size); // Heap Sort Heapify Down
	void heapSort(string attribute); // Heap Sort Method
	int getNumSongs(); // Funtion that get the number of songs
	void testPrint(string attribute); // Print the attributes of the Song including name and artist
};
