#ifndef PLAYERACTORITEM_HH
#define PLAYERACTORITEM_HH

#include <QGraphicsPixmapItem>
#include <QObject>

/**
  * @file
  * @brief Defines a class that implements players graphical object drawing and moving.
  */

namespace Game {

/**
 * @brief PlayerActorItem is a class that implements player graphical object drawing and moving.
 *
 * PlayerActorItem is inherited from IQObject and QGraphicsPixmapItem.
 */

class PlayerActorItem: public QObject, public QGraphicsPixmapItem{

public:
    /**
     * @brief PlayerActorItem constructor
     * @param x is players initilial x coordinate
     * @param y is players initilial y coordinate
     * @param parent is a QGraphicsItem pointer that defaults to 0
     */
    PlayerActorItem(int x, int y, QGraphicsItem *parent = 0);
    virtual ~PlayerActorItem();
    /**
     * @brief move sets key pressed states to true
     * @param QKeyEvent pointer to pressed key
     */
    void move(QKeyEvent *event);
    /**
     * @brief stop sets key pressed states to false
     * @param event
     */
    void stop(QKeyEvent *event);
    /**
     * @brief width
     * @return width of QGraphicsPixmapItem
     */
    int width() const;
    /**
     * @brief height
     * @return height of QGraphicsPixmapItem
     */
    int height() const;    

private slots:
    void smoothMove();

private:
    bool isMoveKeysPressed() const;
    QTimer *movetimer_;
    int timestep_;
    int movedirection_;
    bool playermoving_;
    bool leftpressed_;
    bool rightpressed_;
    bool downpressed_;
    bool uppressed_;
};
} // namespace Game
#endif // PLAYERACTORITEM_HH
