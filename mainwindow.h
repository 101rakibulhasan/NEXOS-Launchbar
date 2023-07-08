
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFocusEvent>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int runningAnimations = 0;

    bool launchbar_hidden = false;
    int launchbar_width = 75;
    int launchbar_x;

private slots:
    bool event(QEvent *event) override;
    void launchbaranim_hide();
    void launchbaranim_show();
    void onAnimationFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
