
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include "user.h"
#include "network.h"
#include "post.h"


// PREFIX: a Network Object
const std::vector<User*>& Network::getNetwork() const {
    return users_;
}
// POSTFIX: returns the vector of users in the network





// PREFIX: a USER ID  
User* Network::getUser(int id){
        for (User* user_1 : this->getNetwork()) {
            int userid = user_1->getId();
            if(userid == id) {
                 //std::cout << "User Found" << std::endl;
                return user_1;    
            }
               
        
        }
        std::cout << "User Not Found" << std::endl;
        return nullptr;
}
//POSTFIX : Returns a pointer to the User to which the ID belongs




// PREFIX: a pointer to the new user
void Network::addUser(User* user) {
    
    int assignedId = users_.size();
    
    users_.push_back(user);
}
//POSTFIX: A User has been added to the Network


// PREFIX: Name of a User
User* Network::uzr_from_name(const std::string& nameof) const {
    auto uzr = this->getNetwork();
    
    for(auto it = uzr.begin(); it != uzr.end(); ++it){
       
        if ((*it)->getName() == nameof){
            return *it; 
        }
    }
    return nullptr; 
}
// POSTFIX: Returns a pointer to a user from a name
    
bool Network::user_in_network(std::string namer){
    auto x = this->getNetwork();
    for (User* user : x){
        if (user->getName() == namer){
            return true;
        }

    }
    return false;
}

// POSTFIX: Returns a Pointer to the User


//PREFIX: THE USERNAMES OF TWO USERS
int Network::addConnection(const std::string& s1, const std::string& s2) {
    // Assume both users exist.
    User* user1 = uzr_from_name(s1);
    User* user2 = uzr_from_name(s2);

    // Check if already friends.
    if (user1->getFriends().find(user2->getId()) != user1->getFriends().end())
        return 1;

    // Add each other as friends.
    user1->addFriend(user2->getId());
    user2->addFriend(user1->getId());
    return 0;
}



  

// POSTFIX: ADDS A CONNECTION BETWEEN THE TWO USERS AFTER CHECKING THAT ONE DOES NOT EXIST ALREADY

// PREFIX: THE NAMES OF TWO USERS 
int Network::deleteConnection(std::string s1, std::string s2) {
    bool user_1_search = this->user_in_network(s1);
    bool user_2_search = this->user_in_network(s2);
    if ((user_1_search == false) || user_2_search == false){
        return -1;
    }
    
    User* user1_ptr = this->uzr_from_name(s1);
    User* user2_ptr = this->uzr_from_name(s2);

    if ((user1_ptr == nullptr) || (user2_ptr == nullptr)){
        std::cerr << "Error: One or both users do not exist." << std::endl;
        return -1;
    }

    user1_ptr->deleteFriend(user2_ptr->getId());
    user2_ptr->deleteFriend(user1_ptr->getId());

    std::cout << "Friend connection deleted between \"" << s1 << "\" and \"" << s2 << "\"." << std::endl;

    return 0;
}
//POSTFIX: REMOVES THE CONNECTION BETWEEN USERS AFTER CHECKING THAT THE USERS ARE IN THE NETWORK AND THAT  A CONNECTION EXISTS


//PREFIX: THE NAME OF A USER 
int Network::getId(std::string name) {
    User* user = uzr_from_name(name);
    if (user != nullptr) {
        return user->getId();
    }
    return -1; 
}
//POSTFIX: RETURNS THE ID OF THE USER IF THEY ARE IN THE NETWORK

//prefix :  NETWORK OBJECT
int Network::numUsers() {
    return this->users_.size();
}
// POSTFIX: RETURNS THE NUMBER OF USERS


static std::string trimLeadingTab(const std::string& line) {
    if (!line.empty() && line[0] == '\t') {
        return line.substr(1);
    }
    return line;
}

static std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

