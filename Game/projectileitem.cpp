#include "projectileitem.hh"
#include "config.hh"
#include "nysseactoritem.hh"

#include <QTimer>
#include <QtMath>
#include <QDebug>

namespace Game {

ProjectileItem::ProjectileItem(int x, int y, int direction, QGraphicsItem *parent): QObject(),
    QGraphicsPixmapItem(parent),
    movedistance_(0),
    destroyed_(false)
{
    setPixmap(PROJ_ACTOR_IMG);
    setRotation(direction-90);
    setOffset(this->pixmap().width(), -this->pixmap().height()/2);
    setPos(x, y);

    // connect a timer to move()
    QTimer *move_timer = new QTimer(this);
    connect(move_timer, &QTimer::timeout, this, &ProjectileItem::move);
    move_timer->start(30);
}

ProjectileItem::~ProjectileItem()
{

}

void ProjectileItem::move()
{
    invariant();
    double theta = rotation();
    double dy = BULLET_MOVEMENT * qSin(qDegreesToRadians(theta));
    double dx = BULLET_MOVEMENT * qCos(qDegreesToRadians(theta));
    // Collision detection of projectiles and busses
    QList<QGraphicsItem *> collidingitems = collidingItems();
    // check if the collision objects are nysses
    foreach (QGraphicsItem *item, collidingitems) {
        if (dynamic_cast<NysseActorItem*>(item)){
            this->destroy();
            emit destroyCollidingItemSignal(collidingitems);
            emit destroyProjectileSignal(this);
        }
    }
    if (movedistance_ >= 100){
        // Destroy object if gone too far
        movedistance_ = 0;
        this->destroy();
        emit destroyProjectileSignal(this);
        return;
    } else {
        setPos(x()+dx, y()+dy);
        movedistance_ += sqrt(dx*dx + dy*dy);
    }
}

void ProjectileItem::invariant() const
{
    Q_ASSERT(movedistance_ <= 100);
}

int ProjectileItem::width() const
{
    invariant();
    return this->pixmap().width();
}

int ProjectileItem::height() const
{
    invariant();
    return this->pixmap().height();
}

bool ProjectileItem::destroyed() const
{
    invariant();
    return destroyed_;
}

void ProjectileItem::destroy()
{
    invariant();
    destroyed_ = true;
}

} // namespace Game
