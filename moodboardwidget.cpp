// moodboardwidget.cpp
#include "moodboardwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QDateTime>
#include <cstdlib> // for rand()

MoodboardWidget::MoodboardWidget(User* user, QWidget* parent)
    : QWidget(parent),
    user_(user),
    isOwner_(false),
    scene_(new ClickableGraphicsScene(this)),
    view_(new QGraphicsView(scene_, this)),
    comboStickerType_(new QComboBox(this)),
    addStickerButton_(new QPushButton("Add Sticker", this)),
    clearButton_(new QPushButton("Clear Moodboard", this)),
    readyToPlaceSticker_(false)

{

    comboStickerType_->addItem("Star",      (int)StickerType::Star);
    comboStickerType_->addItem("HappyFace", (int)StickerType::HappyFace);
    comboStickerType_->addItem("SadFace",   (int)StickerType::SadFace);
    comboStickerType_->addItem("Heart",     (int)StickerType::Heart);
    comboStickerType_->addItem("Ghost",     (int)StickerType::Ghost);
    comboStickerType_->addItem("Lion",     (int)StickerType::Lion);
    comboStickerType_->addItem("Mr One",     (int)StickerType::Mr_One);
    comboStickerType_->addItem("Mr Two",     (int)StickerType::Mr_Two);
    comboStickerType_->addItem("Mr Two",     (int)StickerType::Mr_Three);
    comboStickerType_->addItem("Mr Four",     (int)StickerType::Mr_Four);
    comboStickerType_->addItem("Kirby",     (int)StickerType::Kirby);
    comboStickerType_->addItem("Duck",     (int)StickerType::Duck);
    comboStickerType_->addItem("Sad Star",    (int)StickerType::SadStar);


    // Layout
    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addWidget(comboStickerType_);
    topLayout->addWidget(addStickerButton_);
    topLayout->addWidget(clearButton_); // Add the clear button
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(view_);

    setLayout(mainLayout);


    this->setStyleSheet(R"(
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #C0C0C0, stop:1 #808080);
    border: 2px solid #A0A0A0;
    border-radius: 10px;
    box-shadow: 5px 5px 10px #00000050;
)");


    // Connect signals
    connect(addStickerButton_, &QPushButton::clicked,
            this, &MoodboardWidget::onAddStickerClicked);
    connect(scene_, &ClickableGraphicsScene::sceneClicked,
            this, &MoodboardWidget::onSceneClicked);
    connect(clearButton_, &QPushButton::clicked, this, &MoodboardWidget::onClearMoodboard);

    // Render existing stickers from the user’s moodboard
    if (user_) {
        const auto& stickers = user_->getMoodboard().getStickers();
        for (auto& s : stickers) {

            QPixmap pix(QString::fromStdString(s.imagePath));
            if (pix.isNull()) {

                continue;
            }
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix);
            item->setPos(s.x, s.y);
            scene_->addItem(item);
        }
    }
}
void MoodboardWidget::setUser(User* user, bool isOwner)
{
    user_ = user;
    isOwner_ = isOwner;
    scene_->clear();
    clearButton_->setVisible(isOwner_);
    if (user_) {
        const auto& stickers = user_->getMoodboard().getStickers();
        for (const auto& s : stickers) {
            QPixmap pix(QString::fromStdString(s.imagePath));
            if (!pix.isNull()) {
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pix);
                item->setPos(s.x, s.y);
                scene_->addItem(item);
            }
        }
    }
}
void MoodboardWidget::onAddStickerClicked()
{

    if (!user_) return;
    int typeInt = comboStickerType_->currentData().toInt();
    currentStickerType_ = (StickerType)typeInt;
    readyToPlaceSticker_ = true;
}

QString MoodboardWidget::getStickerImagePath(StickerType type) {
    switch (type) {
    case StickerType::Star:
        return ":/images/star1.JPG";
    case StickerType::HappyFace:
        return ":/images/happyface.JPG";
    case StickerType::SadFace:
        return ":/images/sadface.JPG";
    case StickerType::Heart:
        return ":/images/heart1.JPG";
    case StickerType::Ghost:
        return ":/images/ghost1.JPG";
    case StickerType::Kirby:
        return ":/images/kirby.JPG";
    case StickerType::Lion:
        return ":/images/lion.JPG";
    case StickerType::Duck:
        return ":/images/duck.JPG";
    case StickerType::Mr_One:
        return ":/images/man1.JPG";
    case StickerType::Mr_Two:
        return ":/images/man2.JPG";
    case StickerType::Mr_Three:
        return ":/images/man3.JPG";
    case StickerType::Mr_Four:
        return ":/images/man4.JPG";
    case StickerType::SadStar:
        return ":/images/sadstar.JPG";
    default:
        return ":/images/default.JPG";
    }
}

void MoodboardWidget::onSceneClicked(const QPointF &scenePos)
{
    if (!user_ || !readyToPlaceSticker_) return;

    Sticker newSticker;
    newSticker.stickerId   = rand() % 100000;
    newSticker.stickerType = currentStickerType_;
    newSticker.x           = (int)scenePos.x();
    newSticker.y           = (int)scenePos.y();
    newSticker.timestamp   = QDateTime::currentDateTime();

    // Store the resource path in imagePath
    QString path = getStickerImagePath(newSticker.stickerType);
    newSticker.imagePath = path.toStdString();

    user_->getMoodboard().addSticker(newSticker);

    // Visualize
    QPixmap pix(path);
    if (pix.isNull()) {
        qDebug() << "Failed to load pixmap from path:" << path;
    }
    QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pix);
    pixItem->setPos(newSticker.x, newSticker.y);
    scene_->addItem(pixItem);

    readyToPlaceSticker_ = false;
}

void MoodboardWidget::onClearMoodboard()
{
    if (!user_ || !isOwner_) return;
    user_->getMoodboard().clearStickers(); // Clear the moodboard's stickers
    scene_->clear();
}
/*
 *

void MoodboardWidget::onSceneClicked(const QPointF &scenePos)
{
      qDebug() << "[MoodboardWidget] onSceneClicked at" << scenePos;
    // Only place a new sticker if user clicked "Add Sticker"
    if (!user_ || !readyToPlaceSticker_) return;

    // Create a new Sticker
    Sticker newSticker;
    newSticker.stickerId    = rand() % 100000; // or use a robust ID generator
    newSticker.stickerType  = currentStickerType_;
    newSticker.x            = (int)scenePos.x();
    newSticker.y            = (int)scenePos.y();
    newSticker.timestamp    = QDateTime::currentDateTime();

    // (Optionally set newSticker.imagePath here if you have an icon)
    newSticker.imagePath    = "";

    // Add to user’s moodboard
    user_->getMoodboard().addSticker(newSticker);

    // Visualize it
    // Example: draw a green ellipse

         QGraphicsEllipseItem* it = new QGraphicsEllipseItem(newSticker.x, newSticker.y, 20, 20);
    it->setBrush(Qt::green);
    scene_->addItem(it);



    QString path = getStickerImagePath(newSticker.stickerType);
    QPixmap pix(path);
    if (pix.isNull()) {
        qDebug() << "Failed to load pixmap from path:" << path;
        // Possibly fallback to an ellipse or a default image
        // e.g., pix = QPixmap(":/images/default.png");
    }
    QGraphicsPixmapItem* pixItem = new QGraphicsPixmapItem(pix);
    pixItem->setPos(newSticker.x, newSticker.y);
    scene_->addItem(pixItem);

    // Reset
    readyToPlaceSticker_ = false;
}
*/

