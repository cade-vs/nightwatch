/****************************************************************************
**
**  NightWatch Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  http://cade.datamax.bg/nw/
**
****************************************************************************/

#ifndef _NW_H_
#define _NW_H_

#include <QString>
#include <QDesktopWidget>
#include <QTextBrowser>
#include <QSettings>

#define NW_VERSION   "4.05"

#define DEFAULT_MOVIES_EXTENSIONS_FILTER   ".AVI.MKV.MPG.MPEG.MP4.TS."
#define DEFAULT_IMAGES_EXTENSIONS_FILTER   ".JPG.JPEG.PNG."

const QString ITEM_TYPE_DIR( "[DIR]" );

extern QDesktopWidget *Desktop;
extern int DeskW;
extern int DeskH;

extern QString movies_extensions_filter;
extern QString images_extensions_filter;

extern QSettings Settings;
extern QSettings LastPlayed;

extern int opt_thumbs_size;
extern int opt_create_thumbs;
extern int opt_create_smooth_thumbs;
extern int opt_create_jpeg_thumbs;
extern int opt_show_dir_thumbs;
extern int opt_use_toolbar;


#endif
