#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtNetwork/QNetworkAccessManager"
#include "QtNetwork/QNetworkReply"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void unlockAndSetVisible();
private slots:
    void on_pushButton_clicked();
    void netReply(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
};
#endif // MAINWINDOW_H