void Network::readUsers(const char* fname) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open file '" << fname << "' for reading.\n";
        return;
    }

    // Clear existing users
    for (User* user : users_) {
        delete user;
    }
    users_.clear();


    std::string line;

    if (!std::getline(infile, line)) {
        std::cerr << "Error: Failed to read the number of users from the file.\n";
        return;
    }

    // TOTAL NUMBER OF USERS
    int numUsers = std::stoi(trim(line));


    std::cout << "Number of users to read: " << numUsers << "\n"; // Debug statement

    // iterate through all user's data
    for (int i = 0; i < numUsers; ++i) {
        // read User ID
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading User ID for user " << i << ".\n";
            return;
        }
        int id = std::stoi(trim(line));

        //std::cout << "Reading User ID: " << id << "\n"; // Debug statement

        // read User Name (with leading tab)
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading User Name for user ID " << id << ".\n";
            return;
        }
        std::string name = trimLeadingTab(line);
        name = trim(name);
        if (name.empty()) {
            std::cerr << "Error: Empty User Name for user ID " << id << ".\n";
            return;
        }
        //std::cout << "Reading User Name: " << name << "\n"; // Debug statement

        // read Birth Year (with leading tab)
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading Birth Year for user ID " << id << ".\n";
            return;
        }
        int birthYear = 0;
        try {
            birthYear = std::stoi(trimLeadingTab(line));
        } catch (const std::invalid_argument&) {
            std::cerr << "Error: Invalid Birth Year format for user ID " << id << ".\n";
            return;
        }
        //std::cout << "Reading Birth Year: " << birthYear << "\n"; // Debug statement

        // read ZIP Code (with leading tab)
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading ZIP Code for user ID " << id << ".\n";
            return;
        }
        int zipCode = 0;
        try {
            zipCode = std::stoi(trimLeadingTab(line));
        } catch (const std::invalid_argument&) {
            std::cerr << "Error: Invalid ZIP Code format for user ID " << id << ".\n";
            return;
        }
        //std::cout << "Reading ZIP Code: " << zipCode << "\n";

        //  Read Friend IDs
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading Friend IDs for user ID " << id << ".\n";
            return;
        }
        std::set<int> friendIDs;
        std::string friendsLine = trimLeadingTab(line);
        friendsLine = trim(friendsLine);
        if (!friendsLine.empty()) {
            std::stringstream ss(friendsLine);
            int friendID;
            while (ss >> friendID) {
                friendIDs.insert(friendID);
            }
        }
        //std::cout << "Reading Friend IDs: ";


        User* newUser = new User(id, name, birthYear, zipCode, friendIDs);
        users_.push_back(newUser);

    }

    infile.close();
    std::cout << "Successfully read " << numUsers << " user(s) from '" << fname << "'.\n";
}


void Network::listUsers() const {
    if (users_.empty()) {
        std::cout << "No users in the network.\n";
        return;
    }
    std::cout << "List of Users:\n";
    for ( User* user : users_) {
        std::cout << "ID: " << user->getId()
                << ", Name: " << user->getName()
                  << ", Birth Year: " << user->getYear()
                  << ", ZIP Code: " << user->getZip()
                  << ", Friends: ";
        const std::set<int>& friends = user->getFriends();
        if (friends.empty()) {
            std::cout << "None";
        } else {
            for (auto it = friends.begin(); it != friends.end(); ++it) {
                std::cout << *it;
                if (std::next(it) != friends.end()) {
                    std::cout << ", ";
                }
            }
        }

    }
}


// PREFIX: FILE NAME CONTAINING NETWORK INFORMATION
void Network::writeUsers(const char* fname) {
    std::ofstream ofile(fname);
    if (!ofile) {
        std::cerr << "Error opening file for write: " << fname << std::endl;
        return;
    }


    ofile << users_.size() << "\n";


    for (User* u : users_) {

        ofile << u->getId() << "\n";

        ofile << "\t" << u->getName() << "\n";

        ofile << "\t" << u->getYear() << "\n";

        ofile << "\t" << u->getZip() << "\n";

        ofile << "\t";
        const std::set<int>& friends = u->getFriends();
        bool first = true;
        for (int fid : friends) {
            if (!first) {
                ofile << " ";
            }
            ofile << fid;
            first = false;
        }
        ofile << "\n";
    }

}




