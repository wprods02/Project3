#include "SongCollection.h"

using namespace std;

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

// Test if worked
void SongCollection::testPrint(string attribute)
{
	for (unsigned int x = 0; x < songs.size(); x++)
	{
		cout << x << " " << songs.at(x).getName() <<" | "<< songs[x].getAttribute("tempo")<< endl;
	}

}
