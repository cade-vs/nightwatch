/****************************************************************************
**
**  NightWatch Video Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  https://github.com/cade-vs/nightwatch
**
****************************************************************************/

#include <QApplication>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QFile>
#include <QFont>
#include <QRawFont>
#include <QDataStream>
#include <QFileDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QDateTime>
#include <QProgressDialog>
#include <QImage>
#include <QPixmap>
#include <QCryptographicHash>
#include <QProcess>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QSizePolicy>
#include <QIcon>
#include <QPen>
#include <QColor>
#include <QMenu>
#include <QFontDialog>
#include <QTreeWidgetItem>
#include <QThread>
#include <QRandomGenerator>

#include "nw.h"
#include "nw_main_win.h"
#include "nw_help.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

/*****************************************************************************/

NWTreeWidgetItem::NWTreeWidgetItem()
     : QTreeWidgetItem( 10001 )
{
}

/*****************************************************************************/

NWTreeWidget::NWTreeWidget( QWidget *parent )
     : QTreeWidget( parent )
{
}

NWTreeWidget::NWTreeWidget()
     : QTreeWidget()
{
}

void NWTreeWidget::findNext( QString str, int full_match )
{
  NWTreeWidgetItem *lwi = (NWTreeWidgetItem*)currentItem();

  int i;
  int start;

  int x = topLevelItemCount();

  i = indexOfTopLevelItem( lwi );
  start = i;

  if( x <= 1 or i < 0 ) return; // not found or empty list

  while(4)
    {
    i++;
    if( i >= x ) i = 0;
    if( i == start ) break;
    lwi = (NWTreeWidgetItem*)topLevelItem( i );
    if(   full_match && lwi->text( 1 ).toUpper() == str.toUpper() ) break;
    if( ! full_match && lwi->text( 1 ).toUpper().indexOf( str.toUpper() ) == 0 ) break;
    lwi = NULL;
    }
  if( lwi )
    {
    setCurrentItem( lwi );
    scrollToItem( lwi );
    }
}

void NWTreeWidget::findNextThe( QString str )
{
  NWTreeWidgetItem *lwi = (NWTreeWidgetItem*)currentItem();

  str = str.toUpper();

  int i;
  int start;

  int x = topLevelItemCount();

  i = indexOfTopLevelItem( lwi );
  start = i;

  if( x <= 1 or i < 0 ) return; // not found or empty list

  while(4)
    {
    i++;
    if( i >= x ) i = 0;
    if( i == start ) break;
    lwi = (NWTreeWidgetItem*)topLevelItem( i );

    QString name = lwi->text( 1 ).toUpper();

    if( name.indexOf( str ) == 0 ) break;
    lwi = NULL;
    }

  if( lwi )
    {
    setCurrentItem( lwi );
    scrollToItem( lwi );
    }
}


void NWTreeWidget::keyPressEvent ( QKeyEvent * e )
{
  main_window->cancelAutoPlay();

  e->ignore();
  int a = e->text() == "" ? 0 : e->text().toLatin1().at(0);
  int m = e->modifiers();

  if( ( m == Qt::ShiftModifier || m == Qt::NoModifier ) && a >= '!' && a <= 'z' )
    {
    findNextThe( QString( a ) );
    }
  else
    {
    QTreeWidget::keyPressEvent( e );
    }

}


/*****************************************************************************/

