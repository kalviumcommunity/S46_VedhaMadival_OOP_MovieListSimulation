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
    vector<Movie> watchlist;
    vector<Movie> watched;
    vector<Movie> favorites;

    public:
    User(string name){
        this->name = name;
    }

    User& addToWatchList(const Movie& movie) {
        this->watchlist.push_back(movie);
        return *this;
        }

    void addToWatched(const string& movieName){
        for (auto i = this->watchlist.begin(); i!=watchlist.end(); ++i){
            if(i->getName() == movieName) {
                this->watched.push_back(*i);
                this->watchlist.erase(i);
                return;
            }
        }
        cout<<"Movie not found in watchlist."<<endl;
    }

    void listMovies(const vector<Movie>& movies)const{
        for(const auto& movie : movies){
            cout<< "Name:" << movie.getName() << ", Genre:"<< movie.getGenre()<< ", Duration:"<< movie.getDuration()<< "mins"<<endl;
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
    Movie movie1("Inception");
    Movie movie2("The Godfather", "Crime", 175);
    Movie movie3("The Dark Knight", "Action", 152);

    User user("Vedha");

    user.addToWatchList(movie1);
    user.addToWatchList(movie2);

    user.listWatchList();
    user.addToWatched("Inception");
    user.listWatched();
    user.listWatchList();

    return 0;
}