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

int opt_thumbs_size;
int opt_create_thumbs;
int opt_create_smooth_thumbs;
int opt_create_jpeg_thumbs;
int opt_show_dir_thumbs;
int opt_use_toolbar;

int main(int argc, char **argv)
{
  QApplication app( argc, argv );
  Q_INIT_RESOURCE(nw);

  help_browser = NULL;

  Desktop = QApplication::desktop();

  DeskW = Desktop->width();  // get width of screen
  DeskH = Desktop->height(); // get height of screen

  opt_thumbs_size          = Settings.value( "thumbs_size", 128 ).toInt();
  opt_create_thumbs        = Settings.value( "create_thumbs", 0 ).toInt();
  opt_create_jpeg_thumbs   = Settings.value( "create_jpeg_thumbs", 0 ).toInt();
  opt_create_smooth_thumbs = Settings.value( "create_smooth_thumbs", 1 ).toInt();
  opt_show_dir_thumbs      = Settings.value( "opt_show_dir_thumbs", 0 ).toInt();
  opt_use_toolbar          = Settings.value( "use_toolbar", 1 ).toInt();

  movies_extensions_filter = Settings.value( "movies_extensions_filter", QString( DEFAULT_MOVIES_EXTENSIONS_FILTER ) ).toString();
  images_extensions_filter = Settings.value( "images_extensions_filter", QString( DEFAULT_IMAGES_EXTENSIONS_FILTER ) ).toString();

  QStringList args = app.arguments();

  args.takeFirst(); // remove app name

  NWMainWindow *main_win = new NWMainWindow();
  main_win->loadDir( QString( "." ) );
  //main_win->move( view->width() + 10, view->height() - main_win->height() );
  main_win->move( 100, 100 );
//  main_win->resize( 1280, 768 );
  main_win->show();

  return app.exec();
}