NWMainWindow::NWMainWindow()
    : QMainWindow()
{
    rand_seeded = 0;
    first_load  = 0;

    last_sort_col = Settings.value( "last_sort_col",  1  ).toInt();
    last_sort_ord = Settings.value( "last_sort_ord", 'A' ).toInt();

    setAttribute( Qt::WA_DeleteOnClose );

    setObjectName( "NWMainWindow" );
    setWindowTitle( QString() + " NightWatch " + NW_VERSION );

    // crashes ICEWM :(
    //setWindowIcon( QIcon( QPixmap( ":/images/nw_icon_128x128.png" ) ) );

    int x = Settings.value( "x", 100 ).toInt();
    int y = Settings.value( "y", 100 ).toInt();
    int w = Settings.value( "w", 900 ).toInt();
    int h = Settings.value( "h", 400 ).toInt();

    resize( w, h );
    move( x, y );

    poster = new NWPoster();
    //poster->setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed ) );
    //poster->setMinimumSize( 300, 400 );
    //poster->resize( 300, 400 );

    tree = new NWTreeWidget();
    tree->main_window = this;
    //tree->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding ) );
    //tree->setMinimumSize( 600, 400 );
    //tree->resize( 600, 400 );

    NWTreeWidgetItem *header = new NWTreeWidgetItem();

    header->setText( 0, "Type" );
    header->setText( 1, "Name" );
    header->setText( 2, "Size" );
    header->setText( 3, "Modify Time" );
    header->setTextAlignment( 2, Qt::AlignRight );

    tree->setColumnCount( 4 );
    tree->setHeaderItem( header );

    tree->setColumnWidth( 0,  70 );
    tree->setColumnWidth( 1, 300 );
    tree->setColumnWidth( 2,  80 );
    tree->setColumnWidth( 3, 120 );

    tree->setIconSize( QSize( 64, 64 ) );

    tree->setSortingEnabled( 1 );
    sortColumn( last_sort_col );

    tree->setDragEnabled( 1 );

    setupMenuBar();
    
    QWidget *central_widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout( central_widget );


    layout->addWidget( poster, 1 );
    layout->addWidget( tree,   2 );

    layout->setStretchFactor( poster, 1 );
    layout->setStretchFactor( tree,   2 );
    
    layout->setSpacing( 0 );
    
    setCentralWidget( central_widget );

    statusBar()->setFont( status_bar_font );

    timer = new QTimer( this );
    auto_play_timer = new QTimer( this );
    
    connect( timer, SIGNAL(timeout()), this, SLOT(slotLoadCurrentImage()));
    connect( auto_play_timer, SIGNAL(timeout()), this, SLOT(slotAutoPlayNext()));
    connect( tree,  SIGNAL(itemActivated(QTreeWidgetItem *, int)), this, SLOT(slotItemActivated(QTreeWidgetItem *, int)));
    connect( tree,  SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(slotCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));
    connect( &dir_watcher, SIGNAL(directoryChanged(const QString&)), this, SLOT(slotDirChanged(const QString&)) );
}

NWMainWindow::~NWMainWindow()
{
  delete poster;
  delete tree;
  delete timer;
  delete auto_play_timer;
}

/*****************************************************************************/

