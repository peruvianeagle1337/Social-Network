// moodboardwidget.h
#ifndef MOODBOARDWIDGET_H
#define MOODBOARDWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QGraphicsView>
#include "user.h"
#include "clickablegraphicscene.h"

class MoodboardWidget : public QWidget {
    Q_OBJECT
public:
    explicit MoodboardWidget(User* user, QWidget* parent = nullptr);
    static QString getStickerImagePath(StickerType type);
    void setUser(User* user, bool isOwner_);
private slots:
    void onAddStickerClicked();
    void onSceneClicked(const QPointF &scenePos);
    void onClearMoodboard();


private:
    User* user_;
    bool isOwner_;
    ClickableGraphicsScene* scene_;
    QGraphicsView* view_;

    QComboBox* comboStickerType_;
    QPushButton* addStickerButton_;
    QPushButton* clearButton_;
    StickerType currentStickerType_;
    bool readyToPlaceSticker_;
};

#endif // MOODBOARDWIDGET_H
