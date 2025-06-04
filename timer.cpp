#include "timer.h"
#include "ui_timer.h"
#include <QTimer>
#include <vector>
#include <list>
using namespace std;
//creating window
Timer::Timer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Timer)
{
    QIcon icon("C:\\Users\\omare\\OneDrive\\Desktop\\Timer project\\Timer_Project\\old windows clock icon.ico");
    setWindowIcon(icon);

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
    //hide messages of settings
    ui->Background_Line_Edit->setVisible(false);
    ui->Background_change_button->setVisible(false);
    ui->AppLogo_Line_Edit->setVisible(false);
    ui->AppLogo_change_button->setVisible(false);
    ui->Settings_label->setVisible(false);
    ui->Return_button_to_timer->setVisible(false);
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


void Timer::on_Background_change_button_clicked()
{
    //remove " at start and end of file path
    QString background_new = ui->Background_Line_Edit->text();
    background_new.removeLast();
    background_new.removeFirst();
    QPixmap bkgnd(background_new);
    //
    bkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding); // fixing aspect ratio
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}


void Timer::on_AppLogo_change_button_clicked()
{
    //remove " at start and end of file path
    QString AppLogo_new = ui->AppLogo_Line_Edit->text();
    AppLogo_new.removeLast();
    AppLogo_new.removeFirst();
    //
    QIcon icon(AppLogo_new);
    setWindowIcon(icon);
}


void Timer::on_Settings_button_clicked()
{
    //Show settings and hide the timer options
    ui->Background_Line_Edit->setVisible(true);
    ui->Background_change_button->setVisible(true);
    ui->AppLogo_Line_Edit->setVisible(true);
    ui->AppLogo_change_button->setVisible(true);
    ui->Settings_label->setVisible(true);
    ui->Return_button_to_timer->setVisible(true);
    ui->Timer_bar->setVisible(false);
    ui->Hour_Label->setVisible(false);
    ui->Minute_Label->setVisible(false);
    ui->Second_Label->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->Hour_Line_Edit->setVisible(false);
    ui->Minute_Line_Edit->setVisible(false);
    ui->Seconds_Line_Edit->setVisible(false);
    ui->Settings_button->setVisible(false);
    ui->label_2->setVisible(false);
    ui->label_3->setVisible(false);
    ui->Hour_error_message->setVisible(false);
    ui->Minute_error_message->setVisible(false);
    ui->Second_error_message->setVisible(false);
}



void Timer::on_Return_button_to_timer_clicked()
{
    //Show timer and settings the timer options
    ui->Background_Line_Edit->setVisible(false);
    ui->Background_change_button->setVisible(false);
    ui->AppLogo_Line_Edit->setVisible(false);
    ui->AppLogo_change_button->setVisible(false);
    ui->Settings_label->setVisible(false);
    ui->statusbar->setVisible(true);
    ui->Hour_Label->setVisible(true);
    ui->Minute_Label->setVisible(true);
    ui->Second_Label->setVisible(true);
    ui->pushButton->setVisible(true);
    ui->Hour_Line_Edit->setVisible(true);
    ui->Minute_Line_Edit->setVisible(true);
    ui->Seconds_Line_Edit->setVisible(true);
    ui->Settings_button->setVisible(true);
    ui->label_2->setVisible(true);
    ui->label_3->setVisible(true);
    ui->Hour_error_message->setVisible(true);
    ui->Minute_error_message->setVisible(true);
    ui->Second_error_message->setVisible(true);
}

