#ifndef CITY_HH
#define CITY_HH

#include "gamemainwindow.hh"

#include <interfaces/icity.hh>

/**
  * @file
  * @brief Defines a class that implements City for Game
  */

namespace Game {

class City : public Interface::ICity
{
public:
    City();
    ~City();

    // ICity interface
public:
    void setBackground(QImage &basicbackground, QImage &bigbackground) override;
    void setClock(QTime clock) override;
    void addStop(std::shared_ptr<Interface::IStop> stop) override;
    void startGame() override;
    void addActor(std::shared_ptr<Interface::IActor> newactor) override;
    void removeActor(std::shared_ptr<Interface::IActor> actor) override;
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;
    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;
    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;
    std::vector<std::shared_ptr<Interface::IActor> > getNearbyActors(Interface::Location loc) const override;
    bool isGameOver() const override;

    // City methods
public:
    /**
     * @brief setGameWindow sets GameMainwindow inside city as pointer
     * @param w pointer to GameMainWindow object
     */
    void setGameWindow(GameMainWindow *w);
    /**
     * @brief getNearbyActorsWithRange
     * @param loc is Interface::Location object
     * @param range is unsigned int
     * @return vector of shared pointers to IActors withing range
     */
    std::vector<std::shared_ptr<Interface::IActor> > getNearbyActorsWithRange(Interface::Location loc, unsigned int range) const;
    /**
     * @brief getClock
     * @return pointer to citys clock
     */
    QTime *getClock();
    /**
     * @brief endGame sets gameover_ to true
     */
    void endGame();

private:
    GameMainWindow *mainWindow_;
    QImage basicbackground_;
    QImage bigbackground_;
    QTime clock_;
    std::vector<std::shared_ptr<Interface::IStop>> stops_;
    std::vector<std::shared_ptr<Interface::IActor>> actors_;
    bool gamestarted_;
    bool gameover_;
};

} // namespace Game
#endif // CITY_HH
