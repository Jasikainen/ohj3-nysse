#include "nysseactoritem.hh"
#include "config.hh"

namespace Game {


NysseActorItem::NysseActorItem(int x, int y, QGraphicsItem *parent):
    QGraphicsPixmapItem(parent)
{
    setPixmap(NYSSE_ACTOR_IMG);
    setTransformOriginPoint(this->pixmap().width()/2, this->pixmap().height()/2);
    setOffset(-this->pixmap().width()/2, -this->pixmap().height()/2);
    setPos(x, y);
}

NysseActorItem::~NysseActorItem(){

}

int NysseActorItem::width() const
{
    return this->pixmap().width();
}

int NysseActorItem::height() const
{
    return this->pixmap().height();
}

} // namespace Game
