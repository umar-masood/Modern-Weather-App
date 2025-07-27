#include "currentWeatherModel.h"

CurrentWeatherModel::CurrentWeatherModel(QObject *parent) {
   manager = new QNetworkAccessManager(this);
}

void CurrentWeatherModel::setUserLocation(const QString &userLocation)
{  
   this->userLocation = userLocation;
   if (!userLocation.isEmpty()) sendRequest();
}

void CurrentWeatherModel::sendRequest()
{  
   apiLink = QString("https://api.weatherapi.com/v1/forecast.json?key=%1&q=%2&days=1&aqi=no").arg(API_KEY).arg(userLocation);
   QUrl url(apiLink);
   QNetworkRequest request(url);
   reply = manager->get(request);

   connect(reply, &QNetworkReply::finished, this, &CurrentWeatherModel::retrieveWeatherData);
}

void CurrentWeatherModel::retrieveWeatherData()
{  
   if (reply->error() != QNetworkReply::NoError) {
      qCritical() << "Error Fetching" << reply->errorString(); 
      data = reply->readAll();
      validateJson();
      QJsonObject mainObj = doc.object();
      if (mainObj.contains("error")) {
         QJsonObject errorObj = mainObj["error"].toObject();
         int errorCode = errorObj["code"].toInt();
         if (errorCode == 1006) 
            emit errorNoLocationFound();
         else 
            emit somethingWrong();
      }        
      return;
   } else {
      data = reply->readAll();
      validateJson();
      parseWeatherData(doc);
      saveCurrentWeatherData();
      emit currentWeatherUpdated();
   }
   reply->deleteLater();
}

void CurrentWeatherModel::saveCurrentWeatherData() {
   QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config";
   QDir dir(path);
   if (!dir.exists()) dir.mkpath(".");
   
   QFile file(path + "/weather.json");
   if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      file.write(data);
      file.close();
   }
}

void CurrentWeatherModel::parseWeatherData(const QJsonDocument &doc)
{
   QJsonObject mainObj = doc.object();
   QJsonObject locationObj = mainObj["location"].toObject();
   location = locationObj["name"].toString() + ", " + locationObj["country"].toString();
   latitude = locationObj["lat"].toDouble();
   longitude = locationObj["lon"].toDouble();
   localtime_epoch = locationObj["localtime_epoch"].toInt();
   QJsonObject currentObj = mainObj["current"].toObject();
   cTemp_c = currentObj["temp_c"].toDouble();
   cTemp_f = currentObj["temp_f"].toDouble();

   QJsonObject conditionObj = currentObj["condition"].toObject();
   QString condText = conditionObj["text"].toString();
   if (condText == "Patchy rain nearby") wDescrp = "Light rain nearby";
   else wDescrp = condText;

   iconCode = conditionObj["code"].toInt();
   iconPath = forecastModel.forecastIcons.value(iconCode, "");
   
   wSpeed_mph = currentObj["wind_mph"].toDouble();
   wSpeed_kph = currentObj["wind_kph"].toDouble();
   humi = currentObj["humidity"].toInt();
   cloud = currentObj["cloud"].toInt();
   visi_km = currentObj["vis_km"].toInt();
   visi_miles = currentObj["vis_miles"].toInt();
   
   QJsonArray forecastArray = mainObj["forecast"].toObject()["forecastday"].toArray();
      if (!forecastArray.isEmpty()) {
        QJsonObject firstDay = forecastArray[0].toObject();
        QJsonObject astroObj = firstDay["astro"].toObject();
        sunRise = astroObj["sunrise"].toString();
        sunSet = astroObj["sunset"].toString();
      }
   
   dt = QDateTime::fromSecsSinceEpoch(localtime_epoch);
}

void CurrentWeatherModel::fetchPreviousData()
{
   QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config/weather.json";
   QFile file(path);

   if (!file.exists())  {
      emit noInitialCurrentWeatherData();
      return; 
   } 

   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      data = file.readAll();
      file.close();
   }

   validateJson();
   parseWeatherData(doc);
   emit currentWeatherUpdated();
}

void CurrentWeatherModel::validateJson() {
   doc = QJsonDocument::fromJson(data, &parseError);
   if (parseError.error != QJsonParseError::NoError) {
      qCritical() << "Parsing Error";
      return;
   }
   if (!doc.isObject()) return;
}

QString CurrentWeatherModel::currentLocation() { return location; }

QString CurrentWeatherModel::currentDay() { return dt.toString("dddd"); }

QString CurrentWeatherModel::currentDate() { return dt.toString("dd MMMM yyyy"); }

QString CurrentWeatherModel::currentTime() { return dt.toString("hh:mm:ss AP"); }

double CurrentWeatherModel::currentTemp_c() { return cTemp_c; }

double CurrentWeatherModel::currentTemp_f() { return cTemp_f; }

QString CurrentWeatherModel::currentWeatherDescrp() { return wDescrp; }

int CurrentWeatherModel::visibility_km() { return visi_km; }

int CurrentWeatherModel::visibility_miles() { return visi_miles; }

int CurrentWeatherModel::humidity() { return humi; }

int CurrentWeatherModel::cloudiness() { return cloud; }

double CurrentWeatherModel::windSpeed_kph() { return wSpeed_kph; }

double CurrentWeatherModel::windSpeed_mph() { return wSpeed_mph; }

QString CurrentWeatherModel::currentWeatherIcon() { return iconPath; }

QString CurrentWeatherModel::sunrise() { return sunRise; }

QString CurrentWeatherModel::sunset() { return sunSet; }