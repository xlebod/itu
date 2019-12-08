#ifndef BACKEND_H
#define BACKEND_H

#include <QtCharts/QAbstractSeries>
#include <QObject>
#include <QString>
#include "wifi_scan.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string>
#include <fstream>

#define WIFI_LIMIT 40
#define MAX_INTERFACE_LEN 20

QT_CHARTS_USE_NAMESPACE

class BackEnd : public QObject
{
    Q_OBJECT
    Q_PROPERTY(READ st_sig_strength NOTIFY success_station)
    Q_PROPERTY(READ st_avg_sig_strength NOTIFY success_station)
    Q_PROPERTY(READ st_ssid NOTIFY success_station)

public:
    explicit BackEnd(QObject *parent = nullptr);
    void close_scanner();
    int scan_all();
    int scan_station();
    void init_scanner();
    qreal st_sig_strength;
    qreal st_avg_sig_strength;
    QString st_ssid;
signals:
    void success_all();
    void success_station();
public slots:
    void update(QAbstractSeries *series);
    void generateData();
private:
    QList<QPointF> m_data;
    int m_index;
    struct wifi_scan *wifi;
    struct station_info *station;
    struct bss_info bss[WIFI_LIMIT];

    int f_id;
    void set_station_data();
    char interface_name[MAX_INTERFACE_LEN];
    int find_interface();
    int gen_channel();
    void appendFile(std::string file_name);
};

#endif // BACKEND_H
