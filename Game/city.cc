#include "city.hh"

#include <errors/gameerror.hh>
#include <errors/initerror.hh>
#include <actors/nysse.hh>

namespace Game {

City::City():
    mainWindow_(nullptr),
    gamestarted_(false),
    gameover_(false)
{

}

City::~City()
{

}

void City::setBackground(QImage &basicbackground, QImage &bigbackground)
{
    try {
        this->basicbackground_ = basicbackground;
        this->bigbackground_ = bigbackground;
        if ((this->basicbackground_ != basicbackground) & (this->bigbackground_ != bigbackground)){
            this->basicbackground_ = QImage();
            this->bigbackground_ = QImage();
            throw Interface::InitError("Setting the picture was unsuccesful or the picture was invalid.");
        }
    } catch (Interface::InitError& e) {
        qDebug() << e.what();
        qDebug() << "Error: " << e.giveMessage();
    }

}

void City::setClock(QTime clock)
{
    if (clock.isValid() == true)
        this->clock_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop){
    try {
        Interface::Location stopLocation = stop->getLocation();
        // Stops graphed grey
        mainWindow_->addStop(stopLocation.giveX()-5, 495-stopLocation.giveY(), 245);
        this->stops_.push_back(stop);

    } catch (Interface::InitError& e) {
        qDebug() << e.what();
        qDebug() << "Error: " << e.giveMessage();
    }

}

void City::startGame()
{
    if (!gamestarted_ == false){
        gamestarted_ = true;
        gameover_ = false;
        qDebug() << "The game started";
    }
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    try {
        for (auto it = actors_.begin(); it != actors_.end(); it++){
            if (it->get() == newactor.get()){
                throw Interface::GameError("Actor is already in the city");
            }
        }
        // If the actor was not found already, get actors location and add it
        Interface::Location actorLocation = newactor->giveLocation();

        if (std::dynamic_pointer_cast<CourseSide::Nysse>(newactor)){
            mainWindow_->addNysse(actorLocation.giveX(), 495-actorLocation.giveY(), newactor);
        }
        this->actors_.push_back(newactor);

    } catch (Interface::GameError& e) {
        qDebug() << e.what();
        qDebug() << "Error: " << e.giveMessage();
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
    // Logic kutsuu tätä kun se poistaa actoreita
    try {
        for (auto it = actors_.begin(); it != actors_.end(); it++){
            if (it->get() == actor.get()){
                if (std::dynamic_pointer_cast<CourseSide::Nysse>(actor)){
                    mainWindow_->removeNysseItem(actor);

                } else if (std::dynamic_pointer_cast<CourseSide::Passenger>(actor)) {
                    qDebug() << "Passenger removed from game";
                }
                actors_.erase(it);
                return;
            }
        }
        throw Interface::GameError("Actor not found in the city");
    } catch (Interface::GameError& e) {
        qDebug() << e.what();
        qDebug() << "Error: " << e.giveMessage();
    }
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{
    if (!std::dynamic_pointer_cast<CourseSide::Nysse>(actor)->isRemoved()){
        actor->remove();  // Mark as removed
        qDebug() << "Nysse status changed to removed";
    }
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    bool ret = false;
    for (auto it = actors_.begin(); it != actors_.end(); it++){
        if (it->get() == actor.get()){
            ret = true;
            break;
        }
    }
    if (std::dynamic_pointer_cast<CourseSide::Passenger>(actor))
    {
        qDebug() << "Passenger found";
    } else {
        qDebug() << "Nysse found ";
    }
    return ret;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    Interface::Location actorLocation = actor->giveLocation();
    if (std::dynamic_pointer_cast<CourseSide::Nysse>(actor)){
        mainWindow_->updateNysseItem(actorLocation.giveX(), 500-actorLocation.giveY(), actor);
    }

}

std::vector<std::shared_ptr<Interface::IActor>> City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearbyActorsVector;
    for (const auto& actor : actors_ ){
        if ( loc.isClose(actor->giveLocation()) ) {
            nearbyActorsVector.push_back(actor);
        }
    }
    return nearbyActorsVector;
}

bool City::isGameOver() const
{
    return gameover_;
}

void City::setGameWindow(GameMainWindow *w)
{
    mainWindow_ = w;
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActorsWithRange(Interface::Location loc, unsigned int range) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearbyActorsVector;
    for (const auto& actor : actors_ ){
        if ( loc.isClose(actor->giveLocation(), range) ) {
            nearbyActorsVector.push_back(actor);
        }
    }
    return nearbyActorsVector;
}

QTime *City::getClock()
{
    return &clock_;
}

void City::endGame()
{
    gameover_ = true;
}

} // namespace game
