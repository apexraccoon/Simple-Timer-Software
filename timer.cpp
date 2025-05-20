#include "timer.h"
#include "ui_timer.h"
#include <QTimer>
Timer::Timer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Timer)
{
    ui->setupUi(this);
    countdownTimer = new QTimer(this);
    ui->Timer_bar->setValue(100);
    ui->Timer_bar->setVisible(false);
    connect(countdownTimer, &QTimer::timeout, this, &Timer::update_time);
}

Timer::~Timer()
{
    delete ui;
}
void Timer::on_pushButton_clicked()
{
    //setting timer
    ui->Hour_Label->setText(ui->Hour_Line_Edit->text());
    ui->Minute_Label->setText(ui->Minute_Line_Edit->text());
    ui->Second_Label->setText(ui->Seconds_Line_Edit->text());
    //hiding Text Fields
    ui->Hour_Line_Edit->setVisible(false);
    ui->Minute_Line_Edit->setVisible(false);
    ui->Seconds_Line_Edit->setVisible(false);
    initial_hour = ui->Hour_Line_Edit->text().toInt();
    initial_minute = ui->Minute_Line_Edit->text().toInt();
    initial_second = ui->Seconds_Line_Edit->text().toInt();
    ui->Timer_bar->setVisible(true);
    countdownTimer->start(1000);
}
//countdown
void Timer::update_time()
{
    //check if second is equal to zero
    if(ui->Second_Label->text().toInt() == 0){
        if(ui->Minute_Label->text().toInt() == 0){
            ui->Hour_Label->setText(QString::number((ui->Hour_Label->text().toInt()) - 1)); // reduce hour by 1 in case Second and Minute are zero
            ui->Minute_Label->setText(QString::number((ui->Minute_Label->text().toInt()) + 59));
            ui->Second_Label->setText(QString::number((ui->Second_Label->text().toInt()) +59));
        }
        else{
            ui->Minute_Label->setText(QString::number((ui->Minute_Label->text().toInt()) - 1)); // reduce Minute by 1 in case Second is zero
            ui->Second_Label->setText(QString::number((ui->Second_Label->text().toInt()) +59));
        }
    }
    else{
        ui->Second_Label->setText(QString::number((ui->Second_Label->text().toInt()) - 1)); // reduce second by 1
    }
    //progress bar(percentage of time remaining)
    on_progressBar_valueChanged(((ui->Hour_Label->text().toInt()*3600 + ui->Minute_Label->text().toInt() * 60 + ui->Second_Label->text().toInt())*100)/(initial_hour * 3600 + initial_minute * 60 + initial_second)); // testing progress bar
}


void Timer::on_progressBar_valueChanged(int value)
{
    ui->Timer_bar->setValue(value);
}

