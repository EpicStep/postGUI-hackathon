#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QTimer"
#include "QtDebug"
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"
#include "QUrlQuery"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(unlockAndSetVisible()));

    ui->textBrowser->setVisible(false);

    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::netReply);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::netReply(QNetworkReply *reply) {
    if (reply->error()) {
        ui->textBrowser->setText(reply->errorString());
    } else {
        ui->textBrowser->setText(reply->readAll());
    }

    timer->start(5000);
    reply->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(true);
    ui->textBrowser->setVisible(true);
    QNetworkRequest request(QUrl("http://localhost:8000/api"));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    manager->post(request, "{'param1': 1, 'param2': 2}");
}

void MainWindow::unlockAndSetVisible() {
    ui->textBrowser->setText("");
    ui->pushButton->setDisabled(false);
    ui->textBrowser->setVisible(false);
}
