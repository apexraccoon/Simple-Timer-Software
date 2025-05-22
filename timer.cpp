#include "timer.h"
#include "ui_timer.h"
#include <QTimer>
using namespace std;
//creating window
Timer::Timer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Timer)
{
    ui->setupUi(this);
    QPixmap bkgnd("C:\\Users\\omare\\OneDrive\\Desktop\\Timer project\\Timer_Project\\Lofi girl timer project.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding); // fixing aspect ratio
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    countdownTimer = new QTimer(this);
    ui->Timer_bar->setValue(100);
    ui->Timer_bar->setVisible(false); //hide timer bar
    //hide error messages before checking
    ui->Hour_error_message->setVisible(false);
    ui->Minute_error_message->setVisible(false);
    ui->Second_error_message->setVisible(false);
    connect(countdownTimer, &QTimer::timeout, this, &Timer::update_time);
}

Timer::~Timer()
{
    delete ui;
}
void Timer::on_pushButton_clicked()
{
    // try and catch to check if hour and minute and seconds are corrct and I know that using an if statement is better!
    try{
        //hide error messages before checking
        ui->Hour_error_message->setVisible(false);
        ui->Minute_error_message->setVisible(false);
        ui->Second_error_message->setVisible(false);
        //check if number is negative or hour is greater than 23 or minutes greater than 60 or seconds greater than 60
        if(ui->Hour_Line_Edit->text().toInt() < 0 || ui->Minute_Line_Edit->text().toInt() < 0 || ui->Seconds_Line_Edit->text().toInt() < 0 || ui->Hour_Line_Edit->text().toInt() > 23 || ui->Minute_Line_Edit->text().toInt() > 59 || ui->Seconds_Line_Edit->text().toInt() > 59){
            throw invalid_argument("Error");
        }
        else{
            throw 1;
        }
    }
    catch(invalid_argument e){
        if(ui->Hour_Line_Edit->text().toInt() < 0 || ui->Hour_Line_Edit->text().toInt() > 23){
            ui->Hour_error_message->setVisible(true);
        }
        if(ui->Minute_Line_Edit->text().toInt() < 0 || ui->Minute_Line_Edit->text().toInt() > 59){
            ui->Minute_error_message->setVisible(true);
        }
        if(ui->Seconds_Line_Edit->text().toInt() < 0 || ui->Seconds_Line_Edit->text().toInt() > 59){
            ui->Second_error_message->setVisible(true);
        }
    }
    //All numbers are valid
    catch(int i){
        //setting timer
        ui->Hour_Label->setText(ui->Hour_Line_Edit->text());
        ui->Minute_Label->setText(ui->Minute_Line_Edit->text());
        ui->Second_Label->setText(ui->Seconds_Line_Edit->text());
        //hiding Text Fields
        ui->Hour_Line_Edit->setVisible(false);
        ui->Minute_Line_Edit->setVisible(false);
        ui->Seconds_Line_Edit->setVisible(false);
        ui->pushButton->setVisible(false);

        initial_hour = ui->Hour_Line_Edit->text().toInt();
        initial_minute = ui->Minute_Line_Edit->text().toInt();
        initial_second = ui->Seconds_Line_Edit->text().toInt();
        ui->Timer_bar->setVisible(true);
        countdownTimer->start(1000);
    }
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

