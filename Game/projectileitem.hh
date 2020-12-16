#ifndef PROJECTILEITEM_HH
#define PROJECTILEITEM_HH

#include <QGraphicsPixmapItem>
#include <QObject>

/**
  * @file
  * @brief Defines a class that implements shooted projectile graphical object drawing and moving.
  */

namespace Game {

class ProjectileItem: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    /**
     * @brief ProjectileItem is actoritem that is projectile shot by player
     * @param x Sets the location on map
     * @param y Sets the location on map
     * @param direction is the direction as degrees
     */
    ProjectileItem(int x, int y, int direction, QGraphicsItem *parent = 0);
    virtual ~ProjectileItem();
    /**
     * @brief width is used to tell width of actoritem
     * @return width of the QPixmap item
     */
    int width() const;
    /**
     * @brief height is used to tell height of actoritem
     * @return height of the QPixmap item
     */
    int height() const;
    /**
     * @brief destroyed tells if projectiles state is destroyed
     * @return true if projectile is to be removed from game
     */
    bool destroyed() const;
    /**
     * @brief destroy changes the value of objects state
     */
    void destroy();

public slots:

signals:
    /**
     * @brief destroySignal is emited to gamemainwindow to delete projectile
     * @param item projectile to be deleted
     */
    void destroyProjectileSignal(ProjectileItem *item);
    /**
     * @brief collidingItems is emited to gamemainwindow to delete
     * @param collidingitems
     * @return
     */
    QList<QGraphicsItem*> destroyCollidingItemSignal(QList<QGraphicsItem*> items);
private slots:
    /**
     * @brief move moves the projectile in the map until destroyed
     */
    void move();
private:
    int movedistance_;
    bool destroyed_;
    /**
     * @brief invariant is used to check if projectile is in given
     * range from starting point
     */
    void invariant() const;
};
} // namespace Game

#endif // PROJECTILEITEM_HH
