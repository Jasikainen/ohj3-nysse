#ifndef CONFIG_HH
#define CONFIG_HH

#include <QString>
#include <QTime>

/**
  * @file
  * @brief config.hh includes global constants for game.
  */

namespace Game {

enum Controls {
    LEFT  = Qt::Key_A,
    RIGHT = Qt::Key_D,
    DOWN  = Qt::Key_S,
    UP    = Qt::Key_W,
    SHOOT = Qt::Key_Space
};

// default backgrounds
const QString DEFAULTMAP(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
const QString BIGMAP(":/offlinedata/offlinedata/kartta_iso_1095x592.png");

const QString PLAYER_ACTOR_IMG = ":/images/airplane_50x50.png";
const QString NYSSE_ACTOR_IMG = ":/images/bus_20x20.png";
const QString PROJ_ACTOR_IMG = ":/images/projectile_15x15";
const QString RADAR_IMG = ":/images/radar2_63x63.gif";
const QString START_DIALOG_IMG = ":/images/tampere_view_big.png";

const QTime PLAY_TIME = QTime(0, 2, 0); // hh, mm, ss

const int PLAYER_MOVEMENT_SPEED = 3; // Accepted values 1-5, 1 is slowest and 5 is fastest
const int BULLET_MOVEMENT = 5;
const unsigned int RADAR_DISTANCE = 30;

const int WIDTH = 500;
const int HEIGHT = 500;
const int PADDING = 10;
const int BUTTON_SIZE = 100;

} // namespace Game
#endif // CONFIG_HH
