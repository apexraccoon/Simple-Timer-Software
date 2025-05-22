#ifndef TIMER_H
#define TIMER_H
#include <QThread>
#include <QMainWindow>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui {
class Timer;
}
QT_END_NAMESPACE

class Timer : public QMainWindow
{
    Q_OBJECT

public:
    Timer(QWidget *parent = nullptr);
    ~Timer();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void update_time();

    void on_progressBar_valueChanged(int value);

private:
    Ui::Timer *ui;
    QTimer *countdownTimer;
    int initial_hour,initial_minute, initial_second;
};

#endif // TIMER_H
