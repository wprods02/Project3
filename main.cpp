#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "song.h"
#include "songs.h"

using namespace std;

void parseFile(const std::string& filename, Songs &songList, vector<Song>& allSongs){
    //create an input filestream
    std::fstream file;

    file.open(filename, std::ios::in);

    //temp variable to hold the line
    std::string line;

    //check if file is open
    if (file.is_open()) {
        //get header line
        std::getline(file, line);

        //loop through the file
        while (std::getline(file,line)) {
            //vector to hold each song value
            std::vector<std::string> songInfo;

            //create stringstream
            std::stringstream temp(line);

            //variable to hold each value
            std::string value;

            //add each value to vector
            while (getline(temp, value, '|')) {
                songInfo.push_back(value);
            }

            // Remove the first two characters
            songInfo[4] = songInfo[4].substr(2);

            // Remove the last two characters
            songInfo[4] = songInfo[4].substr(0, songInfo[4].size() - 2);


            // Create a new song object for the B tree
            Song newSong(  /*Name*/ songInfo[1],
                    /*Artists*/ songInfo[4],
                    /*Album*/ songInfo[2],
                    /*Danceability*/ stod(songInfo[9]),
                    /*Energy*/ stod(songInfo[10]),
                    /*Speechiness*/ stod(songInfo[14]),
                    /*Acousticness*/ stod(songInfo[15]),
                    /*Instrumentalness*/ stod(songInfo[16]),
                    /*Liveliness*/ stod(songInfo[17]),
                    /*Valence*/ stod(songInfo[18]),
                    /*Tempo*/ stod(songInfo[19]));


            // Add song object to vector of songs
            allSongs.push_back(newSong);
            //add song to songList
            songList.AddSong(newSong);
        }
    }
    else {
        //throw error if file was not opened
        std::cout << "ERROR: FILE NOT OPENED" << std::endl;
        return;
    }
}

int main() {
    string search = "";
    string artist = "";
    string playlistString = "";
    Songs songList;
    vector<Song> allSongs;

    parseFile("./Songs100k.txt", songList, allSongs);


    cout << "What song are you searching for?:  ";

    getline(cin, search);
    cout << "Who is the artist?:  ";

    getline(cin, artist);

    //1) SEARCHING FOR SONG
    Song* searchedSong;
    cout << "Finding songs similar to: " + search + "...\n";

    // THIS PART MUST BE REPLACED BY SEARCHING DATA STRUCTURES
    for (int i = 0; i < allSongs.size(); ++i) {
        if (allSongs[i].name == search && allSongs[i].artists == artist){
            searchedSong = &allSongs[i];
            break;
        }
    }
    // Heap Sort 
    // auto start1 = high_resolution_clock::now();
	// songs.heapSort("Difference");
	// auto stop1 = high_resolution_clock::now();
	// auto dur1 = duration_cast<milliseconds>(stop1 - start1);
	// cout << "The HeapSort took: " << dur1.count() << " milliseconds" << endl; 
    
    // *******************************************************


    cout << "Found " << searchedSong->name << " by " << searchedSong->artists << "." << endl;

    //2) CREATING PLAYLIST OF SIMILAR SONGS
    vector<Song> temp = songList.FindSimilar(*searchedSong);

    for (int i = 0; i < temp.size(); ++i) {
        playlistString += temp[i].name + " by: " + temp[i].artists+ "\n";
    }

    cout << playlistString << endl;

    return 0;
}

