#include "SongCollection.h"

using namespace std;

// Quick Sort
void SongCollection::quickSort(string attribute, int low, int high)
{

	if (low < high) 
	{
		int piv = partition(attribute, low, high);

		quickSort(attribute, low, piv - 1);
		quickSort(attribute, piv + 1, high);
	}
}

// Partition under Quick Sort
int SongCollection::partition(string attribute, int low, int high)
{

	int up = low;
	int down = high;

	auto pivot = recommended2[low].getAttribute(attribute);
	while (down > up) {
		for (int i = high; i > low; i--) {
			if (recommended2[down].getAttribute(attribute) < pivot)
				break;
			down--;
		}
		for (int i = up; i < high; i++) {
			if (recommended2[up].getAttribute(attribute) > pivot)
				break;
			up++;
		}

		if (down > up)
			swap(up, down);
	}
		
	swap(low, down);
	return down;
	
}

// Swap index with user input
void SongCollection::swap(int index1, int index2)
{

	auto temp = recommended2[index1];
	recommended2[index1] = recommended2[index2];
	recommended2[index2] = temp;
}

// Heapify Down
void SongCollection::heapifyDown(int index, string attribute, int size)
{
		int leftIndex = (2 * index) + 1;
		int rightIndex = (2 * index) + 2;
		int greatestIndex = index;
				
		if (leftIndex < size && recommended1.at(leftIndex).getAttribute(attribute) > recommended1.at(greatestIndex).getAttribute(attribute))
		{
			greatestIndex = leftIndex;
		}

		if (rightIndex < size && recommended1.at(rightIndex).getAttribute(attribute) > recommended1.at(greatestIndex).getAttribute(attribute))
		{
			greatestIndex = rightIndex;
		}

		if (greatestIndex != index)
		{
			Song temp = recommended1.at(index);
			recommended1.at(index) = recommended1.at(greatestIndex);
			recommended1.at(greatestIndex) = temp;
			heapifyDown(greatestIndex,attribute,size);
		}
	
}

// Heap Sort
void SongCollection::heapSort(string attribute)
{
	for (int i = recommended1.size() / 2; i > 0; i--)
	{
		heapifyDown(i - 1, attribute, recommended1.size());
	}

	int endIndex = recommended1.size() - 1;
	for (endIndex; endIndex > 0; endIndex--)
	{
		Song temp = recommended1.at(0);
		recommended1.at(0) = recommended1.at(endIndex);
		recommended1.at(endIndex) = temp;

		heapifyDown(0, attribute, endIndex);
	}

}

int SongCollection::getNumSongs()
{
	return numSongs;
}

// Test if worked
void SongCollection::testPrint(string attribute)
{
	for (unsigned int x = 0; x < songs.size(); x++)
	{
		cout << x << " " << songs.at(x).getName() <<" | "<< songs[x].getAttribute("tempo")<< endl;
	}

}