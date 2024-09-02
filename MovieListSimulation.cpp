#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie {
    private:
    string name;
    string genre;
    int duration;

    public:
    Movie(string name, string genre = " ", int duration=0){
        this->name = name;  
        this->genre = genre;
        this->duration=duration;
    }

    string getName()const{
        return this->name;
    }

    string getGenre()const{
        return this->genre;
    }

    int getDuration()const{
        return this->duration;
    }
};

class User {
    private:
    string name;
    vector<Movie*> watchlist;
    vector<Movie*> watched;
    vector<Movie*> favorites;

    public:
    User(string name){
        this->name = name;
    }

    // Destructor : Automatically called when delete user is called and deletes the movies created.
    ~User(){
        for(Movie* movie:watchlist){
            delete movie;
        }
        for(Movie* movie:watched){
            delete movie;
        }
        for(Movie* movie:favorites){
            delete movie;
        }
    }

    User& addToWatchList(Movie* movie) {
        this->watchlist.push_back(movie);
        return *this;
        }

    void addToWatched(const string& movieName){
        for (auto i = this->watchlist.begin(); i!=watchlist.end(); ++i){
            if((*i)->getName() == movieName) {
                this->watched.push_back(*i);
                this->watchlist.erase(i);
                return;
            }
        }
        cout<<"Movie not found in watchlist."<<endl;
    }

    void listMovies(const vector<Movie*>& movies)const{
        for(const auto& movie : movies){
            cout<< "Name:" << movie->getName() << ", Genre:"<< movie->getGenre()<< ", Duration:"<< movie->getDuration()<< "mins"<<endl;
        }
    }

    void listWatchList() const {
        cout<<"--------------------"<<endl;
        cout<<"Movies in watchlist:" <<endl;
        cout<<"--------------------"<<endl;
        this->listMovies(this->watchlist);
    }

    void listWatched() const {        
        cout<<"--------------------"<<endl;
        cout<< "Movies in Watched:" <<endl;
        cout<<"--------------------"<<endl;
        this->listMovies(this->watched);
    }
};

int main(){
    Movie* movies[]= {
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

    delete user;

    return 0;
}