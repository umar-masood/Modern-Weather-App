#include "Home.h"

Home::Home(QWidget *parent) : Window(parent) {
   // TaskBar App Icon & Text
   setWindowTitle("Weather");
   setWindowIcon(QIcon(titleBarIconPath));
   resize(760,600);
   QString theme = settings.value("Default theme").toString();
   if (theme == "Light theme") {
      isDarkMode = false;
   } else {
      isDarkMode = true;
   }

   // TitleBar
   titleBar = _titleBarArea();

   // Title Bar Icon
   titleBarIcon = new QLabel;
   titleBarIcon->setPixmap(QPixmap(titleBarIconPath).scaled(QSize(24,24), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

   // TitleBar Text
   titleBarText = new QLabel;
   titleBarText->setFont(QFont("Segoe UI", 12));
   titleBarText->setStyleSheet("color: black;");
   titleBarText->setContentsMargins(0, 2, 0, 0);
   titleBarText->setText("Weather");

   // Back Button
   backBtn = button(backIconLight, backIconDark, QSize(22,22), QSize(30,30));
   backBtnContainer = new QWidget;
   backBtnLayout = new QHBoxLayout(backBtnContainer);
   backBtnLayout->setContentsMargins(0,0,0,0);
   backBtnLayout->setSpacing(0);
   backBtnLayout->addSpacing(5);
   backBtnLayout->addWidget(backBtn, 0, Qt::AlignLeft);
   backBtnContainer->setVisible(false);
   backBtnContainer->setFixedWidth(36);
   backBtnContainer->setProperty("clickable widget", true);

   // TitleBar Drag Spacer
   dragSpacer = new QWidget;
   dragSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
   dragSpacer->setAttribute(Qt::WA_TransparentForMouseEvents, false); 

   // Setting TitleBar Layout
   _titleBarLayout()->addWidget(backBtnContainer, 0, Qt::AlignLeft);
   _titleBarLayout()->addSpacing(10);
   _titleBarLayout()->addWidget(titleBarIcon, 0, Qt::AlignLeft);
   _titleBarLayout()->addSpacing(10);
   _titleBarLayout()->addWidget(titleBarText, 0, Qt::AlignVCenter | Qt::AlignLeft);
   _titleBarLayout()->addWidget(dragSpacer);

   // Dialogs
   noInternetDialog = dialog(noInternetIconPath, QSize(100, 100), "Oops! No internet connection.\nPlease make sure you are connected to the internet.", "Retry");
   noLocationDialog = dialog(noLocationIconPath, QSize(100, 100), "Oops! No matching location found.\nPlease make sure the location is typed correctly.", "Retry");
   wentWrongDialog = dialog(wentWrongIconPath, QSize(100, 100), "Oops! Something went wrong.", "OK");

   // Models
   currentModel = new CurrentWeatherModel;
   forecastModel = new ForecastModel;

   // Search Fields
   searchField1 = searchField();  
   searchField2 = searchField();

   // Refresh Button
   refreshBtn = button(refreshIconLight, refreshIconDark, QSize(25, 24), QSize(36, 36));
   refreshTip = new ToolTip(refreshBtn, "Refresh");

   // Theme Button
   themeBtn = button(themeIconLight, themeIconDark, QSize(25, 24), QSize(36, 36));
   themeTip = new ToolTip(themeBtn, "Theme Mode");

   // Settings Button
   settingsBtn = button(settingsIconLight, settingsIconDark, QSize(25, 24), QSize(36, 36));
   settingsTip = new ToolTip(settingsBtn, "Settings");
   
   // Current Weather Card
   currentWeatherCard = new CurrentWeatherCard;
   currentWeatherCard->setMinimumWidth(620);
   currentWeatherCard->setFixedHeight(360);
   currentWeatherCard->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   currentWeatherCard->setVisible(false);

   // Forecast Cards
   forecastCard1 = forecastCard();
   forecastCard2 = forecastCard();
   forecastCard3 = forecastCard();
   forecastCard4 = forecastCard();
   forecastCard5 = forecastCard();
   forecastCard6 = forecastCard();
   forecastCard7 = forecastCard();
   cards = { forecastCard1, forecastCard2, forecastCard3, forecastCard4, forecastCard5, forecastCard6, forecastCard7 };

   // Layouts
   header = new QHBoxLayout;
   header->setAlignment(Qt::AlignTop);
   header->addStretch();
   header->addWidget(searchField1, 0, Qt::AlignHCenter);
   header->addStretch();
   header->addSpacing(5);
   header->addWidget(refreshBtn, 0, Qt::AlignRight);
   header->addSpacing(5);
   header->addWidget(settingsBtn, 0, Qt::AlignRight);

   QHBoxLayout *cardsLayout = new QHBoxLayout;
   cardsLayout->setContentsMargins(0, 0, 0, 0);
   cardsLayout->setSpacing(10);
   for (ForecastCard *card : cards) {
      cardsLayout->addWidget(card, 0);
      card->setVisible(false);
   }

   QHBoxLayout *weatherMapLayout = new QHBoxLayout;
   weatherMapLayout->setContentsMargins(0, 0, 0, 0);
   weatherMapLayout->setSpacing(5);
   weatherMapLayout->addWidget(currentWeatherCard, 0, Qt::AlignTop);
   weatherMapLayout->addSpacing(5);
   weatherMapLayout->setAlignment(Qt::AlignTop);

   mainLayout = new QVBoxLayout;
   mainLayout->addLayout(header);
   mainLayout->addSpacing(5);
   mainLayout->addLayout(weatherMapLayout, 0);
   mainLayout->addSpacing(5);
   mainLayout->addLayout(cardsLayout, 0);
   mainLayout->addStretch();
   
   // Content Widget
   contentWidget = _contentArea();

   // Loader
   loader = new SpinnerProgress(contentWidget);
   loader->setSize(QSize(250, 140));
   loader->setIndeterminate(true);
   loader->setText(QString(""));
   loader->setAttribute(Qt::WA_StyledBackground, true);
   loader->raise(); 

   // Home Page
   homePage = new QWidget(contentWidget);
   homePage->setAttribute(Qt::WA_StyledBackground, true);
   homePage->setStyleSheet("background-color: transparent;");

   location_vector = new QLabel;
   location_vector->setPixmap(currentWeatherCard->pixmap(locationVectorIcon, locationVectorIcon, QSize(200,300)));

   homePageLayout = new QVBoxLayout(homePage);   
   homePageLayout->addStretch();
   homePageLayout->addWidget(location_vector, 0, Qt::AlignHCenter);
   homePageLayout->addSpacing(10);
   homePageLayout->addWidget(searchField2, 0, Qt::AlignHCenter);
   homePageLayout->addStretch();

   // Settings Page
   settingsPage = new Settings(contentWidget);
   settingsPage->setDarkMode(isDarkMode);
   
   // Weather Page
   weatherPage = new QWidget(contentWidget);
   weatherPage->setContentsMargins(0,0,0,0);
   weatherPage->setAttribute(Qt::WA_StyledBackground, true);
   weatherPage->setStyleSheet("background-color: transparent;");
   weatherPage->setLayout(mainLayout);

   // Stacked layout
   stackLayout = new QStackedLayout;
   stackLayout->addWidget(homePage);
   stackLayout->addWidget(weatherPage);
   stackLayout->addWidget(settingsPage);
   stackLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
   stackLayout->setCurrentIndex(1);
   contentWidget->setLayout(stackLayout);

   // Connect Signals/Slots
   setupConnections();
   themeChange();

   // Previous Data Load
   currentModel->fetchPreviousData();
   forecastModel->fetchPreviousData();
}

Button* Home::button(const QString &iconLight, const QString &iconDark, QSize iconSize, QSize buttonSize) {
   Button *b = new Button;
   b->setIconPaths(iconLight, iconDark);
   b->setSecondary(true);
   b->setIconSize(iconSize);
   b->setDisplayMode(Button::ToolButton);
   b->setSize(buttonSize);
   return b;
}

Dialog *Home::dialog(const QString &iconPath, QSize iconSize, const QString &message, const QString &btnText)
{
   Dialog *d = new Dialog(this);
   d->setIconSize(iconSize);
   d->setText(message);
   d->setButtonText(btnText);
   d->setIcon(iconPath, iconPath);
   d->setSize(QSize(360, 256));
   return d;
}

ForecastCard* Home::forecastCard() {
   ForecastCard *c = new ForecastCard;
   if (c) {
     c->setFixedHeight(260);
     c->setMinimumWidth(140);
     c->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   }
   return c;
}

TextField* Home::searchField() {
   TextField *searchField = new TextField;
   searchField->setClearButton(true);
   searchField->setTextFieldIcon(true);
   searchField->setIconPaths(searchIcon, searchIcon);
   searchField->setPlaceholderText("Search for location");
   searchField->setSize(QSize(550, 36));
   return searchField;
}

void Home::setupConnections() {
   connect(searchField1, &TextField::returnPressed, this, &Home::performedMainSearch);
   connect(searchField2, &TextField::returnPressed, this, &Home::performedInitialSearch);
   connect(currentModel, &CurrentWeatherModel::noInitialCurrentWeatherData, this, &Home::onInitialSearchPerformed);  
   connect(currentModel, &CurrentWeatherModel::currentWeatherUpdated, this, &Home::displayCurrentWeather);
   connect(currentModel, &CurrentWeatherModel::errorNoLocationFound, this, &Home::displayNoLocationFoundDailog);
   connect(currentModel, &CurrentWeatherModel::somethingWrong, this, &Home::displaySomethingWrongDailog);
   connect(forecastModel, &ForecastModel::forecastWeatherUpdated, this, &Home::displayForecastWeather);
   connect(refreshBtn, &Button::clicked, this, &Home::onRefreshBtnClicked);
   //connect(themeBtn, &Button::clicked, this, &Home::themeChange);
   connect(backBtn, &Button::clicked, this, &Home::onBackClicked);
   connect(settingsBtn, &Button::clicked, this, &Home::onSettingsClicked);
   connect(settingsPage, &Settings::settingValueChanged, this, &Home::restoreLastSearch);
   connect(settingsPage, &Settings::settingValueChanged, this, &Home::displayCurrentWeather);
   connect(settingsPage, &Settings::settingValueChanged, this, &Home::displayForecastWeather);
   connect(settingsPage, &Settings::themeValueChanged, this, &Home::themeChange);
}

void Home::hideCards() {
   currentWeatherCard->setVisible(false);
   for (ForecastCard* card : cards) {
      card->setVisible(false);
   }
}

bool Home::checkNetworkStatus() {
   QNetworkInformation::loadDefaultBackend();
   auto *networkInfo = QNetworkInformation::instance();
   return networkInfo->reachability() == QNetworkInformation::Reachability::Online;
}

void Home::applyLocationToModels(const QString &location) {
   if (!location.isEmpty()) {
      hideCards();
      loader->start();
      currentModel->setUserLocation(location);
      forecastModel->setUserLocation(location);
   }
}

void Home::applyUserLocation(TextField *searchField) {
   QString location = searchField->text().trimmed();
   settings.setValue("Last Search", location);

   if (checkNetworkStatus()) 
      applyLocationToModels(location);
   else 
      dialogsUninteraction(noInternetDialog);
   
}

void Home::dialogsUninteraction(Dialog *dialog) {
   dialog->setParent(this);
   dialog->setUninteractiveWidgets(contentWidget, titleBar);
   dialog->show();
}

void Home::displayNoLocationFoundDailog() {
   if (loader->isVisible()) loader->stop();
   dialogsUninteraction(noLocationDialog);
}

void Home::displaySomethingWrongDailog() {
   if (loader->isVisible()) loader->stop();
   dialogsUninteraction(wentWrongDialog);
}

void Home::performedMainSearch() {
   applyUserLocation(searchField1);
}

void Home::performedInitialSearch() {
   applyUserLocation(searchField2);
   bool visible = noInternetDialog->isVisible();
   if (visible) {
      stackLayout->setCurrentIndex(0);
   } else { 
      stackLayout->setCurrentIndex(1);
   }
}

void Home::restoreLastSearch() {
   QString lastLocation = settings.value("Last Location").toString();
   if (!lastLocation.isEmpty()) {
      currentModel->setUserLocation(lastLocation);
      forecastModel->setUserLocation(lastLocation);
   }
}

void Home::loaderPos() {
   if (loader && loader->isVisible()) {
      int x = (contentWidget->width() - loader->width()) / 2;
      int y = (contentWidget->height() - loader->height()) / 2;
      loader->move(x, y);
   }
}

void Home::resizeEvent(QResizeEvent *event) {
   loaderPos();
   Window::resizeEvent(event);
}

void Home::showEvent(QShowEvent *event)
{
   QWidget::showEvent(event);
   QTimer::singleShot(0, this, [this]()
   {
      QScreen *screenAtCursor = QApplication::screenAt(QCursor::pos());
      if (!screenAtCursor) screenAtCursor = QApplication::primaryScreen();
      QRect screenGeo = screenAtCursor->availableGeometry();

      QSize windowSize = size();
      int x = screenGeo.x() + (screenGeo.width() - windowSize.width()) / 2;
      int y = screenGeo.y() + (screenGeo.height() - windowSize.height()) / 2;
      move(x, y);
   });
}

void Home::displayCurrentWeather() {
   loader->stop();
   currentWeatherCard->updateUnits();
   currentWeatherCard->setCurrentLocation(currentModel->currentLocation());
   currentWeatherCard->setCurrentDateTime(currentModel->currentDay(), currentModel->currentTime(), currentModel->currentDate());
   currentWeatherCard->setCurrentTemp((currentWeatherCard->tempUnit == "°C") ? currentModel->currentTemp_c() : currentModel->currentTemp_f());
   currentWeatherCard->setCurrentWeatherDescrp(currentModel->currentWeatherDescrp());
   currentWeatherCard->setVisibility((currentWeatherCard->visibilityUnit == "km") ? currentModel->visibility_km() : currentModel->visibility_miles());
   currentWeatherCard->setHumidity(currentModel->humidity());
   currentWeatherCard->setCloudiness(currentModel->cloudiness());
   currentWeatherCard->setWindSpeed((currentWeatherCard->windSpeedUnit == "km/h") ? currentModel->windSpeed_kph() : currentModel->windSpeed_mph());
   currentWeatherCard->setSunrise(currentModel->sunrise());
   currentWeatherCard->setSunset(currentModel->sunset());
   currentWeatherCard->setCurrentWeatherIcon(currentModel->currentWeatherIcon());
   currentWeatherCard->setData();
   QTimer::singleShot(150, this, [this](){
      currentWeatherCard->setVisible(true);
   });
}

void Home::displayForecastWeather() {
   loader->stop();
   for (int i = 0; i < cards.size(); ++i) {
      forecastModel->setCurrentIndex(i);
      cards[i]->setDay(forecastModel->currentDay());
      cards[i]->setWeatherCondition(forecastModel->weatherCondition());
      cards[i]->setMaxTemp((currentWeatherCard->tempUnit == "°C") ? forecastModel->maximumTemp_c() : forecastModel->maximumTemp_f());
      cards[i]->setMinTemp((currentWeatherCard->tempUnit == "°C") ? forecastModel->minimumTemp_c() : forecastModel->minimumTemp_f());
      cards[i]->setWeatherIcon(forecastModel->weatherIcon());
      cards[i]->setData();
      QTimer::singleShot(180, this, [this, i](){
         cards[i]->setVisible(true);
      });
   }
}

void Home::themeChange() {
   QString theme = settings.value("Default theme").toString();
   if (theme == "Light theme") isDarkMode = false;
   else isDarkMode = true;

   // App theme
   titleBarText->setStyleSheet(QString("color: %1;").arg(isDarkMode ? "white" : "black"));
   setDarkMode(isDarkMode);

   // UI components theme
   loader->setDarkMode(isDarkMode);

   searchField1->setDarkMode(isDarkMode);
   searchField2->setDarkMode(isDarkMode);

   themeBtn->setDarkMode(isDarkMode);
   themeBtn->setIconPaths(themeIconLight, themeIconDark);

   settingsBtn->setDarkMode(isDarkMode);
   settingsBtn->setIconPaths(settingsIconLight, settingsIconDark);

   backBtn->setDarkMode(isDarkMode);
   backBtn->setIconPaths(backIconLight, backIconDark);

   refreshBtn->setDarkMode(isDarkMode);
   refreshBtn->setIconPaths(refreshIconLight, refreshIconDark);

   // Weather page elements theme
   currentWeatherCard->setDarkMode(isDarkMode);
   for (ForecastCard *card : cards) card->setDarkMode(isDarkMode);

   // Settings page theme
   settingsPage->setDarkMode(isDarkMode);

   // Dailogs
   if (noInternetDialog) noInternetDialog->setDarkMode(isDarkMode);
   if (noLocationDialog) noLocationDialog->setDarkMode(isDarkMode);
   if (wentWrongDialog) wentWrongDialog->setDarkMode(isDarkMode);

   // ToolTips
   themeTip->setDarkMode(isDarkMode);
   settingsTip->setDarkMode(isDarkMode);
   refreshTip->setDarkMode(isDarkMode); 
}

void Home::onBackClicked()
{
   if (backBtnContainer) backBtnContainer->setVisible(false);
   if (stackLayout) stackLayout->setCurrentIndex(1);   
   if (loader && loader->isVisible()) loader->stop();
}

void Home::onSettingsClicked()
{
   if (backBtnContainer) backBtnContainer->setVisible(true);
   if (stackLayout) stackLayout->setCurrentIndex(2); 
   if (loader && loader->isVisible()) loader->stop();
}

void Home::onInitialSearchPerformed() { if (stackLayout) stackLayout->setCurrentIndex(0); }

void Home::onRefreshBtnClicked()
{
   QString location = settings.value("Last Search").toString();
   if (location.isEmpty()) {
      dialogsUninteraction(noLocationDialog);
      return;
   }

   if (checkNetworkStatus())
      applyLocationToModels(location);
   else 
      dialogsUninteraction(noInternetDialog);
}
