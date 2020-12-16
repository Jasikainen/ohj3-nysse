#ifndef DIGITALCLOCK_HH
#define DIGITALCLOCK_HH

#include <QLCDNumber>
#include <QTime>

/**
  * @file
  * @brief Defines a class that can display QTime in digitalclock format
  */

namespace Game {

enum Style {
    HH_MM,
    MM_SS
};

/**
 * @brief DigitalClock is a class that can display QTime in digitalclock format.
 *
 * DigitalClock is inherited from QLCDNumber.
 */

class DigitalClock : public QLCDNumber
{
    Q_OBJECT

public:
    /**
     * @brief DigitalClock constructor
     * @param parent pointer to QWidget
     * @param time pointer to QTime that defaults to nullptr
     * @param style set style of digitalclock to HH_MM or MM_SS, default: HH_MM
     */
    DigitalClock(QWidget *parent, QTime *time = nullptr, int style = HH_MM);
    /**
     * @brief setTime
     * @param time QTime object for digitalclock
     */
    void setTime(QTime* time);
    /**
     * @brief connectTimer sets digital clock run with 1 second interval
     */
    void connectTimer();

public slots:
    /**
     * @brief showTime show digitalclock current time in QLCD if QTime is set for digitalclock
     */
    void showTime();

private:
    QTime* clock_;
    const int style_;
};
} // namespace Game

#endif // DIGITALCLOCK_HH
