
#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QScreen>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAttribute( Qt::WA_TranslucentBackground, true );
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    int screenwidth;
    int screenheight;

    //Screen Size
    QScreen* screen = QGuiApplication::primaryScreen();
    screenwidth = screen->geometry().width();
    screenheight = screen->geometry().height();

    this->setGeometry(0,0,screenwidth, screenheight);

    int clock_widget_x = screenwidth / 10;
    int clock_widget_y = screenheight - ui->clock_widget->geometry().height() - screenheight / 11;
    ui->clock_widget->setGeometry(clock_widget_x,clock_widget_y,ui->clock_widget->geometry().width(),ui->clock_widget->geometry().height());

    int launchbar_offset = 10;
    int launchbar_height = screenheight-2*launchbar_offset;
    launchbar_x = screenwidth - ui->launchbar->geometry().width() - launchbar_offset;
    int launchbar_y = screenheight/2 - launchbar_height/2;

    ui->launchbar->setGeometry(launchbar_x,launchbar_y,launchbar_width,launchbar_height);

    ui->launchbar->setStyleSheet("#launchbar { background-color: rgba(220, 220, 220, 150); border-radius: 5px; }");

    int menubar_offset = 10;
    int menubar_width = 310;
    int menubar_height = screenheight-2*menubar_offset;
    int menubar_x = screenwidth - ui->launchbar->geometry().width() - ui->menubar->geometry().width() - 2*launchbar_offset;
    int menubar_y = screenheight/2 - menubar_height/2;

    ui->menubar->setGeometry(menubar_x,menubar_y,menubar_width,menubar_height);

    ui->menubar->hide();
}



MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent *event)
{
    if (event->type() == QEvent::WindowDeactivate | event->type() == QEvent::Leave) {
        MainWindow::launchbaranim_hide();
    } else if (event->type() == QEvent::Enter) {
        MainWindow::launchbaranim_show();
    }

    return QMainWindow::event(event);
}

void MainWindow::launchbaranim_hide()
{
    if(!launchbar_hidden && runningAnimations == 0){
    runningAnimations++;
    int new_width = ui->launchbar->geometry().width()/12;
    int new_x = ui->launchbar->geometry().x() + (ui->launchbar->geometry().width()- new_width);
    QPropertyAnimation *animation = new QPropertyAnimation(ui->launchbar, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(ui->launchbar->geometry());
    animation->setEndValue(QRect(new_x , ui->launchbar->geometry().y(), new_width, ui->launchbar->geometry().height()));
    animation->start();

    QList <QWidget *> widgets = ui->launchbar->findChildren<QWidget *>();
    foreach (QWidget *widget, widgets){
        widget->hide();
    }

    launchbar_hidden = true;

    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::onAnimationFinished);
    }
}

// Slot to handle when the animation is finished
void MainWindow::onAnimationFinished()
{
    runningAnimations--;
}

void MainWindow::launchbaranim_show()
{
    if(launchbar_hidden && runningAnimations == 0){
    runningAnimations++;
    QPropertyAnimation *animation = new QPropertyAnimation(ui->launchbar, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(ui->launchbar->geometry());
    animation->setEndValue(QRect(launchbar_x, ui->launchbar->geometry().y(), launchbar_width, ui->launchbar->geometry().height()));
    animation->start();

    QList <QWidget *> widgets = ui->launchbar->findChildren<QWidget *>();
    foreach (QWidget *widget, widgets){
        widget->show();
    }

    launchbar_hidden = false;

    connect(animation, &QPropertyAnimation::finished, this, &MainWindow::onAnimationFinished);
    }
}


