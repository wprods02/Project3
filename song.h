#pragma once

#include <string>
using namespace std;

struct Song
{
    string name;
    string artists;
    string album;
    Song* next = nullptr;

    // Metrics for determining song closeness
    double danceability;
    double energy;
    double speechiness;
    double acousticness;
    double instrumentalness;
    double liveliness;
    double valence;
    double tempo;

    Song() : name("") {};

    Song(string _name, string _artist, string _album, double _danceability, double _energy,
         double _speechiness, double _acousticness, double _instrumentalness, double _liveliness, double _valence, double _tempo){
        name = _name;
        artists = _artist;
        album = _album;
        danceability = _danceability;
        energy = _energy;
        speechiness = _speechiness;
        acousticness = _acousticness;
        instrumentalness = _instrumentalness;
        liveliness = _liveliness;
        valence = _valence;
        tempo = _tempo;
    };
};