#pragma once

#include <QtWidgets>
#include "currentWeatherCard.h"
#include "../../components/ToolTip.h"


class ForecastCard : public QWidget {
   Q_OBJECT
   public:
   ForecastCard(QWidget *parent = nullptr);

   void setThemedFonts();
   void setWeatherIcon(const QString &iconPath);
   void setDarkMode(bool value);
   void setMinTemp(double value);
   void setMaxTemp(double value);
   void setWeatherCondition(const QString &condition);
   void setDay(const QString &day);
   void setData();

   private:
   void applyStyleSheet();
   void applyToolTips();
   void applyShadow();

   bool isDarkMode = false;
   double minTemp, maxTemp = 0.0;
   QString weatherCondition, day, icon = QString();

   QVBoxLayout *mainLayout = nullptr;
   QLabel *dayText = nullptr;
      ToolTip *dayTip = nullptr;
   QLabel *weatherIcon = nullptr;
   QLabel *conditionText = nullptr;
      ToolTip *conditionTip = nullptr;
   QLabel *temp = nullptr;
      ToolTip *tempTip = nullptr;

   QGraphicsDropShadowEffect *shadowEffect = nullptr;
   QSettings setting;
   CurrentWeatherCard card;
};