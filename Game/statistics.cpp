#include "statistics.hh"
#include <iostream>
namespace Game {

Statistics::Statistics():
    passengers_(0),
    nysses_(0),
    nyssesleft_(0),
    nyssesdestroyed_(0),
    accuracy_(100),
    projectiles_(0),
    score_(0)
{
}

void Statistics::morePassengers(int num)
{
    invariant();
    passengers_ += abs(num);
    qDebug() << num << "new passengers added";
    invariant();
}

void Statistics::nysseRemoved()
{
    invariant();
    nyssesleft_ += 1;
    qDebug() << "Nysse removed";
    invariant();
}

void Statistics::newNysse()
{
    invariant();
    nysses_ += 1;
    qDebug() << "Nysse added";
    invariant();
}

void Statistics::nysseLeft()
{
    invariant();
    qDebug() << "Nysse left the game";
}

void Statistics::shotProjectile()
{
    invariant();
    projectiles_ += 1;
    qDebug() << "Projectiles fired" << projectiles_;
    invariant();
}

void Statistics::nysseDestroyed()
{
    invariant();
    nyssesdestroyed_ += 1;
    qDebug() << "Total nysses destroyed " << nyssesdestroyed_;
    invariant();
}

void Statistics::calculateAccuracy()
{
    invariant();
    if (projectiles_ != 0){
        accuracy_ = (nyssesdestroyed_ / double(projectiles_)) * 100;
    }
    if (accuracy_ > 100){
        accuracy_ = 100;
    }

}

void Statistics::calculateScore(unsigned int addedscore)
{
    invariant();
    score_ += addedscore;
    invariant();
}

unsigned int Statistics::getScore() const
{
    invariant();
    return score_;
}

double Statistics::getAccuracy() const
{
    invariant();
    return accuracy_;
}
void Statistics::setName(std::string name)
{
    invariant();
    playername_ = name;
    invariant();
}
std::string Statistics::getName() const
{
    invariant();
    return playername_;
}

unsigned int Statistics::getNyssesDestroyed() const
{
    invariant();
    return nyssesdestroyed_;
}


void Statistics::invariant() const
{
    Q_ASSERT(0 <= accuracy_ && accuracy_ <= 100);
    Q_ASSERT(nysses_ >= (nyssesleft_+nyssesdestroyed_));
}

}
