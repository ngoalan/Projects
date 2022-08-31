#include <string>
#include <iostream>
#include "Playlist.h"

using namespace std;

PlaylistNode::PlaylistNode(){
    uniqueID = "none";
    songName = "none";
    artistName = "none";
    songLength = 0;
    nextNodePtr = nullptr;
}

PlaylistNode::PlaylistNode(string id, string sn, string artist, int sl){
    uniqueID = id;
    songName = sn;
    artistName = artist;
    songLength = sl;
    nextNodePtr = nullptr;
}

void PlaylistNode::InsertAfter(PlaylistNode * n){
    n->SetNext(nextNodePtr);
    nextNodePtr = n;
}

string PlaylistNode::GetID() const{
    return uniqueID;
}

void PlaylistNode::SetNext(PlaylistNode* next){
    nextNodePtr = next;
}

string PlaylistNode::GetArtistName() const{
    return artistName;
}

int PlaylistNode::GetSongLength() const{
    return songLength;
}

string PlaylistNode::GetSongName() const{
    return songName;
}

PlaylistNode * PlaylistNode::GetNext() const{
    return nextNodePtr;
}

Playlist::Playlist(string title){
    this->title = title;
    head = nullptr;
    tail = head;
}

void PlaylistNode::PrintPlaylistNode(){
    cout << "Unique ID: " << uniqueID << endl
         << "Song Name: " << songName << endl
         << "Artist Name: " << artistName << endl
         << "Song Length (in seconds): " << songLength << endl;
}

void Playlist::OutputFullPlaylist() {
    if (head == nullptr){
        cout << title << " - OUTPUT FULL PLAYLIST" << endl;
        cout << "Playlist is empty" << endl;
        cout << endl;
    }
    else {
        unsigned counter = 1;
        cout << title << " - OUTPUT FULL PLAYLIST" << endl;
        for (PlaylistNode* i = head; i != nullptr; i = i->GetNext()){
            cout << counter << "." << endl;
            i->PrintPlaylistNode();
            cout << endl;
            counter++;
        }
    }
}

void Playlist::AddSong(){
    string id;
    string sn;
    string an;
    int sl = 0;
    cout << "ADD SONG" << endl << "Enter song's unique ID:" << endl;
    cin >> id;
    cin.ignore();
    cout << "Enter song's name:" << endl;
    getline(cin, sn);
    cout << "Enter artist's name:" << endl;
    getline(cin, an);
    cout << "Enter song's length (in seconds):" << endl;
    cin >> sl;
    PlaylistNode* temp = new PlaylistNode(id, sn, an, sl);
    if (head == nullptr){
        tail = temp;
        head = tail;
    }
    else{
        tail->InsertAfter(temp);
        tail = temp;
    }
}

void Playlist::RemoveSong(string id){
    if(head == nullptr){
        return;
    }
    PlaylistNode* prev = head;
    for (PlaylistNode* i = head; i != nullptr; i = i->GetNext()){
        if (i->GetID() == id){
            if(i == head && i == tail){
                cout << '"' << i->GetSongName() << '"' << " removed." << endl;
                delete i;
                head = nullptr;
                tail = head;
            }
            else if (i == head){
                head = i->GetNext();
                cout << '"' << i->GetSongName() << '"' << " removed." << endl;
                delete i;
            }
            else if(i == tail){
                prev->SetNext(i->GetNext());
                i->SetNext(nullptr);
                cout << '"' << i->GetSongName() << '"' << " removed." << endl;
                delete i;
                tail = prev;
            }
            else{
                prev->SetNext(i->GetNext());
                i->SetNext(nullptr);
                cout << '"' << i->GetSongName() << '"' << " removed." << endl;
                delete i;
                }
            return;
        }
        prev = i;
    }  
}

void Playlist::OutputSongsSpecificArtist(string a){
    if (head != nullptr){
        unsigned counter = 1;
        for (PlaylistNode* i = head; i != nullptr; i = i->GetNext()){
            if (i->GetArtistName() == a){
                cout << counter << "." << endl;
                i->PrintPlaylistNode();
                cout << endl;
            }
            counter++;
        }
    }
}

void Playlist::OutputTotalTime(){
    unsigned total = 0;
    for (PlaylistNode* i = head; i != nullptr; i = i->GetNext()){
        total += i->GetSongLength();
    }
    cout << "Total time: " << total << " seconds" << endl; 
}

void Playlist::ChangePosition(int oldPos, int newPos){
    string sn;
    if (head == nullptr){
        return;
    }
    PlaylistNode* prev = nullptr;
    PlaylistNode* curr = head;
    for (int i = 1; i < oldPos && curr != nullptr; ++i){
        prev = curr;
        curr = curr->GetNext();
    }
    if (curr != nullptr){
        if (prev == nullptr){
            head = curr->GetNext();
        }
        else {
            prev->SetNext(curr->GetNext());
        }
        if (curr == tail){
            tail = prev;
        }
        PlaylistNode* pn = nullptr;
        PlaylistNode* n = head;
        for (int i = 1; i < newPos && n != nullptr; ++i){
            pn = n;
            n = n->GetNext();
        }
        if (pn == nullptr){
            curr->SetNext(head);
            head = curr;
        }
        else {
            pn->InsertAfter(curr);
        }
        if (n == nullptr){
            tail = curr;
        }
        sn = curr->GetSongName();
        cout << '"' << sn << '"' << " moved to position " << newPos << endl;
    }
    else{
        cout << "invalid" << endl;
        return;
    }
}
