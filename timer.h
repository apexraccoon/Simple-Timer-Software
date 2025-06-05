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

    void on_Background_change_button_clicked();

    void on_AppLogo_change_button_clicked();

    void on_Settings_button_clicked();

    void on_Start_button_clicked();

    void on_Return_button_to_timer_clicked();

    void on_Restart_button_clicked();

    void on_nothing_button_clicked();

private:
    Ui::Timer *ui;
    QTimer *countdownTimer;
    int initial_hour,initial_minute, initial_second;
};

#endif // TIMER_H
