#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Manages Movie Only
class Movie {
private:
    string name;
    string genre;
    int duration;
    static int movieCount;

public:
    Movie(string name, string genre = "Unknown", int duration = 0) {
        this->name = name;
        this->genre = genre;
        this->duration = duration;
        ++movieCount;
    }

    ~Movie() {
        --movieCount;
    }

    string getName() const {
         return this->name; 
         }
    string getGenre() const {
         return this->genre; 
         }
    int getDuration() const {
         return this->duration; 
         }

    static int getMovieCount() {
         return movieCount; 
         }
};

int Movie::movieCount = 0;


//Displaying the Movie
class MovieDisplay {
public:
    static void displayShort(const Movie& movie) {
        cout << movie.getName() << " (" << movie.getGenre() << ")" << endl;
    }

    static void displayDetailed(const Movie& movie) {
        cout << "Name: " << movie.getName()
             << ", Genre: " << movie.getGenre()
             << ", Duration: " << movie.getDuration() << " mins" << endl;
    }
};


//Manages the watchlist and watchedlist
class User {
private:
    string name;
    vector<Movie*> watchlist;
    vector<Movie*> watched;

public:
    User(string name) : name(name) {}

    string getName() const {
         return this->name; 
         }

    void addToWatchlist(Movie* movie) {
         this->watchlist.push_back(movie); 
         }

    void moveToWatched(const string& movieName) {
        for (auto it = watchlist.begin(); it != watchlist.end(); ++it) {
            if ((*it)->getName() == movieName) {
                this->watched.push_back(*it);
                watchlist.erase(it);
                return;
            }
        }
        cout << "Movie not found in watchlist." << endl;
    }

    void listWatchlist() const {
        cout << "--- Watchlist ---" << endl;
        for (const auto& movie : watchlist) {
            MovieDisplay::displayShort(*movie);
        }
    }

    void listWatched() const {
        cout << "--- Watched Movies ---" << endl;
        for (const auto& movie : watched) {
            MovieDisplay::displayShort(*movie);
        }
    }
};


//Adds functionality for the admin user
class AdminUser : public User {
public:
    AdminUser(string name) : User(name) {}

    void manageMovies() {
        cout << "Admin " << getName() << " is managing movies in the system." << endl;
    }
};


//Manages adding and listing all movies
class MovieManager {
private:
    vector<Movie*> allMovies;

public:
    void addMovie(Movie* movie) {
        allMovies.push_back(movie);
    }

    void listAllMovies() const {
        cout << "--- All Movies ---" << endl;
        for (const auto& movie : allMovies) {
            MovieDisplay::displayDetailed(*movie);
        }
    }

    ~MovieManager() {
        for (auto movie : allMovies) {
            delete movie;
        }
    }
};

int main() {
    MovieManager movieManager;

    Movie* inception = new Movie("Inception", "Sci-Fi", 148);
    Movie* godfather = new Movie("The Godfather", "Crime", 175);
    Movie* loveActually = new Movie("Love Actually", "Romantic Comedy", 135);

    movieManager.addMovie(inception);
    movieManager.addMovie(godfather);
    movieManager.addMovie(loveActually);

    AdminUser admin("Vedha");
    User regularUser("Alex");

    admin.manageMovies();
    movieManager.listAllMovies();

    regularUser.addToWatchlist(inception);
    regularUser.addToWatchlist(godfather);
    regularUser.listWatchlist();

    regularUser.moveToWatched("Inception");
    regularUser.listWatched();
    regularUser.listWatchlist();

    return 0;
}
