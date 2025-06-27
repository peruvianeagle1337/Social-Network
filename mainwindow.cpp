#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QMainWindow>
#include <QLabel>
#include <QTableWidgetItem>
#include <QString>
#include <QMessageBox>
#include <set>
#include <vector>
#include <QTimer>
#include <QFileDialog>
#include <moodboardwidget.h>
#include <QDebug>
// Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , loggedInUser(nullptr)
    , currentProfile(nullptr)
    , mbw(nullptr)
    , mbwVisible(false)
{
    ui->setupUi(this);


    network = new Network();


    ui->login_2->show();
    ui->profile->hide();

    // Read posts and users from file.

    network->readUsers("D:/socialQT/socialnetwork/users.txt");
    network->readPosts("D:/socialQT/socialnetwork/posts.txt");
    network->readMoodboards("moodboards.txt");
    network->readProfilePics("profilepics.txt");
    network->readBios("D:/socialQT/socialnetwork/bios.txt");

    postsWidget = new QWidget;
    postsLayout = new QVBoxLayout(postsWidget);
    postsWidget->setLayout(postsLayout);

    ui->postsScrollArea->setWidget(postsWidget);
    ui->postsScrollArea->setWidgetResizable(true);

    ui->postsScrollArea->setStyleSheet("QScrollArea { background: transparent; }");
    postsWidget->setStyleSheet("");

    QString styleSheet = R"(
    QMainWindow {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #00BFFF, stop:1 #003366);
    }
    QPushButton {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0E0E0, stop:1 #A0A0A0);
        border: 1px solid #808080;
        border-radius: 5px;
        padding: 5px;
        color: #000000;
    }
    QPushButton:hover {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F0F0F0, stop:1 #B0B0B0);
    }
    QComboBox {
        background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0E0E0, stop:1 #A0A0A0);
        border: 1px solid #808080;
        border-radius: 5px;
        padding: 5px;
        color: #000000;
    }
    QLabel {
        color: #00FFFF;
        font-family: "Courier New", monospace;
        font-size: 12px;
        background: rgba(255, 255, 255, 0.1);
        padding: 2px;
    }
    QTextEdit {
        background: rgba(255, 255, 255, 0.8);
        border: 1px solid #A0A0A0;
        border-radius: 5px;
        padding: 5px;
        color: #000000;
    }
)";
    this->setStyleSheet(styleSheet);


    connect(ui->myButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_myButton_clicked);


    connect(ui->suggestionsTableWidget,
            &QTableWidget::cellClicked,
            this,
            &MainWindow::on_suggestionsTableWidget_cellClicked);


    connect(ui->backButton, &QPushButton::clicked,
            this, &MainWindow::on_backButton_clicked);

    connect(ui->friendTableWidget, &QTableWidget::cellClicked,
            this, &MainWindow::on_friendTableWidget_cellClicked);

    connect(ui->addFriendButton, &QPushButton::clicked,
            this, &MainWindow::on_addFriendButton_clicked);

    connect(ui->OpenMoodboard, &QPushButton::clicked,
            this, &MainWindow::handleOpenMoodboard);

    connect(ui->uploadProfile, &QPushButton::clicked,
            this, &MainWindow::uploadProfileSlot);

    connect(ui->SaveBio,&QPushButton::clicked, this, &MainWindow::on_SaveBio_clicked );


}

// Destructor
MainWindow::~MainWindow()
{
    // Save posts and users on exit.

    network->writeUsers("D:/socialQT/socialnetwork/users.txt");
    network->writePosts("D:/socialQT/socialnetwork/posts.txt");
    network->writeMoodboards("moodboards.txt");
    network->writeProfilePics("profilepics.txt");
    network->writeBios("D:/socialQT/socialnetwork/bios.txt");
    delete network;
    delete ui;
}


