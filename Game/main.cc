#include "gameengine.hh"

#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Q_INIT_RESOURCE(offlinedata);

    Game::GameEngine engine(0);
    engine.initializeGame();

    if(!engine.startGame()) {
        return 0;
    }
    int retval;
    try {
        return a.exec();
    } catch (const std::bad_alloc &) {
        return EXIT_FAILURE;
    }
    return retval;

}
