/****************************************************************************
**
**  NightWatch Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  http://cade.datamax.bg/NW/
**
****************************************************************************/

#include <QApplication>

#include "nw.h"
#include "nw_main_win.h"
#include "nw_help.h"

QDesktopWidget *Desktop;
int DeskW;
int DeskH;

QString movies_extensions_filter;
QString images_extensions_filter;

QSettings Settings( "CSA", "NW4" );
QSettings LastPlayed( "CSA", "NW4_LP" );
QSettings LastLocations( "CSA", "NW4_LL" );

int opt_use_toolbar;

int main(int argc, char **argv)
{
  QApplication app( argc, argv );
  Q_INIT_RESOURCE(nw);

  help_browser = NULL;

  Desktop = QApplication::desktop();

  DeskW = Desktop->width();  // get width of screen
  DeskH = Desktop->height(); // get height of screen

  opt_use_toolbar          = Settings.value( "use_toolbar", 1 ).toInt();

  movies_extensions_filter = Settings.value( "movies_extensions_filter", QString( DEFAULT_MOVIES_EXTENSIONS_FILTER ) ).toString();
  images_extensions_filter = Settings.value( "images_extensions_filter", QString( DEFAULT_IMAGES_EXTENSIONS_FILTER ) ).toString();

  QStringList args = app.arguments();

  args.takeFirst(); // remove app name
  
  QString target_dir = ".";
  
  if( args.count() > 0 ) target_dir = args[0];
  
  NWMainWindow *main_win = new NWMainWindow();
  main_win->loadDir( target_dir, 1 );

  return app.exec();
}