void NWMainWindow::loadDir( QString path, int mode )
{
  statusBar()->showMessage( "Reading..." );

  QString last_path = cdir.absolutePath();
  
  dir_watcher.removePath( last_path );

  cdir.cd( path );

  QString new_path = cdir.absolutePath();

  if( opt_use_per_directory_sorting )
    {
    last_sort_col = LocalSort.value( "COL." + new_path,  1  ).toInt();
    last_sort_ord = LocalSort.value( "ORD." + new_path, 'A' ).toInt();
    sortColumn( last_sort_col, last_sort_ord );
    }

  dir_watcher.addPath( new_path );

  setWindowTitle( QString() + " NightWatch " + NW_VERSION + ": " + new_path );

  QStringList filters;
  filters.append( QString( "*" ) );

  QFileInfoList info_list = cdir.entryInfoList( filters );

  NWTreeWidgetItem *current = NULL;
  last_played = NULL;
  QString last_played_here = LastPlayed.value( new_path ).toString();

  QIcon icon_video(  ":/images/video-x-generic.png" );
  QIcon icon_folder( ":/images/folder.png" );

  QString save_item_name;
  if( mode == 0 && tree->topLevelItemCount() > 0 ) save_item_name = tree->currentItem()->text( 1 );

  tree->clear();
  
  videos_count = 0;
  videos_posters = 0;
  for( int i = 0; i < info_list.count(); i++ )
    {
    QFileInfo fi = info_list.at( i );

    if( fi.fileName() == "."  ) continue;
    if( fi.fileName() == ".." ) continue;

    QString ext = "." + fi.suffix() + ".";
    if( ! fi.isDir() && videos_extensions_filter.indexOf( ext.toUpper() ) < 0 ) continue;

    QString file_name = fi.fileName();

    NWTreeWidgetItem *item = new NWTreeWidgetItem();
    if( ! current ) current = item;

    if( fi.isDir() )
      {
      item->is_dir = 1;
      //item->setText( 0, ITEM_TYPE_DIR );
      item->setIcon( 0, icon_folder );
      }
    else  
      {
      item->is_dir = 0;
      item->setIcon( 0, icon_video  );
      videos_count++;
      
      if( ! item->is_dir && find_image_for_file( new_path, file_name ) != "" ) videos_posters++;
      }

    item->fn = file_name;

    file_name.replace( QRegularExpression( "\\.([a-z_0-9]+)$" ), " [\\1]" );
    file_name.replace( QRegularExpression( "[_.]" ), " " );
    file_name.replace( QRegularExpression( "^THE (.+)", QRegularExpression::CaseInsensitiveOption ), "\\1 [The *]" );
    
    item->setText( 1, file_name );
    item->setText( 2, fi.isDir() ? "" : QVariant( fi.size() / 1024 / 1024 ).toString() + " MB" );
    item->setText( 3, fi.lastModified().toString( "yyyy-MM-dd hh:mm:ss" ) );
    item->setTextAlignment( 2, Qt::AlignRight );

    item->setFont( 0, main_list_small_font );
    item->setFont( 1, main_list_big_font   );
    item->setFont( 2, main_list_small_font );
    item->setFont( 3, main_list_small_font );

    tree->addTopLevelItem( item );

    if( ! last_played && last_played_here == item->fn ) last_played = item;

    if( mode == 0 && save_item_name == file_name              ) current     = item;
    if( mode == 2 && last_path   == new_path + "/" + item->fn ) current     = item;
    
    //qDebug() << "load dir: " << file_name;
    }
    
  if( videos_count > 1 && last_played )  
    {
    last_played->setIcon( 1, QIcon( ":/images/last-played.png" ) );
    if( mode == 1 ) current = last_played;
    }

  if( current ) tree->setCurrentItem( current );

  statusBar()->showMessage( QString() + "Press [INSERT] or [0] for keypad menu, [DEL] or [.] for previous locations. " + ( last_sort_col == 1 ? "Sort by NAME" : "Sort by MODIFY TIME" ) + ". Videos: " + QVariant( videos_count ).toString() );

  tree->resizeColumnToContents( 0 );
  tree->resizeColumnToContents( 1 );
  tree->resizeColumnToContents( 2 );
  tree->resizeColumnToContents( 3 );

  show();
  //qDebug() << "loaddir: " << first_load;
  if( first_load < 2 ) poster->loadImage( QString( ":/images/journey_by_t1na.credits.jpg" ) );
};

/*****************************************************************************/

void NWPoster::loadImage( const QString file_name )
{
  if( fn == file_name ) return;
  fn = file_name;
  rescaleImage();
  //qDebug() << "load image: " << fn;
};

void NWPoster::rescaleImage()
{
  if( fn == "" || ! im.load( fn ) ) im.load( QString( ":/images/journey_by_t1na.notfound.jpg" ) );
  im = im.scaled( size(), Qt::KeepAspectRatio, Qt::SmoothTransformation );
  update();
}

void NWPoster::paintEvent( QPaintEvent * e )
{
  QPainter painter( this );
  if ( im.isNull() ) return;
  
  int ox = ( width()  - im.width()  ) / 2;
  int oy = ( height() - im.height() ) / 2;
  
  painter.drawImage( ox, oy, im );
};

/*****************************************************************************/

void NWMainWindow::goToDir( int mode )
{
  mode = ! mode; // FIXME: for what??
  QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;

  QString new_dir = QFileDialog::getExistingDirectory( this,
                              tr( "Change directory" ),
                              cdir.absolutePath(),
                              options );
  if ( ! new_dir.isEmpty() )
      loadDir( new_dir, 1 );
};

/*****************************************************************************/

QString isSingleVideoDir( QString target )
{
  QStringList filters;
  filters.append( QString( "*" ) );

  QDir dir;
  dir.cd( target );

  QFileInfoList info_list = dir.entryInfoList( filters );

  QString found;
  int videos_count = 0;
  int dirs_count = 0;
  for( int i = 0; i < info_list.count(); i++ )
    {
    QFileInfo fi = info_list.at( i );

    if( fi.fileName() == "."  ) continue;
    if( fi.fileName() == ".." ) continue;

    if( fi.isDir() )
      {
      dirs_count++;
      continue;
      }

    QString ext = "." + fi.suffix() + ".";
    if( videos_extensions_filter.indexOf( ext.toUpper() ) < 0 ) continue;
    
    videos_count++;
    found = fi.fileName();
    }
  
  if( videos_count == 1 and dirs_count == 0 ) return found;
  return QString();
}

