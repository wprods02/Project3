#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <stdlib.h>
#include "song.h"

using namespace std;

class Songs {
private:
    vector<Song> songList;

public:
    void AddSong(Song&);
    vector<Song> FindSimilar(const Song& searchSong);
    void printSongs();

};

void Songs::AddSong(Song& newSong) {
    songList.push_back(newSong);
}

vector<Song> Songs::FindSimilar(const Song& searchSong) {

    vector<Song> results;

    string searchName = searchSong.name;

    vector<pair<double, Song>> rankings;
    double distance = 0;

    for(int i = 0; i < songList.size(); i++)
    {
        pair <double, Song> temp;
        double distance = 0;

        // Calculate the squares of the danceability differences
        double danceability_difference = songList[i].danceability - searchSong.danceability;
        distance += (2 * danceability_difference*danceability_difference);

        // Calculate the squares of the energy differences
        double energy_difference = songList[i].energy - searchSong.energy;
        distance += ( 2 * (energy_difference*energy_difference));

        // Calculate the squares of the speechiness differences
        double speechiness_difference = songList[i].speechiness - searchSong.speechiness;
        distance += (speechiness_difference*speechiness_difference);

        // Calculate the squares of the acousticness differences
        double acousticness_difference = songList[i].acousticness - searchSong.acousticness;
        distance += (acousticness_difference*acousticness_difference);

        // Calculate the squares of the instrumentalness differences
        double instrumentalness_difference = songList[i].instrumentalness - searchSong.instrumentalness;
        distance += (instrumentalness_difference*instrumentalness_difference);

        // Calculate the squares of the liveliness differences
        double liveliness_difference = songList[i].liveliness - searchSong.liveliness;
        distance += (liveliness_difference * liveliness_difference);

        // Calculate the squares of the valence differences
        double valence_difference = songList[i].valence - searchSong.valence;
        distance += (4 * (valence_difference * valence_difference));

        // Calculate the squares of the tempo differences
        double tempo_difference = songList[i].tempo - searchSong.tempo;
        distance += ((0.0001) * (tempo_difference * tempo_difference));

        temp.first = distance;
        temp.second = songList[i];
        rankings.push_back(temp);
    }

    std::sort(rankings.begin(), rankings.end(),
              [](const auto& lhs, const auto& rhs) {
                  return lhs.first < rhs.first;
              });

    for (int i = 0; i < 10; ++i)
        results.push_back(rankings[i].second);

    return results;
}