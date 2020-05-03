/****************************************************************************
**
**  NightWatch Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  http://cade.datamax.bg/nw/
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

#include <QTreeWidgetItem>
#include <QAbstractItemView>

#include <qdebug.h>

#include "nw.h"
#include "nw_main_win.h"
#include "nw_help.h"


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
    if( name.indexOf( str.toUpper() ) == 0 ) break;
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

  e->ignore();
  int a = e->text() == "" ? 0 : e->text().toLatin1().at(0);
  int m = e->modifiers();

  if( ( m == Qt::ShiftModifier || m == Qt::NoModifier ) && a >= '!' && a <= 'z' )
    {
    findNextThe( QString( QVariant( a ).toChar() ) );
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

    opt_thumbs        = 0;
    opt_dirs_only     = 0;

    last_sort_col = 1;
    last_sort_ord = Qt::AscendingOrder;

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
    tree->sortByColumn( 1, Qt::AscendingOrder );

    tree->setDragEnabled( 1 );

    tree->setSelectionMode( QAbstractItemView::ExtendedSelection );

    setupMenuBar();
    
    QWidget *central_widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout( central_widget );


    layout->addWidget( poster, 1 );
    layout->addWidget( tree,   2 );

    layout->setStretchFactor( poster, 1 );
    layout->setStretchFactor( tree,   2 );
    
    layout->setSpacing( 0 );
    
    setCentralWidget( central_widget );

    poster->loadImage( QString( ":/images/journey_by_t1na.jpg" ) );

    timer = new QTimer( this );

    connect( timer, SIGNAL(timeout()), this, SLOT(slotLoadCurrentImage()));
    connect( tree,  SIGNAL(itemActivated(QTreeWidgetItem *, int)), this, SLOT(slotItemActivated(QTreeWidgetItem *, int)));
    connect( tree,  SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)), this, SLOT(slotCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));
}

NWMainWindow::~NWMainWindow()
{
  delete poster;
  delete tree;
}

/*****************************************************************************/

void NWMainWindow::loadDir( QString path, int mode )
{
  QString last_path = cdir.absolutePath();

  cdir.cd( path );

  QString new_path = cdir.absolutePath();

  setWindowTitle( QString() + " NightWatch " + NW_VERSION + ": " + new_path );

  QStringList filters;
  filters.append( QString( "*" ) );

  QFileInfoList info_list = cdir.entryInfoList( filters );

  NWTreeWidgetItem *current = NULL;

  QFont font_big(   QFont( "Coolvetica", 24, QFont::Bold, false ) );
  QFont font_small( QFont( "Coolvetica", 12, QFont::Bold, false ) );
  
  QIcon icon_video(  ":/images/video-x-generic.png" );
  QIcon icon_folder( ":/images/folder.png" );

  QString save_item_name;
  if( mode == 0 && tree->topLevelItemCount() > 0 ) save_item_name = tree->currentItem()->text( 1 );

  tree->clear();
  
  int movies_found = 0;
  for( int i = 0; i < info_list.count(); i++ )
    {
    QFileInfo fi = info_list.at( i );

    if( opt_dirs_only && ! fi.isDir() ) continue;

    if( fi.fileName() == "."  ) continue;
    if( fi.fileName() == ".." ) continue;

    QString ext = "." + fi.suffix() + ".";
    if( ! fi.isDir() && movies_extensions_filter.indexOf( ext.toUpper() ) < 0 ) continue;

    QString file_name = fi.fileName();

    NWTreeWidgetItem *item = new NWTreeWidgetItem();

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
      movies_found++;
      }

    item->fn = file_name;

    file_name.replace( QRegularExpression( "[_.]" ), " " );
    file_name.replace( QRegularExpression( "^THE (.+)", QRegularExpression::CaseInsensitiveOption ), "\\1 [The *]" );
    
    item->setText( 1, file_name );
    item->setText( 2, fi.isDir() ? "" : QVariant( fi.size() / 1024 / 1024 ).toString() + " MB" );
    item->setText( 3, fi.lastModified().toString( "yyyy-MM-dd hh:mm:ss" ) );
    item->setTextAlignment( 2, Qt::AlignRight );

    item->setFont( 0, font_small );
    item->setFont( 1, font_big   );
    item->setFont( 2, font_small );
    item->setFont( 3, font_small );

    tree->addTopLevelItem( item );

    if( LastPlayed.value( new_path ) == item->fn ) last_played = item;

    if( mode == 0 && save_item_name == file_name              ) current     = item;
    if( mode == 2 && last_path   == new_path + "/" + item->fn ) current     = item;
    }
    
  if( movies_found > 1 && last_played )  
    {
    QIcon lp_icon( ":/images/last-played.png" );
    last_played->setIcon( 1, lp_icon );
    if( mode == 1 ) current = last_played;
    }

  tree->setCurrentItem( tree->topLevelItem( 0 ) );
  if( current )
    tree->setCurrentItem( current );

  qDebug() << "load dir mode = " << mode;

  statusBar()->showMessage( QString( tr( "Loaded items" ) ) + ": " + QVariant( tree->topLevelItemCount() ).toString() );

  if( opt_thumbs )
    loadThumbs();
    
  tree->resizeColumnToContents( 0 );
  tree->resizeColumnToContents( 1 );
  tree->resizeColumnToContents( 2 );
  tree->resizeColumnToContents( 3 );
};

