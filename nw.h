/****************************************************************************
**
**  NightWatch Video Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  https://github.com/cade-vs/nightwatch
**
****************************************************************************/

#ifndef _NW_H_
#define _NW_H_

#include <QString>
#include <QSettings>
#include <QString>
#include <QFont>
#include <qdebug.h>

#define NW_VERSION   "2.05"

#define DEFAULT_VIDEOS_EXTENSIONS_FILTER   ".AVI.MKV.MPG.MPEG.MP4.TS."
#define DEFAULT_IMAGES_EXTENSIONS_FILTER   ".JPG.JPEG.PNG."

#define MAX_PLAY_LOCATIONS         16
#define DEFAULT_AUTO_PLAY           3
#define DEFAULT_AUTO_PLAY_PAUSE  4000

const QString ITEM_TYPE_DIR( "[DIR]" );

extern QString videos_extensions_filter;
extern QString images_extensions_filter;

extern QSettings Settings;
extern QSettings LastPlayed;
extern QSettings LastLocations;

extern QFont main_list_big_font;
extern QFont main_list_small_font;
extern QFont keypad_menu_font;
extern QFont status_bar_font;

extern int opt_use_toolbar;

void save_fonts_to_settings();
QString find_first_image_in_dir( QString dir );
QString find_image_for_file( QString dir, QString file_name );

#endif
