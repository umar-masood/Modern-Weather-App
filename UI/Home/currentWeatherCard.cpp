#include "CurrentWeatherCard.h"
#include "forecastCard.h"

CurrentWeatherCard::CurrentWeatherCard(QWidget *parent) : QWidget(parent) {
    init();
    applyStyleSheet();
    applyThemedFonts();
    applyThemedIcons();
    applyToolTips();
    applyShadow();
}

void CurrentWeatherCard::updateUnits() {
    QString t = setting.value("Temperature Unit").toString();
    QString w = setting.value("Wind Speed Unit").toString();
    QString v = setting.value("Visibility Unit").toString();

    tempUnit = (t == "Celsius (°C)") ? "°C" : "°F";
    windSpeedUnit = (w == "Kilometers per hour (km/h)") ? "km/h" : "mph";
    visibilityUnit = (v == "Kilometers (km)") ? "km" : "mi";
}

void CurrentWeatherCard::setData() {
    currentLocation->setText(location);
    currentDay->setText(day);
    currentDate->setText(date);
    currentTime->setText(time);

    temp->setText(QString("%1<sup>%2</sup>").arg(QString::number(temperature)).arg(tempUnit));
    weatherDescp->setText(condition);
    visibilityText->setText(QString("%1 %2").arg(QString::number(visibility)).arg(visibilityUnit));
    humidityText->setText(QString("%1 %").arg(humidity));
    windSpeedText->setText(QString("%1 %2").arg(QString::number(windSpeed)).arg(windSpeedUnit));
    cloudinessText->setText(QString("%1 %").arg(cloudiness));
    sunsetText->setText(sunsetTime);
    sunriseText->setText(sunriseTime);
}

void CurrentWeatherCard::init() {
    currentWeatherCardLayout = new QVBoxLayout(this);

    // ---------- Header ----------
    headerWidget = new QWidget(this);
    headerWidget->setMinimumHeight(50);

    headerText = new QLabel("Current Weather");
    currentLocation = new QLabel;
    currentLocation->setTextInteractionFlags(Qt::TextSelectableByKeyboard | Qt::TextSelectableByMouse);

    locationIcon = new QLabel;

    headerLayout = new QVBoxLayout(headerWidget);
    headerSubLayout = new QHBoxLayout();
    headerSubLayout->addWidget(headerText);
    headerSubLayout->addStretch();
    headerSubLayout->addWidget(locationIcon);
    headerSubLayout->addSpacing(5);
    headerSubLayout->addWidget(currentLocation);

    headerLayout->setContentsMargins(0,0,0,0);
    headerLayout->setSpacing(0);
    headerLayout->addLayout(headerSubLayout);

    currentDay = new QLabel;
    currentDate = new QLabel;
    currentTime = new QLabel;

    headerLayout->addSpacing(5);
    headerLayout->addWidget(currentDay);
    headerLayout->addSpacing(5);
    headerLayout->addWidget(currentDate);
    headerLayout->addSpacing(5);
    headerLayout->addWidget(currentTime);
    headerLayout->addStretch();

    currentWeatherCardLayout->addWidget(headerWidget);

    // ---------- Weather Section ----------
    weatherWidget = new QWidget(this);
    weatherWidget->setMinimumHeight(130);
    weatherLayout = new QGridLayout(weatherWidget);

    weatherIcon = new QLabel;
    temp = new QLabel;
    weatherDescp = new QLabel;
    weatherDescp->setWordWrap(true);

    QWidget *tempDescp = new QWidget;
    QVBoxLayout *tempDescpLayout = new QVBoxLayout(tempDescp);
    tempDescpLayout->addWidget(temp, 0, Qt::AlignCenter);
    tempDescpLayout->addSpacing(10);
    tempDescpLayout->addWidget(weatherDescp, 0, Qt::AlignCenter);
    tempDescpLayout->setContentsMargins(0,0,0,0);
    tempDescpLayout->setSpacing(0);
    tempDescpLayout->addStretch();

    weatherLayout->addWidget(weatherIcon, 0, 0, 2, 1, Qt::AlignCenter);
    weatherLayout->addWidget(tempDescp, 0, 1, 2, 1, Qt::AlignCenter);
    weatherLayout->setContentsMargins(0,0,0,0);

    currentWeatherCardLayout->addSpacing(14);
    currentWeatherCardLayout->addWidget(weatherWidget);
    currentWeatherCardLayout->addStretch();

    // --- Main Weather Card Widget ---
    currentWeatherCard = new QWidget;
    currentWeatherCard->setMinimumHeight(358);
    currentWeatherCard->setLayout(currentWeatherCardLayout);

    // --- Visibility ---
    visiblityWidget = new QWidget(this);
    visiblityWidget->setMinimumSize(150, 164);
    visibilityText = new QLabel;
    visibilityIcon = new QLabel;
    visiblityLayout = metricsCardLayout(visiblityWidget, visibilityIcon, visibilityText);

    // --- Humidity ---
    humidityWidget = new QWidget(this);
    humidityWidget->setMinimumSize(150, 164);
    humidityText = new QLabel;
    humidityIcon = new QLabel;
    humidityLayout = metricsCardLayout(humidityWidget, humidityIcon, humidityText);

    // --- Wind Speed ---
    windSpeedWidget = new QWidget(this);
    windSpeedWidget->setMinimumSize(150, 164);
    windSpeedText = new QLabel;
    windIcon = new QLabel;
    windSpeedLayout = metricsCardLayout(windSpeedWidget, windIcon, windSpeedText);

    // --- Cloudiness ---
    cloudinessWidget = new QWidget(this);
    cloudinessWidget->setMinimumSize(150, 164);
    cloudinessText = new QLabel;
    cloudinessIcon = new QLabel;
    cloudinessLayout = metricsCardLayout(cloudinessWidget, cloudinessIcon, cloudinessText);

    // --- Sunrise ---
    sunriseWidget = new QWidget(this);
    sunriseWidget->setMinimumSize(150, 164);
    sunriseText = new QLabel;
    sunriseIcon = new QLabel;
    sunriseLayout = metricsCardLayout(sunriseWidget, sunriseIcon, sunriseText);

    // --- Sunset ---
    sunsetWidget = new QWidget(this);
    sunsetWidget->setMinimumSize(150, 164);
    sunsetText = new QLabel;
    sunsetIcon = new QLabel;
    sunsetLayout = metricsCardLayout(sunsetWidget, sunsetIcon, sunsetText);

    // Size policies
    QWidget* metrics[] = {
        visiblityWidget, humidityWidget, windSpeedWidget,
        cloudinessWidget, sunriseWidget, sunsetWidget
    };
    for (QWidget* w : metrics)
        w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    currentWeatherCardLayout->addStretch();
    currentWeatherCardLayout->setContentsMargins(15,15,15,15);
    currentWeatherCardLayout->setSpacing(10);

    // Grid for Side Metrics
    gridLayout = new QGridLayout;
    gridLayout->addWidget(visiblityWidget, 0, 0);
    gridLayout->addWidget(windSpeedWidget, 0, 1);
    gridLayout->addWidget(cloudinessWidget, 0, 2);
    gridLayout->addWidget(humidityWidget, 1, 0);
    gridLayout->addWidget(sunsetWidget, 1, 1);
    gridLayout->addWidget(sunriseWidget, 1, 2);
    gridLayout->setVerticalSpacing(8);
    gridLayout->setHorizontalSpacing(8);

    // Final layout
    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(currentWeatherCard);
    mainLayout->addSpacing(6);
    mainLayout->addLayout(gridLayout);

    setLayout(mainLayout);
}


