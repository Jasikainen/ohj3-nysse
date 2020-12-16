#ifndef GAMEMAINWINDOW_HH
#define GAMEMAINWINDOW_HH

#include "digitalclock.hh"
#include "nysseactoritem.hh"
#include "player.hh"
#include "playeractoritem.hh"
#include "projectileitem.hh"
#include "radaritem.hh"
#include "statistics.hh"

#include <interfaces/iactor.hh>

#include <QMainWindow>
#include <QMediaPlayer>

/**
  * @file
  * @brief Defines a class that implements game graphical interface.
  */

namespace Ui {
class GameMainWindow;
}

/**
 * @brief GameMainWindow is a class that implements game graphical interface.
 *
 * GameMainWindow is inherited from QMainWindow.
 * GameMainWindow handles drawing of all graphical objects of the game.
 */

namespace Game {

class GameMainWindow: public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief GameMainWindow constructor
     * @param parent is a QWidget pointer that defaults to 0
     */
    explicit GameMainWindow(QWidget *parent = 0);
    virtual ~GameMainWindow();

    /**
     * @brief setTick sets tick rate for gamewindow updating
     * @param t timeinterval as ms
     */
    void setTick(int t);
    /**
     * @brief addStop
     * @param locX location in sceme
     * @param locY location in sceme
     * @param type represents the color
     */
    void addStop(int locX, int locY, int type = 0);
    /**
     * @brief updateCoords updates coordinates of wanted
     * @param nX
     * @param nY
     */
    void updateCoords(int nX, int nY);
    /**
     * @brief setPicture sets background to QGraphicsScene
     * @param img QImage of wanted map
     */
    void setPicture(QImage &img);
    /**
     * @brief addNysse adds nysse element to the game.
     * @pre  Nysse pointer exists
     * @return -
     * @post Exception guarantee: nothrow.
     */
    void addNysse(int locX, int locY, std::shared_ptr<Interface::IActor> newnysse = nullptr);
    /**
     * @brief updateNysseItem updates the coordinates of wanted nysse
     * @param locX new location in x direction
     * @param locY new location in x direction
     * @param updatenysse
     */
    void updateNysseItem(int locX, int locY, std::shared_ptr<Interface::IActor> updatednysse);
    /**
     * @brief removeNysseItem removes Nysse from game
     * @param removenysse the actor to be removed
     */
    void removeNysseItem(std::shared_ptr<Interface::IActor> removenysse);
    /**
     * @brief setGameClock sets clock to the digital clock in UI
     * @param time current time
     */
    void setGameClock(QTime *time);
    /**
     * @brief setCityClock sets clock to the digital clock in UI
     * @param time current time
     */
    void setCityClock(QTime *time);
    /**
     * @brief addProjectile to the game
     */
    void addProjectile();
    /**
     * @brief addRadar temporar radar to map
     * @param event
     */
    void addRadar(QMouseEvent *event);
    /**
     * @brief setStatistics sets shared_ptr of statistics to mainwindow
     */
    void setStatistics(std::shared_ptr<Statistics> statistics);
public slots:
    // Mietitään nyt mitä tietoja kysellään jne
    void receiveFromDialog(std::string name);
    /**
     * @brief destroyProjectile removes Projectileitem from game
     */
    void destroyProjectile(ProjectileItem *item);
    /**
     * @brief destroyCollidingItems removes items that were hit by projectile
     * @param itemlist QGraphicItems to be removed
     */
    void destroyCollidingItems(QList<QGraphicsItem*> itemlist);
    /**
     * @brief updateRadarSpottedValues to the UI
     * @param passengers to be updated
     * @param vehicles to be updated
     */
    void updateRadarSpottedValues(int passengers, int vehicles);
    /**
     * @brief pauseGame stops timers closes gamemainwindow
     */
    void pauseGame();
signals:
    void gameStarted();
    void endGame();
    void leftButtonClickLocation(Interface::Location loc);
    int setScore(int score);
    void gameOver();
private slots:
    /**
     * @brief on_startBtn_clicked initializes players character in game
     */
    void on_startBtn_clicked();
    /**
     * @brief on_endBtn_clicked pops up confirmation window if game is closed
     */
    void on_endBtn_clicked();
    /**
     * @brief mousePressEvent decides the function based on QMouseEvent
     * @param event
     */
    void mousePressEvent(QMouseEvent *event) override;
    /**
     * @brief keyPressEvent decides the function based on QKeyEven
     * @param event
     */
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    /**
     * @brief updateAccuracy is called every game tick to update accuracy
     */
    void updateAccuracy();

private:
    void setButtons();
    void setUIelements();
    void setTimersAndSound();
    bool isPlayerMoveKey(QKeyEvent *event) const;
    Ui::GameMainWindow *ui;
    QGraphicsScene *map;
    QTimer *timer;
    QTimer *shoottimer_;
    QTimer *accuracytimer_;
    std::map<std::shared_ptr<Interface::IActor>, NysseActorItem *> actorsmap_; // Busses basicly
    std::vector< std::shared_ptr<Interface::IActor> > destroyednysses_;
    NysseActorItem* lastnysse_;
    PlayerActorItem *playeractor_; // Pointterit sekä luokkaan että kuvaan pelaajasta
    Player *player_;
    std::string playername_;
    bool playerspawned_;
    std::shared_ptr<Statistics> statistics_;
    DigitalClock *digitalclockgame_;
    DigitalClock *digitalclockcity_;
    RadarItem *radar_;

    QMediaPlayer *projectilesound_;
    QMediaPlayer *scoresound_;

    int tick_ = 500; //ms
};

} // namespace "Game"
#endif // GAMEMAINWINDOW_HH

