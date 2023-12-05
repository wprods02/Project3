#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "song.h"
#include "songs.h"
#include "hash.h"

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
    vector<Song> songsWithTitle;
    Hash songHash;

    //ADDING SONGS TO HASHMAP & Vector
    parseFile("./Songs100k.txt", songList, allSongs);

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < allSongs.size(); ++i) {
        songHash.AddSong(allSongs[i]);
    }
    auto stop = std::chrono::steady_clock::now();
    std::chrono::duration<double>  duration = stop - start;
    start = std::chrono::steady_clock::now();
    stop = std::chrono::steady_clock::now();
    duration = stop - start;


    /*Inputting Song to Search*/
    cout << "What song are you searching for?: ";

    getline(cin, search);
    cout << "Who is the artist?:  ";

    getline(cin, artist);

    /*Searching For Inputted Song In Data Structures*/
    Song* searchedSong;
    cout << "-------------------------------------------\n";

   //FINDING SONG WITH HASH ALGORITHM
    start = std::chrono::steady_clock::now();
    songHash.FindSong(search, artist);
    stop = std::chrono::steady_clock::now();
    duration = stop - start;
    cout << "Time taken to find song in hash map: " << to_string(duration.count()) << " ms\n";

    //FINDING SONG WITH QUADRATIC ALGORITHM
    start = std::chrono::steady_clock::now();
    for (int i = 0; i < allSongs.size(); ++i) {
        if (allSongs[i].name == search){
            songsWithTitle.push_back(allSongs[i]);
        }
        for (int j = 0; j < songsWithTitle.size(); ++j) {
            if (songsWithTitle[j].artists == artist){
                searchedSong = &songsWithTitle[j];
            }
        }
    }
    stop = std::chrono::steady_clock::now();
    duration = stop - start;
    cout << "Time taken to find song with O(n^2) algorithm: " << to_string(duration.count()) << " ms\n";

    /*CREATING PLAYLIST OF SIMILAR SONGS*/
    vector<Song> temp = songList.FindSimilar(*searchedSong);

    cout << "Playlist for: " << temp[0].name << " by: " << temp[0].artists << endl;
    cout << "-------------------------------------------\n";

    for (int i = 1; i < temp.size(); ++i) {
        playlistString += temp[i].name + " by: " + temp[i].artists+ "\n";
    }
    cout << playlistString << endl;

    return 0;
}

