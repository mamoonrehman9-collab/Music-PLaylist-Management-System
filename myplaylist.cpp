#include <iostream>
#include <string>
using namespace std;

// --------------------- BASE CLASS ---------------------
class Song {
public:
    string title;
    string singer;
    string genre;
    bool liked;

    Song() { liked = false; }
    Song(string t, string s, string g) {
        title = t;
        singer = s;
        genre = g;
        liked = false;
    }

    virtual void display() {
        cout << title << " | " << singer << " | " << genre;
        if (liked) cout << " ❤";
        cout << endl;
    }
};

// --------------------- DERIVED CLASSES ---------------------
class SadSong : public Song {
public:
    SadSong(string t, string s) : Song(t, s, "Sad") {}
    void display() override {
        cout << "😢 " << title << " - " << singer;
        if (liked) cout << " ❤";
        cout << endl;
    }
};

class PartySong : public Song {
public:
    PartySong(string t, string s) : Song(t, s, "Party") {}
    void display() override {
        cout << "🎉 " << title << " - " << singer;
        if (liked) cout << " ❤";
        cout << endl;
    }
};

class RelaxSong : public Song {
public:
    RelaxSong(string t, string s) : Song(t, s, "Relaxation") {}
    void display() override {
        cout << "🌿 " << title << " - " << singer;
        if (liked) cout << " ❤";
        cout << endl;
    }
};

// --------------------- PLAYLIST CLASS ---------------------
class Playlist {
public:
    Song* songs[20];//each element has pointer of song object
    int count;
    int current;

    int backStack[20]; //store history of previous songs
    int backTop; // stack pointer

    Playlist() {
        count = 0; // no song in starting of playlist
        current = 0;//ready for first song
        backTop = -1;//previous history empty
    }

    void addSong(Song* s) {
        if (count < 20)
            songs[count++] = s;
    }

    void showAll() {
        cout << "\n🎵 ---- ALL SONGS ---- 🎵\n";
        for (int i = 0; i < count; i++)
            songs[i]->display();
    }

    void showGenre(string g) {
        cout << "\n📀 ---- GENRE: " << g << " ----\n";
        for (int i = 0; i < count; i++)
            if (songs[i]->genre == g)
                songs[i]->display();
    }

    void showSinger(string s) {
        cout << "\n🎤 ---- SINGER: " << s << " ----\n";
        for (int i = 0; i < count; i++)
            if (songs[i]->singer == s)
                songs[i]->display();
    }

    void searchSong(string keyword) {
        cout << "\n🔍 ---- SEARCH: " << keyword << " ----\n";
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (songs[i]->title.find(keyword) != string::npos) {
                songs[i]->display();
                found = true;
            }
        }
        if (!found) cout << "❌ No songs found.\n";
    }

    void playCurrent() {
        if (count == 0) { 
            cout << "Playlist empty.\n"; 
            return; 
        }
        cout << "\n▶ Playing: ";
        songs[current]->display();
    }

    void nextSong() {
        if (count == 0) { cout << "Playlist empty.\n"; return; }
        if (backTop < 19) backStack[++backTop] = current; // push current to back
        current = (current + 1) % count;
        playCurrent();
    }

    void previousSong() {
        if (backTop < 0) {
            cout << "⛔ No previous song.\n";
            return;
        }
        current = backStack[backTop--]; // pop back
        playCurrent();
    }

    void shuffle() {
        if (count == 0) { cout << "Playlist empty.\n"; return; }
        if (backTop < 19) backStack[++backTop] = current;
        current = (current + 3) % count;  // simple deterministic shuffle
        cout << "🔀 Shuffle!\n";
        playCurrent();
    }

    void likeCurrent() {
        if (count == 0) { cout << "Playlist empty.\n"; return; }
        songs[current]->liked = true;
        cout << "❤ Liked: " << songs[current]->title << endl;
    }

    void dislikeCurrent() {
        if (count == 0) { cout << "Playlist empty.\n"; return; }
        songs[current]->liked = false;
        cout << "💔 Disliked: " << songs[current]->title << endl;
    }
};

// --------------------- MAIN ---------------------
int main() {
    Playlist p;

    // ---- Atif Aslam songs ----
    p.addSong(new SadSong("Tera Hone Laga Hoon", "Atif Aslam"));
    p.addSong(new RelaxSong("Jeena Jeena", "Atif Aslam"));
    p.addSong(new PartySong("Doorie Dance Mix", "Atif Aslam"));
    p.addSong(new SadSong("Tu Jaane Na", "Atif Aslam"));
    p.addSong(new RelaxSong("Rafta Rafta", "Atif Aslam"));
    p.addSong(new PartySong("Baarishein Remix", "Atif Aslam"));

    // ---- Hasan Raheem songs ----
    p.addSong(new SadSong("Aisay Kaisay", "Hasan Raheem"));
    p.addSong(new PartySong("Joona", "Hasan Raheem"));
    p.addSong(new RelaxSong("Aunty Disco", "Hasan Raheem"));
    p.addSong(new SadSong("Peechay Hutt", "Hasan Raheem"));
    p.addSong(new RelaxSong("Paisa", "Hasan Raheem"));

    // ---- Young Stunners songs ----
    p.addSong(new SadSong("Gumaan", "Young Stunners"));
    p.addSong(new SadSong("Afsanay", "Young Stunners"));
    p.addSong(new PartySong("Kaun Talha", "Young Stunners"));
    p.addSong(new PartySong("Don't Mind", "Young Stunners"));

    // ---- Rahat Fateh Ali Khan songs ----
    p.addSong(new SadSong("Afreen Afreen", "Rahat Fateh Ali Khan"));
    p.addSong(new SadSong("Teri Ore", "Rahat Fateh Ali Khan"));
    p.addSong(new RelaxSong("Saiyaan", "Rahat Fateh Ali Khan"));
    p.addSong(new PartySong("Mast Qalandar", "Rahat Fateh Ali Khan"));
    p.addSong(new SadSong("Dil Diyan Gallan", "Rahat Fateh Ali Khan"));

    int choice;
    string input;

    while (true) {
        cout << "\n====== 🎧 MUSIC PLAYLIST 🎧 ======\n";
        cout << "1. 🎵 View All Songs\n";
        cout << "2. 📀 View by Genre\n";
        cout << "3. 🎤 View by Singer\n";
        cout << "4. 🔍 Search by Song Title\n";
        cout << "5. ▶ Play Current Song\n";
        cout << "6. ⏭ Next Song\n";
        cout << "7. ⏮ Previous Song\n";
        cout << "8. 🔀 Shuffle\n";
        cout << "9. ❤ Like Current Song\n";
        cout << "10. 💔 Dislike Current Song\n";
        cout << "11. ❎ Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: p.showAll(); break;
            case 2:
                cout << "Enter genre: ";
                cin.ignore();
                getline(cin, input);
                p.showGenre(input);
                break;
            case 3:
                cout << "Enter singer: ";
                cin.ignore();
                getline(cin, input);
                p.showSinger(input);
                break;
            case 4:
                cout << "Enter keyword: ";
                cin.ignore();
                getline(cin, input);
                p.searchSong(input);
                break;
            case 5: p.playCurrent(); break;
            case 6: p.nextSong(); break;
            case 7: p.previousSong(); break;
            case 8: p.shuffle(); break;
            case 9: p.likeCurrent(); break;
            case 10: p.dislikeCurrent(); break;
            case 11: cout << "👋 Exiting playlist...\n"; return 0;
            default: cout << "❌ Invalid option.\n";
        }
    }
}
