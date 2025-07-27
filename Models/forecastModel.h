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
#include <QMap>

class ForecastModel : public QObject{
   Q_OBJECT

   public:
   ForecastModel(QObject *parent = nullptr);

   void setUserLocation(const QString &userLocation);
   void setCurrentIndex(int index);
   void fetchPreviousData();

   struct ForecastDayData {
      QString day, weatherDescrp, iconPath;
      double minTemp_c, minTemp_f, maxTemp_f, maxTemp_c;
   };

   QMap <int, QString> forecastIcons = {
      {1000, ":/Assets/Icons/sunny.png"}, 
      {1000 + 10000, ":/Assets/Icons/full_moon.png"}, 
      
      {1003, ":/Assets/Icons/partly_cloudy.png"},
      {1003 + 10000, ":/Assets/Icons/moon_small_cloud.png"}, 
      {1006, ":/Assets/Icons/cloudy.png"},
      {1006 + 10000, ":/Assets/Icons/moon_half_cloud.png"}, 
      {1009, ":/Assets/Icons/overcast.png"},
      {1009 + 10000, ":/Assets/Icons/half_moon.png"}, 
      
      {1030, ":/Assets/Icons/mist.png"},
      {1135, ":/Assets/Icons/mist.png"},
      {1147, ":/Assets/Icons/freezing_fog.png"},
      
      {1063, ":/Assets/Icons/light_sun_rain.png"},
      {1180, ":/Assets/Icons/light_sun_rain.png"},
      {1240, ":/Assets/Icons/light_sun_rain.png"},
      
      {1183, ":/Assets/Icons/light_rain.png"},
      {1186, ":/Assets/Icons/moderate_rain.png"},
      {1189, ":/Assets/Icons/moderate_rain.png"},
      {1192, ":/Assets/Icons/heavy_rain.png"},
      {1195, ":/Assets/Icons/heavy_rain.png"},
      
      {1087, ":/Assets/Icons/thundery_outbreaks.png"},
      {1273, ":/Assets/Icons/sun_thunder_cloud.png"},
      {1276, ":/Assets/Icons/heavy_rain_thunder.png"},
      
      {1114, ":/Assets/Icons/blowing_snow.png"},
      {1117, ":/Assets/Icons/blizzard.png"},
      {1210, ":/Assets/Icons/snow_showers.png"},
      {1213, ":/Assets/Icons/snow_showers.png"},
      {1216, ":/Assets/Icons/snow_showers.png"},
      {1219, ":/Assets/Icons/snow_showers.png"},
      {1222, ":/Assets/Icons/snow_showers.png"},
      {1225, ":/Assets/Icons/snow_showers.png"},
      
      {1252, ":/Assets/Icons/heavy_sleet_showers.png"},
      {1237, ":/Assets/Icons/ice_pellets.png"},
      {1261, ":/Assets/Icons/ice_pellets.png"},
      {1264, ":/Assets/Icons/ice_pellets.png"},
      
      {1072, ":/Assets/Icons/freezing_drizzle.png"},
      {1168, ":/Assets/Icons/freezing_drizzle.png"},
      {1171, ":/Assets/Icons/heavy_freezing_drizzle.png"},
   };

   QString currentDay();
   QString weatherCondition();
   QString weatherIcon();
   double minimumTemp_c();
   double maximumTemp_c();
   double minimumTemp_f();
   double maximumTemp_f();

   signals:
   void forecastWeatherUpdated();

   private:
   void saveCurrentWeatherData();
   void parseWeatherData(const QJsonDocument &doc);
   void sendRequest();
   bool validateIndex();

   ForecastDayData forecastDay;
   QVector<ForecastDayData> forecastDataList;

   int index = 0;
   qint64 localdate_epoch = 0;
   QString userLocation, apiLink = QString();
   const QString API_KEY = "7d860bec997f450985b90333252707";

   QNetworkAccessManager *manager = nullptr;
   QNetworkReply *reply = nullptr;
   QByteArray data;
   QJsonParseError parseError;
   QJsonDocument doc;
   QDateTime dt;

   private slots:
   void retrieveWeatherData();
};