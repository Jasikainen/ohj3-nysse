#include "gamemainwindow.hh"
#include "ui_gamemainwindow.h"
#include "config.hh"

#include <graphics/simpleactoritem.hh>
#include <errors/initerror.hh>
#include <actors/nysse.hh>

#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>

namespace Game {

GameMainWindow::GameMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameMainWindow),
    map(new QGraphicsScene(this)),
    timer(new QTimer(this)),
    shoottimer_(new QTimer(this)),
    accuracytimer_(new QTimer(this)),
    player_(nullptr),
    playerspawned_(false),
    digitalclockgame_(new DigitalClock(this, 0, MM_SS)),
    digitalclockcity_(new DigitalClock(this, 0, HH_MM)),
    radar_(new RadarItem),
    projectilesound_(new QMediaPlayer),
    scoresound_(new QMediaPlayer)
{
    ui->setupUi(this);
    setFixedSize(WIDTH + 200, HEIGHT + 5);

    setButtons();
    setUIelements();
    setTimersAndSound();
}


GameMainWindow::~GameMainWindow()
{
    delete ui;
    delete radar_;
    delete projectilesound_;
    delete scoresound_;
    delete shoottimer_;
    delete accuracytimer_;
    delete digitalclockgame_;
    delete digitalclockcity_;
}


void GameMainWindow::setTick(int t)
{
    tick_ = t;
}

void GameMainWindow::addStop(int locX, int locY, int type)
{
    // type = 245 <-> white color
    if ((locX >= 0) && (locX <= 501) && (locY >= 0) && (locY <= 501)){
        CourseSide::SimpleActorItem* nActor = new CourseSide::SimpleActorItem(locX, locY, type);
        map->addItem(nActor);
    } else {
        throw (Interface::InitError("Stops position is not valid"));
    }

}

void GameMainWindow::updateCoords(int nX, int nY)
{
    lastnysse_->setPos(nX,nY);
}

void GameMainWindow::setPicture(QImage &img)
{
    map->setBackgroundBrush(img);
}

void GameMainWindow::addNysse(int locX, int locY, std::shared_ptr<Interface::IActor> newnysse)
{
    NysseActorItem* nActor = new NysseActorItem(locX, locY);
    std::shared_ptr<CourseSide::Nysse> ptr = std::dynamic_pointer_cast<CourseSide::Nysse>(newnysse);
    map->addItem(nActor);
    actorsmap_[newnysse] = nActor;
    lastnysse_ = nActor;

    statistics_.get()->morePassengers(ptr->getPassengers().size());
    statistics_.get()->newNysse();
}

void GameMainWindow::updateNysseItem(int locX, int locY, std::shared_ptr<Interface::IActor> updatednysse)
{
    for (auto it = actorsmap_.begin(); it != actorsmap_.end(); ++it){
        if ( it->first == updatednysse ){
            lastnysse_ = it->second;
            updateCoords(locX, locY);
            return;
        }
    }
}

void GameMainWindow::removeNysseItem(std::shared_ptr<Interface::IActor> removenysse)
{
    for (auto it = actorsmap_.begin(); it != actorsmap_.end(); ++it){
        if ( it->first == removenysse ){
            map->removeItem(it->second);
            delete it->second;
            actorsmap_.erase(it->first);
            return;
        }
    }
}

void GameMainWindow::setGameClock(QTime *time)
{
    digitalclockgame_->setTime(time);
}

void GameMainWindow::setCityClock(QTime *time)
{
    digitalclockcity_->setTime(time);
}

void GameMainWindow::addProjectile()
{
    ProjectileItem *projectileitem_ = new ProjectileItem(playeractor_->x() + playeractor_->width()/2,
                                                         playeractor_->y() + playeractor_->height()/2,
                                                         playeractor_->rotation());

    connect(projectileitem_, &ProjectileItem::destroyProjectileSignal, this, &GameMainWindow::destroyProjectile);
    connect(projectileitem_, &ProjectileItem::destroyCollidingItemSignal, this, &GameMainWindow::destroyCollidingItems);
    map->addItem(projectileitem_);
    // Play sound when shooting projectiles
    if (projectilesound_->state() == QMediaPlayer::PlayingState){
        projectilesound_->setPosition(0);
    } else if (projectilesound_->state() == QMediaPlayer::StoppedState){
        projectilesound_->play();
    }
    statistics_.get()->shotProjectile();
}

