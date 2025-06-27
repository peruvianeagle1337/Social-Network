#include <string>
#include <set>
#include <vector>
#include "user.h"
#include "post.h"


User::~User() {

    }
// prefix: User
int User::getId(){
    return id_;
}
// postfix: returns ID of user

std::string User::getName(){
    return name_;
}
// postfix: returns name of user

int User::getYear() {
    return year_;
}
// postfix: returns birth year of user

int User::getZip(){
    return zip_;
}
// postfix: returns zip code of user

std::set<int> &User::getFriends(){
    return friends_;
}

const std::set<int>& User::getFriends() const {
    return friends_;
}


// postfix: returns set of friend IDs

//prefix: ID of friend to Add
void User::addFriend(int id){
    friends_.insert(id);
}
// postfix: adds a friend to the user's list

// prefix: ID of friend to delete
void User::deleteFriend(int id){
  
    friends_.erase(id);
}
// postfix: removes a friend from user friend list

void User::setID(int id) {
    id_ = id;
}
//postfix: sets user UD

void User::addPost(Post* newpost) {
    if (newpost) {
        messages_.push_back(newpost);
    }
}




std::vector<Post*>& User::getPosts(){
    return messages_;
}




std::string User::getPostsString(int howMany, bool showOnlyPublic) {
    std::string out = "";
    std::vector<Post*> posts = getPosts(); 

  
    if (showOnlyPublic) {
        std::vector<Post*> publicPosts;
        for (Post* post : posts) {
            if (post->getIsPublic()) {
                publicPosts.push_back(post);
            }
        }
        posts = publicPosts;  
    }


    if (posts.empty()) {
        return "No posts to show.";
    }

    int numPostsToShow = std::min(howMany, static_cast<int>(posts.size()));

    for (int i = posts.size() - 1; i >= (int)posts.size() - numPostsToShow; i--) {
        out += "\n\n" + posts[i]->toString();
    }

    return out;
}




