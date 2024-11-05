#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie {
    //Abstract Class
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
        // cout << "---Default Constructor called: " << name << " created.---" << endl;
    }

    // Parameterized Constructor
    Movie(string name, string genre = "Unknown", int duration = 0) {
        this->name = name;
        this->genre = genre;
        this->duration = duration;
        ++movieCount;
        // cout << "---Parametrized Constructor called: " << name << " created.---" << endl;
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

    //Display Function
    // void display() const {
    //     cout << "Movie Name: " << getName()
    //     <<" , Genre: " <<getGenre()
    //     <<" , Duration: "<<getDuration()<<endl;
    // }

    //Overloaded display Function
    // void display(const string& format){
    //     if(format == "short"){
    //         cout << getName() << "("<<getGenre() <<")"<<endl;
    //         }
    //     else{
    //         display();
    //     }
    // }

    // Pure Virtual Function
    virtual void display() const = 0;
    
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

    void display() const override{
        cout << " RomCom Movie - Name: " << getName()
             << ", Duration: " << getDuration()
             << " mins, Feel Good: " << (feelGood ? "Yes" : "No") << endl;
    }
};

class CrimeThrillerMovie : public Movie {
    public:
    CrimeThrillerMovie(string name, int duration) 
    : Movie (name , "Crime" , duration) {}

    void display() const override{
        cout<< " CrimeThriller Movie - Name: " << getName()
        << ", Duration: "<<getDuration()<<" mins "<<endl;
    }
};

class SciFiMovie : public Movie {
    public:
    SciFiMovie(string name, int duration) 
    : Movie (name , "Sci-Fi" , duration) {}

    void display() const override{
        cout<< " SciFi Movie - Name: " << getName()
        << ", Duration: "<<getDuration()<<" mins "<<endl;
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
        // cout << "User Constructor called: " << name << " created." << endl;
    }

    // Destructor
    ~User() {
        for (auto movie : watchlist) {
            delete movie;
        }
        for (auto movie : watched) {
            delete movie;
        }
        --userCount;
        // cout << "User Destructor called: " << name << " destroyed." << endl;
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
    Movie* movie1 = new SciFiMovie("Inception", 148);
    Movie* movie2 = new CrimeThrillerMovie("The Godfather", 175);

    // cout << "--- Demonstrating RomComMovie ---" << endl;
    RomComMovie* romCom = new RomComMovie("Crazy Rich Asians", 121);
    romCom->display();
    movie2->display();
    movie1->display();

    // cout << "--- Creating Users ---" << endl;
    AdminUser* admin = new AdminUser("Vedha");
    RegularUser* user1 = new RegularUser("Alex");

    // cout << "--- Regular User Activities ---" << endl;
    user1->addToWatchList(movie1);
    user1->addToWatchList(movie2);
    user1->listWatchList();

    // cout << "--- Admin User Activities ---" << endl;
    admin->manageUsers();

    // cout << "--- Watching a Movie ---" << endl;
    user1->addToWatched("Inception");
    user1->listWatched();
    user1->listWatchList();

    delete user1; 
    delete admin; 
    delete romCom; 

    return 0;
}