void GameMainWindow::addRadar(QMouseEvent *event)
{
    if (map->sceneRect().contains(event->x(), HEIGHT-event->y())){
        Interface::Location loc;
        loc.setXY(event->x(), HEIGHT-event->y());
        radar_->move(loc);
        if (!radar_->isAddedToScene()) {
            map->addWidget(radar_);
            radar_->addedToScene();
        } else {
            radar_->show();
        }
        emit leftButtonClickLocation(loc);
    }
}

void GameMainWindow::setStatistics(std::shared_ptr<Statistics> statistics)
{
    statistics_ = statistics;
}

void GameMainWindow::receiveFromDialog(std::string name)
{
    playername_ = name;
}

void GameMainWindow::destroyProjectile(ProjectileItem *item)
{
    map->removeItem(item);
    delete item;
}

void GameMainWindow::destroyCollidingItems(QList<QGraphicsItem*> itemlist)
{
    for (int item = 0, n = itemlist.size(); item < n; ++item){

        // Only deletes items that represent Nysse
        if ( typeid (*(itemlist[item])) == typeid (NysseActorItem) ){
            for (auto it = actorsmap_.begin(); it != actorsmap_.end(); ++it){
                std::shared_ptr<CourseSide::Nysse> ptr = std::dynamic_pointer_cast<CourseSide::Nysse>(it->first);
                if ((ptr != nullptr) & (it->second == itemlist[item])){
                    // This ensures that only one colliding projectile can destroy NysseActorItem
                    if ( std::find( destroyednysses_.begin(), destroyednysses_.end(), ptr) == destroyednysses_.end() ){
                        destroyednysses_.push_back(ptr);
                        // Nysse 10 pts and passenger 1 pt
                        int score = 10 + ptr->getPassengers().size();

                        if (scoresound_->state() == QMediaPlayer::PlayingState){
                            scoresound_->setPosition(0);
                        } else if (scoresound_->state() == QMediaPlayer::StoppedState){
                            scoresound_->play();
                        }
                        statistics_.get()->calculateScore(score);
                        statistics_.get()->nysseDestroyed();
                        // Accuracy automatically updated
                        emit setScore(statistics_.get()->getScore());
                    }
                    ptr->remove();
                }
            }
        }
    }
}

void GameMainWindow::updateRadarSpottedValues(int passengers, int vehicles)
{
    ui->passengerLCD->display(passengers);
    ui->vehicleLCD->display(vehicles);
}

void GameMainWindow::pauseGame()
{
    timer->stop();
    accuracytimer_->stop();
    shoottimer_->stop();
    this->close();
    emit gameOver();
}

void GameMainWindow::on_startBtn_clicked()
{
    statistics_->setName(playername_);
    player_ = new Player();
    // Location 250, 250
    playeractor_ = new PlayerActorItem(player_->giveLocation().giveX(), player_->giveLocation().giveX());
    map->addItem(playeractor_);
    playerspawned_ = true;
    QString Qstrname = QString::fromStdString(playername_);
    qDebug() << "The player "<< Qstrname << " has been set in the game";
    ui->startBtn->setEnabled(0);
    emit gameStarted();
}

void GameMainWindow::on_endBtn_clicked()
{
    QMessageBox::StandardButton msgBox = QMessageBox::question(this, "EXIT GAME",
                                                               "Do you want to end the game",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (msgBox == QMessageBox::Yes){
        qDebug() << "End game";
        emit endGame();
    } else if (msgBox == QMessageBox::No) {
        qDebug() << "Continue game";
    }
}

void GameMainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Temporarily show radar on clicked location
        addRadar(event);
    } else {
        // pass on other buttons to base class
        QMainWindow::mousePressEvent(event);
    }
}

void GameMainWindow::keyPressEvent(QKeyEvent *event)
{
    if (isPlayerMoveKey(event) && playerspawned_ && timer->isActive()){
        playeractor_->move(event);
        player_->location_.setXY(playeractor_->x(),playeractor_->y());
        // Movement

    } else if (event->key() == Game::Controls::SHOOT && playerspawned_ && !event->isAutoRepeat() && timer->isActive()){
        shoottimer_->start(tick_);
        addProjectile();
        // Shooting

    } else {
        qDebug() << "You typed" << event->key();
        // pass on other buttons to base class
        QMainWindow::keyPressEvent(event);
    }

}

void GameMainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (isPlayerMoveKey(event) && playerspawned_){
        playeractor_->stop(event);
        player_->location_.setXY(playeractor_->x(),playeractor_->y());
        // Movement

    } else if (event->key() == Game::Controls::SHOOT && playerspawned_ && !event->isAutoRepeat()){
        shoottimer_->stop();
        // Shooting

    } else {
        qDebug() << "You typed" << event->key();
        QMainWindow::keyPressEvent(event);
    }
}

void GameMainWindow::updateAccuracy()
{
    statistics_.get()->calculateAccuracy();
    ui->accuracyBar->setValue(statistics_->getAccuracy());
}

void GameMainWindow::setButtons()
{
    // Start/end button
    ui->startBtn->setMaximumSize(BUTTON_SIZE/2, BUTTON_SIZE/4);
    ui->startBtn->move(WIDTH+ui->startBtn->width(), PADDING);
    ui->endBtn->setMaximumSize(BUTTON_SIZE/2, BUTTON_SIZE/4);
    QObject::connect(this, SIGNAL(endGame()), qApp, SLOT(quit()));

    // Define WASD keys to show movement buttons in UI
    ui->leftBtn->setText("A");
    ui->leftBtn->setEnabled(0);
    ui->leftBtn->setMaximumSize(BUTTON_SIZE/3, BUTTON_SIZE/3);
    ui->leftBtn->setStyleSheet("background-color: red;");

    ui->rightBtn->setText("D");
    ui->rightBtn->setEnabled(0);
    ui->rightBtn->setMaximumSize(BUTTON_SIZE/3, BUTTON_SIZE/3);
    ui->rightBtn->setStyleSheet("background-color: red;");

    ui->upBtn->setText("W");
    ui->upBtn->setEnabled(0);
    ui->upBtn->setMaximumSize(BUTTON_SIZE/3, BUTTON_SIZE/3);
    ui->upBtn->setStyleSheet("background-color: red;");

    ui->downBtn->setText("S");
    ui->downBtn->setEnabled(0);
    ui->downBtn->setMaximumSize(BUTTON_SIZE/3, BUTTON_SIZE/3);
    ui->downBtn->setStyleSheet("background-color: red;");

    ui->spaceBtn->setText("SPACEBAR");
    ui->spaceBtn->setEnabled(0);
    ui->spaceBtn->setMaximumSize(BUTTON_SIZE, BUTTON_SIZE/3);
    ui->spaceBtn->setStyleSheet("background-color: red;");
}

void GameMainWindow::setUIelements()
{
    ui->gameView->setFixedSize(WIDTH+2, HEIGHT+2);
    ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->centralwidget->setFixedSize(WIDTH + 200 + PADDING, HEIGHT + PADDING);

    ui->gameView->setScene(map);
    map->setSceneRect(0,0, WIDTH, HEIGHT); // 500x500
    resize(minimumSizeHint());

    // LCD Score counter
    ui->pointsLCD->display(0);
    ui->pointsLCD->setSegmentStyle(QLCDNumber::Flat);
    QObject::connect(this, SIGNAL(setScore(int)), ui->pointsLCD, SLOT(display(int)));
    // Accuracy Bar
    ui->accuracyBar->setRange(0, 100);
    ui->accuracyBar->setValue(100);
    // city and game time
    digitalclockgame_->move(WIDTH+PADDING, PADDING);
    digitalclockcity_->move(WIDTH+PADDING, PADDING*4);
}

void GameMainWindow::setTimersAndSound()
{
    connect(timer, &QTimer::timeout, map, &QGraphicsScene::advance);
    timer->start(tick_);
    connect(shoottimer_, &QTimer::timeout, this, &GameMainWindow::addProjectile);
    connect(accuracytimer_, &QTimer::timeout, this, &GameMainWindow::updateAccuracy);
    accuracytimer_->start(tick_*2);

    connect(this, &GameMainWindow::gameStarted, digitalclockgame_, &DigitalClock::connectTimer);
    digitalclockcity_->connectTimer();

    projectilesound_->setMedia(QUrl("qrc:/sounds/projectile.mp3"));
    scoresound_->setMedia(QUrl("qrc:/sounds/scoreUp.mp3"));
}

bool GameMainWindow::isPlayerMoveKey(QKeyEvent *event) const
{
    switch (event->key()) {
    case Game::Controls::LEFT  : return true;
    case Game::Controls::RIGHT : return true;
    case Game::Controls::DOWN  : return true;
    case Game::Controls::UP    : return true;
    }
    return false;
}

} // namespace game