std::vector<int> Network::shortestPath(int from, int to){
    User* user1 = getUser(from);
    User* user2 = getUser(to);

    if (user1 == nullptr || user2 == nullptr){
        std::cout<<"Invalid Users"<<std::endl;
        return {};
    }

    auto n = getNetwork().size();

    std::queue<int> q;
    std::vector<bool> isVisited(n,0);
    std::vector<int> prev(n, -1); 

    isVisited[from] = true;
    q.push(from);

    std::set<int> conns = user1->getFriends();
    int distance = 0;
    while(q.size()>0){
        int cur = q.front();
        q.pop();
        User* curuser = getUser(cur);
        std::set<int> curfriends = curuser->getFriends();
        for(int curfriend : curfriends ){
            if(!isVisited[curfriend]){
                prev[curfriend] = cur;
                isVisited[curfriend] = true;
                q.push(curfriend);
            }
        }

   
    }
    std::vector<int> output;
    int cur = to;
    while (cur != -1) {
      output.push_back(cur);
      cur = prev[cur];
    }
    reverse(output.begin(), output.end());
    if((output.empty()) || (output[0] != from)){
        return {};
    }
        
    
    return output;
}



/*




User at a given distance (18 points)
Add a public method
vector<int> Network::distanceUser(int from, int& to, int distance)
to your Network class that finds a user whose relational distance from the given user exactly
matches the distance given, and returns the shortest path to that user. The call by reference
parameter int & to should be set to the id of the user found, and the method should return
a vector of the IDs of the users on the shortest path. If no such user exists, the function
should return an empty vector and set the ”to” parameter to -1

*/


std::vector<int> Network::distanceUser(int from, int& to, int distance) {
    User* user1 = getUser(from);
    if (user1 == nullptr) {
        to = -1;
        return {}; 
    }

    std::vector<int> bestPath;
    to = -1; 

    // Try every user in the network
    for (User* user : getNetwork()) {
        int user_id = user->getId();
        if (user_id == from) continue;  // skip self

    
        std::vector<int> path = shortestPath(from, user_id);
        if (!path.empty()) {
            int distEdges = path.size() - 1;

            if (distEdges == distance) {
                
                to = user_id;   // set the by-reference param
                return path;   
            }
        }
    }

    return {}; 
}

/*



Add a public method
vector<int> Network::suggestFriends(int who, int& score)
to compute a list of from suggestions for a particular user who. You should suggest users
who have a ’strong’ connection to the friends of the specified user. To do so, say that the
“score” of a potential new friend is the number of common friends they would share with
the specified user. Return a list of friend suggestions corresponding to the users with the
highest score. Obviously, you should not consider any users who are already friends. Set the
call by reference parameter score to the highest score found, and return a list of the ids of
Users who have that score. If no suggestions exists, return the empty vector and set score
to 0.
*/

std::vector<int> Network::suggestFriends(int who, int& score) {

        
        User* usr = getUser(who);

        if (!usr) {
            score = 0;
            return {};
        }   

        std::set<int> usr_friends = usr->getFriends();
        int maxCommon = 0;
        std::vector<int> candidates;

        for(User* person : getNetwork()){
            int person_id = person->getId();

            if (person_id==who){
                continue;
            }

            if(usr_friends.find(person_id) != usr_friends.end()){
                continue;
            }
            
            std::vector<int> common_friends;
            std::set_intersection(usr_friends.begin(),usr_friends.end(),person->getFriends().begin(),person->getFriends().end(),std::back_inserter(common_friends));
            int new_score = common_friends.size();

            if(new_score > maxCommon){
                
                maxCommon = new_score;
                candidates.clear();
                candidates.push_back(person_id);
            }

            else if (new_score == maxCommon && maxCommon > 0){
                candidates.push_back(person_id);
            }
            
            
           //Print info for debugging:
           //std::cout << person->getName() << " and "
            //<< usr->getName() << " have "
          //  << new_score << " friends in common\n";
           
         }

    if (maxCommon == 0) {
        score = 0;
        return {};
    }
    score = maxCommon;
    return candidates;
    

        
}

