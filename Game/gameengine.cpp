#include "gameengine.hh"
#include "highscoredialog.hh"
#include "startdialog.hh"

namespace Game {

GameEngine::GameEngine(QWidget *parent) :
    QWidget(parent),
    mainWindow_(new GameMainWindow(this)),
    city_(std::make_shared<City>()),
    gamelogic_(this),
    gamestatistics_(std::make_shared<Statistics>()),
    gameclock_(QTime(0,0)),
    timer_(new QTimer(this)),
    initilizationcomplete_(false)
{
    connect(timer_, &QTimer::timeout, this, &GameEngine::increaseTime);

    connect(mainWindow_, &GameMainWindow::gameStarted, this, &GameEngine::startClockTimer);
    connect(mainWindow_, &GameMainWindow::leftButtonClickLocation, this, &GameEngine::gameWindowLeftClick);

    connect(this, &GameEngine::radarSpotted, mainWindow_, &GameMainWindow::updateRadarSpottedValues);
    connect(this, &GameEngine::outOfTime, mainWindow_, &GameMainWindow::pauseGame);
}


void GameEngine::initializeGame(QImage defaultMap, QImage bigMap)
{
    initializeGameWindow(defaultMap);
    initializeCity(defaultMap, bigMap);
    initializeGameLogic();

    initilizationcomplete_ = true;
}

bool GameEngine::startGame()
{
    if (!initilizationcomplete_) {
        qDebug() << "Game is not initialized!";
        return false;
    }

    StartDialog dialog(this);
    connect(&dialog, &StartDialog::sendData, mainWindow_, &GameMainWindow::receiveFromDialog);

    if (dialog.exec() != QDialog::Accepted) {
        return false;
    }

    gamelogic_.finalizeGameStart();
    mainWindow_->show();

    return true;
}

void GameEngine::endGame()
{
    stopClockTimer();
    city_->endGame();
    showHighScore();
}

void GameEngine::gameWindowLeftClick(Interface::Location loc){
    int passengers = 0;
    int vehicles = 0;
    for (const auto& actor : city_->getNearbyActorsWithRange(loc, RADAR_DISTANCE)) {
        if (std::dynamic_pointer_cast<CourseSide::Nysse>(actor)) {
            vehicles++;
        } else if (std::dynamic_pointer_cast<CourseSide::Passenger>(actor)) {
            passengers++;
        }
    }
    emit radarSpotted(passengers, vehicles);
}

void GameEngine::initializeGameWindow(QImage &map)
{
    mainWindow_->setGameClock(&gameclock_);
    mainWindow_->setCityClock(city_->getClock());
    mainWindow_->setPicture(map);
    mainWindow_->setStatistics(gamestatistics_);
}

void GameEngine::initializeCity(QImage &defaultMap, QImage &bigMap)
{
    city_->setGameWindow(mainWindow_);
    city_->setBackground(defaultMap, bigMap);
}

void GameEngine::initializeGameLogic()
{
    gamelogic_.fileConfig();
    gamelogic_.takeCity(city_);
}

void GameEngine::showHighScore()
{
    HighScoreDialog highscoredialog(this);
    connect(this, &GameEngine::sendStatistics, &highscoredialog, &HighScoreDialog::receiveStatistics);
    emit sendStatistics(gamestatistics_);
    highscoredialog.exec();

}

void GameEngine::increaseTime()
{
    gameclock_ = gameclock_.addMSecs(1000);

    if (gameclock_ >= PLAY_TIME) {        
        emit outOfTime();
        endGame();
    }
}

void GameEngine::startClockTimer()
{
    timer_->start(1000);
}

void GameEngine::stopClockTimer()
{
    timer_->stop();
}

} // namespace game