void NWMainWindow::enter( QTreeWidgetItem *item )
{
  if( ! item ) return;

  NWTreeWidgetItem *nw_item = (NWTreeWidgetItem*)item;
  
  QString single_video = nw_item->is_dir ? isSingleVideoDir( cdir.absolutePath() + "/" + nw_item->fn ) : "";

  if( nw_item->is_dir && single_video == "" )
    {
    loadDir( nw_item->fn, 1 );
    }
  else
    {
    auto_play_timer->stop();
    
    QString ndir = cdir.absolutePath();

    if( videos_count > 1 )
      {
      LastPlayed.setValue( ndir, nw_item->fn );
      if( last_played ) last_played->setIcon( 1, QIcon() );
      nw_item->setIcon( 1, QIcon( ":/images/last-played.png" ) );
      last_played = nw_item;
      }

    addPlayLocation( ndir );

    QString fn = nw_item->fn;
    if( single_video != "" ) fn += "/" + single_video;
    QStringList exec_args = { ndir + "/" + fn };
    
    slotStopPlayer();
    connect( &player_process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotPlayerFinished(int,QProcess::ExitStatus)) );
    player_process.start( "nightwatch-video-player", exec_args );
    }
};

void NWMainWindow::enterCurrent()
{
  enter( tree->currentItem() );
}

/*****************************************************************************/

void NWMainWindow::slotPlayerFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
  if( auto_play > 0 )
    {
    auto_play--;
    if( auto_play < 1 )
      {
      auto_play_timer->stop();
      statusBar()->showMessage( "Auto-Play ended." );
      }
    else
      {  
      auto_play_timer->start( DEFAULT_AUTO_PLAY_PAUSE );
      statusBar()->showMessage( "*** Auto-Play is active for the next " + QVariant( auto_play - 1 ).toString() + " video file(s). Press any navigation key to cancel ***" );
      }
    }
};

void NWMainWindow::slotItemActivated( QTreeWidgetItem *item, int column )
{
  enter( item );
};

void NWMainWindow::slotCurrentItemChanged( QTreeWidgetItem *current, QTreeWidgetItem *previous )
{
  if( ! current ) return;
  if( first_load++ > 0 ) timer->start( 100 );
}


void NWMainWindow::slotLoadCurrentImage()
{
  timer->stop();
  QString abs_path = cdir.absolutePath();

  NWTreeWidgetItem *current = (NWTreeWidgetItem*)tree->currentItem();
  if( ! current ) return;

  QString item_name = current->fn;
  QString found_image_name;

  if( current->is_dir )
    {
    found_image_name = find_first_image_in_dir( abs_path + "/" + item_name );
    }
  else
    {
    found_image_name = find_image_for_file( abs_path, item_name );
    if( videos_posters == 0 && ( found_image_name == "" || ! QFile::exists( found_image_name ) ) )
      found_image_name = find_first_image_in_dir( abs_path );
    }  

  poster->loadImage( found_image_name );
}

/*****************************************************************************/

void NWMainWindow::slotNewWindow()
{
  NWMainWindow *new_mainwin = new NWMainWindow();
  new_mainwin->show();
  new_mainwin->loadDir( cdir.absolutePath(), 1 );
};

/*****************************************************************************/

void NWMainWindow::slotGoUp()
{
  loadDir( "..", 2 );
};

/*****************************************************************************/

void NWMainWindow::slotChangeDir()
{
  goToDir( 0 );
}

void NWMainWindow::slotHomeDir()
{
  loadDir( cdir.homePath(), 1 );
}

void NWMainWindow::slotReloadDir()
{
  loadDir( cdir.absolutePath(), 0 );
}

void NWMainWindow::slotDirChanged( const QString &dir )
{
  slotReloadDir();
}

