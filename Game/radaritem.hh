#ifndef RADARITEM_HH
#define RADARITEM_HH

#include <QLabel>
#include <QMovie>

#include <interfaces/iactor.hh>

/**
  * @file
  * @brief Defines a class that implements radar graphical object drawing.
  */

namespace Game {

/**
 * @brief RadarItem is a class that implements radar graphical object drawing and moving.
 *
 * RadarItem is inherited from Interface::IActor interface and QLabel.
 */

class RadarItem : public Interface::IActor, public QLabel
{
public:
    RadarItem();
    virtual ~RadarItem();
    /**
     * @brief spawnRadar displays radar animation 1s
     */
    void spawnRadar();
    /**
     * @brief addedToScene must be called after RadarItem is added to QGraphicsScene
     */
    void addedToScene();
    /**
     * @brief isAddedToScene
     * @return true if addedToScene is called
     */
    bool isAddedToScene();

    // IActor interface

    /**
     * @copydoc Interface::IActor::giveLocation()
     */
    Interface::Location giveLocation() const override;
    /**
     * @brief move moves radar to given location and calls its animation
     * @param loc is Interface::Location object
     */
    void move(Interface::Location loc) override;
    /**
     * @copydoc Interface::IActor::isRemoved()
     */
    bool isRemoved() const override;
    /**
     * @copydoc Interface::IActor::remove()
     */
    void remove() override;

private slots:
    void selfDestruct();
private:
    QMovie *radarMovie_;
    QTimer *showTimer_;
    Interface::Location loc_;
    bool removed_;
    bool isinscene_;

};
} // namespace Game
#endif // RADARITEM_HH
