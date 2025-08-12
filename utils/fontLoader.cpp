#include "fontLoader.h"

void loadFonts() {
   QStringList fontPaths = {
     ":/Assets/Fonts/Outfit-ExtraLight.ttf",
     ":/Assets/Fonts/Outfit-Light.ttf",
     ":/Assets/Fonts/Outfit-Medium.ttf",
     ":/Assets/Fonts/Outfit-Regular.ttf",
     ":/Assets/Fonts/Outfit-SemiBold.ttf",
     ":/Assets/Fonts/Outfit-Thin.ttf",
     ":/Assets/Fonts/Outfit-Black.ttf",
     ":/Assets/Fonts/Outfit-Bold.ttf",
     ":/Assets/Fonts/Outfit-ExtraBold.ttf",
     ":/Assets/Fonts/Segoe Fluent Icons.ttf"
   };

   for (const QString &font : fontPaths) {
      int id = QFontDatabase::addApplicationFont(font);
      if (id == -1) {
         qCritical() << "Failed to Load Font";
         return;
      } 
   }
}