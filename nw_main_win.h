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
#include <QPushButton>
#include <QWidget>
#include <QImage>
#include <QTimer>

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

 public:

     NWTreeWidget   *tree;
     NWPoster       *poster;
     QTimer         *timer;

     QDir            cdir;

     int             last_sort_col;
     Qt::SortOrder   last_sort_ord;

     int             opt_thumbs;
     int             opt_dirs_only;
     
     NWTreeWidgetItem *last_played;

     NWMainWindow();
     ~NWMainWindow();

     void closeAllViews();

     void loadDir( QString path, int mode ); // modes: 0 reload, 1 enter new, 2 go up
     void goToDir( int mode );

     void loadThumbs();

     void goPrevNext( int r, int skip_dirs = 1 );
     void goPrevNextDir( int r );

     void sortColumn( int n );

     int deleteItems( int current_only );

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

     void slotNewWindow();
     void slotGoUp();
     void slotThumbs();
     void slotCreateThumbs();
     void slotJPEGThumbs();
     void slotSmoothThumbs();
     void slotDirThumbs();

     void slotChangeDir();
     void slotHomeDir();
     void slotReloadDir();
     void slotShowDirsOnly();

     void slotSortColumn1();
     void slotSortColumn3();

     void slotRandomItem();
     void slotKeypadMenu();

     void slotHelp();
     void slotAbout();
     

 private:
     void setupMenuBar();
};

#endif