void NWMainWindow::sortColumn( int n, int d )
{
  last_sort_col = n;
  last_sort_ord = d;
  
  tree->sortByColumn( last_sort_col, last_sort_ord == 'A' ? Qt::AscendingOrder : Qt::DescendingOrder );
  Settings.setValue( "last_sort_col", last_sort_col );
  Settings.setValue( "last_sort_ord", last_sort_ord );
  if( opt_use_per_directory_sorting )
    {
    LocalSort.setValue( "COL." + cdir.absolutePath(), last_sort_col );
    LocalSort.setValue( "ORD." + cdir.absolutePath(), last_sort_ord );
    }
};

void NWMainWindow::toggleSortColumns()
{
  if( last_sort_col == 3 )
    {
    slotSortByName();
    statusBar()->showMessage( QString( tr( "List sorted: NAME (A-Z)" ) ) );
    }
  else
    {
    slotSortByModTime();
    statusBar()->showMessage( QString( tr( "List sorted: MODIFY TIME (newest first)" ) ) );
    }
  tree->scrollToItem( tree->currentItem() );  
}

void NWMainWindow::slotSortByName()
{
  sortColumn( 1 );
};

void NWMainWindow::slotSortByModTime()
{
  sortColumn( 3, 'D' );
};

void NWMainWindow::slotTogglePerDirSorting()
{
  opt_use_per_directory_sorting = ! opt_use_per_directory_sorting;
  Settings.setValue( "opt_use_per_directory_sorting", opt_use_per_directory_sorting );
  statusBar()->showMessage( opt_use_per_directory_sorting ? "Local (per directory) sorting enabled" : "Global sorting enabled" );
};

void NWMainWindow::slotRandomItem()
{
  int x = tree->topLevelItemCount();
  //if( rand_seeded == 0 ) qsrand( QDateTime::currentDateTime().toTime_t() );
  //rand_seeded = 1;
  //int r = qrand();
  unsigned int r = QRandomGenerator::global()->generate();

  unsigned int n = int( r % x );

  tree->setCurrentItem( tree->topLevelItem( n ) );
};

void NWMainWindow::slotStopPlayer()
{
  if( player_process.state() != QProcess::Running ) return;
  player_process.terminate();
  player_process.waitForFinished( 1000 );
  if( player_process.state() != QProcess::Running ) return;
  player_process.kill();
  player_process.waitForFinished( 1000 );
};

void NWMainWindow::slotHelp()
{
  display_help( this );
};

void NWMainWindow::slotAbout()
{
  poster->loadImage( ":/images/journey_by_t1na.credits.jpg" );
};

void NWMainWindow::addPlayLocation( QString location )
{
  QVector<QString> locs;
  locs.append( location );
  
  for( int i = 0; i < MAX_PLAY_LOCATIONS; i++ )
    {
    QString s = LastLocations.value( QVariant( i ).toString() ).toString();
    if ( s == "" ) break;
    if ( s == location ) continue;
    locs.append( s );
    }
  for( int i = 0; i < locs.size(); i++ )
    LastLocations.setValue( QVariant( i ).toString(), locs[i] );
};

void NWMainWindow::slotSelectLastPlayLocation()
{
    QMenu menu( "Select last play location", this );
    menu.setFont( keypad_menu_font );

    QAction *act_cancel = menu.addAction( "Cancel" );
    act_cancel->setShortcut( Qt::Key_Insert );
    menu.setActiveAction( act_cancel );
    
    for( int i = 0; i < MAX_PLAY_LOCATIONS; i++ )
      {
      QString s = LastLocations.value( QVariant( i ).toString() ).toString();
      if( s == "" ) break;
      menu.addAction( s );
      }

    QAction *res = menu.exec( mapToGlobal( poster->pos() ) );
    
    if( ! res || res == act_cancel ) return;
    loadDir( res->text(), 1 );
};

void NWMainWindow::slotAutoPlayNext()
{
  NWTreeWidgetItem *current = (NWTreeWidgetItem *)tree->currentItem();
  NWTreeWidgetItem *next    = current;
  while(4)
    {
    next = (NWTreeWidgetItem *)tree->itemBelow( next );
    if( ! next )
      return cancelAutoPlay();
    if( ! next->is_dir )
      break;
    }
  tree->setCurrentItem( next );
  tree->scrollToItem( next );
  auto_play_timer->stop();
  qDebug() << "+++";
  if( auto_play < 1 ) return;
  enterCurrent();
};

