/****************************************************************************
**
**  NightWatch Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  http://cade.datamax.bg/nw/
**
****************************************************************************/

#ifndef _NW_MAIN_WIN_H_
#define _NW_MAIN_WIN_H_

#include <QMainWindow>
#include <QTreeWidget>
#include <QDir>
#include <QMenu>
#include <QString>
#include <QDialog>
#include <QWidget>
#include <QImage>
#include <QTimer>

class NWMainWindow;

class NWTreeWidgetItem : public QTreeWidgetItem
{

  public:
    NWTreeWidgetItem();
    
    QString fn;
    int     is_dir;
};

class NWPoster : public QWidget
{
    Q_OBJECT

    QString fn;
    QImage  im;

  public:
    void loadImage( const QString file_name );
    void rescaleImage();

  protected:
    void paintEvent( QPaintEvent * e );
};

class NWTreeWidget : public QTreeWidget
{

     Q_OBJECT

 public:
     NWMainWindow *main_window;

     NWTreeWidget();
     NWTreeWidget( QWidget *parent );

     void findNext( QString str, int full_match = 0 );
     void findNextThe( QString str );

 protected:
     void keyPressEvent(QKeyEvent *event);
};

class NWMainWindow : public QMainWindow
{

     Q_OBJECT

     int rand_seeded;
     int first_load; 

 public:

     NWTreeWidget   *tree;
     NWPoster       *poster;
     QTimer         *timer;

     QDir            cdir;
     int             movies_count;
     int             movies_posters;

     int             last_sort_col;
     int             last_sort_ord;

     int             auto_play;
     QTimer         *auto_play_timer;
     
     NWTreeWidgetItem *last_played;

     NWMainWindow();
     ~NWMainWindow();

     void closeAllViews();

     void loadDir( QString path, int mode ); // modes: 0 reload, 1 enter new, 2 go up
     void goToDir( int mode );

     void goPrevNext( int r, int skip_dirs = 1 );
     void goPrevNextDir( int r );

     void sortColumn( int n, int d = 'A' );

     int deleteItems( int current_only );

     void addPlayLocation( QString location );
     void beginAutoPlay();
     void cancelAutoPlay();

 protected:

     void showEvent(QShowEvent *event);
     void keyPressEvent(QKeyEvent *event);
     void resizeEvent(QResizeEvent *event);
     void moveEvent(QMoveEvent *event);

 public slots:

     void toggleSortColumns();

     void enter( QTreeWidgetItem *item );
     void enterCurrent();

     void actionTriggered(QAction *action);
     void switchLayoutDirection();

     void slotItemActivated( QTreeWidgetItem *item, int column );
     void slotCurrentItemChanged( QTreeWidgetItem *current, QTreeWidgetItem *previous );
     void slotLoadCurrentImage();

     void slotAutoPlayNext();

     void slotNewWindow();
     void slotGoUp();

     void slotChangeDir();
     void slotHomeDir();
     void slotReloadDir();

     void slotSortColumn1();
     void slotSortColumn3();

     void slotRandomItem();
     void slotKeypadMenu();

     void slotHelp();
     void slotAbout();
     
     void slotSelectLastPlayLocation();

     void slotSelectMainListBigFont();
     void slotSelectMainListSmallFont();
     void slotSelectKeyPadFont();
     void slotStatusBarFont();
     void slotResetFonts();

 private:
     void setupMenuBar();
};

#endif
