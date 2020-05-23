/****************************************************************************
**
**  NightWatch Video Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  https://github.com/cade-vs/nightwatch
**
****************************************************************************/

#include <QApplication>

#include "nw.h"
#include "nw_main_win.h"
#include "nw_help.h"

QString videos_extensions_filter;
QString images_extensions_filter;
QStringList images_extensions_list;

QSettings Settings( "CSA", "NW2" );
QSettings LastPlayed( "CSA", "NW2_LP" );
QSettings LastLocations( "CSA", "NW2_LL" );
QSettings LocalSort( "CSA", "NW2_LS" );

QFont main_list_big_font;
QFont main_list_small_font;
QFont keypad_menu_font;
QFont status_bar_font;

QProcess player_process;

int opt_use_toolbar;
int opt_use_per_directory_sorting;

void save_fonts_to_settings()
{
  Settings.beginGroup( "fonts" );
  Settings.setValue( "main_list_big_font",   main_list_big_font.toString()   );
  Settings.setValue( "main_list_small_font", main_list_small_font.toString() );
  Settings.setValue( "keypad_menu_font",     keypad_menu_font.toString()     );
  Settings.setValue( "status_bar_font",      status_bar_font.toString()      );
  Settings.endGroup();
}

QString find_first_image_in_dir( QString dir )
{
  QDir tdir;
  tdir.cd( dir );

  QStringList filters = { "*" };

  QFileInfoList info_list = tdir.entryInfoList( filters );

  for( int i = 0; i < info_list.count(); i++ )
    {
    QFileInfo fi = info_list.at( i );

    if( fi.fileName() == "."  ) continue;
    if( fi.fileName() == ".." ) continue;

    QString ext = "." + fi.suffix() + ".";

    if( fi.isDir() || images_extensions_filter.indexOf( ext.toUpper() ) < 0 ) continue;

    return QString( dir + "/" + fi.fileName() );
    }
    
  return QString();  
}

QString find_image_for_file( QString dir, QString file_name )
{
  QString mask = file_name;
  
  mask.replace( QRegularExpression( "\\.([a-z_0-9]+)$" ), "." );

  for( int i = 0; i < images_extensions_list.count(); i++ )
    {
    QString c = dir + "/" + mask + images_extensions_list[i];
    if( QFile::exists( c ) ) return c; 
    }
    
  return QString();  
}

int main(int argc, char **argv)
{
  QApplication app( argc, argv );
  Q_INIT_RESOURCE(nw);

  help_browser = NULL;

  opt_use_toolbar               = Settings.value( "use_toolbar",                   1 ).toInt();
  opt_use_per_directory_sorting = Settings.value( "opt_use_per_directory_sorting", 0 ).toInt();

  videos_extensions_filter = Settings.value( "videos_extensions_filter", QString( DEFAULT_VIDEOS_EXTENSIONS_FILTER ) ).toString();
  images_extensions_filter = Settings.value( "images_extensions_filter", QString( DEFAULT_IMAGES_EXTENSIONS_FILTER ) ).toString();

  images_extensions_list = images_extensions_filter.split( "." );
  images_extensions_list.removeFirst();
  images_extensions_list.removeLast();

  Settings.beginGroup( "fonts" );
  main_list_big_font.fromString(   Settings.value( "main_list_big_font",   QFont( "Coolvetica", 24, QFont::Bold, false ).toString() ).toString() );
  main_list_small_font.fromString( Settings.value( "main_list_small_font", QFont( "Coolvetica", 12, QFont::Bold, false ).toString() ).toString() );
  keypad_menu_font.fromString(     Settings.value( "keypad_menu_font",     QFont( "Coolvetica", 20, QFont::Bold, false ).toString() ).toString() );
  status_bar_font.fromString(      Settings.value( "status_bar_font",      QFont( "Coolvetica", 18, QFont::Bold, false ).toString() ).toString() );
  Settings.endGroup();

  QStringList args = app.arguments();

  args.takeFirst(); // remove app name
  
  QString target_dir = ".";
  
  if( args.count() > 0 ) target_dir = args[0];
  
  NWMainWindow *main_win = new NWMainWindow();
  main_win->loadDir( target_dir, 1 );

  return app.exec();
}
