// clickablegraphicscene.h
#ifndef CLICKABLEGRAPHICSSCENE_H
#define CLICKABLEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class ClickableGraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit ClickableGraphicsScene(QObject* parent = nullptr)
        : QGraphicsScene(parent) {}

signals:
    void sceneClicked(const QPointF &pos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit sceneClicked(event->scenePos());
        }
        QGraphicsScene::mousePressEvent(event);
    }
};

#endif // CLICKABLEGRAPHICSSCENE_H
