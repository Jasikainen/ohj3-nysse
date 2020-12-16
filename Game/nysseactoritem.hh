#ifndef NYSSEACTORITEM_HH
#define NYSSEACTORITEM_HH

#include <QGraphicsPixmapItem>

/**
  * @file
  * @brief Defines a class that implements pixmap drawing for Nysses.
  */

namespace Game {

/**
 * @brief NysseActorItem is a class that implements Nysses graphical object drawing and moving.
 *
 * NysseActorItem is inherited from QGraphicsPixmapItem.
 */

class NysseActorItem: public QGraphicsPixmapItem
{
public:
    /**
     * @brief NysseActorItem constructor
     * @param x is Nysses initilial x coordinate
     * @param y is Nysses initilial y coordinate
     * @param parent is a QGraphicsItem pointer that defaults to 0
     */
    NysseActorItem(int x, int y, QGraphicsItem *parent = 0);
    virtual ~NysseActorItem();
    /**
     * @brief width
     * @return width of nysse pixmap
     */
    int width() const;
    /**
     * @brief height
     * @return height of nysse pixmap
     */
    int height() const;
};
} // namespace Game
#endif // NYSSEACTORITEM_HH
