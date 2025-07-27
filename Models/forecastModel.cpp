#include "forecastModel.h"

ForecastModel::ForecastModel(QObject * parent) { 
   manager = new QNetworkAccessManager(this); }

void ForecastModel::sendRequest() {
   apiLink = QString("https://api.weatherapi.com/v1/forecast.json?key=%1&q=%2&days=7").arg(API_KEY).arg(userLocation);
   QUrl url(apiLink);
   QNetworkRequest request(url);
   reply = manager->get(request);

   connect(reply, &QNetworkReply::finished, this, &ForecastModel::retrieveWeatherData);
}

void ForecastModel::saveCurrentWeatherData(){
   QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config";

   QDir dir(path);
   if (!dir.exists()) {
      dir.mkpath(".");
   }

   QFile file(path + "/forecast.json");
   if(file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      file.write(data);
      file.close();
   }
}

void ForecastModel::fetchPreviousData()
{
   QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/config/forecast.json";
   QFile file(path);

   if (!file.exists()) return; 
   if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      data = file.readAll();
      file.close();
   }

   doc = QJsonDocument::fromJson(data, &parseError);

   if (parseError.error != QJsonParseError::NoError) return;
   if (!doc.isObject()) return;

   parseWeatherData(doc);
   emit forecastWeatherUpdated();
}

bool ForecastModel::validateIndex() {  return index >= 0 && index < forecastDataList.size(); }

void ForecastModel::retrieveWeatherData() {
   if (reply->error() != QNetworkReply::NoError) {
      qDebug() << "Error Fetching Data form API" << reply->errorString(); return;
   } else {
      data = reply->readAll();
      doc = QJsonDocument::fromJson(data, &parseError);

      if (parseError.error != QJsonParseError::NoError)  return;
      if (!doc.isObject()) return;
      
      parseWeatherData(doc);
      saveCurrentWeatherData();

      emit forecastWeatherUpdated();
      reply->deleteLater();
   }
}

void ForecastModel::parseWeatherData(const QJsonDocument &doc) {
   forecastDataList.clear();

   QJsonObject mainObj = doc.object();
   QJsonObject forecastObj = mainObj["forecast"].toObject();
   QJsonArray forecastArr = forecastObj["forecastday"].toArray();
      
   for (auto i = 0; i < forecastArr.size(); i++) {
      QJsonObject forecastDayObj = forecastArr[i].toObject();
      localdate_epoch = forecastDayObj["date_epoch"].toInteger(); 
      
      QJsonObject dayObj = forecastDayObj["day"].toObject();
      forecastDay.minTemp_c = dayObj["mintemp_c"].toDouble();
      forecastDay.minTemp_f = dayObj["mintemp_f"].toDouble();
      forecastDay.maxTemp_c = dayObj["maxtemp_c"].toDouble();
      forecastDay.maxTemp_f = dayObj["maxtemp_f"].toDouble();
      
      QJsonObject conditionObj = dayObj["condition"].toObject();
      QString condText = conditionObj["text"].toString();
      if (condText == "Patchy rain nearby")
         forecastDay.weatherDescrp = "Light rain nearby";
      else 
         forecastDay.weatherDescrp = condText;

      int iconCode = conditionObj["code"].toInt();  
      forecastDay.iconPath = forecastIcons.value(iconCode, "");

      dt = QDateTime::fromSecsSinceEpoch(localdate_epoch);
      forecastDay.day = dt.toString("dddd");
      forecastDataList.append(forecastDay);
   }
}

void ForecastModel::setUserLocation(const QString &userLocation)
{  
   this->userLocation = userLocation;
   if (!userLocation.isEmpty()) sendRequest();
}

void ForecastModel::setCurrentIndex(int index) { this->index = index; }

QString ForecastModel::currentDay() {
   return validateIndex() ? forecastDataList[index].day : "";
}

QString ForecastModel::weatherCondition() {
   return validateIndex() ? forecastDataList[index].weatherDescrp : "";
}

double ForecastModel::minimumTemp_c() {
   return validateIndex() ? forecastDataList[index].minTemp_c : 0.0;
}

double ForecastModel::maximumTemp_c() {
   return validateIndex() ? forecastDataList[index].maxTemp_c : 0.0;
}

double ForecastModel::minimumTemp_f() {
   return validateIndex() ? forecastDataList[index].minTemp_f : 0.0;
}

double ForecastModel::maximumTemp_f() {
   return validateIndex() ? forecastDataList[index].maxTemp_f : 0.0;
}

QString ForecastModel::weatherIcon() {
   return validateIndex() ? forecastDataList[index].iconPath : "";
}

