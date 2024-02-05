#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "resume.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateOutput();

public slots:
    void setName();
    void setLastName();
    void setSecondName();
    void setPosition();
    void setPhone();
    void addExperience();

private:
    ResumeProxy* resume = nullptr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
