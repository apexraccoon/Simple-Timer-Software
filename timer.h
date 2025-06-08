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

    void update_time();

    void on_progressBar_valueChanged(int value);

    void on_Background_change_button_clicked();

    void on_AppLogo_change_button_clicked();

    void on_Settings_button_clicked();

    void on_Return_button_to_timer_clicked();

    void on_Restart_button_clicked();

    void on_Change_Alarm_button_clicked();

    void on_To_Do_List_button_clicked();

    void on_Add_To_do_task_button_clicked();

    void checklist();
    void on_Delete_all_tasks_done_clicked();

    void on_Delete_To_do_task_button_clicked();

    void on_Return_to_do_to_main_button_clicked();

private:
    Ui::Timer *ui;
    QTimer *countdownTimer;
    int initial_hour,initial_minute, initial_second;
};

#endif // TIMER_H
