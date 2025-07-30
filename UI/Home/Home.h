#pragma once

#include <QtWidgets>
#include "../../Window/Window.h"
#include "../../components/TextField.h"
#include "../../components/Button.h"
#include "../../components/Dialog.h"
#include "../../components/SpinnerProgress.h"
#include "../../utils/fontLoader.h"
#include "../../Models/currentWeatherModel.h"
#include "../../Models/ForecastModel.h"
#include "../Settings/settings.h"
#include "currentWeatherCard.h"
#include "forecastCard.h"
#include <QNetworkInformation>

class Home : public Window {
   Q_OBJECT

public:
   explicit Home(QWidget *parent = nullptr);

protected:
   void resizeEvent(QResizeEvent *event) override;
   void showEvent(QShowEvent *event) override;

private:
   // Title Bar
   QWidget *titleBar = nullptr;
   QLabel *titleBarIcon = nullptr;
   QLabel *titleBarText = nullptr;
   QWidget *dragSpacer = nullptr;

   const QString titleBarIconPath = ":/Assets/Icons/weather.png";

   // Search Fields
   TextField *searchField1 = nullptr;
   const QString searchIcon = ":Assets/Icons/search.svg";

   TextField *searchField2 = nullptr;

   // Theme & Settings & Refresh
   Button *themeBtn = nullptr;
   Button *settingsBtn = nullptr;
   Button *refreshBtn = nullptr;

   Button *backBtn = nullptr;
   QWidget *backBtnContainer = nullptr;
   QHBoxLayout *backBtnLayout = nullptr;

   const QString themeIconLight    = ":/Assets/Icons/LightMode.svg";
   const QString themeIconDark     = ":/Assets/Icons/DarkMode.svg";
   const QString settingsIconLight = ":/Assets/Icons/settings_light.svg";
   const QString settingsIconDark  = ":/Assets/Icons/settings.svg";
   const QString backIconLight     = ":/Assets/Icons/back_light.svg";
   const QString backIconDark      = ":/Assets/Icons/back.svg";
   const QString refreshIconLight  = ":/Assets/Icons/refresh_light.svg";
   const QString refreshIconDark   = ":/Assets/Icons/refresh_dark.svg";
   const QString locationVectorIcon = ":/Assets/Icons/homepage_location.png";

   // Layouts
   QHBoxLayout *header = nullptr;
   QVBoxLayout *mainLayout = nullptr;

   // Current Weather
   CurrentWeatherCard *currentWeatherCard = nullptr;

   // Forecast Cards
   QVector<ForecastCard*> cards;
   ForecastCard *forecastCard1 = nullptr;
   ForecastCard *forecastCard2 = nullptr;
   ForecastCard *forecastCard3 = nullptr;
   ForecastCard *forecastCard4 = nullptr;
   ForecastCard *forecastCard5 = nullptr;
   ForecastCard *forecastCard6 = nullptr;
   ForecastCard *forecastCard7 = nullptr;

   // Models
   CurrentWeatherModel *currentModel = nullptr;
   ForecastModel *forecastModel = nullptr;
   QSettings settings;

   // Pages
   Settings *settingsPage=  nullptr;

   QWidget *homePage = nullptr;
   QVBoxLayout *homePageLayout = nullptr;
   QLabel *location_vector = nullptr;

   QWidget *weatherPage = nullptr;

   QVBoxLayout *contentLayout = nullptr;
   QWidget *contentWidget = nullptr;

   SpinnerProgress *loader = nullptr;

   QStackedLayout *stackLayout = nullptr;

   // Default Values
   bool isDarkMode = false;

   // Dialogs:
   Dialog *noInternetDialog = nullptr;
   Dialog *wentWrongDialog = nullptr;
   Dialog *noLocationDialog = nullptr;

   const QString noInternetIconPath = ":/Assets/Icons/no-internet.png";
   const QString noLocationIconPath = ":/Assets/Icons/no-location.png";
   const QString wentWrongIconPath = ":/Assets/Icons/error.png";

   // Tooltips
   ToolTip *themeTip = nullptr;
   ToolTip *settingsTip = nullptr;
   ToolTip *refreshTip = nullptr;

   Button* button(const QString &iconLight, const QString &iconDark, QSize iconSize, QSize buttonSize);
   Dialog* dialog(const QString &iconPath, QSize iconSize, const QString &message, const QString &btnText);
   ForecastCard *forecastCard();
   TextField *searchField();
   void setupConnections();
   void hideCards();
   void applyUserLocation(TextField *searchField);
   void dialogsUninteraction(Dialog *dialog);
   void displayNoLocationFoundDailog();
   void displaySomethingWrongDailog();
   void loaderPos();
   void applyLocationToModels(const QString &location);
   bool checkNetworkStatus();

private slots:
   void performedMainSearch();
   void performedInitialSearch();
   void restoreLastSearch();
   void displayCurrentWeather();
   void displayForecastWeather();
   void themeChange();
   void onBackClicked();
   void onSettingsClicked();
   void onInitialSearchPerformed();
   void onRefreshBtnClicked();

};
