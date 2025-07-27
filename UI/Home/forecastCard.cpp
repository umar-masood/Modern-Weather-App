#include "forecastCard.h"

ForecastCard::ForecastCard(QWidget *parent)
{  
   mainLayout = new QVBoxLayout(this);

   dayText = new QLabel;
   dayText->setWordWrap(true);
   dayText->setAlignment(Qt::AlignCenter);

   weatherIcon = new QLabel;

   conditionText = new QLabel;
   conditionText->setWordWrap(true);
   conditionText->setMinimumWidth(100);
   conditionText->setAlignment(Qt::AlignCenter);

   temp = new QLabel;

   mainLayout->addWidget(dayText, 0, Qt::AlignCenter);
   mainLayout->addWidget(weatherIcon, 0, Qt::AlignCenter);
   mainLayout->addWidget(conditionText, 0, Qt::AlignCenter);
   mainLayout->addWidget(temp, 0, Qt::AlignCenter);
   mainLayout->setContentsMargins(15,15,15,15);
   mainLayout->setSpacing(5);

   applyStyleSheet();
   setThemedFonts();
   applyShadow();
   applyToolTips();
}

void ForecastCard::setMinTemp(double value) { minTemp = value; }

void ForecastCard::setMaxTemp(double value) { maxTemp = value; }

void ForecastCard::setWeatherCondition(const QString &condition) { weatherCondition = condition; }

void ForecastCard::setDay(const QString &day){ this->day = day; }

void ForecastCard::setData() {
   dayText->setText(day);
   conditionText->setText(weatherCondition);

   QString t, tempUnit;
   t = setting.value("Temperature Unit").toString(); 
   tempUnit = (t == "Celsius (°C)") ? "°C" : "°F";
   temp->setText(QString("%1/%2<sup>%3</sup>").arg(maxTemp).arg(minTemp).arg(tempUnit)); 
}

void ForecastCard::applyStyleSheet() {
   this->setObjectName("mainCard");

   QString mainWidget = QString("#mainCard { background-color: %1; border-radius: 14px; border: none; }").arg(isDarkMode ? "#121212" :"#FFFFFF");
   QString metricsWidget = "QLabel { background-color: transparent; border: none; }";

   this->setAttribute(Qt::WA_StyledBackground, true);
   this->setStyleSheet(mainWidget);

   for (QLabel *l : {dayText, weatherIcon, conditionText, temp}) 
      if (l)  l->setAttribute(Qt::WA_TranslucentBackground);
   
   card.setDarkMode(isDarkMode);
   for (ToolTip *tip : {dayTip, conditionTip, tempTip}) {
      if (tip) tip->setDarkMode(isDarkMode);
   }
}

void ForecastCard::applyToolTips() {
   dayTip = new ToolTip(dayText, "Day");
   conditionTip = new ToolTip(conditionText, "Weather Condition");
   tempTip = new ToolTip(temp, "Minimum & Maximum Temperature");
}

void ForecastCard::applyShadow()
{
   if (!shadowEffect) {
      shadowEffect = new QGraphicsDropShadowEffect(this);
      this->setGraphicsEffect(shadowEffect);
   }

   if (shadowEffect) {
      shadowEffect->setBlurRadius(26); 
      shadowEffect->setOffset(0, 0);   
      if (isDarkMode) shadowEffect->setColor(QColor("#2C2C2C")); else shadowEffect->setColor(QColor("#B0C1D2"));  
   }
}

void ForecastCard::setThemedFonts()
{  
   dayText->setFont(card.font("Outfit", "Medium", 14, dayText, "#757575", "#B0B0B0"));
   conditionText->setFont(card.font("Outfit", "SemiBold", 14, conditionText, "black", "white"));
   temp->setFont(card.font("Outfit", "SemiBold", 14, temp, "black", "white"));
}

void ForecastCard::setWeatherIcon(const QString &iconPath)
{
   if (icon == iconPath) return;
   icon = iconPath;
   if (weatherIcon) weatherIcon->setPixmap(card.pixmap(icon, icon, QSize(60,60)));
}

void ForecastCard::setDarkMode(bool value)
{
   if (isDarkMode == value) return;
   isDarkMode = value;
   applyStyleSheet();
   setThemedFonts();
   applyShadow();
}
