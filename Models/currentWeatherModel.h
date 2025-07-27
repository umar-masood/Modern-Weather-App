#pragma once
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonValue>
#include <QString>
#include <QFile>
#include <QDateTime>
#include <QStandardPaths>
#include <QDir>
#include "forecastModel.h"

class CurrentWeatherModel : public QObject{
   Q_OBJECT
   public:
   CurrentWeatherModel(QObject *parent = nullptr);

   void setUserLocation(const QString &userLocation);
   void fetchPreviousData();

   QString currentLocation();
   QString currentDay();
   QString currentDate();
   QString currentTime();
   QString currentWeatherIcon();
   QString currentWeatherDescrp();
   QString sunset();
   QString sunrise();
   int visibility_km();
   int visibility_miles();
   int humidity();
   int cloudiness();
   double windSpeed_mph();
   double windSpeed_kph();
   double currentTemp_c();
   double currentTemp_f();

   signals:
   void currentWeatherUpdated();
   void noInitialCurrentWeatherData();
   void errorNoLocationFound();
   void somethingWrong();

   private:
   void saveCurrentWeatherData();
   void parseWeatherData(const QJsonDocument &doc);
   void sendRequest();
   void validateJson();

   QString location, day, date, time, wDescrp, iconPath, userLocation, apiLink, sunRise, sunSet = QString();
   int visi_km, visi_miles, humi, cloud, iconCode = 0;
   double  wSpeed_mph, wSpeed_kph = 0.0;
   double cTemp_c, cTemp_f, latitude, longitude = 0.0;
   qint64 localtime_epoch = 0;
   const QString API_KEY = "7d860bec997f450985b90333252707";

   QNetworkAccessManager *manager = nullptr;
   QNetworkReply *reply = nullptr;
   QByteArray data;
   QJsonParseError parseError;
   QJsonDocument doc;
   QDateTime dt;

   ForecastModel forecastModel;

   private slots:
   void retrieveWeatherData();
};