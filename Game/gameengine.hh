#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include "city.hh"
#include "config.hh"
#include "gamemainwindow.hh"
#include "statistics.hh"

#include <core/location.hh>
#include <core/logic.hh>

#include <QWidget>

/**
  * @file
  * @brief Defines a class that handles game initialization, start and end phases.
  * GameEngine is also used as a connector between classes.
  */

namespace Game
{

class GameEngine : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief GameEngine constructor
     * @param parent is a QWidget pointer that defaults to 0
     */
    explicit GameEngine(QWidget *parent = nullptr);
    /**
     * @brief initializeGame is used call city_, gamelogic_ and mainwindow_ initilization methods
     * @param defaultMap is to set city background
     * @param bigMap is to set city background
     */
    void initializeGame(QImage defaultMap = QImage(DEFAULTMAP), QImage bigMap = QImage(BIGMAP));
    /**
     * @brief startGame opens start dialog
     * @return true if game was started, false if game was not started
     */
    bool startGame();
    /**
     * @brief endGame ends current game and shows highscore dialog
     */
    void endGame();
public slots:
    /**
     * @brief gameWindowLeftClick emits radarSpotted signal with number of vehicles and passengers
     * within range defined by const RADAR_DISTANCE
     * @param Interface::Location object
     */
    void gameWindowLeftClick(Interface::Location loc);
signals:
    /**
     * @brief radarSpotted is used to emit data near the radar location
     * @param passengers near the pinged area
     * @param vehicles near the pinger area
     */
    void radarSpotted(int passengers, int vehicles);
    /**
     * @brief outOfTime is emited after time has run out after starting game
     */
    void outOfTime();
    /**
     * @brief sendStatistics is used to send statistics to other objects
     * @param statistics
     */
    void sendStatistics(std::shared_ptr<Statistics> statistics);
private:
    void initializeGameWindow(QImage &map);
    void initializeCity(QImage &defaultMap, QImage &bigMap);
    void initializeGameLogic();
    void increaseTime();
    void startClockTimer();
    void stopClockTimer();
    void showHighScore();
    GameMainWindow *mainWindow_;
    std::shared_ptr<City> city_;
    CourseSide::Logic gamelogic_;
    std::shared_ptr<Statistics> gamestatistics_;
    QTime gameclock_;
    QTimer *timer_;
    bool initilizationcomplete_;
};

}
#endif // GAMEENGINE_HH