/*
Add a public method
that computes the connected components of the network. A connected component is a group
of users who all have paths to one another but have no edges to all other uses. You must
use DFS to compute the connected components of the network. The output should be a list
of lists, where each list contains the ids of the users in one connected component.
*/
std::vector<std::vector<int>> Network::groups(){
    
    std::vector<bool> visited(getNetwork().size(),0);
    std::vector<std::vector<int>> solution({});
 
    std::vector<int> IDs;

    for (User* u : getNetwork()){
        IDs.push_back(u->getId());
    }

    for(int i = 0; i < IDs.size(); i++) {
        if(!visited[i]){
            std::vector<int> component;
            std::stack<int> stck;
            visited[i] = true;
            stck.push(IDs[i]);

            while(!stck.empty()){
                int current = stck.top();
                stck.pop();
                component.push_back(current);
                for(int z : getUser(current)->getFriends()){
                    if(!visited[z]){
                        visited[z] = true;
                        stck.push(IDs[z]);
                    }
                }
            }

            solution.push_back(component);
        }

    }

    return solution;
    }
    
      

    void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic){ 
        if(getUser(ownerId) == nullptr){
            std::cout << "User not in Network" << std::endl;
            return;
        }
        
        auto& user_posts = getUser(ownerId)->getPosts();
        int messageId = getNextPostId();
    
        if(isIncoming == true){
            IncomingPost* p = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
            user_posts.push_back(p);
        }
        else {
            Post* p = new Post(messageId, ownerId, message, likes);
            user_posts.push_back(p);
        }
    }
    
//      int,         int,           std::string,        int,            bool, std::string
//Post(int messageId, int ownerId, std::string message, int likes) : messageId_(messageId),ownerId_(ownerId),message_(message),likes_(likes) {
//IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author) : Post(messageId, ownerId, message, likes), isPublic_(isPublic), author_(author) {
std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic){
    if(getUser(ownerId) == nullptr){
        return "User not in Network";
    }

    return getUser(ownerId)->getPostsString(howMany,showOnlyPublic);
}

/*


void DFS(int source) {
    stack<int> stck;
    vector<bool> visited (n(), 0);

    visited[source] = true;
    stck.push(source);

    while (stck.size() > 0) {
      int cur = stck.top();
      stck.pop();
      for (auto neighbor : adjLists_[cur]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          stck.push(neighbor);
        }
      }
      // HERE
      // print statements added
      cout << "cur: " << cur << endl;
      cout << "stck: ";
      print_stack(stck);
      cout << "visited: ";
      for (int i = 0; i < n(); i ++) {
        cout << i << (visited[i] ? "T" : "F") << " ";
      }
      cout << endl << endl;
    }
  }


*/

//+readPosts(char* fname): int
//+writePosts(char* fname): int



// Example declarations for Post and IncomingPost:
//
// class Post {
// public:
//     Post(int messageId, int ownerId, const std::string &message, int likes);
//     virtual ~Post();
//     int getMessageId() const;
//     int getOwnerId() const;
//     std::string getMessageText() const;
//     int getLikes() const;
//     // For file writing: For an owner post these return empty strings.
//     virtual std::string getStatus() const { return ""; }
//     virtual std::string getAuthor() const { return ""; }
// };
//
// class IncomingPost : public Post {
// public:
//     IncomingPost(int messageId, int ownerId, const std::string &message, int likes,
//                  bool isPublic, const std::string &author);
//     virtual ~IncomingPost();
//     virtual std::string getStatus() const override; // returns "public" or "private"
//     virtual std::string getAuthor() const override;
// };


 bool Network::comparator(Post* post1, Post* post2) {
    return post1->getMessageId() < post2->getMessageId();
}





std::vector<Post*> Network::getAllPostsSorted() const {
    std::vector<Post*> allPosts;
    for (User* user : getNetwork()) {
        // Assuming each user has a getPosts() method that returns a vector<Post*>
        for (Post* p : user->getPosts()) {
            allPosts.push_back(p);
        }
    }
    std::sort(allPosts.begin(), allPosts.end(), Network::comparator);
    return allPosts;
}


