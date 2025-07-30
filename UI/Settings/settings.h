#pragma once
#include "../../components/RoundedBox.h"
#include "../../components/ComboBox.h"
#include "../../components/Button.h"
#include <QtWidgets>

class Settings : public QWidget {
   Q_OBJECT
   public:
   Settings(QWidget *parent = nullptr);
   ~Settings() noexcept override = default;

   void setDarkMode(bool value);

private:
   void applyFontStyles();
   void applyThemedIcons();
   void applyStyleSheet();
   void applyThemeToComponents();
   void loadSettings();
   void saveDefaultsIfMissing();

   QWidget* settingCard(QLabel *main, QLabel *sub, QLabel *icon, ComboBox *w);
   QPixmap pixmap(int iconLightKey, int iconDarkKey);

   QLabel *headerText = nullptr;
   QLabel *headerIcon = nullptr;
   const QString headerIconPathLight = ":/Assets/Icons/settings_light.svg";
   const QString headerIconPathDark = ":/Assets/Icons/settings.svg";
   QHBoxLayout *headerLayout = nullptr;

   bool isDarkMode = true;

   QWidget *countryWidget = nullptr;
   QWidget *windWidget = nullptr;
   QWidget *tempWidget = nullptr;
   QWidget *visibilityWidget = nullptr;
   QWidget *themeWidget = nullptr;

   QVBoxLayout *cardsLayout = nullptr;
   QMap<int, QString> cardsIcons = {
      {2, ":/Assets/Icons/country_dark.svg"},
      {3, ":/Assets/Icons/country_light.svg"},
      {4, ":/Assets/Icons/thermometer_dark.svg"},
      {5, ":/Assets/Icons/thermometer_light.svg"},
      {6, ":/Assets/Icons/palette_light.svg"},
      {7, ":/Assets/Icons/palette_dark.svg"},
      {9, ":/Assets/Icons/waves_light.svg"},
      {10, ":/Assets/Icons/waves.svg"},
      {11, ":/Assets/Icons/wind_light.svg"},
      {12, ":/Assets/Icons/wind.svg"}
   };

   QLabel *countryMain, *countrySub;
   QLabel *tempMain, *tempSub;
   QLabel *windMain, *windSub;
   QLabel *visibilityMain, *visibilitySub;
   QLabel *themeMain, *themeSub;

   QLabel *countryIcon = nullptr;
   QLabel *visibilityIcon = nullptr;
   QLabel *windIcon = nullptr;
   QLabel *tempIcon = nullptr;
   QLabel *themeIcon = nullptr;

   ComboBox *countryBox = nullptr;
   QStringList countries = {
    "Afghanistan", "Albania", "Algeria", "Andorra", "Angola", "Antigua and Barbuda", "Argentina", "Armenia", "Australia", "Austria", "Azerbaijan",
    "Bahamas", "Bahrain", "Bangladesh", "Barbados", "Belarus", "Belgium", "Belize", "Benin", "Bhutan", "Bolivia", "Bosnia and Herzegovina", "Botswana", "Brazil", "Brunei", "Bulgaria", "Burkina Faso", "Burundi",
    "Cabo Verde", "Cambodia", "Cameroon", "Canada", "Central African Republic", "Chad", "Chile", "China", "Colombia", "Comoros", "Congo (Congo-Brazzaville)", "Costa Rica", "Croatia", "Cuba", "Cyprus", "Czech Republic",
    "Democratic Republic of the Congo", "Denmark", "Djibouti", "Dominica", "Dominican Republic",
    "Ecuador", "Egypt", "El Salvador", "Equatorial Guinea", "Eritrea", "Estonia", "Eswatini", "Ethiopia",
    "Fiji", "Finland", "France",
    "Gabon", "Gambia", "Georgia", "Germany", "Ghana", "Greece", "Grenada", "Guatemala", "Guinea", "Guinea-Bissau", "Guyana",
    "Haiti", "Honduras", "Hungary",
    "Iceland", "India", "Indonesia", "Iran", "Iraq", "Ireland", "Israel", "Italy",
    "Jamaica", "Japan", "Jordan",
    "Kazakhstan", "Kenya", "Kiribati", "North Korea", "South Korea", "Kuwait", "Kyrgyzstan",
    "Laos", "Latvia", "Lebanon", "Lesotho", "Liberia", "Libya", "Liechtenstein", "Lithuania", "Luxembourg",
    "Madagascar", "Malawi", "Malaysia", "Maldives", "Mali", "Malta", "Marshall Islands", "Mauritania", "Mauritius", "Mexico", "Micronesia", "Moldova", "Monaco", "Mongolia", "Montenegro", "Morocco", "Mozambique", "Myanmar",
    "Namibia", "Nauru", "Nepal", "Netherlands", "New Zealand", "Nicaragua", "Niger", "Nigeria", "North Macedonia", "Norway",
    "Oman",
    "Pakistan", "Palau", "Panama", "Papua New Guinea", "Paraguay", "Peru", "Philippines", "Poland", "Portugal",
    "Qatar",
    "Romania", "Russia", "Rwanda",
    "Saint Kitts and Nevis", "Saint Lucia", "Saint Vincent and the Grenadines", "Samoa", "San Marino", "Sao Tome and Principe", "Saudi Arabia", "Senegal", "Serbia", "Seychelles", "Sierra Leone", "Singapore", "Slovakia", "Slovenia", "Solomon Islands", "Somalia", "South Africa", "South Sudan", "Spain", "Sri Lanka", "Sudan", "Suriname", "Sweden", "Switzerland", "Syria",
    "Taiwan", "Tajikistan", "Tanzania", "Thailand", "Timor-Leste", "Togo", "Tonga", "Trinidad and Tobago", "Tunisia", "Turkey", "Turkmenistan", "Tuvalu",
    "Uganda", "Ukraine", "United Arab Emirates", "United Kingdom", "United States", "Uruguay", "Uzbekistan",
    "Vanuatu", "Vatican City", "Venezuela", "Vietnam",
    "Yemen",
    "Zambia", "Zimbabwe"
   };
   ComboBox *tempBox = nullptr;
   ComboBox *windBox = nullptr;
   ComboBox *visibilityBox = nullptr;
   ComboBox *themeBox = nullptr;

   private slots:
   void saveCountry(const QString &text);
   void saveTempUnit(const QString &text);
   void saveWindUnit(const QString &text);
   void saveVisibilityUnit(const QString &text);
   void saveDefaultTheme(const QString &text);

signals:
   void onSettingValueChanged();
   void onThemeValueChanged();
};