#include "player.hh"

namespace Game {

Player::Player():
    location_(0,0),
    removed_(false)
{
    location_.setXY(250, 250);
}

Player::~Player()
{

}

Interface::Location Player::giveLocation() const{
    return location_;
}

void Player::move(Interface::Location loc){
    location_.setXY(loc.giveX(), loc.giveY());
}

bool Player::isRemoved() const{
    return removed_;
}

void Player::remove(){
    removed_ = true;
}

void Player::setCity(std::shared_ptr<Interface::ICity> city){
    city_ = city;
}

} // namespace Game
