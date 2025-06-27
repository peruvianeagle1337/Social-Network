
#include <string>
#include <set>

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
#ifndef post_h
#define post_h

class Post {
protected:

    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;
    std::set<int> likedBy_;



public:
    Post()=default;
    Post(int messageId, int ownerId, std::string message, int likes) : messageId_(messageId),ownerId_(ownerId),message_(message),likes_(likes) {
    }


    std::string toString();
    int getMessageId();
    int getOwnerId();
    std::string getMessage();
    virtual int getLikes();

    void addLike(int userId) {
        // If user not in set, insert
        auto result = likedBy_.insert(userId);
        if (result.second) {
            // If successfully inserted, increment the old integer to keep them in sync
            likes_ = (int)likedBy_.size();
        }
    }
    void removeLike(int userId) {
        size_t erased = likedBy_.erase(userId);
        if (erased > 0) {
            likes_ = (int)likedBy_.size();
        }
    }
    bool hasLiked(int userId) const {
        return (likedBy_.find(userId) != likedBy_.end());
    }



    virtual std::string getAuthor();
    virtual bool getIsPublic();


};

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

class IncomingPost : public Post {
protected:
    std::string author_;
    bool isPublic_;

public:

    IncomingPost() = default;
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author) : Post(messageId, ownerId, message, likes), author_(author),isPublic_(isPublic) {
    }
    virtual ~IncomingPost() {}

    virtual std::string getAuthor() override;
    virtual bool getIsPublic() override;
    std::string toString();
    };


#endif
