// creativespacewidget.h
#ifndef CREATIVE_SPACE_WIDGET_H
#define CREATIVE_SPACE_WIDGET_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include "user.h"

class CreativeSpaceWidget : public QWidget {
    Q_OBJECT
public:
    explicit CreativeSpaceWidget(User* user, QWidget* parent = nullptr);
    QSize sizeHint() const override { return QSize(600, 400); } // default size

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    User* user_;
    bool drawing_;
    QPoint lastPoint_;
};

#endif // CREATIVE_SPACE_WIDGET_H