QVBoxLayout* CurrentWeatherCard::metricsCardLayout(QWidget *parent, QWidget *w1, QWidget *w2) {
    QVBoxLayout *layout = new QVBoxLayout(parent);
    layout->addStretch();
    layout->addWidget(w1, 0, Qt::AlignCenter);
    layout->addSpacing(14);
    layout->addWidget(w2, 0, Qt::AlignCenter);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addStretch();
    return layout;
}

void CurrentWeatherCard::applyStyleSheet() {
    QString mainWidget = QString("background-color: %1; border-radius: 14px; border: 2px solid %2;")
        .arg(isDarkMode ? "#121212" : "#FFFFFF")
        .arg(isDarkMode ? "#333333" : "#DDDDDD");
    QString metricsWidget = "background-color: transparent; border: none;";

    QWidget* widgets[] = {headerWidget, weatherWidget};
    QWidget* metrics[] = {visiblityWidget, humidityWidget, windSpeedWidget, cloudinessWidget, sunriseWidget, sunsetWidget};
    for (QWidget* w : metrics) {    
        w->setStyleSheet(QString("background-color: %1; border-radius: 14px; border: none;").arg(isDarkMode ? "#1E1E1E" :"#F5F5F5"));
        w->setAttribute(Qt::WA_StyledBackground, true);
    }

    for (QWidget* w : widgets) {
        if (w) {
            w->setAttribute(Qt::WA_StyledBackground, true);
            w->setStyleSheet(metricsWidget);
        }
    }

    for (ToolTip *tip : {locationTooltip, visibilityTooltip, humidityTooltip, windTooltip, cloudinessTooltip, sunriseTooltip, sunsetTooltip})
    {
        if (tip) tip->setDarkMode(isDarkMode);
    }
}

void CurrentWeatherCard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QRect rec = rect().adjusted(1, 1, -1, -1);
    painter.setPen(Qt::NoPen);

    QColor bgcolor = isDarkMode ? QColor("#121212") : QColor("#FFFFFF");
    painter.setBrush(bgcolor);

    QPainterPath path;
    path.addRoundedRect(rec, 14, 14);
    painter.drawPath(path);
}

