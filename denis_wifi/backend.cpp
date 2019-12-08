#include "backend.h"
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QRandomGenerator>
#include <QtCore/QtMath>
#include <QPointF>
#include <iostream>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

BackEnd::BackEnd(QObject *parent) :
    QObject(parent),
    m_index(-1)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
}

void BackEnd::update(QAbstractSeries *series)
{
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        xySeries->replace(m_data);
}

void BackEnd::generateData()
{
    QPointF point;
    BackEnd::scan_station();
    point.setY(st_sig_strength);
   if(m_data.size() >= 10){
       point.setX(10);
       m_data.pop_back();
       m_data.prepend(point);
       return;
   }

   std::cout << point.x();
}

int BackEnd::gen_channel(){
    static int inited = 0;
    if (!inited){
        srand(time(NULL));
        inited = 1;
    }
    return rand()%20;
}


int BackEnd::find_interface(){
    FILE * fp = popen ("iw dev | awk '$1==\"Interface\"{print $2}'", "r");
    if (fp == NULL){
        fprintf(stderr, "Nepodaril sa vykonat popen\n");
        return 0;
    }
    int c = 0;
    for (int i = 0; i < 30; i++){
        c = fgetc(fp);
        if (feof(fp) || c == '\n'){
            c = i;
            break;
        }
        interface_name[i] = c;
    }
    interface_name[c] = '\0';
    pclose(fp);
    return 1;
}

int BackEnd::scan_all(){ // updatnut s initom a sleepom
    int status;
    if (errno != EBUSY){
        status=wifi_scan_all(wifi, bss, 10);
        return 1;
    } else {
        return 0;
    }
}

void BackEnd::set_station_data(){
    st_sig_strength = station->signal_dbm;
    st_avg_sig_strength = station->signal_avg_dbm;
    st_ssid = QString::fromUtf8(station->ssid);
}

int BackEnd::scan_station(){
    if (!find_interface()){
        return 1;
    }
    wifi = wifi_scan_init(interface_name);
    int status;
        if (errno != EBUSY){
            status=wifi_scan_station(wifi, station);
            set_station_data();
          //  emit success_station();
          //  appendFile("scan.out");
    }
}

void BackEnd::close_scanner(){
    wifi_scan_close(wifi);
}

void BackEnd::appendFile(std::string file_name){
  std::fstream file;

  if(access( file_name.c_str(), F_OK ) == -1){
    //does no exist, creating a new file
    file.open(file_name, std::fstream::in | std::fstream::app);
    //appending the firs row
    const std::string first_row = "id,ssid,signal strength,average signal strenght\n";
    file << first_row;
  }else{
    file.open(file_name, std::fstream::in | std::fstream::app);
  }
  const std::string output = std::to_string(f_id) + "," + station->ssid + "," + std::to_string(station->signal_dbm) + "," + std::to_string(station->signal_avg_dbm) + "\n";
  file << output;
  file.close();
}

