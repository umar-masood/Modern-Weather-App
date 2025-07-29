#include "UI/Home/Home.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);

   QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
   QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

   QCoreApplication::setApplicationName("Weather");
   QCoreApplication::setOrganizationName("Umar Creations");
   QCoreApplication::setApplicationVersion("2.0.0");

   loadFonts();

   Home home;
   home.show();

   return app.exec();
}