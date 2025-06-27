// moodboard.h
#ifndef MOODBOARD_H
#define MOODBOARD_H

#include <vector>
#include <string>
#include <QDateTime> // or use <ctime>, etc.

enum class StickerType {
    Star,
    HappyFace,
    SadFace,
    Heart,
    Ghost,
    Lion,
    Mr_One,
    Mr_Two,
    Mr_Three,
    Mr_Four,
    Kirby,
    Duck,
    SadStar


};
struct Sticker {
    int stickerId;
    std::string imagePath; // The local path or URL for the sticker image
    StickerType stickerType;
    int x;
    int y;
    QDateTime timestamp;
};

class Moodboard {
private:
    std::vector<Sticker> stickers_;

public:
    Moodboard() = default;

    void addSticker(const Sticker& s) {
        stickers_.push_back(s);
    }

    void removeSticker(int stickerId) {
        stickers_.erase(std::remove_if(stickers_.begin(),
                                       stickers_.end(),
                                       [=](const Sticker &stk) {
                                           return (stk.stickerId == stickerId);
                                       }),
                        stickers_.end());
    }

    const std::vector<Sticker>& getStickers() const {
        return stickers_;
    }

    void clearStickers() { stickers_.clear(); }
};

#endif // MOODBOARD_H