PostWidget::PostWidget(Post* post, int userId, QWidget* parent)
    : QWidget(parent), post_(post), userId_(userId) {

 //  std::cout << "PostWidget constructor called for post: " << post->toString() << std::endl;
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    textLabel_ = new QLabel(this);
    likesLabel_ = new QLabel(this);
    likeButton_ = new QPushButton("Like", this);

    layout->addWidget(textLabel_);
    layout->addWidget(likesLabel_);
    layout->addWidget(likeButton_);
    layout->addStretch();
    this->setAutoFillBackground(true);
   // this->setStyleSheet("background-color: #404040;");
    this->setStyleSheet(R"(
        QWidget {
            background-color: #404040; /* Dark gray */
        }
        QLabel {
            color: #00008B; /* Dark blue text */
            background-color: transparent;
            padding: 2px;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0E0E0, stop:1 #A0A0A0);
            border: 1px solid #808080;
            border-radius: 5px;
            padding: 5px;
            color: #000000;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F0F0F0, stop:1 #B0B0B0);
        }
    )");
/*

 * R"(
        QWidget {
            background-color: #404040;
        }
        QLabel {
            color: #00008B;
            background-color: transparent;
            padding: 2px;
        }
        QPushButton {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #E0E0E0, stop:1 #A0A0A0);
            border: 1px solid #808080;
            border-radius: 5px;
            padding: 5px;
            color: #000000;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F0F0F0, stop:1 #B0B0B0);
        }
    )");
 * */

    updateUI();

    connect(likeButton_, &QPushButton::clicked, this, &PostWidget::onLikeClicked);
}
void MainWindow::display()
{
    if (!currentProfile)
        return;


    if (currentProfile != lastProfilePtr) {
        ui->friend_status->setText("");
        lastProfilePtr = currentProfile;
    }

    ui->login_2->hide();
    ui->profile->show();
    ui->bioLabel->setText(QString::fromStdString(currentProfile->getBiography()));

    if (currentProfile == loggedInUser) {
        ui->uploadProfile->show();
        ui->SaveBio->show();
        ui->BioTextEdit->show();
        ui->addFriendButton->hide();
    } else {
        ui->uploadProfile->hide();
        ui->BioTextEdit->hide();
        ui->SaveBio->hide();
        if(loggedInUser->getFriends().find(currentProfile->getId()) == loggedInUser->getFriends().end()){
              ui->addFriendButton->show();
        }

    }

    // Display the profile pic in the label
    std::string picPath = currentProfile->getProfilePicture();
    if (!picPath.empty()) {
        QPixmap pix(QString::fromStdString(picPath));
        if (!pix.isNull()) {
            ui->profilePicLabel->setPixmap(
                pix.scaled(ui->profilePicLabel->size(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation));
        } else {

            ui->profilePicLabel->clear();
        }
    } else {

        ui->profilePicLabel->clear();
    }

    if (currentProfile->getName() == loggedInUser->getName()) {
        ui->profileTitleLabel->setText("My Profile");
        ui->backButton->hide();


        int score = 0;
        std::vector<int> suggestions = network->suggestFriends(network->getId(loggedInUser->getName()), score);
        ui->suggestionsTableWidget->setRowCount(static_cast<int>(suggestions.size()));
        ui->suggestionsTableWidget->setColumnCount(1);
        int row = 0;
        for (int suggestionId : suggestions) {
            User* suggestionUser = network->getUser(suggestionId);
            if (suggestionUser) {
                QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(suggestionUser->getName()));
                ui->suggestionsTableWidget->setItem(row, 0, item);
            }
            ++row;
        }
        ui->suggestionsTableWidget->show();
    } else {
        ui->profileTitleLabel->setText(QString::fromStdString(currentProfile->getName()) + "'s Profile");
        ui->backButton->show();
        ui->suggestionsTableWidget->hide();
    }


    std::set<int> friendIDs = currentProfile->getFriends();
    ui->friendTableWidget->setRowCount(static_cast<int>(friendIDs.size()));
    ui->friendTableWidget->setColumnCount(1);
    int row = 0;
    for (int friendId : friendIDs) {
        User* friendUser = network->getUser(friendId);
        QString qfriendName = friendUser ? QString::fromStdString(friendUser->getName()) : "Unknown";
        QTableWidgetItem* item = new QTableWidgetItem(qfriendName);
        ui->friendTableWidget->setItem(row, 0, item);
        ++row;
    }

    // Clear existing posts
    while (postsLayout->count() > 0) {
        QLayoutItem* item = postsLayout->takeAt(0);
        delete item->widget();
        delete item;
    }

    std::vector<Post*> posts = currentProfile->getPosts();
     qDebug() << "Displaying" << posts.size() << "posts for user:" << currentProfile->getName().c_str();
    for (Post* post : posts) {
        qDebug() << "Creating PostWidget for post:" << post->toString().c_str();
        PostWidget* postWidget = new PostWidget(post, loggedInUser->getId(), this);
        connect(postWidget, &PostWidget::likeToggled, this, &MainWindow::onLikeToggled);
        postsLayout->insertWidget(0, postWidget); // Insert at top instead of addWidget
    }
     postsLayout->addStretch();
}


