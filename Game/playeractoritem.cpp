#include "playeractoritem.hh"
#include "config.hh"

#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
namespace Game {

PlayerActorItem::PlayerActorItem(int x, int y, QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    movetimer_(new QTimer(this)),
    timestep_(25/PLAYER_MOVEMENT_SPEED),
    playermoving_(false),
    leftpressed_(false),
    rightpressed_(false),
    downpressed_(false),
    uppressed_(false)
{
    setPixmap(PLAYER_ACTOR_IMG);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);
    setPos(x, y);

    connect(movetimer_, &QTimer::timeout, this, &PlayerActorItem::smoothMove);
}

PlayerActorItem::~PlayerActorItem()
{

}

void PlayerActorItem::move(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) {
        playermoving_ = true;
        movetimer_->start(timestep_);

        switch (event->key()) {
        case Game::Controls::LEFT  : leftpressed_  = true; break;
        case Game::Controls::RIGHT : rightpressed_ = true; break;
        case Game::Controls::DOWN  : downpressed_  = true; break;
        case Game::Controls::UP    : uppressed_    = true; break;
        }
        smoothMove();   //Push player on move right after keypress (no time to wait timer timeout)
    }
}

void PlayerActorItem::stop(QKeyEvent *event)
{
    if (!event->isAutoRepeat()) {
        if(!isMoveKeysPressed()) {
            movetimer_->stop();
            playermoving_ = false;
        }
        switch (event->key()) {
        case Game::Controls::LEFT  : leftpressed_  = false; break;
        case Game::Controls::RIGHT : rightpressed_ = false; break;
        case Game::Controls::DOWN  : downpressed_  = false; break;
        case Game::Controls::UP    : uppressed_    = false; break;
        }
    }
}

void PlayerActorItem::smoothMove()
{
    auto rect = scene()->sceneRect();
    if (playermoving_) {
        // Diagonal movement
        if (leftpressed_ && downpressed_) {
            setRotation(-135);
            if (rect.contains(this->x()-0.7, this->y()+0.7+height())) {
                moveBy(-0.7, 0.7);
            }
        } else if (leftpressed_ && uppressed_) {
            setRotation(-45);
            if (rect.contains(this->x()-0.7, this->y()-0.7)) {
            moveBy(-0.7, -0.7);
            }
        } else if (rightpressed_ && downpressed_) {
            setRotation(135);
            if (rect.contains(this->x()+0.7+width(), this->y()+0.7+height())) {
            moveBy(0.7, 0.7);
            }
        } else if (rightpressed_ && uppressed_) {
            setRotation(45);
            if (rect.contains(this->x()+0.7+width(), this->y()-0.7)) {
                moveBy(0.7, -0.7);
            }
        // Horizontal and vertical movement
        } else if (leftpressed_) {
            setRotation(-90);
            if (rect.contains(this->x()-1, this->y())) {
                moveBy(-1, 0);
            }
        } else if (rightpressed_) {
            setRotation(90);
            if (rect.contains(this->x()+1+width(), this->y())) {
                moveBy(1, 0);
            }
        } else if (downpressed_) {
            setRotation(180);
            if (rect.contains(this->x(), this->y()+1+height())) {
                moveBy(0, 1);
            }
        } else if (uppressed_) {
            setRotation(0);
            if (rect.contains(this->x(), this->y()-1)) {
                moveBy(0, -1);
            }
        }
    }
}

bool PlayerActorItem::isMoveKeysPressed() const
{
    return leftpressed_ or rightpressed_ or downpressed_ or uppressed_;
}

int PlayerActorItem::width() const
{
    return pixmap().width();
}

int PlayerActorItem::height() const
{
    return pixmap().height();
}

} // namespace Game
