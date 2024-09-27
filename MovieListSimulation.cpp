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
        cout << "Default Constructor called: " << name << " created." << endl;
    }

    // Parametrized Constructor
    Movie(string name, string genre = " ", int duration = 0) {
        this->name = name;
        this->genre = genre;
        this->duration = duration;
        ++movieCount;
        cout << "Parametrized Constructor called: " << name << " created." << endl;
    }

    // Destructor
    ~Movie() {
        --movieCount;
        cout << "Destructor called: " << name << " destroyed." << endl;
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
        cout << "User Constructor called: " << name << " created." << endl;
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
        cout << "User Destructor called: " << name << " destroyed." << endl;
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
    //with default constructor
    Movie* defaultMovie = new Movie(); 

    //with parameterized constructor
    Movie* movies[] = {
        new Movie("Inception", "Sci-Fi", 148),
        new Movie("The Godfather", "Crime", 175),
        new Movie("The Dark Knight", "Action", 152)
    };


    User* user1 = new User("Vedha");
    User* user2 = new User("Alex");

    for (const auto& movie : movies) {
        user1->addToWatchList(movie);
    }

    user1->listWatchList();


    user1->addToWatched("Inception");
    user1->listWatched();

    user2->addToWatchList(new Movie("The Dark Knight", "Action", 152));
    user2->listWatchList();

    // Calling Static Functions
    cout << "_______________________________________________________" << endl;
    cout << "Total Number Of Movies: " << Movie::getMovieCount() << endl;
    cout << "Total Number Of Users: " << User::getUserCount() << endl;

    delete defaultMovie;
    delete user1; 
    delete user2; 

    return 0;
}