void NWMainWindow::beginAutoPlay()
{
  if( videos_count < 1 )
    {
    statusBar()->showMessage( "WARNING: Cannot start Auto-Play, need at least 1 video." );
    return;
    }
  auto_play = DEFAULT_AUTO_PLAY + 1;
  enterCurrent();
}

void NWMainWindow::cancelAutoPlay()
{
  if( auto_play < 1 ) return;
  auto_play = 0;
  auto_play_timer->stop();
  statusBar()->showMessage( "Auto-Play ended or cancelled." );
}

void NWMainWindow::slotKeypadMenu()
{
    QMenu menu( "MENU", this );
    menu.setFont( keypad_menu_font );

    QAction *act_cancel = menu.addAction( "Cancel" );
    act_cancel->setIcon( QIcon( ":/images/act-cancel.png" ) );
    act_cancel->setShortcut( Qt::Key_Insert );
    menu.setActiveAction( act_cancel );

    QAction *act_last_loc = menu.addAction( "List last play locations" );
    act_last_loc->setIcon( QIcon( ":/images/act-last-loc.png" ) );
    act_last_loc->setShortcut( Qt::Key_Delete );

    QAction *act_auto_play = menu.addAction( "Auto-Play next " + QVariant( DEFAULT_AUTO_PLAY ).toString() + " videos" );
    act_auto_play->setIcon( QIcon( ":/images/act-auto-play.png" ) );

    QAction *act_reload_dir = menu.addAction( "Reload current directory" );
    act_reload_dir->setIcon( QIcon( ":/images/act-reload.png" ) );

    menu.addSeparator();
    QAction *act_persort = menu.addAction( "Use local (per directory) sorting" );
    act_persort->setCheckable( true );
    act_persort->setChecked( opt_use_per_directory_sorting );
    connect( act_persort, SIGNAL( toggled(bool) ), this, SLOT(slotTogglePerDirSorting()) );

    menu.addSeparator();
    QAction *act_help = menu.addAction( "Help" );
    act_help->setIcon( QIcon( ":/images/help-browser.png" ) );

    QAction *act_about = menu.addAction( "About" );
    act_about->setIcon( QIcon( ":/images/face-glasses.png" ) );

    QAction *res = menu.exec( mapToGlobal( poster->pos() ) );

    if( res == act_last_loc   ) return slotSelectLastPlayLocation();
    if( res == act_auto_play  ) return beginAutoPlay();
    if( res == act_reload_dir ) return slotReloadDir();
    if( res == act_help       ) return slotHelp();
    if( res == act_about      ) return slotAbout();
};

void NWMainWindow::slotSelectMainListBigFont()
{
  bool ok;
  QFont font = QFontDialog::getFont( &ok, main_list_big_font, this);
  if( ! ok ) return;
  main_list_big_font = font;
  save_fonts_to_settings();
};

void NWMainWindow::slotSelectMainListSmallFont()
{
  bool ok;
  QFont font = QFontDialog::getFont( &ok, main_list_small_font, this);
  if( ! ok ) return;
  main_list_small_font = font;
  save_fonts_to_settings();
};

void NWMainWindow::slotSelectKeyPadFont()
{
  bool ok;
  QFont font = QFontDialog::getFont( &ok, keypad_menu_font, this);
  if( ! ok ) return;
  keypad_menu_font = font;
  save_fonts_to_settings();
};

void NWMainWindow::slotStatusBarFont()
{
  bool ok;
  QFont font = QFontDialog::getFont( &ok, status_bar_font, this);
  status_bar_font = font;
  save_fonts_to_settings();
  statusBar()->setFont( status_bar_font );
  tree->setFocus( Qt::OtherFocusReason );
};

void NWMainWindow::slotResetFonts()
{
  main_list_big_font   = QFont( "Coolvetica", 24, QFont::Bold, false );
  main_list_small_font = QFont( "Coolvetica", 12, QFont::Bold, false );
  keypad_menu_font     = QFont( "Coolvetica", 20, QFont::Bold, false );
  status_bar_font      = QFont( "Coolvetica", 18, QFont::Bold, false );
  save_fonts_to_settings();
  statusBar()->setFont( status_bar_font );
  tree->setFocus( Qt::OtherFocusReason );
};

/*****************************************************************************/

