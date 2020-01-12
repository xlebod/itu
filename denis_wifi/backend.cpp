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
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

BackEnd::BackEnd(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
}

void BackEnd::graphData()
{
    QPointF point;
    point.setY(linkQuality);
    if(m_data.size() >= 10){
        point.setX(9);
        m_data.pop_front();
        m_data.append(point);
        for(int i = 0; i < 10; i++){
            QPointF temp = m_data.at(i);
            temp.setX(i);
            m_data.replace(i,temp);
        }
        return;
    }
    point.setX(m_data.size());
    m_data.append(point);
}

void BackEnd::update(QAbstractSeries *series)
{
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        qDebug() << m_data;
        xySeries->replace(m_data);
}
bool BackEnd::loadFile(QString file_path)
{

    QFile file_obj(file_path);
    if(!file_obj.exists()){
        std::cout << "You're fucked." << std::endl;
        exit(1);
    }
    if (!file_obj.open(QIODevice::ReadOnly)) {
        std::cout << "Failed to open file " << std::endl;
        exit(1);
        }
    QTextStream file_text(&file_obj);
    QString json_string;
    json_string = file_text.readAll();
    file_obj.close();
    QByteArray json_bytes = json_string.toLocal8Bit();
    json_doc = QJsonDocument::fromJson(json_bytes);

    if (json_doc.isNull()) {
        std::cout << "Failed to create JSON doc." << std::endl;
        return false;
    }
    if (!json_doc.isObject()) {
        std::cout << "JSON is not an object." << std::endl;
        return false;
    }

    json_obj = json_doc.object();

    if (json_obj.isEmpty()) {
        std::cout << "JSON object is empty." << std::endl;
        return false;
    }

    emit network_changed();
    return true;
}
void BackEnd::generateData()
{
    ssid = get_ssid();
    channel = get_channel();
    encryption = get_enc();
    frequency = get_frq();
    interface = get_interface();
    signalStrength = get_sS();
    linkQuality = get_lQ();
    sentPackets = get_packets();
}
QString BackEnd::get_ssid()
{

    if(ssid != json_obj["ssid"].toString())
        ssid = json_obj["ssid"].toString();
    return ssid;
}

QString BackEnd::get_channel()
{

    if(channel != json_obj["channel"].toString())
        channel = json_obj["channel"].toString();
    return channel;
}

QString BackEnd::get_enc()
{

    if(encryption != json_obj["encryption"].toString())
        encryption = json_obj["encryption"].toString();
    return encryption;
}

QString BackEnd::get_frq()
{

    if(frequency != json_obj["frequency"].toString())
        frequency = json_obj["frequency"].toString();
    return frequency;
}

QString BackEnd::get_interface()
{

    if(interface != json_obj["interface"].toString())
        interface = json_obj["interface"].toString();
    return interface;
}

int BackEnd::get_sS()
{
    if(signalStrength != json_obj["signalStrength"].toInt()){
        signalStrength = json_obj["signalStrength"].toInt();
    }
    return signalStrength;
}

int BackEnd::get_lQ()
{
    if(linkQuality != json_obj["linkQuality"].toInt()){
        linkQuality = json_obj["linkQuality"].toInt();
    }
    return linkQuality;
}

int BackEnd::get_packets()
{
    if(sentPackets != json_obj["sentPackets"].toInt()){
        sentPackets = json_obj["sentPackets"].toInt();
    }
    return sentPackets;
}

void BackEnd::set_sS()
{
    int inc = rand() % 5 + (-2);
    int newVal = json_obj["signalStrength"].toInt() + inc;
    if (newVal >= -30)
        newVal = -30;
    json_obj.insert("signalStrength",newVal);
    emit sS_changed();
}

void BackEnd::set_lQ()
{
    int inc = rand() % 7 + (-3);
    int newVal = json_obj["linkQuality"].toInt() + inc;
    if (newVal >= 100){
        newVal = 100;
    }
    json_obj.insert("linkQuality",newVal);
    emit lQ_changed();
}

void BackEnd::set_packets()
{
    int inc = rand() % 15 + 2;
    int newVal = json_obj["sentPackets"].toInt() + inc;
    json_obj.insert("sentPackets",newVal);
    emit packets_changed();
}

void BackEnd::resetData()
{
    json_obj.insert("ssid","Test Wifi");
    json_obj.insert("signalStrength", -36);
    json_obj.insert("linkQuality", 95);
    json_obj.insert("channel","1");
    json_obj.insert("encryption","WPA");
    json_obj.insert("frequency","2.427GHz");
    json_obj.insert("interface", "wlan0");
    json_obj.insert("sentPackets",0);
}
