#include "radaritem.hh"
#include "config.hh"

#include <QTimer>

namespace Game {

RadarItem::RadarItem() :
    radarMovie_(0),
    showTimer_(0),
    removed_(false),
    isinscene_(false)
{
    radarMovie_ = new QMovie(RADAR_IMG);
    radarMovie_->start();
    radarMovie_->setSpeed(100);
    this->setStyleSheet("QLabel { background-color: rgba(255, 255, 255, 0);}");
    this->setWindowFlags(Qt::WindowStaysOnTopHint);

    setFixedSize(radarMovie_->currentPixmap().width(), radarMovie_->currentPixmap().height());

    // Timer for radar animation
    showTimer_ = new QTimer(this);
    connect(showTimer_, &QTimer::timeout, this, &QLabel::hide);
}

RadarItem::~RadarItem()
{
    delete radarMovie_;
    delete showTimer_;
}

void RadarItem::spawnRadar()
{
    this->setMovie(radarMovie_);
    showTimer_->start(1000);
}

void RadarItem::addedToScene()
{
    isinscene_ = true;
}

bool RadarItem::isAddedToScene()
{
    return isinscene_;
}

Interface::Location RadarItem::giveLocation() const
{
    return loc_;
}

void RadarItem::selfDestruct()
{
    this->~RadarItem();
}

void RadarItem::move(Interface::Location loc)
{
    loc_ = loc;
    QLabel::move(loc_.giveX() - radarMovie_->currentPixmap().width()/2,
                 HEIGHT-loc_.giveY() - radarMovie_->currentPixmap().height()/2);
    spawnRadar();
}

bool RadarItem::isRemoved() const
{
    return removed_;
}

void RadarItem::remove()
{
    removed_ = true;
}

} // namespace Game
