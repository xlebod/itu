#ifndef BACKEND_H
#define BACKEND_H

#include <QtCharts/QAbstractSeries>
#include <QObject>
#include <QString>
#include <QJsonObject>
#include "wifi_scan.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string>
#include <fstream>
#include <QJsonDocument>

#define WIFI_LIMIT 40
#define MAX_INTERFACE_LEN 20

QT_CHARTS_USE_NAMESPACE

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ssid READ get_ssid NOTIFY network_changed)
    Q_PROPERTY(QString channel READ get_channel NOTIFY network_changed)
    Q_PROPERTY(QString encryption READ get_enc NOTIFY network_changed)
    Q_PROPERTY(QString frequency READ get_frq NOTIFY network_changed)
    Q_PROPERTY(QString interface READ get_interface NOTIFY network_changed)
    Q_PROPERTY(int signalStrength READ get_sS NOTIFY sS_changed)
    Q_PROPERTY(int linkQuality READ get_lQ NOTIFY lQ_changed)
    Q_PROPERTY(int sentPackets READ get_packets NOTIFY packets_changed)
public:
    explicit BackEnd(QObject *parent = nullptr);
    int linkQuality;
    int signalStrength;
    QString ssid;
    QString channel;
    QString encryption;
    QString frequency;
    QString interface;
    int sentPackets;
    QString get_ssid();
    QString get_channel();
    QString get_enc();
    QString get_frq();
    QString get_interface();
    int get_sS();
    int get_lQ();
    int get_packets();
signals:
    void network_changed();
    void sS_changed();
    void lQ_changed();
    void packets_changed();
public slots:
    void set_sS();
    void set_lQ();
    void set_packets();
    void graphData();
    void update(QAbstractSeries *series);
    void generateData();
    bool loadFile(QString file_path);
    void resetData();
private:
    QVector<QPointF> m_data;
    int a;
    QJsonDocument json_doc;
    QJsonObject json_obj;
};

#endif // BACKEND_H
