#ifndef BTCCM_H
#define BTCCM_H

#include <QMainWindow>
#include <QTimer>
#include <QtNetwork>
#include <QLabel>

namespace Ui {
    class btccm;
}

class btccm : public QMainWindow
{
    Q_OBJECT

public:
    explicit btccm(QWidget *parent = 0);
    ~btccm();

public slots:
    void downloadCharts();
    void updateChart(QNetworkReply * reply);
    void updateOrderbook(QNetworkReply * reply);
    void updateAOrderbook(QNetworkReply * reply);

protected:
    void downloadImage(const char* slot, QUrl url);
    void updateLabel(QLabel *label, QNetworkReply * reply);

private:



    Ui::btccm *ui;
    QTimer timer;
    QLabel orderbookLabel;
    QLabel aorderbookLabel;

};

#endif // BTCCM_H
