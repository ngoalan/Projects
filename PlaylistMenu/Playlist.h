#include <string>
#include <iostream>

using namespace std;

#ifndef PLAYLIST_H
#define PLAYLIST_H

class PlaylistNode{
    public:
    PlaylistNode();
    PlaylistNode(string, string, string, int);
    void InsertAfter(PlaylistNode*);
    void SetNext(PlaylistNode*);
    string GetID()const;
    string GetArtistName() const;
    string GetSongName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void PrintPlaylistNode();
    private:
    string uniqueID;
    string songName;
    string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
    };

    class Playlist{
        public: 
        Playlist(string);
        void OutputFullPlaylist();
        void OutputSongsSpecificArtist(string);
        void OutputTotalTime();
        void AddSong();
        void RemoveSong(string);
        void ChangePosition(int, int);
        private:
        string title;
        PlaylistNode* head;
        PlaylistNode* tail;
    };
    #endif