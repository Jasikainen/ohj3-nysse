#ifndef PLAYER_HH
#define PLAYER_HH

#include <interfaces/iactor.hh>
#include <interfaces/icity.hh>

/**
 * @file
 * @brief Defines a class that implements actual player
 */

namespace Game {

/**
 * @brief Player is an implementation of actual player
 *
 * Player is inherited from ActorIF interface.
 * If class method doesn't have exception guarantee of nothrow, method can leak out exception `std::bad_alloc` (out of memory)???ei varmaan
 */
class Player : public virtual Interface::IActor
{
public:
    /**
      * @brief Constructor of player
      * @post Players Location is set at middle of the game
      */
    Player();
    ~Player();

    // IActor interface
    Interface::Location giveLocation() const;
    void move(Interface::Location loc);
    bool isRemoved() const;
    void remove();

    // Player functions
    /**
     * @brief setCity sets city for player
     * @param shared pointer to ICity
     */
    void setCity(std::shared_ptr<Interface::ICity> city);
    /**
     * @brief location_ stores location object of player
     */
    Interface::Location location_;

private:
    bool removed_;
    std::shared_ptr<Interface::ICity> city_;
};

} // namespace "Game"
#endif // PLAYER_HH