void Network::printSortedPosts() const {
    std::vector<Post*> sortedPosts = getAllPostsSorted();
    std::cout << "Sorted Post Message IDs:\n";
    for (Post* p : sortedPosts) {
        std::cout << p->getMessageId() << " ";
    }
    std::cout << std::endl;
}

int Network::readPosts(const char* fname) {
    // Open the file in input mode.
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::cerr << "Error: Unable to open file '" << fname << "' for reading.\n";
        return -1;
    }

    // Check if the file is empty.
    if (infile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Posts file is empty. No posts to read.\n";
        infile.close();
        return 0;  // File is empty; leave existing posts intact.
    }

    // Now that we know the file is non-empty, clear posts from all users.
    for (User* u : getNetwork()) {
        u->getPosts().clear();
    }

    std::vector<Post*> global_posts;
    std::string line;

    // Read the total number of posts (first line).
    if (!std::getline(infile, line)) {
        std::cerr << "Error: Failed to read the number of posts from the file.\n";
        infile.close();
        return -1;
    }

    int numPosts = std::stoi(trim(line));
    // Debug: std::cout << "Number of posts to read: " << numPosts << "\n";

    // Process each post.
    for (int i = 0; i < numPosts; ++i) {
        // 1. Read Message ID (line 1).
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading message ID for post " << i << ".\n";
            infile.close();
            return -1;
        }
        int messageId = std::stoi(trimLeadingTab(line));
        // Debug: std::cout << "Message ID: " << messageId << "\n";

        // 2. Read Message Text (line 2).
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading message text for post " << messageId << ".\n";
            infile.close();
            return -1;
        }
        std::string message_text = trimLeadingTab(line);
        // Debug: std::cout << "Message: " << message_text << "\n";

        // 3. Read Owner ID (line 3).
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading owner ID for post " << messageId << ".\n";
            infile.close();
            return -1;
        }
        int ownerId = std::stoi(trimLeadingTab(line));
        // Debug: std::cout << "Owner ID: " << ownerId << "\n";

        // 4. Read Likes (line 4).
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading likes for post " << messageId << ".\n";
            infile.close();
            return -1;
        }
        int likes = std::stoi(trimLeadingTab(line));
        // Debug: std::cout << "Likes: " << likes << "\n";

        // 5. Read Status (line 5).
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading status for post " << messageId << ".\n";
            infile.close();
            return -1;
        }
        std::string status = trimLeadingTab(line);

        // 6. Read Author (line 6).
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading author for post " << messageId << ".\n";
            infile.close();
            return -1;
        }
        std::string author = trimLeadingTab(line);

        // Create the Post object:
        Post* newPost = nullptr;
        if (status.empty()) {
            // Owner post – use the base Post constructor.
            newPost = new Post(messageId, ownerId, message_text, likes);
        } else {
            // Incoming post – determine whether the post is public.
            bool isPublic = (status == "public");
            newPost = new IncomingPost(messageId, ownerId, message_text, likes, isPublic, author);
        }

        global_posts.push_back(newPost);
    }
    infile.close();

    // Sort the vector of posts in ascending order.
    std::sort(global_posts.begin(), global_posts.end(), Network::comparator);

    // Distribute posts to the corresponding user.
    for (Post* p : global_posts) {
        User* ownerUser = getUser(p->getOwnerId());
        if (ownerUser != nullptr) {
            ownerUser->getPosts().push_back(p);
        } else {
            std::cerr << "Warning: Owner with ID " << p->getOwnerId()
            << " not found for post " << p->getMessageId() << ". Post discarded.\n";
        }
    }

    return 0;
}


