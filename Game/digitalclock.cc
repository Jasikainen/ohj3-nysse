#include "digitalclock.hh"

#include <QTimer>

namespace Game {

DigitalClock::DigitalClock(QWidget *parent, QTime *time, int style):
    QLCDNumber(parent),
    clock_(time),
    style_(style)
{
    setSegmentStyle(Flat);
    display(QString("00:00"));
}

void DigitalClock::setTime(QTime *time)
{
    clock_ = time;
}

void DigitalClock::connectTimer()
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000); // second
}

void DigitalClock::showTime()
{
    if (clock_ == nullptr) {
        return;
    }

    if (style_ == MM_SS) {
        QString text = clock_->toString("mm:ss");
        display(text);
    } else {
        QString text = clock_->toString("hh:mm");
        display(text);
    }
}

} // namespace game
