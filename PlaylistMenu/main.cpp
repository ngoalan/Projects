#include "Playlist.h"
#include <string>
#include <iostream>

using namespace std;

void PrintMenu(Playlist &, string);

int main(){
    string title;
    cout << "Enter playlist's title:" << endl;
    getline(cin, title);
    Playlist myplaylist = Playlist(title);
    cout << endl;
    PrintMenu(myplaylist, title);
}

void PrintMenu(Playlist &p, string title){
    while(1){
        char x = ' ';
        cout << title << " PLAYLIST MENU" << endl;
        cout << "a - Add song\nd - Remove song\nc - Change position of song\ns - Output songs by specific artist\nt - Output total time of playlist (in seconds)\no - Output full playlist\nq - Quit" << endl;
        while (x != 'a' && x != 'd' && x != 'c' && x != 's' && x != 't' && x != 'o' && x != 'q'){
            cout << endl << "Choose an option:" << endl;
            cin >> x;
            cin.ignore();
        }
        if (x == 'a'){
            p.AddSong();
            cout << endl;
        }
        else if(x == 'd'){
            string id;
            cout << "REMOVE SONG" << endl;
            cout << "Enter song's unique ID:" << endl;
            cin >> id;
            p.RemoveSong(id);
            cout << endl;
        }
        else if(x == 'c'){
            int oldPos = -1;
            int newPos = -1;
            cout << "CHANGE POSITION OF SONG" << endl;
            cout << "Enter song's current position:" << endl;
            cin >> oldPos;
            cout << "Enter new position for song:" << endl;
            cin >> newPos;
            p.ChangePosition(oldPos, newPos);
            cout << endl;
        }
        else if(x == 's'){
            string artist;
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
            cout << "Enter artist's name:" << endl << endl;
            getline(cin, artist);
            p.OutputSongsSpecificArtist(artist);
        }
        else if(x == 't'){
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
            p.OutputTotalTime();
            cout << endl;
        }
        else if(x == 'o'){
            p.OutputFullPlaylist();
        }
        else if(x == 'q'){
            return;
        }
    }
}