#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    resume = new ResumeProxy(new Resume());

    connect(ui->name,           SIGNAL(returnPressed()),    SLOT(setName()));
    connect(ui->seconName,      SIGNAL(returnPressed()),    SLOT(setSecondName()));
    connect(ui->lastName,       SIGNAL(returnPressed()),    SLOT(setLastName()));
    connect(ui->position,       SIGNAL(returnPressed()),    SLOT(setPosition()));
    connect(ui->phone,          SIGNAL(returnPressed()),    SLOT(setPhone()));
    connect(ui->addExperience,  SIGNAL(clicked()),          SLOT(addExperience()));
}

MainWindow::~MainWindow()
{
    delete resume->getBase();
    delete resume;
    delete ui;
}

void MainWindow::updateOutput()
{
    ui->textOutput->setHtml(resume->toHTML());
}

void MainWindow::setName()
{
    resume->setName(ui->name->text());
    updateOutput();
}

void MainWindow::setLastName()
{
    resume->setLastName(ui->lastName->text());
    updateOutput();
}

void MainWindow::setSecondName()
{
    resume->setSecondnName(ui->seconName->text());
    updateOutput();
}

void MainWindow::setPosition()
{
    resume->setPosition(ui->position->text());
    updateOutput();
}

void MainWindow::setPhone()
{
    resume->setPhone(ui->phone->text());
    updateOutput();
}

void MainWindow::addExperience()
{
    resume->addExperience(Experience(ui->fromDate->date(),
                                     ui->toDate->date(),
                                     ui->company->text(),
                                     ui->experiencePosition->text()));
    updateOutput();
}

