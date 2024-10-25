#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie {
private:
    string name;
    string genre;
    int duration;
    static int movieCount;

public:
    // Default Constructor
    Movie() {
        name = "Unknown";
        genre = "Unknown";
        duration = 0;
        cout << "---Default Constructor called: " << name << " created.---" << endl;
    }

    // Parametrized Constructor
    Movie(string name, string genre = "Unknown", int duration = 0) {
        this->name = name;
        this->genre = genre;
        this->duration = duration;
        ++movieCount;
        cout << "---Parametrized Constructor called: " << name << " created.---" << endl;
    }

    // Destructor
    ~Movie() {
        --movieCount;
        cout << "---Destructor called: " << name << " destroyed.---" << endl;
    }

    // Accessor (getter) methods
    string getName() const {
        return this->name;
    }

    string getGenre() const {
        return this->genre;
    }

    int getDuration() const {
        return this->duration;
    }

    // Static Function
    static int getMovieCount() {
        return movieCount;
    }
};

int Movie::movieCount = 0;

// Single Inheritance
class RomComMovie : public Movie {
private:
    bool feelGood;

public:
    RomComMovie(string name, int duration, bool feelGood = true)
        : Movie(name, "Romantic Comedy", duration), feelGood(feelGood) {}

    bool getFeelGood() const { return feelGood; }

    void display() const {
        cout << "RomCom Movie - Name: " << getName()
             << ", Duration: " << getDuration()
             << " mins, Feel Good: " << (feelGood ? "Yes" : "No") << endl;
    }
};

class User {
private:
    string name;
    vector<Movie*> watchlist;
    vector<Movie*> watched;
    static int userCount;

public:
    // Constructor
    User(string name) {
        this->name = name;
        ++userCount;
        cout << "User Constructor called: " << name << " created." << endl;
    }

    // Destructor
    ~User() {
        // Clean up movies in the watchlist and watched lists
        for (auto movie : watchlist) {
            delete movie; // Deleting movies in the watchlist
        }
        for (auto movie : watched) {
            delete movie; // Deleting watched movies
        }
        --userCount;
        cout << "User Destructor called: " << name << " destroyed." << endl;
    }

    // Accessor (getter) methods
    string getName() const {
        return this->name;
    }

    // Mutator (setter) methods
    void setName(const string& name) {
        this->name = name;
    }

    User& addToWatchList(Movie* movie) {
        this->watchlist.push_back(movie);
        return *this;
    }

    void addToWatched(const string& movieName) {
        for (auto i = this->watchlist.begin(); i != watchlist.end(); ++i) {
            if ((*i)->getName() == movieName) {
                this->watched.push_back(*i);
                this->watchlist.erase(i);
                return;
            }
        }
        cout << "Movie not found in watchlist." << endl;
    }

    void listMovies(const vector<Movie*>& movies) const {
        for (const auto& movie : movies) {
            cout << "Name: " << movie->getName() << ", Genre: " << movie->getGenre() << ", Duration: " << movie->getDuration() << " mins" << endl;
        }
    }

    void listWatchList() const {
        cout << "--------------------" << endl;
        cout << "Movies in watchlist:" << endl;
        cout << "--------------------" << endl;
        this->listMovies(this->watchlist);
    }

    void listWatched() const {
        cout << "--------------------" << endl;
        cout << "Movies in Watched:" << endl;
        cout << "--------------------" << endl;
        this->listMovies(this->watched);
    }

    // Static Function
    static int getUserCount() {
        return userCount;
    }
};

int User::userCount = 0;

class AdminUser : public User {
public:
    AdminUser(string name) : User(name) {}

    void manageUsers() const {
        cout << "Admin " << getName() << " is managing users." << endl;
    }
};

class RegularUser : public User {
public:
    RegularUser(string name) : User(name) {}

    void giveFeedback() const {
        cout << "Regular user " << getName() << " is giving feedback." << endl;
    }
};

int main() {
    Movie* movie1 = new Movie("Inception", "Sci-Fi", 148);
    Movie* movie2 = new Movie("The Godfather", "Crime", 175);

    cout << "--- Demonstrating RomComMovie ---" << endl;
    RomComMovie* romCom = new RomComMovie("Crazy Rich Asians", 121);
    romCom->display();

    cout << "--- Creating Users ---" << endl;
    AdminUser* admin = new AdminUser("Vedha");
    RegularUser* user1 = new RegularUser("Alex");

    cout << "--- Regular User Activities ---" << endl;
    user1->addToWatchList(movie1);
    user1->addToWatchList(movie2);
    user1->listWatchList();

    cout << "--- Admin User Activities ---" << endl;
    admin->manageUsers();

    cout << "--- Watching a Movie ---" << endl;
    user1->addToWatched("Inception");
    user1->listWatched();

    delete user1; 
    delete admin; 
    delete romCom; 

    return 0;
}
