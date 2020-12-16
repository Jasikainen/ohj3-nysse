#include "creategame.hh"
#include "city.hh"

namespace Interface {

std::shared_ptr<Interface::ICity> createGame() {
    std::shared_ptr<Interface::ICity> ptr = std::make_shared<Game::City>();
    return ptr;
}

}
