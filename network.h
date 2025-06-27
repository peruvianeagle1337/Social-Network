#include <string>
#include <set>
#include <vector>
#include <iostream>
#include "user.h"

#ifndef network_h
#define network_h


class Network {
private: 
    std::vector<User*> users_;

public: 

    Network() = default;

    const std::vector<User*>& getNetwork() const;
    User* getUser(int id);

    int addConnection(const std::string& s1, const std::string& s2);
    int deleteConnection(std::string s1, std::string s2);

    
    User* uzr_from_name(const std::string& nameof) const;

    void addUser(User*);

    int getId(std::string name);

    int numUsers();
    void readUsers(const char* fname);
    void writeUsers(const char* fname);
    void listUsers() const; // Added method
    

    bool user_in_network(std::string namer);
    std::vector<int> shortestPath(int from, int to);
    std::vector<int> distanceUser(int from, int& to, int distance);

    std::vector<int> suggestFriends(int who, int& score);

    std::vector<std::vector<int>> groups();

    void addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic);

    std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);
    int readPosts(const char* fname);
    /*
    
    +addPost(ownerId:int, message:string, likes:int,
    isIncoming:bool, authorName:string, isPublic:bool): void
    +getPostsString(ownerId:int, howMany:int, showOnlyPublic:bool): string
    */

    static bool comparator(Post* post1, Post* post2);
    void printSortedPosts() const;
    void writePosts(const char* fname);
    std::vector<Post*> getAllPostsSorted() const;
    int getNextPostId() const;

    void readMoodboards(const char* fname);
    void writeMoodboards(const char* fname);
    void readProfilePics(const char* fname);
    void writeProfilePics(const char* fname);
    void readBios(const char* fname);
    void writeBios(const char* fname);
};






#endif


