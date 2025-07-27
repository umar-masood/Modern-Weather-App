#pragma once
#include <QtWidgets>
#include "../../components/ToolTip.h"
#include "../Settings/settings.h"

class CurrentWeatherCard : public QWidget{
   Q_OBJECT
   public:
   CurrentWeatherCard(QWidget *parent = nullptr);
   void updateUnits();

   QFont font(const QString &family, const QString& styleName, int pointSize, QLabel *text, const QString& colorLight, const QString &colorDark, int letterSpacing = 0);
   QPixmap pixmap(const QString &iconPath, const QString &iconPathDark, const QSize size);
   QSettings setting;
   QString tempUnit, windSpeedUnit, visibilityUnit;
   
   void setDarkMode(bool value);
   void setCurrentLocation(const QString &location);
   void setCurrentDateTime(const QString &day, const QString &time, const QString &date);
   void setCurrentTemp(double temp);
   void setCurrentWeatherDescrp(const QString &condition);
   void setVisibility(int value);
   void setHumidity(int percent);
   void setCloudiness(int percent);
   void setWindSpeed(int speed);
   void setSunrise(const QString &time);
   void setSunset(const QString &time);
   void setCurrentWeatherIcon(const QString &path);
   void setData();

   protected:
   void paintEvent(QPaintEvent *event) override;
   
   private:
   void init();
   void applyStyleSheet();
   void applyThemedFonts();
   void applyThemedIcons();
   void applyToolTips();
   void applyShadow();
   QVBoxLayout* metricsCardLayout(QWidget *parent, QWidget *w1, QWidget *w2);

   bool isDarkMode = false;
   QString location, day, date, time, iconPath, sunriseTime, sunsetTime, condition = QString();
   int visibility, humidity, windSpeed, cloudiness = 0;
   double temperature = 0.0;

   QWidget *headerWidget = nullptr; 
   QVBoxLayout *headerLayout = nullptr;
      QHBoxLayout *headerSubLayout = nullptr;
         QLabel *headerText = nullptr;
         QLabel *currentLocation = nullptr;
      
      QLabel *currentDay = nullptr;
      QLabel *currentDate = nullptr;
      QLabel *currentTime = nullptr;

   QWidget *weatherWidget = nullptr;
   QGridLayout *weatherLayout = nullptr;
      QLabel *temp = nullptr;
      QLabel *weatherDescp = nullptr;
   
   QWidget *visiblityWidget = nullptr;
   QVBoxLayout *visiblityLayout = nullptr;
      QLabel *visibilityText = nullptr;

   QWidget *humidityWidget = nullptr;
   QVBoxLayout *humidityLayout = nullptr;
      QLabel *humidityText = nullptr;

   QWidget *windSpeedWidget = nullptr;
   QVBoxLayout *windSpeedLayout = nullptr;
      QLabel *windSpeedText = nullptr;
   
   QWidget *cloudinessWidget = nullptr;
   QVBoxLayout *cloudinessLayout = nullptr;
      QLabel *cloudinessText = nullptr;

   QWidget *sunsetWidget = nullptr;
   QVBoxLayout *sunsetLayout = nullptr;
      QLabel *sunsetText = nullptr;

   QWidget *sunriseWidget = nullptr;
   QVBoxLayout *sunriseLayout = nullptr;
      QLabel *sunriseText = nullptr;

   QWidget *currentWeatherCard = nullptr;
   QVBoxLayout *currentWeatherCardLayout = nullptr;

   QLabel *locationIcon = nullptr;
   QLabel *weatherIcon = nullptr;
   QLabel *visibilityIcon = nullptr;
   QLabel *humidityIcon = nullptr;
   QLabel *windIcon = nullptr;
   QLabel *cloudinessIcon = nullptr;
   QLabel *sunriseIcon = nullptr;
   QLabel *sunsetIcon = nullptr;

   QGraphicsDropShadowEffect *shadowEffect = nullptr;

   ToolTip *locationTooltip = nullptr;
   ToolTip *visibilityTooltip = nullptr;
   ToolTip *humidityTooltip = nullptr;
   ToolTip *windTooltip = nullptr;
   ToolTip *cloudinessTooltip = nullptr;
   ToolTip *sunriseTooltip = nullptr;
   ToolTip *sunsetTooltip = nullptr;

   QGridLayout *gridLayout = nullptr;
   QHBoxLayout *mainLayout = nullptr;

};
