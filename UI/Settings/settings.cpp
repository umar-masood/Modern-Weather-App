#include "Settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent)
{
   setContentsMargins(0, 0, 0, 0);
   setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   setObjectName("mainObj");

   // Header
   headerText = new QLabel("Settings");
   headerIcon = new QLabel;

   QHBoxLayout *headerLayout = new QHBoxLayout;
   headerLayout->setContentsMargins(0, 0, 0, 0);
   headerLayout->addWidget(headerIcon, 0, Qt::AlignLeft);
   headerLayout->addSpacing(10);
   headerLayout->addWidget(headerText, 0, Qt::AlignLeft);
   headerLayout->addStretch();

   // Cards Data
   // Country
   countryMain = new QLabel("Default Country or Region");
   countrySub = new QLabel("The app may use your default location to display current weather");
   countryIcon = new QLabel;

   countryBox = new ComboBox;
   countryBox->setSize(QSize(280, 36));
   countryBox->addItems(countries);
   countryBox->setMaxVisibleItems(15);
   countryBox->setPlaceholderText("Select Your Country");

   // Temperature
   tempMain = new QLabel("Temperature Unit");
   tempSub = new QLabel("Choose how temperature is displayed");
   tempIcon = new QLabel;

   tempBox = new ComboBox;
   tempBox->setSize(QSize(200, 36));
   tempBox->addItems({"Celsius (°C)", "Fahrenheit (°F)"});
   tempBox->setPlaceholderText("Select Temp Unit");
   tempBox->setCurrentIndex(0);

   // Wind
   windMain = new QLabel("Wind Speed Unit");
   windSub = new QLabel("Changes will affect how wind speed appears on the home screen");
   windIcon = new QLabel;

   windBox = new ComboBox;
   windBox->setSize(QSize(260, 36));
   windBox->addItems({"Kilometers per hour (km/h)", "Miles per hour (mph)"});
   windBox->setPlaceholderText("Select Wind Speed Unit");
   windBox->setCurrentIndex(0);

   // Visibility
   visibilityMain = new QLabel("Visibility Unit");
   visibilitySub = new QLabel("Changes will affect how visibility appears on the home screen");
   visibilityIcon = new QLabel;

   visibilityBox = new ComboBox;
   visibilityBox->setSize(QSize(200, 36));
   visibilityBox->addItems({"Kilometers (km)", "Miles (mi)"});
   visibilityBox->setPlaceholderText("Select Visibility Speed Unit");
   visibilityBox->setCurrentIndex(0);

   // Theme 
   themeMain = new QLabel("Appearance");
   themeSub = new QLabel("Select which app theme to display");
   themeIcon = new QLabel;

   themeBox = new ComboBox;
   themeBox->setSize(QSize(200, 36));
   themeBox->addItems({"Light theme", "Dark theme"});
   themeBox->setCurrentIndex(0);
   
   // Cards
   QWidget* cards[] = {
      countryWidget = settingCard(countryMain, countrySub, countryIcon, countryBox),
      tempWidget = settingCard(tempMain, tempSub, tempIcon, tempBox),
      windWidget = settingCard(windMain, windSub, windIcon, windBox),
      visibilityWidget = settingCard(visibilityMain, visibilitySub, visibilityIcon, visibilityBox),
      themeWidget = settingCard(themeMain, themeSub, themeIcon, themeBox),
   };
   
   QVBoxLayout *cardsLayout = new QVBoxLayout(this);
   cardsLayout->setContentsMargins(50, 15, 50, 15);
   cardsLayout->addLayout(headerLayout); 
   cardsLayout->addSpacing(10);
      
   for (QWidget* card : cards) {
      cardsLayout->addSpacing(6);
      cardsLayout->addWidget(card);
   }
   cardsLayout->addStretch();   

   applyFontStyles();
   applyThemedIcons();
   applyStyleSheet();

   saveDefaultsIfMissing();
   loadSettings();

   connect(countryBox, &ComboBox::valueChanged, this, &Settings::saveCountry);
   connect(tempBox, &ComboBox::valueChanged, this, &Settings::saveTempUnit);
   connect(windBox, &ComboBox::valueChanged, this, &Settings::saveWindUnit);
   connect(visibilityBox, &ComboBox::valueChanged, this, &Settings::saveVisibilityUnit);
   connect(themeBox, &ComboBox::valueChanged, this, &Settings::saveDefaultTheme);

   applyThemeToComponents();
}

void Settings::saveDefaultsIfMissing() {
   QSettings setting;

   if (!setting.contains("Country")) saveCountry(countryBox->currentText());
   if (!setting.contains("Temperature Unit")) saveTempUnit(tempBox->currentText());
   if (!setting.contains("Wind Speed Unit")) saveWindUnit(windBox->currentText());
   if (!setting.contains("Visibility Unit")) saveVisibilityUnit(visibilityBox->currentText());
   if (!setting.contains("Default theme")) saveDefaultTheme(themeBox->currentText());
}

void Settings::saveCountry(const QString &text) {
   QSettings setting;
   setting.setValue("Country", text);
   emit settingValueChanged();
}

void Settings::saveTempUnit(const QString &text) {
   QSettings setting;
   setting.setValue("Temperature Unit", text);
   emit settingValueChanged();
}

