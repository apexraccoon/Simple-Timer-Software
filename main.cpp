#include "timer.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QtMultimedia/QMediaPlayer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //play sound when music is done
    /*
    QMediaPlayer *player = new QMediaPlayer;
    player = new QMediaPlayer;
    QAudioOutput audioOutput = new QAudioOutput();
    player->setAudioOutput(audioOutput);*/




    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Timer_Project_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Timer w;
    w.setFixedSize(1050,600);
    w.show();
    return a.exec();
}