void NWMainWindow::keyPressEvent ( QKeyEvent * e )
{
  cancelAutoPlay();

  e->accept();
  if( e->modifiers() & Qt::CTRL )
    {
    switch( e->key() )
      {
      default: e->ignore(); QMainWindow::keyPressEvent( e ); break;
      }
    }
  else if( e->modifiers() & Qt::ALT )
    {
    switch( e->key() )
      {
      default: e->ignore(); QMainWindow::keyPressEvent( e ); break;
      }
    }
  else
    {
    switch( e->key() )
      {
      case Qt::Key_F1: slotHelp(); break;
      case Qt::Key_Escape : slotStopPlayer(); break;
/*
      case Qt::Key_F3    : slotNewWindow(); break;
      case Qt::Key_F4    : close();
                           delete this;
                           break;
*/
      case Qt::Key_Left  : slotGoUp(); break;
      case Qt::Key_Right : enter( tree->currentItem() ); break;

//      case Qt::Key_BracketLeft  : slotGoPrev(); break;
//      case Qt::Key_Space        :
//      case Qt::Key_BracketRight : slotGoNext(); break;
      
//      case Qt::Key_Slash        : toggleSortColumns(); break;

/*
      case Qt::Key_F1    : closeAll();
                           views.append( new NWView( this ) );
                           views.first()->load( "*logo*" );
                           break;

      case Qt::Key_F5    : loadDir( cdir.absolutePath() ); break;

      case Qt::Key_BracketLeft  : slotGoPrev(); break;
      case Qt::Key_BracketRight : slotGoNext(); break;
      case Qt::Key_Backspace    :
      case Qt::Key_Escape       : closeAll(); break;
      case Qt::Key_Insert       : optCenter = !optCenter; break;
      case Qt::Key_Delete       : slotDelete(); break;
*/
/*
      default:
        if ( e->text().toLatin1().at(0) && isalnum(e->text().toLatin1().at(0)) )
          find( e->text().toLatin1().at(0) );
        else
          switch( e->text().toLatin1().at(0) )
            {
            case 13  : Enter( tree->currentItem() ); break;
            case '~' : goToDir( '~' ); break;
            case '`' : goToDir( '`' ); break;
            default: QMainWindow::keyPressEvent( e );
            }
*/
      default:
            if( e->text() == "" )
              QWidget::keyPressEvent( e );
            else
              switch( e->text().toLatin1().at(0) )
              {
//              case '[' : slotGoPrev(); break;
//              case ']' : slotGoNext(); break;

//              case '\'':
//              case '{' : slotGoPrevDir(); break; // FIXME: not working?

//              case ';' :
//              case '}' : slotGoNextDir(); break; // FIXME: not working?

              case '~' : slotHomeDir();   break;
              case '`' : slotChangeDir(); break;
              
//              case '/' : toggleSortColumns(); break;

              default: 
                  e->ignore(); 
                  QMainWindow::keyPressEvent( e ); 
                  break;
              }
      }
    }
}

void NWMainWindow::resizeEvent(QResizeEvent *event)
{
  poster->rescaleImage();

  Settings.setValue( "x", x() );
  Settings.setValue( "y", y() );
  Settings.setValue( "w", width()  );
  Settings.setValue( "h", height() );
};

void NWMainWindow::moveEvent(QMoveEvent *event)
{
  Settings.setValue( "x", x() );
  Settings.setValue( "y", y() );
  Settings.setValue( "w", width()  );
  Settings.setValue( "h", height() );
}

/*****************************************************************************/

void NWMainWindow::actionTriggered(QAction *action)
{
    qDebug("action '%s' triggered", action->text().toLocal8Bit().data());
}

/*****************************************************************************/