void Network::writePosts(const char* fname) {
    std::ofstream ofile(fname);
    if (!ofile) {
        std::cerr << "Error opening file for write: " << fname << std::endl;
        return;
    }
    

    std::vector<Post*> allposts = getAllPostsSorted();
    
    // Write total number of posts.
    ofile << allposts.size() << "\n";

    // Write each post using exactly six lines.
    for (Post* p : allposts) {
        // 1. Write Message ID (no leading tab)
        ofile << p->getMessageId() << "\n";
        
        // 2. Write Message Text (with a leading tab)
        ofile << "\t" << p->getMessage() << "\n";
        
        // 3. Write Owner ID (with a leading tab)
        ofile << "\t" << p->getOwnerId() << "\n";
        
        // 4. Write Likes (with a leading tab)
        ofile << "\t" << p->getLikes() << "\n";
        
        // 5. Write Status (with a leading tab)
        if (p->getAuthor().empty()) {
            ofile << "\t" << "\n";
        } else {
            ofile << "\t" << (p->getIsPublic() ? "public" : "private") << "\n";
        }
        
        // 6. Write Author (with a leading tab)
        ofile << "\t" << p->getAuthor() << "\n";
    }
}

int Network::getNextPostId() const {
    int maxId = -1;
    for (User* u : getNetwork()) {
        for (Post* p : u->getPosts()) {
            if (p->getMessageId() > maxId) {
                maxId = p->getMessageId();
            }
        }
    }
    return maxId + 1;
}



void Network::readMoodboards(const char* fname) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::cerr << "Warning: Could not open moodboard file '"
                  << fname << "' for reading. Skipping.\n";
        return;
    }

    std::string line;
    if (!std::getline(infile, line)) {
        // If file is empty or missing a count, we just skip
        std::cerr << "Moodboard file empty or invalid.\n";
        return;
    }

    int numEntries = std::stoi(line);

    for (int i = 0; i < numEntries; ++i) {
        // 1) Read userId
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of moodboard file.\n";
            break;
        }
        int userId = std::stoi(line);

        // 2) Find that user in the network
        User* user = getUser(userId);
        if (!user) {
            // The user might not exist in older networks, skip their data
            // but still read lines so we don't break parsing
            std::cerr << "Warning: Moodboard data for non-existent userId "
                      << userId << ". Skipping.\n";
        }

        // 3) Read numberOfStickers
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading stickers.\n";
            break;
        }
        int stickerCount = std::stoi(line);

        for (int s = 0; s < stickerCount; ++s) {
            if (!std::getline(infile, line)) {
                std::cerr << "Error: Unexpected end of file reading a sticker.\n";
                break;
            }
            std::stringstream ss(line);

            Sticker st;
            int typeInt;
            long long epochTime;

            ss >> st.stickerId >> typeInt >> st.x >> st.y >> st.imagePath >> epochTime;
            st.stickerType = (StickerType)typeInt;
            st.timestamp = QDateTime::fromSecsSinceEpoch(epochTime);



            user->getMoodboard().addSticker(st);

        }
    }

    infile.close();
    std::cout << "Successfully read moodboards from '" << fname << "'\n";
}

/**
 * writeMoodboards:
 *  Writes moodboard data to a separate file. For each user with stickers,
 *  we store userId, numberOfStickers, then each sticker line.
 */
void Network::writeMoodboards(const char* fname) {
    std::ofstream ofile(fname);
    if (!ofile) {
        std::cerr << "Error: Could not open moodboard file '"
                  << fname << "' for writing.\n";
        return;
    }

    // We'll count how many users actually have stickers
    // so we can store that count first.
    int userCountWithStickers = 0;
    for (User* u : users_) {
        if (!u->getMoodboard().getStickers().empty()) {
            userCountWithStickers++;
        }
    }
    ofile << userCountWithStickers << "\n";

    // Now write data for each user that has stickers
    for (User* u : users_) {
        const auto& stickers = u->getMoodboard().getStickers();
        if (stickers.empty()) continue;

        // userId
        ofile << u->getId() << "\n";

        // numberOfStickers
        ofile << stickers.size() << "\n";

        // each sticker
        for (auto& st : stickers) {
            // stickerId, stickerType, x, y, imagePath, epochTimestamp
            ofile << st.stickerId << " "
                  << (int)st.stickerType << " "
                  << st.x << " "
                  << st.y << " "
                  << st.imagePath << " "
                  << st.timestamp.toSecsSinceEpoch()
                  << "\n";
        }
    }

    ofile.close();
    std::cout << "Successfully wrote moodboards to '" << fname << "'\n";
}