void Settings::saveWindUnit(const QString &text) {
   QSettings setting;
   setting.setValue("Wind Speed Unit", text);
   emit settingValueChanged();
}

void Settings::saveVisibilityUnit(const QString &text) {
   QSettings setting;
   setting.setValue("Visibility Unit", text);
   emit settingValueChanged();
}

void Settings::saveDefaultTheme(const QString &text) {
   QSettings setting;
   setting.setValue("Default theme", text);
   emit themeValueChanged();
}

void Settings::applyThemeToComponents() {
   countryBox->setDarkMode(isDarkMode);
   tempBox->setDarkMode(isDarkMode);
   windBox->setDarkMode(isDarkMode);
   visibilityBox->setDarkMode(isDarkMode);
   themeBox->setDarkMode(isDarkMode);
}

void Settings::loadSettings() {
 QSettings setting;

 QString country = setting.value("Country").toString();
 QString temp = setting.value("Temperature Unit").toString();
 QString wind = setting.value("Wind Speed Unit").toString();
 QString visibility = setting.value("Visibility Unit").toString();
 QString theme = setting.value("Default theme").toString();

 if (!country.isEmpty()) countryBox->setCurrentText(country);
 if (!temp.isEmpty()) tempBox->setCurrentText(temp);
 if (!wind.isEmpty()) windBox->setCurrentText(wind);
 if (!visibility.isEmpty()) visibilityBox->setCurrentText(visibility);
 if (!theme.isEmpty()) themeBox->setCurrentText(theme);

}

QPixmap Settings::pixmap(int light, int dark) {
   return QPixmap(isDarkMode ? cardsIcons[dark] : cardsIcons[light]).scaled({24, 24}, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
}

void Settings::applyFontStyles() {
   QFont font("Outfit", 20);
   font.setStyleName("Bold");
   headerText->setFont(font);
   headerText->setStyleSheet(QString("background-color: transparent; color: %1; letter-spacing: 2px;").arg(isDarkMode ? "white" : "black"));

   for (QLabel* x : {countryMain, tempMain, visibilityMain, windMain, themeMain}) 
      x->setStyleSheet(QString("background-color: transparent; font-family: Segoe UI; font-size: 14px; margin: 0px; color: %1;").arg(isDarkMode ? "#FFFFFF" : "#000000")); 

   for (QLabel* y : {countrySub, tempSub, visibilitySub, windSub, themeSub}) 
      y->setStyleSheet(QString("background-color: transparent; font-family: Segoe UI; font-size: 12px; margin: 0px; color: %1;").arg(isDarkMode ? "#BBBBBB" : "#666666"));
}

void Settings::applyThemedIcons() {
   headerIcon->setPixmap(QPixmap(isDarkMode ? headerIconPathDark : headerIconPathLight).scaled(QSize(30, 30), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
   countryIcon->setPixmap(pixmap(3, 2));
   visibilityIcon->setPixmap(pixmap(9, 10));
   tempIcon->setPixmap(pixmap(5, 4));
   windIcon->setPixmap(pixmap(11, 12));
   themeIcon->setPixmap(pixmap(6, 7));
}

void Settings::applyStyleSheet() {
   for (QWidget* card : {countryWidget, tempWidget, windWidget, visibilityWidget, themeWidget}) 
      card->setStyleSheet(QString( "QWidget { background-color: %1; border: none; border-radius: 8px; } QWidget::hover { background-color: %2; }").arg(isDarkMode ? "#2B2B2B" : "#FBFBFB").arg(isDarkMode ? "#3A3A3A" : "#F0F0F0"));   

   for (QLabel* icons : {countryIcon, windIcon, tempIcon, visibilityIcon, themeIcon})
      icons->setStyleSheet(QString("background-color: transparent;"));  

   setStyleSheet("#mainObj { background-color: transparent; border: none; }");
}

QWidget* Settings::settingCard(QLabel *main, QLabel *sub, QLabel *icon, ComboBox *w) {
   /* Card Widget */
   QWidget *card = new QWidget;
   card->setAttribute(Qt::WA_StyledBackground, true);
   card->setFixedHeight(64);
   card->setMinimumWidth(400);
   card->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

   /* Layouts */
   QHBoxLayout *mainLayout = new QHBoxLayout(card);
   mainLayout->setContentsMargins(20, 5, 20, 5);
   mainLayout->addSpacing(10);
   mainLayout->addWidget(icon, 0, Qt::AlignLeft | Qt::AlignVCenter);
   mainLayout->addSpacing(20);

   QVBoxLayout *labelsLayout = new QVBoxLayout();
   labelsLayout->setContentsMargins(0,0,0,0);
   labelsLayout->setSpacing(0);
   labelsLayout->addWidget(main, 0);
   labelsLayout->addSpacing(1);
   labelsLayout->addWidget(sub, 0);

   mainLayout->addLayout(labelsLayout);
   mainLayout->setAlignment(labelsLayout, Qt::AlignVCenter | Qt::AlignLeft);
   mainLayout->addStretch();
   if (w) {
      mainLayout->addWidget(w, 1, Qt::AlignVCenter);
      mainLayout->addSpacing(10);
   }
   return card;
}

void Settings::setDarkMode(bool value) {
   if (isDarkMode == value) return;
   isDarkMode = value;
   applyThemeToComponents();
   applyFontStyles();
   applyThemedIcons();
   applyStyleSheet();
}