void CurrentWeatherCard::applyThemedFonts()
{
    headerText->setFont(font("Outfit", "Bold", 16, headerText, "black", "white"));
    currentLocation->setFont(font("Outfit", "Semi-Bold", 14, currentLocation, "black", "white"));
    currentTime->setFont(font("Outfit", "Medium", 13, currentTime, "#757575", "#B0B0B0"));
    currentDay->setFont(font("Outfit", "SemiBold", 13, currentDay, "#757575", "#B0B0B0"));
    currentDate->setFont(font("Outfit", "Medium", 13, currentDate, "#757575", "#B0B0B0"));
    temp->setFont(font("Outfit", "ExtraBold", 58, temp, "black", "white", 3));
    weatherDescp->setFont(font("Outfit", "SemiBold", 18, weatherDescp,"#757575", "#B0B0B0"));
    visibilityText->setFont(font("Outfit", "Medium", 14, visibilityText, "#757575", "#B0B0B0"));
    humidityText->setFont(font("Outfit", "Medium", 14, humidityText, "#757575", "#B0B0B0"));
    windSpeedText->setFont(font("Outfit", "Medium", 14, windSpeedText, "#757575", "#B0B0B0"));
    cloudinessText->setFont(font("Outfit", "Medium", 14, cloudinessText, "#757575", "#B0B0B0"));
    sunriseText->setFont(font("Outfit", "Medium", 14, sunriseText, "#757575", "#B0B0B0"));
    sunsetText->setFont(font("Outfit", "Medium", 14, sunsetText,"#757575", "#B0B0B0"));
}

void CurrentWeatherCard::applyThemedIcons()
{
    const QSize metricsIconSize = QSize(54,54);
    locationIcon->setPixmap(pixmap(":/Assets/Icons/location.png", ":/Assets/Icons/location.png",QSize(24,24)));
    visibilityIcon->setPixmap(pixmap(":/Assets/Icons/visibility.png", ":/Assets/Icons/visibility.png",metricsIconSize));
    humidityIcon->setPixmap(pixmap(":/Assets/Icons/droplet.png", ":/Assets/Icons/droplet.png", metricsIconSize));
    windIcon->setPixmap(pixmap(":/Assets/Icons/wind.png", ":/Assets/Icons/wind.png", metricsIconSize));
    cloudinessIcon->setPixmap(pixmap(":/Assets/Icons/cloud.png", ":/Assets/Icons/cloud.png", metricsIconSize));
    sunriseIcon->setPixmap(pixmap(":/Assets/Icons/sunrise.png", ":/Assets/Icons/sunrise.png", metricsIconSize));
    sunsetIcon->setPixmap(pixmap(":/Assets/Icons/sunset.png", ":/Assets/Icons/sunset.png", metricsIconSize));
}

void CurrentWeatherCard::applyToolTips() {
    locationTooltip = new ToolTip(locationIcon, "Your Current Location");
    visibilityTooltip = new ToolTip(visibilityIcon, "Current Visibility");
    humidityTooltip = new ToolTip(humidityIcon, "Current Humidity");
    windTooltip = new ToolTip(windIcon, "Wind Speed");
    cloudinessTooltip = new ToolTip(cloudinessIcon, "Cloudiness");
    sunriseTooltip = new ToolTip(sunriseIcon, "Sunrise Time");
    sunsetTooltip = new ToolTip(sunsetIcon, "Sunset Time");
}

QFont CurrentWeatherCard::font(const QString &family, const QString &styleName, int pointSize, QLabel *text, const QString &colorLight, const QString &colorDark, int letterSpacing)
{
   QFont font(family, pointSize);
   font.setStyleName(styleName);
   text->setStyleSheet(QString("color: %1; letter-spacing: %2").arg(isDarkMode ? colorDark : colorLight).arg(letterSpacing));
   return font;
}

QPixmap CurrentWeatherCard::pixmap(const QString &iconPathLight, const QString &iconPathDark, const QSize size)
{
    QPixmap pixmap(isDarkMode ? iconPathDark : iconPathLight);
    return pixmap.scaled(size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
}

void CurrentWeatherCard::applyShadow()
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

void CurrentWeatherCard::setCurrentLocation(const QString &location) { this->location = location; }

void CurrentWeatherCard::setCurrentDateTime(const QString &day, const QString &time, const QString &date)
{   
    this->day = day + ",";
    this->date = date;
    this->time = time;
}

void CurrentWeatherCard::setCurrentTemp(double temp) { this->temperature = temp; }

void CurrentWeatherCard::setCurrentWeatherDescrp(const QString &condition) { this->condition = condition; }

void CurrentWeatherCard::setVisibility(int value) { visibility = value; }

void CurrentWeatherCard::setHumidity(int percent) { humidity = percent; }

void CurrentWeatherCard::setCloudiness(int percent) { cloudiness = percent; }

void CurrentWeatherCard::setWindSpeed(int speed) { windSpeed = speed; }

void CurrentWeatherCard::setSunrise(const QString &time) { sunriseTime = time; }

void CurrentWeatherCard::setSunset(const QString &time) { sunsetTime = time; }

void CurrentWeatherCard::setCurrentWeatherIcon(const QString &path)
{
    this->iconPath = path;
    if (weatherIcon) weatherIcon->setPixmap(pixmap(iconPath, iconPath, QSize(150, 150)));
}

void CurrentWeatherCard::setDarkMode(bool value) {
    isDarkMode = value;
    applyStyleSheet();
    applyThemedFonts();
    applyThemedIcons();
    applyShadow();
}
