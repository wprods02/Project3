#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "song.h"
#include "songs.h"
#include "hash.h"
#include "json.hpp"
using json = nlohmann::json;

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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <song> <artist>" << std::endl;
        return 1;
    }

    // Accept song and artist from command line arguments
    std::string search = argv[1];
    std::string artist = argv[2];

    // Initialize necessary data structures
    Songs songList;
    std::vector<Song> allSongs;
    std::vector<Song> songsWithTitle;
    Hash songHash;

    // Parse the song file and populate data structures
    parseFile("./Songs100k.txt", songList, allSongs);

    for (int i = 0; i < allSongs.size(); ++i) {
        songHash.AddSong(allSongs[i]);
    }

    // Find the song using the hash algorithm
    Song* searchedSong = songHash.FindSong(search, artist);
    if (searchedSong == nullptr) {
        std::cerr << "Song not found." << std::endl;
        return 1;
    }

    // Create playlist of similar songs
    std::vector<Song> similarSongs = songList.FindSimilar(*searchedSong);

    // Prepare JSON output
    json output;
    output["searchedSong"]["title"] = search;
    output["searchedSong"]["artist"] = artist;
    output["recommendations"] = json::array();

    for (const Song& song : similarSongs) {
        json songJson;
        songJson["title"] = song.name;
        songJson["artist"] = song.artists;
        // Include other song attributes if necessary
        output["recommendations"].push_back(songJson);
    }

    // Output the JSON string
    std::cout << output.dump(4) << std::endl; // The '4' here is for pretty-printing

    return 0;
}