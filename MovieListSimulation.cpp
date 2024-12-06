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

//Base Class
class MovieOperations {
public:
    virtual void execute(Movie* movie) = 0;
    virtual ~MovieOperations() {}    
};

//Operation to add a movie
class AddMovieOperation : public MovieOperations {
private:
    vector<Movie*>& movieList;

public:
    AddMovieOperation(vector<Movie*>& movies) : movieList(movies) {}

    void execute(Movie* movie) override {
        movieList.push_back(movie);
        cout << "Added movie: " << movie->getName() << endl;
    }
};

//Operation to list all movies
class ListMoviesOperation : public MovieOperations {
private:
    vector<Movie*>& movieList;

public:
    ListMoviesOperation(vector<Movie*>& movies) : movieList(movies) {}

    void execute(Movie* movie = nullptr) override {
        cout << "--- All Movies ---" << endl;
        for (const auto& movie : movieList) {
            MovieDisplay::displayDetailed(*movie);
        }
    }
};

//Manages the watchlist and watchedlist
//Follows LSP
//The User class provides basic functionality
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

// Premium user class that adds favorites functionality
class PremiumUser : public User {
private:
    vector<Movie*> favorites;

public:
    PremiumUser(string name) : User(name) {}

    void addToFavorites(Movie* movie) { favorites.push_back(movie); }

    void listFavorites() const {
        cout << "--- Favorite Movies ---" << endl;
        for (const auto& movie : favorites) {
            MovieDisplay::displayShort(*movie);
        }
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

    // Create movies
    Movie* inception = new Movie("Inception", "Sci-Fi", 148);
    Movie* godfather = new Movie("The Godfather", "Crime", 175);
    Movie* loveActually = new Movie("Love Actually", "Romantic Comedy", 135);

    // Admin functionality
    AdminUser admin("Vedha");
    movieManager.addMovie(inception);
    movieManager.addMovie(godfather);
    movieManager.addMovie(loveActually);
    movieManager.listAllMovies();

    // Regular user functionality
    User regularUser("Alex");
    regularUser.addToWatchlist(inception);
    regularUser.addToWatchlist(godfather);
    regularUser.listWatchlist();

    regularUser.moveToWatched("Inception");
    regularUser.listWatched();
    regularUser.listWatchlist();

    // Premium user functionality
    PremiumUser premiumUser("Sam");
    premiumUser.addToFavorites(loveActually);
    premiumUser.listFavorites();


    return 0;
}