void MainWindow::onLikeToggled(Post* post) {
    PostWidget* postWidget = qobject_cast<PostWidget*>(sender());
    if (postWidget) {
        if (post->hasLiked(loggedInUser->getId())) {
            post->removeLike(loggedInUser->getId());
        } else {
            post->addLike(loggedInUser->getId());
        }
        postWidget->updateUI();
        network->writePosts("D:/socialQT/socialnetwork/posts.txt");
    }
}



void MainWindow::on_postButton_clicked()
{
    QString qContent = ui->postTextEdit->toPlainText().trimmed();
     qDebug() << "Post button clicked, content:" << qContent;
    if(qContent.isEmpty()){
        QMessageBox::warning(this, "Empty Post", "Post content cannot be empty.");
        return;
    }
    std::string content = qContent.toStdString();

    if(currentProfile->getName() == loggedInUser->getName()){
        network->addPost(network->getId(currentProfile->getName()),
                         content,
                         0,              // starting likes
                         false,          // not an incoming post
                         currentProfile->getName(),
                         true);          // public post
    } else {
        network->addPost(network->getId(currentProfile->getName()),
                         content,
                         0,
                         true,           // is an incoming post
                         loggedInUser->getName(),
                         true);          // public post
    }

    network->writePosts("D:/socialQT/socialnetwork/posts.txt");

    ui->postTextEdit->clear();
    display();
}


void MainWindow::on_friendTableWidget_cellClicked(int row, int /*column*/)
{
    QTableWidgetItem* item = ui->friendTableWidget->item(row, 0);
    if (item) {
        std::string friendName = item->text().toStdString();
        User* friendUser = network->uzr_from_name(friendName);
        if (friendUser) {
            currentProfile = friendUser;
            if (mbw && mbwVisible) {
                mbw->hide();
                mbwVisible = false;
                ui->OpenMoodboard->setText("Show Moodboard");
            }
            display();
        }
    }
}

void MainWindow::on_addFriendButton_clicked()
{

    bool suggestionMode = (currentProfile->getName() == loggedInUser->getName());
    std::string targetName;

    if (suggestionMode) {

        QTableWidgetItem* item = ui->suggestionsTableWidget->currentItem();
        if (!item) {
            ui->friend_status->setText("Please select a friend suggestion to add.");
            return;
        }
        targetName = item->text().toStdString();
    } else {

        targetName = currentProfile->getName();
    }

    int result = network->addConnection(loggedInUser->getName(), targetName);
    if (result == 0) {
        ui->friend_status->setText(suggestionMode ? "Friend suggestion added successfully."
                                                  : "Friend added successfully.");
    } else if (result == 1) {
        ui->friend_status->setText("Already friends.");
    } else {
        ui->friend_status->setText(suggestionMode ? "Unable to add friend suggestion."
                                                  : "Could not add friend.");
    }

    network->writeUsers("D:/socialQT/socialnetwork/users.txt");
    display();
}





