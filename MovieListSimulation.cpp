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
    // Constructor
    Movie(string name, string genre = " ", int duration = 0) {
        this->name = name;
        this->genre = genre;
        this->duration = duration;
        ++movieCount;
    }

    // Destructor
    ~Movie() {
        --movieCount;
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

    // Mutator (setter) methods
    void setName(const string& name) {
        this->name = name;
    }

    void setGenre(const string& genre) {
        this->genre = genre;
    }

    void setDuration(int duration) {
        this->duration = duration;
    }

    // Static Function
    static int getMovieCount() {
        return movieCount;
    }
};

int Movie::movieCount = 0;

class User {
private:
    string name;
    vector<Movie*> watchlist;
    vector<Movie*> watched;
    vector<Movie*> favorites;
    static int userCount;

public:
    // Constructor
    User(string name) {
        this->name = name;
        ++userCount;
    }

    // Destructor
    ~User() {
        for (Movie* movie : watchlist) {
            delete movie;
        }
        for (Movie* movie : watched) {
            delete movie;
        }
        for (Movie* movie : favorites) {
            delete movie;
        }
        --userCount;
    }

    // Accessor (getter) methods
    string getName() const {
        return this->name;
    }

    vector<Movie*> getWatchList() const {
        return this->watchlist;
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

int main() {
    Movie* movies[] = {
        new Movie("Inception"),
        new Movie("The Godfather", "Crime", 175),
        new Movie("The Dark Knight", "Action", 152)
    };

    User* user = new User("Vedha");

    for (const auto& movie : movies) {
        user->addToWatchList(movie);
    }

    user->listWatchList();
    user->addToWatched("Inception");
    user->listWatched();
    user->listWatchList();

    // Calling Static Functions
    cout << "_______________________________________________________" << endl;
    cout << "Total Number Of Movies: " << Movie::getMovieCount() << endl;
    cout << "Total Number Of Users: " << User::getUserCount() << endl;

    delete user; // This deletes the user and also deletes all movies in their lists


    return 0;
}
