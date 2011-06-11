#include <QNetworkAccessManager>
#include "btccm.h"
#include "ui_btccm.h"

btccm::btccm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::btccm)
{
    ui->setupUi(this);
    connect(&timer, SIGNAL(timeout()), this, SLOT(downloadCharts()));

    timer.start(60 * 1000);
    downloadCharts();
}

btccm::~btccm()
{
    delete ui;
}


void btccm::downloadCharts() {
    QUrl url("http://bitcoincharts.com/charts/chart.png?width=" + QString::number(ui->chartLabel->width()) + "&m=mtgoxUSD&k=&r=1&i=&c=0&s=&e=&Prev=&Next=&v=1&cv=0&ps=1&l=0&p=0&t=S&b=&a1=&m1=10&a2=&m2=25&x=0&i1=MACD&i2=Momentum&i3=BBW&i4=&SubmitButton=Draw&");
    QUrl orderbook("http://bitcoincharts.com/charts/mtgoxUSD/orderbook.png");
    QUrl aorderbook("http://bitcoincharts.com/charts/mtgoxUSD/accumulated_orderbook.png");


    downloadImage(SLOT(updateChart(QNetworkReply*)), url);
    downloadImage(SLOT(updateOrderbook(QNetworkReply*)), orderbook);
    downloadImage(SLOT(updateAOrderbook(QNetworkReply*)), aorderbook);
}


void btccm::downloadImage(const char* slot, QUrl url) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, slot);
    manager->get(QNetworkRequest(url));

}

void btccm::updateChart(QNetworkReply * reply) {
    updateLabel(ui->chartLabel, reply);
}

void btccm::updateOrderbook(QNetworkReply * reply) {
    updateLabel(ui->orderbookLabel, reply);
}

void btccm::updateAOrderbook(QNetworkReply * reply) {
    updateLabel(ui->aorderbookLabel, reply);
}

void btccm::updateLabel(QLabel *label, QNetworkReply * reply) {
    QImage image;
    if (!image.loadFromData(reply->readAll()))
        return ;

    QPixmap pixmap = QPixmap::fromImage(image);
    if(pixmap.isNull())
        return;

    label->setPixmap(pixmap);
}