void MainWindow::on_suggestionsTableWidget_cellClicked(int row, int /*column*/)
{
    QTableWidgetItem* item = ui->suggestionsTableWidget->item(row, 0);
    if(item){
        std::string suggestionName = item->text().toStdString();
        int result = network->addConnection(loggedInUser->getName(), suggestionName);
        if(result == 0){
            ui->friend_status->setText("Friend suggestion added successfully.");
        } else {
            ui->friend_status->setText("Unable to add friend suggestion.");
        }
        network->writeUsers("D:/socialQT/socialnetwork/users.txt");
        display();
    }
}

void MainWindow::on_backButton_clicked()
{
    currentProfile = loggedInUser;
    if (mbw && mbwVisible) {
        mbw->hide();
        mbwVisible = false;
        ui->OpenMoodboard->setText("Show Moodboard");
    }
    display();
}






void MainWindow::on_uploadProfile_clicked()
{
    if (!loggedInUser) return;
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Profile Picture",
        "",
        "Images (*.png *.jpg *.bmp)"
        );
    if (!filePath.isEmpty()) {
        loggedInUser->setProfilePicture(filePath.toStdString());
    }
}


void MainWindow::on_SaveBio_clicked()
{
    if (!loggedInUser) return;
    QString bio = ui->BioTextEdit->toPlainText();
    loggedInUser->setBiography(bio.toStdString());
    display();
}



void MainWindow::handleOpenMoodboard()
{
    if (!currentProfile) return;
    if (!mbw) {
        mbw = new MoodboardWidget(currentProfile, this);
        mbw->setWindowTitle("Moodboard");
        mbw->resize(600, 400);
    }
    if (mbwVisible) {
        mbw->hide();
        mbwVisible = false;
        ui->OpenMoodboard->setText("Show Moodboard");
    } else {
        mbw->setUser(currentProfile, currentProfile == loggedInUser);
        mbw->show();
        mbw->raise();
        mbw->activateWindow();
        mbwVisible = true;
        ui->OpenMoodboard->setText("Hide Moodboard");
    }
}


void MainWindow::uploadProfileSlot()
{
    if (!loggedInUser) {
        qDebug() << "No user logged in, cannot upload profile picture.";
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Profile Picture",
        "",
        "Images (*.png *.jpg *.bmp *.jpeg)"
        );
    if (!filePath.isEmpty()) {

        loggedInUser->setProfilePicture(filePath.toStdString());


        QPixmap pix(filePath);
        if (!pix.isNull()) {

            ui->profilePicLabel->setPixmap(
                pix.scaled(ui->profilePicLabel->size(),
                           Qt::KeepAspectRatio,
                           Qt::SmoothTransformation));
            ui->profilePicLabel->setScaledContents(false);
        }
    }
}

void MainWindow::on_addSticker_clicked()
{

}




void PostWidget::updateUI() {
    textLabel_->setText(QString::fromStdString(post_->toString()));
    likesLabel_->setText(QString::number(post_->getLikes()) + " likes");
    if (post_->hasLiked(userId_)) {
        likeButton_->setText("Unlike");
    } else {
        likeButton_->setText("Like");
    }
}

void PostWidget::onLikeClicked() {
    emit likeToggled(post_);
}




void MainWindow::on_myButton_clicked()
{
    QString qtext = ui->login->toPlainText();
    std::string text = qtext.toStdString();


    if (network->uzr_from_name(text) != nullptr) {
        loggedInUser = network->uzr_from_name(text);
        currentProfile = loggedInUser;
        display();
    } else {
        ui->label->setText("Invalid user, please try again.");
    }
}

