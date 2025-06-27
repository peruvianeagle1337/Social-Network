// creativespacewidget.cpp
#include "creativespacewidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

CreativeSpaceWidget::CreativeSpaceWidget(User* user, QWidget* parent)
    : QWidget(parent),
    user_(user),
    drawing_(false)
{
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setMouseTracking(true);
}

void CreativeSpaceWidget::paintEvent(QPaintEvent* /*event*/)
{
    if (!user_) return;
    // Retrieve the current QImage from the user's CreativeSpace
    const QImage& canvasImage = user_->getCreativeSpace().getCanvas();

    // Draw it onto this widget
    QPainter painter(this);
    painter.drawImage(0, 0, canvasImage);
}

void CreativeSpaceWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        drawing_ = true;
        lastPoint_ = event->pos();
    }
}

void CreativeSpaceWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (drawing_) {
        // We consider each mouse move as a small line from lastPoint_ to event->pos()
        DrawAction action;
        action.userId  = user_ ? user_->getId() : -1;
        action.startX  = lastPoint_.x();
        action.startY  = lastPoint_.y();
        action.endX    = event->pos().x();
        action.endY    = event->pos().y();
        // if you had color or brush size, add them here

        user_->getCreativeSpace().drawOnCanvas(action.userId, action);

        lastPoint_ = event->pos();
        update(); // triggers paintEvent
    }
}

void CreativeSpaceWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        drawing_ = false;
    }
}
