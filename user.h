#include <string>
#include <set>
#include <vector>

#ifndef user_h
#define user_h
#include "post.h"
#include "moodboard.h"
#include "creativespace.h"

class User {

 private:

    int id_ = 0;
    std::string name_;
    int year_ = 0;
    int zip_;
    std::set<int> friends_;
    std::vector<Post*> messages_;
    std::string profilePicturePath_;  // local file path or URL
    std::string biography_;

    // Experimental Features
    Moodboard moodboard_;        // Each user has their own moodboard
    CreativeSpace creativeSpace_; // Each user’s shared drawing canvas
    
public:


    // Constructors
    User() : creativeSpace_(600, 400) {} // example canvas size: 600x400
    User(int id, std::string name, int year, int zip, std::set<int> friends)
        : id_(id),
        name_(name),
        year_(year),
        zip_(zip),
        friends_(friends),
        creativeSpace_(600, 400) // initialize creative space
    {
    }
    ~User();

    void setID(int id);

    int getId();

    std::string getName();

    int getYear();

    int getZip();

    const std::set<int>& getFriends() const;
    std::set<int>& getFriends();

    void addFriend(int id);

    void deleteFriend(int id);

    void addPost(Post*);
    std::vector<Post*>& getPosts();
    std::string getPostsString(int howMany, bool showOnlyPublic);


    // NEW: Profile Picture
    void setProfilePicture(const std::string& path) {
        profilePicturePath_ = path;
    }
    std::string getProfilePicture() const {
        return profilePicturePath_;
    }

    // NEW: Biography
    void setBiography(const std::string& bio) {
        biography_ = bio;
    }
    std::string getBiography() const {
        return biography_;
    }

    // NEW: Moodboard
    Moodboard& getMoodboard() {
        return moodboard_;
    }

    // NEW: Creative Space
    CreativeSpace& getCreativeSpace() {
        return creativeSpace_;
    }
/*
+addPost(Post*):void
+getPosts(): vector<Post*>
+getPostsString(howMany:int, showOnlyPublic:bool):string
*/
    
};

#endif