void NWMainWindow::setupMenuBar()
{
    /*--------------------------------------------------------------------*/
    QMenu    *menu;

    menu = menuBar()->addMenu( tr("&File") );

    QAction *action;

    action = menu->addAction( tr("&Reload directory"), this, SLOT(slotReloadDir()), Qt::Key_F5 );
    action->setIcon( QIcon( ":/images/view-refresh.png" ) );

    action = menu->addAction( tr("&Quit"), this, SLOT(close()), Qt::AltModifier + Qt::Key_X );
    action->setIcon( QIcon( ":/images/system-log-out.png" ) );

    /*--------------------------------------------------------------------*/

    menu = menuBar()->addMenu( tr("&View"));

    action = menu->addAction( tr("Sort by &Name (A-Z)"),        this, SLOT(slotSortByName()), Qt::AltModifier + Qt::Key_N );
    action = menu->addAction( tr("Sort by &Modify Time (newest first)"), this, SLOT(slotSortByModTime()), Qt::AltModifier + Qt::Key_M );
    action = menu->addAction( tr("T&oggle between sort by Name or Modify Time"), this, SLOT(toggleSortColumns()), Qt::Key_Slash );

    menu->addSeparator();

    action = menu->addAction(tr("Switch layout direction"));
    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));

    /*--------------------------------------------------------------------*/

    menu = menuBar()->addMenu( tr("&Go"));

    action = menu->addAction( tr("Go to p&arent directory"), this, SLOT(slotGoUp()), Qt::Key_Backspace );
    action->setIcon( QIcon( ":/images/go-up.png" ) );

    action = menu->addAction( tr("Change &directory"), this, SLOT(slotChangeDir()), Qt::AltModifier + Qt::Key_D );
    action->setIcon( QIcon( ":/images/folder.png" ) );

    action = menu->addAction( tr("Go to &home directory"), this, SLOT(slotHomeDir()), Qt::AltModifier + Qt::Key_Home );
    action->setIcon( QIcon( ":/images/go-home.png" ) );

    menu->addSeparator();

    action = menu->addAction( tr("Go to &Random item"),   this, SLOT(slotRandomItem()), Qt::Key_Asterisk );
    action = menu->addAction( tr("Activate current item"),  this, SLOT(enterCurrent()), Qt::Key_Right );
    action = menu->addAction( tr("Keypad Menu"),  this, SLOT(slotKeypadMenu()), Qt::Key_Insert );

    menu->addSeparator();

    action = menu->addAction( tr("List "), this, SLOT(slotSelectLastPlayLocation()), Qt::Key_Delete );
    action->setIcon( QIcon( ":/images/act-last-loc.png" ) );

    /*--------------------------------------------------------------------*/

    menu = menuBar()->addMenu( tr("&Window"));

    action = menu->addAction( tr("&New browser window"), this, SLOT(slotNewWindow()), Qt::Key_F3 );
    action->setIcon( QIcon( ":/images/window-new.png" ) );

    menu->addAction( tr("&Close window"), this, SLOT(close()), Qt::Key_F4 );

    /*--------------------------------------------------------------------*/

    menu = menuBar()->addMenu( tr("&Settings"));
    
    action = menu->addAction( tr("Select main list BIG font"),   this, SLOT(slotSelectMainListBigFont()) );
    action = menu->addAction( tr("Select main list small font"), this, SLOT(slotSelectMainListSmallFont()) );
    action = menu->addAction( tr("Select keypad menu font"),     this, SLOT(slotSelectKeyPadFont()) );
    action = menu->addAction( tr("Select status bar font"),      this, SLOT(slotStatusBarFont()) );
    action = menu->addAction( tr("Reset all fonts to default"),  this, SLOT(slotResetFonts()) );

    action = menu->addAction( "Use local (per directory) sorting" );
    action->setCheckable( true );
    action->setChecked( opt_use_per_directory_sorting );
    connect( action, SIGNAL( toggled(bool) ), this, SLOT(slotTogglePerDirSorting()) );

    menu->addSeparator();

    /*--------------------------------------------------------------------*/

    menu = menuBar()->addMenu( tr("&Help") );

    action = menu->addAction( tr("&Help Contents"), this, SLOT(slotHelp()), Qt::Key_F1 );
    action->setIcon( QIcon( ":/images/help-browser.png" ) );

    action = menu->addAction( tr("&About"),  this, SLOT(slotAbout()), Qt::AltModifier + Qt::Key_A );
    action->setIcon( QIcon( ":/images/face-glasses.png" ) );

}

void NWMainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
}

void NWMainWindow::switchLayoutDirection()
{
    QHBoxLayout *hbl = (QHBoxLayout*)(centralWidget()->layout());
    if( hbl->direction() == QBoxLayout::LeftToRight )
      hbl->setDirection( QBoxLayout::RightToLeft );
    else
      hbl->setDirection( QBoxLayout::LeftToRight );
}
