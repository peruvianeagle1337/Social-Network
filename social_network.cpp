#include "network.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// Print usage instructions when not enough arguments are provided.
void printUsage(const std::string& programName) {
    std::cerr << "Usage: " << programName << " <users_filename> <posts_filename>" << std::endl;
}

// Display the interactive menu.
void displayMenu() {
    std::cout << "\n=== Social Network Menu ===\n";
    std::cout << "1. Add a user\n";
    std::cout << "2. Add friend connection\n";
    std::cout << "3. Delete friend connection\n";
    std::cout << "4. Write to file\n";
    std::cout << "5. Recent Posts\n";
    std::cout << "6. Exit\n";
    std::cout << "Please enter your option: ";
}

int main(int argc, char* argv[]) {
    //std::cout << "Hello" << std::endl;
    if (argc < 3) {
        printUsage(argv[0]);
        return 1;
    }

    // Get filenames from command-line arguments.
    std::string usersFile = argv[1];
    std::string postsFile = argv[2];

    // Create a Network object.
    Network mynet;

    // Read in the users and the posts.
    mynet.readUsers(usersFile.c_str());
    mynet.readPosts(postsFile.c_str());
   // mynet.printSortedPosts();

    int totalUsers = mynet.numUsers();
    if (totalUsers == 0) {
        std::cout << "No posts loaded from the file: " << usersFile << std::endl;
        return 0;
    } else {
        std::cout << "Users Loaded" << std::endl;
    }
  
    
    // Main  loop
    while (true) {
        displayMenu();

        std::string inLine;
        std::getline(std::cin, inLine);
        if (inLine.empty()) {
            std::cout << "Invalid input" << std::endl;
            continue;
        }

        std::stringstream ss(inLine);
        int option;
        ss >> option;

        switch (option) {
            case 1: { // Add a user
                std::string firstName, lastName;
                int birthYear, zipCode;
                std::cout << "Enter user details (FirstName LastName BirthYear ZipCode): ";
                std::getline(std::cin, inLine);
                std::stringstream ssAdd(inLine);
                if (!(ssAdd >> firstName >> lastName >> birthYear >> zipCode)) {
                    std::cout << "Invalid input format. Usage: FirstName LastName BirthYear ZipCode\n";
                    break;
                }
                std::string fullName = firstName + " " + lastName;
                int newId = mynet.numUsers(); // New user's ID is the current count.
                User* newUser = new User(newId, fullName, birthYear, zipCode, std::set<int>());
                mynet.addUser(newUser);
                std::cout << "User \"" << fullName << "\" added with ID " << newId << ".\n";
                break;
            }
            case 2: { // Add friend connection
                std::string name1, name2;
                std::cout << "Enter the first username (FirstName LastName): ";
                std::getline(std::cin, name1);
                std::cout << "Enter the second username (FirstName LastName): ";
                std::getline(std::cin, name2);
                int result = mynet.addConnection(name1, name2);
                if (result == -1) {
                    std::cout << "Error: One or both users do not exist.\n";
                } else {
                    std::cout << "Friend connection added between \"" << name1 << "\" and \"" << name2 << "\".\n";
                }
                break;
            }
            case 3: { // Delete friend connection
                std::cout << "Enter two usernames to delete as friends (FirstName LastName FirstName LastName): ";
                std::getline(std::cin, inLine);
                std::stringstream ssDelete(inLine);
                std::string firstName1, lastName1, firstName2, lastName2;
                if (!(ssDelete >> firstName1 >> lastName1 >> firstName2 >> lastName2)) {
                    std::cout << "Invalid input format.\n";
                    break;
                }
                std::string name1 = firstName1 + " " + lastName1;
                std::string name2 = firstName2 + " " + lastName2;
                int result = mynet.deleteConnection(name1, name2);
                if (result == -1) {
                    std::cout << "Error. The users are not friends or do not exist.\n";
                } else {
                    std::cout << "Friend connection deleted between \"" << name1 << "\" and \"" << name2 << "\".\n";
                }
                break;
            }
            case 4: { // Write to file
                std::string outputFilename;
                std::cout << "Enter filename to write user data to: ";
                std::getline(std::cin, inLine);
                std::stringstream ssWrite(inLine);
                if (!(ssWrite >> outputFilename)) {
                    std::cout << "Invalid input format. Usage: <filename>\n";
                    break;
                }
                mynet.writeUsers(outputFilename.c_str());
                std::cout << "Successfully wrote " << mynet.numUsers() << " user(s) to " << outputFilename << std::endl;
                break;
            }
            case 5: { // View recent posts for a user
                std::string username;
                int howMany;
                bool showOnlyPublic = false; // show only public posts.
                std::cout << "Enter the username (FirstName LastName): ";
                std::getline(std::cin, username);
                std::cout << "Enter the number of recent posts to display: ";
                std::cin >> howMany;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                User* user = mynet.uzr_from_name(username);
                
                int i = user->getId();
                
                std::string postsStr = mynet.getPostsString(i, howMany, showOnlyPublic);
                std::cout << "Recent posts for " << username << ":\n" << postsStr << "\n";
                break;
            }
            case 6: { // Exit
                std::cout << "Exiting program.\n";
                return 0;
            }
            default: {
                std::cout << "Invalid option. Exiting program.\n";
                return 0;
            }
        }
    }

    return 0;
}
