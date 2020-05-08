/****************************************************************************
**
**  NightWatch Video Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  https://github.com/cade-vs/nightwatch
**
****************************************************************************/

#ifndef _NW_HELP_H_
#define _NW_HELP_H_

#include <QTextBrowser>

#include "nw_main_win.h"

class NWHelpBrowser : public QTextBrowser
{
    Q_OBJECT

  public:
    NWHelpBrowser();

  protected:
    void keyPressEvent ( QKeyEvent * e );
};

extern NWHelpBrowser *help_browser;

void display_help( NWMainWindow* main_window );

#endif
