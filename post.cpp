
#include "post.h"
#include <string>
#include "network.h"
/*

Post
+ Post()
+ Post(messageId: int, ownerId: int, message: string, likes: int)
+ toString(): string
+ getMessageId(): int
+ getOwnerId(): int
+ getMessage(): string
+ getLikes(): int
+ getAuthor(): string
+ getIsPublic(): bool
- messageId_: int
- ownerId_: int
- message_: string
- likes_: int


*/

/*

The toString() should return a string ”[message_] Liked by [likes_] people.”
where [message_] and [likes_] are replaced by their respective values.

*/

std::string Post::toString() {
    
    return getMessage() + " Liked by " + std::to_string(getLikes()) + " people.";
}
int Post::getMessageId(){
    return messageId_;
}

int Post::getOwnerId(){
    return ownerId_;
}


std::string Post::getMessage(){
    return message_;
}

int Post::getLikes(){
    return (int)likedBy_.size();
}

std::string Post::getAuthor(){
    return "";
}

bool Post::getIsPublic(){
    return true;
}

/*

IncomingPost
+ IncomingPost()
+ IncomingPost(messageId: int, ownerId: int, message: string,
likes: int, isPublic: bool, author: string)
+ toString(): string
+ getAuthor(): string
+ getIsPublic(): bool
- author_: string
- isPublic_: bool

*/

bool IncomingPost::getIsPublic() {
    return isPublic_;
}

std::string IncomingPost::getAuthor() {
    return author_;
}

std::string IncomingPost::toString() {
   
    
    std::string baseStr = Post::toString();
    
    
    std::string prefix;
    if (getIsPublic()) {
        prefix = getAuthor() + " wrote:";  // e.g., "Lillie Cain wrote:"
    } else {
        prefix = getAuthor() + " wrote(private):";  // e.g., "Lillie Cain wrote(private):"
    }
    
    return prefix + " " + baseStr;
}

/*

toString() should return a string ”[author_] wrote[private]: [toString]” where
[author_] is the value of author_, [toString] is the value obtained by calling the
Post toString method, and [private] is the empty string if isPublic_ is true, and
” (private)” if isPublic_ is false

*/
