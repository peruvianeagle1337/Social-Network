#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "user.h"
#include "network.h"
#include "post.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include "moodboardwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class PostWidget : public QWidget {
    Q_OBJECT
public:
    PostWidget(Post* post, int userId, QWidget* parent = nullptr);
    void updateUI();

signals:
    void likeToggled(Post* post);

private slots:
    void onLikeClicked();

private:
    Post* post_;
    int userId_;
    QLabel* textLabel_;
    QPushButton* likeButton_;
    QLabel* likesLabel_;
};





class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void myButtonClick();
    void getText();
    void display();


private slots:
    void on_addSticker_clicked();
    void on_friendTableWidget_cellClicked(int row, int column);
    void on_suggestionsTableWidget_cellClicked(int row, int /*column*/);
    void on_addFriendButton_clicked();
    void on_postButton_clicked();
    void on_backButton_clicked();
    void on_uploadProfile_clicked();
    void on_SaveBio_clicked();

  //  void on_OpenMoodboard_clicked();
    void handleOpenMoodboard();
    void uploadProfileSlot();
    void onLikeToggled(Post* post);
    void on_myButton_clicked();

private:
    Ui::MainWindow *ui;
    Network* network;
    User* loggedInUser;
    User* currentProfile;
    MoodboardWidget* mbw;
    bool mbwVisible;
    User* lastProfilePtr = nullptr;
    QWidget* postsWidget;
    QVBoxLayout* postsLayout;


};
#endif // MAINWINDOW_H