void Network::readProfilePics(const char* fname) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::cerr << "Warning: Could not open profile pics file '"
                  << fname << "' for reading.\n";
        return;
    }

    std::string line;
    if (!std::getline(infile, line)) {
        // file might be empty
        return;
    }
    int numEntries = std::stoi(line);

    for (int i = 0; i < numEntries; ++i) {
        // 1) read userId
        if (!std::getline(infile, line)) break;
        int userId = std::stoi(line);

        // 2) read the picture path
        if (!std::getline(infile, line)) break;
        std::string picPath = line; // could be absolute or relative path

        // 3) find the user
        User* user = getUser(userId);
        if (user) {
            user->setProfilePicture(picPath);
        } else {
            // user not found, skip
        }
    }
    infile.close();
}

void Network::writeProfilePics(const char* fname) {
    std::ofstream ofile(fname);
    if (!ofile) {
        std::cerr << "Error: Could not open profile pics file '"
                  << fname << "' for writing.\n";
        return;
    }

    // Count how many users actually have a profile pic
    int countWithPics = 0;
    for (User* u : users_) {
        if (!u->getProfilePicture().empty()) {
            countWithPics++;
        }
    }
    ofile << countWithPics << "\n";

    // For each user with a picture, write userId + path
    for (User* u : users_) {
        if (!u->getProfilePicture().empty()) {
            ofile << u->getId() << "\n";
            ofile << u->getProfilePicture() << "\n";
        }
    }
    ofile.close();
}


void Network::readBios(const char* fname) {
    std::ifstream infile(fname);
    if (!infile.is_open()) {
        std::cerr << "Warning: Could not open bios file '" << fname << "' for reading. Skipping.\n";
        return;
    }

    std::string line;
    if (!std::getline(infile, line)) {
        std::cerr << "Bios file empty or invalid.\n";
        return;
    }

    int numEntries = std::stoi(line);
    for (int i = 0; i < numEntries; ++i) {
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of bios file.\n";
            break;
        }
        int userId = std::stoi(line);
        User* user = getUser(userId);
        if (!user) {
            std::cerr << "Warning: Bio data for non-existent userId " << userId << ". Skipping.\n";
            continue;
        }
        if (!std::getline(infile, line)) {
            std::cerr << "Error: Unexpected end of file while reading bio lines.\n";
            break;
        }
        int numLines = std::stoi(line);
        std::string bio;
        for (int j = 0; j < numLines; ++j) {
            if (!std::getline(infile, line)) {
                std::cerr << "Error: Unexpected end of file reading bio.\n";
                break;
            }
            if (j > 0) bio += "\n"; // Add newline between lines
            bio += line;
        }
        user->setBiography(bio);
    }
    infile.close();
    std::cout << "Successfully read bios from '" << fname << "'\n";
}

void Network::writeBios(const char* fname) {
    std::ofstream ofile(fname);
    if (!ofile) {
        std::cerr << "Error: Could not open bios file '" << fname << "' for writing.\n";
        return;
    }

    // Count users with non-empty biographies
    int countWithBios = 0;
    for (User* u : users_) {
        if (!u->getBiography().empty()) {
            countWithBios++;
        }
    }
    ofile << countWithBios << "\n";

    // Write each user's biography
    for (User* u : users_) {
        const std::string& bio = u->getBiography();
        if (bio.empty()) continue;
        ofile << u->getId() << "\n";
        std::istringstream iss(bio);
        std::string line;
        std::vector<std::string> lines;
        while (std::getline(iss, line)) {
            lines.push_back(line);
        }
        ofile << lines.size() << "\n";
        for (const std::string& l : lines) {
            ofile << l << "\n";
        }
    }
    ofile.close();
    std::cout << "Successfully wrote bios to '" << fname << "'\n";
}