/*****************************************************************************/

void NWPoster::loadImage( const QString file_name )
{
  fn = file_name;
  rescaleImage();
};

void NWPoster::rescaleImage()
{
  if( ! im.load( fn ) ) im.load( QString( ":/images/journey_by_t1na.jpg" ) );
  im = im.scaled( QSize( width(), height() ), Qt::KeepAspectRatio, Qt::SmoothTransformation );
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

void NWMainWindow::loadThumbs()
{
  QProgressDialog pd( tr( "Loading thumbnails..." ), tr( "Cancel" ), 0, tree->topLevelItemCount() - 1 );
  pd.move( x() + ( ( width() - pd.width() ) / 2 ), y() + ( ( height() - pd.height() ) / 2) );

  QString new_path = cdir.absolutePath();

  for( int i = 0; i < tree->topLevelItemCount(); i++ )
    {
    pd.setValue( i );
    if ( pd.wasCanceled() )
      break;
    QApplication::processEvents();

    if( i >= tree->topLevelItemCount() ) return;

    NWTreeWidgetItem *item = (NWTreeWidgetItem*)tree->topLevelItem( i );

    //qDebug() << tree->topLevelItemCount() << " | " << i << " | " << item;

    QString item_name = item->fn;
    QString item_name_src;

    if( item->is_dir )
      {
      if( ! opt_show_dir_thumbs ) continue;

      //new_path = cdir.absolutePath() + "/" + item_name;

      QDir tdir;
      tdir.cd( new_path + "/" + item_name );

      QStringList filters;
      filters.append( QString( "*" ) );

      QFileInfoList info_list = tdir.entryInfoList( filters );

      for( int i = 0; i < info_list.count(); i++ )
        {
        QFileInfo fi = info_list.at( i );

        if( fi.fileName() == "."  ) continue;
        if( fi.fileName() == ".." ) continue;

        QString ext = "." + fi.suffix() + ".";
        if( ! fi.isDir() && images_extensions_filter.indexOf( ext.toUpper() ) < 0 ) continue;

        item_name_src = item_name + "/" + fi.fileName();
        break;
        }

      //qDebug() << "Show dir thumbs: " << new_path << " | " << item_name;
      }
    else
      {
      item_name_src = item_name;
      item_name_src.replace( QRegularExpression( "\\.[^.]+$" ), ".jpg" ); // TODO: find optional ext, jpg, jpeg, png, etc.
      }  
 
    QStringList icon_fns;
    icon_fns.append( new_path + "/.thumbnails/" + item_name + ".jpg" ); // JPEG thumb idex is 0!
    icon_fns.append( new_path + "/.thumbnails/" + item_name + ".png" ); // PNG  thumb idex is 1!

    int found = -1;
    for( int z = 0; z < icon_fns.count(); z++ )
      {
      if( QFile::exists( icon_fns[z] ) )
        {
        found = z;
        break;
        }
      }

    if( found == -1 && opt_create_thumbs )
      {
      QString icon_dir = new_path + "/.thumbnails";
      if( opt_create_thumbs )
        {
        if( ! cdir.exists( icon_dir ) )
          cdir.mkdir( icon_dir );
        }

      QString file_name = new_path + "/" + item_name_src;
      QImage im;
      im.load( file_name );
      if( im.width() > opt_thumbs_size || im.height() > opt_thumbs_size )
        im = im.scaled( QSize( opt_thumbs_size, opt_thumbs_size ) , Qt::KeepAspectRatio, opt_create_smooth_thumbs ? Qt::SmoothTransformation : Qt::FastTransformation );
      int thumb_format_index = 1; // use PNG index!
      if( opt_create_jpeg_thumbs )
        {
        QFileInfo fi( file_name );
        QString ext = fi.suffix().toLower();
        if( ext == "jpg" || ext == "jpeg" )
          thumb_format_index = 0; // use JPEG index! but only for jpeg files
        }
      im.save( icon_fns[ thumb_format_index ] );
      found = thumb_format_index;
      }

    if( found > -1 )
      {
      QIcon icon( icon_fns[ found ] );
      if( ! icon.isNull() ) item->setIcon( 1, icon );
      }

    } // for tree

}

/*****************************************************************************/

void NWMainWindow::goToDir( int mode )
{
  mode = ! mode; // FIXME: for what??
  QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;
/*
  if (!native->isChecked())
      options |= QFileDialog::DontUseNativeDialog;
*/
  QString new_dir = QFileDialog::getExistingDirectory( this,
                              tr( "Change directory" ),
                              cdir.absolutePath(),
                              options );
  if ( ! new_dir.isEmpty() )
      loadDir( new_dir, 1 );
};

/*****************************************************************************/

void NWMainWindow::enter( QTreeWidgetItem *item )
{
  if( ! item ) return;

  NWTreeWidgetItem *nw_item = (NWTreeWidgetItem*)item;

  if( nw_item->is_dir )
    {
    loadDir( nw_item->fn, 1 );
    }
  else
    {
    QString ndir = cdir.absolutePath();
    LastPlayed.setValue( ndir, nw_item->fn );
    QIcon lp_icon( ":/images/last-played.png" );
    nw_item->setIcon( 1, lp_icon );
    if( last_played ) last_played->setIcon( 1, QIcon() );
    last_played = nw_item;

    QStringList exec_args = { ndir + "/" + nw_item->fn };
    QProcess mpl;
    mpl.execute( "nw-movie-player", exec_args );
    mpl.waitForFinished();
    }
};

void NWMainWindow::enterCurrent()
{
  enter( tree->currentItem() );
}

/*****************************************************************************/

void NWMainWindow::slotItemActivated( QTreeWidgetItem *item, int column )
{
  enter( item );
};

void NWMainWindow::slotCurrentItemChanged( QTreeWidgetItem *current, QTreeWidgetItem *previous )
{
  timer->start( 100 );
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
    found_image_name = abs_path + "/" + item_name;
    found_image_name.replace( QRegularExpression( "\\.[^.]+$" ), ".jpg" ); // TODO: find optional ext, jpg, jpeg, png, etc.
    }  

  if( ! QFile::exists( found_image_name ) )
    found_image_name = find_first_image_in_dir( abs_path );

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

void NWMainWindow::slotThumbs()
{
  opt_thumbs = ! opt_thumbs;
  if( opt_thumbs ) loadThumbs();

  statusBar()->showMessage( opt_thumbs ? tr( "Thumbnails enabled" ) : tr( "Thumbnails disabled" ) );
};

void NWMainWindow::slotCreateThumbs()
{
  opt_create_thumbs = ! opt_create_thumbs;
  Settings.setValue( "create_thumbs", opt_create_thumbs );

  statusBar()->showMessage( opt_create_thumbs ? tr( "Thumbnails creation enabled" ) : tr( "Thumbnails creation disabled" ) );
};

void NWMainWindow::slotJPEGThumbs()
{
  opt_create_jpeg_thumbs = ! opt_create_jpeg_thumbs;
  Settings.setValue( "create_jpeg_thumbs", opt_create_jpeg_thumbs );

  statusBar()->showMessage( opt_create_jpeg_thumbs ? tr( "JPEG Thumbnails creation for JPEGs enabled" ) : tr( "PNG Thumbnails creation for all image types enabled" ) );
};

void NWMainWindow::slotDirThumbs()
{
  opt_show_dir_thumbs = ! opt_show_dir_thumbs;
  Settings.setValue( "opt_show_dir_thumbs", opt_show_dir_thumbs );

  statusBar()->showMessage( opt_show_dir_thumbs ? tr( "Directory thumbnails enabled" ) : tr( "Directory thumbnails disabled" ) );
}

void NWMainWindow::slotSmoothThumbs()
{
  opt_create_smooth_thumbs = ! opt_create_smooth_thumbs;
  Settings.setValue( "create_smooth_thumbs", opt_create_smooth_thumbs );

  statusBar()->showMessage( opt_create_smooth_thumbs ? tr( "Smooth Thumbnails creation enabled" ) : tr( "Fast Thumbnails creation enabled" ) );
};

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

void NWMainWindow::slotShowDirsOnly()
{
  opt_dirs_only = ! opt_dirs_only;
  loadDir( cdir.absolutePath(), 1 );

  statusBar()->showMessage( opt_dirs_only ? tr( "Show directories only" ) : tr( "Show all directories and files" ) );
}

void NWMainWindow::sortColumn( int n )
{
  if( last_sort_col == n )
    {
    last_sort_ord = last_sort_ord == Qt::AscendingOrder ? Qt::DescendingOrder : Qt::AscendingOrder;
    }
  else
    {
    last_sort_ord = Qt::AscendingOrder;
    }
  last_sort_col = n;
  tree->sortByColumn( last_sort_col, last_sort_ord );
};

void NWMainWindow::toggleSortColumns()
{
  if( last_sort_col == 3 )
    {
    sortColumn( 1 );
    statusBar()->showMessage( QString( tr( "Sort entries by NAME" ) ) );
    }
  else
    {
    sortColumn( 3 );  
    statusBar()->showMessage( QString( tr( "Sort entries by MODIFY TIME" ) ) );
    }
  tree->scrollToItem( tree->currentItem() );  
}

void NWMainWindow::slotSortColumn1()
{
  sortColumn( 1 );
};

void NWMainWindow::slotSortColumn3()
{
  sortColumn( 3 );
};

void NWMainWindow::slotRandomItem()
{
  int x = tree->topLevelItemCount();
  if( rand_seeded == 0 ) qsrand( QDateTime::currentDateTime().toTime_t() );
  rand_seeded = 1;
  int r = qrand();

  int n = int( r % x );

  tree->setCurrentItem( tree->topLevelItem( n ) );
};

void NWMainWindow::slotHelp()
{
  display_help();
};

void NWMainWindow::slotAbout()
{
  poster->loadImage( ":/images/journey_by_t1na.jpg" );
};

/*****************************************************************************/

void NWMainWindow::keyPressEvent ( QKeyEvent * e )
{

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
/*
    action = menu->addAction(tr("Save layout..."));
    connect(action, SIGNAL(triggered()), this, SLOT(saveLayout()));

    action = menu->addAction(tr("Load layout..."));
    connect(action, SIGNAL(triggered()), this, SLOT(loadLayout()));
    action = menu->addAction(tr("Switch layout direction"));
    connect(action, SIGNAL(triggered()), this, SLOT(switchLayoutDirection()));

    menu->addSeparator();
*/

    action = menu->addAction( tr("&Reload directory"), this, SLOT(slotReloadDir()), Qt::Key_F5 );
    action->setIcon( QIcon( ":/images/view-refresh.png" ) );

    action = menu->addAction( tr("&Quit"), this, SLOT(close()), Qt::AltModifier + Qt::Key_X );
    action->setIcon( QIcon( ":/images/system-log-out.png" ) );

    /*--------------------------------------------------------------------*/

    menu = menuBar()->addMenu( tr("&View"));

    action = menu->addAction( tr("Enable &thumbnails") );
    action->setCheckable( true );
    action->setChecked( opt_thumbs );
    action->setShortcut( Qt::Key_F6 );
    connect( action, SIGNAL( toggled(bool) ), this, SLOT(slotThumbs()) );

    action = menu->addAction( tr("Show d&irectories only") );
    action->setCheckable( true );
    action->setChecked( opt_dirs_only );
    action->setShortcut( Qt::AltModifier + Qt::Key_I );
    connect( action, SIGNAL( toggled(bool) ), this, SLOT(slotShowDirsOnly()) );

    menu->addSeparator();

    action = menu->addAction( tr("Sort by &Name"),        this, SLOT(slotSortColumn1()), Qt::AltModifier + Qt::Key_N );
    action = menu->addAction( tr("Sort by &Modify Time"), this, SLOT(slotSortColumn3()), Qt::AltModifier + Qt::Key_M );
    action = menu->addAction( tr("T&oggle between sort by Name or Modify Time"), this, SLOT(toggleSortColumns()), Qt::Key_Slash );

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

    /*--------------------------------------------------------------------*/

    menu = menuBar()->addMenu( tr("&Window"));

    action = menu->addAction( tr("&New browser window"), this, SLOT(slotNewWindow()), Qt::Key_F3 );
    action->setIcon( QIcon( ":/images/window-new.png" ) );

    menu->addAction( tr("&Close window"), this, SLOT(close()), Qt::Key_F4 );

    /*--------------------------------------------------------------------*/

    menu = menuBar()->addMenu( tr("&Settings"));

    action = menu->addAction( tr("Create thumbnails if needed") );
    action->setCheckable( true );
    action->setChecked( opt_create_thumbs );
    connect( action, SIGNAL( toggled(bool) ), this, SLOT(slotCreateThumbs()) );

    action = menu->addAction( tr("Create smooth thumbnails") );
    action->setCheckable( true );
    action->setChecked( opt_create_smooth_thumbs );
    connect( action, SIGNAL( toggled(bool) ), this, SLOT(slotSmoothThumbs()) );

    action = menu->addAction( tr("Create new thumbnails in JPEG for JPEGs") );
    action->setCheckable( true );
    action->setChecked( opt_create_jpeg_thumbs );
    connect( action, SIGNAL( toggled(bool) ), this, SLOT(slotJPEGThumbs()) );

    action = menu->addAction( tr("Show directory thumbnails") );
    action->setCheckable( true );
    action->setChecked( opt_show_dir_thumbs );
    connect( action, SIGNAL( toggled(bool) ), this, SLOT(slotDirThumbs()) );

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
    if (layoutDirection() == Qt::LeftToRight)
        qApp->setLayoutDirection(Qt::RightToLeft);
    else
        qApp->setLayoutDirection(Qt::LeftToRight);
}
