// creativespace.h
#ifndef CREATIVE_SPACE_H
#define CREATIVE_SPACE_H

#include <QImage>
#include <QPainter>
#include <vector>

struct DrawAction {
    int userId;   // which user performed the draw
    int startX;
    int startY;
    int endX;
    int endY;
    // you could add brush color, thickness, etc.
};

class CreativeSpace {
private:
    QImage canvas_;
    std::vector<DrawAction> history_;

public:
    CreativeSpace(int width, int height)
        : canvas_(width, height, QImage::Format_ARGB32)
    {
        // Fill with white
        canvas_.fill(Qt::white);
    }

    // Called when a user draws a line from (startX,startY) to (endX,endY)
    void drawOnCanvas(int userId, const DrawAction &action) {
        // Save to history
        history_.push_back(action);

        // Draw on QImage
        QPainter painter(&canvas_);
        painter.setPen(Qt::black); // or vary by user
        painter.drawLine(action.startX, action.startY, action.endX, action.endY);
        painter.end();
    }

    // Owner can clear the entire canvas
    void clearCanvas() {
        canvas_.fill(Qt::white);
        history_.clear();
    }

    const QImage& getCanvas() const {
        return canvas_;
    }

    const std::vector<DrawAction>& getHistory() const {
        return history_;
    }
};

#endif // CREATIVE_SPACE_H
