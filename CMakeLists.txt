cmake_minimum_required(VERSION 3.16)
project(WeatherApp VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(Qt6_DIR "C:/Qt/6.10.0/msvc2022_64/lib/cmake/Qt6")

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

include_directories(
    ${CMAKE_SOURCE_DIR}/UI
    ${CMAKE_SOURCE_DIR}/Models
    ${CMAKE_SOURCE_DIR}/utils
)

if (MSVC)
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_SOURCE_DIR}/app.rc")
endif()

add_executable(WeatherApp
    main.cpp

    # Components
    components/Button.cpp
    components/ComboBox.cpp
    components/Delegate.cpp
    components/Menu.cpp
    components/RoundedBox.cpp
    components/ScrollBar.cpp
    components/SmoothOpacity.cpp
    components/SmoothShadow.cpp
    components/SpinnerProgress.cpp
    components/TextField.cpp
    components/Toggle.cpp
    components/Dialog.cpp
    components/ToolTip.cpp

    # UI
    UI/Home/Home.cpp
    UI/Home/currentWeatherCard.cpp
    UI/Home/forecastCard.cpp
    UI/Settings/settings.cpp

    # Models
    Models/currentWeatherModel.cpp
    Models/forecastModel.cpp

    # Utils
    utils/fontLoader.cpp
    utils/fontLoader.h

    # Window
    Window/Window.cpp
    Window/resources.qrc

    # Resources )
    Resources/resources.qrc
)

# Link Qt libraries
target_link_libraries(WeatherApp PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network dwmapi user32)
set_target_properties(WeatherApp PROPERTIES WIN32_EXECUTABLE TRUE)

if(WIN32)
    target_sources(WeatherApp PRIVATE
        resources/resource.rc
    )
endif()