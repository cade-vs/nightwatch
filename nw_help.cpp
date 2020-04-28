/****************************************************************************
**
**  NightWatch Navigator
**  2020 (c) Vladi Belperchinov-Shabanski
**  <cade@bis.bg> <shabanski@gmail.com> <cade@cpan.org>
**  http://cade.datamax.bg/NW/
**
****************************************************************************/

#include <QKeyEvent>
#include <QResource>

#include "nw_help.h"

NWHelpBrowser::NWHelpBrowser()
  : QTextBrowser()
{
};

void NWHelpBrowser::keyPressEvent ( QKeyEvent * e )
{
  if( e->modifiers() & Qt::ALT )
    {
    switch( e->key() )
      {
      default: QTextBrowser::keyPressEvent( e ); break;
      }
    }
  else
    {
    switch( e->key() )
      {
      case Qt::Key_Escape:
      case Qt::Key_Return:
      case Qt::Key_F4    : close(); break;

      default:
            if( e->text() == "" )
              QTextBrowser::keyPressEvent( e );
            else
              switch( e->text().toLatin1().at( 0 ) )
              {
              default: QTextBrowser::keyPressEvent( e ); break;
              }
      }
    }
};

NWHelpBrowser *help_browser;

void display_help()
{
  if( help_browser == NULL )
    help_browser = new NWHelpBrowser;
  help_browser->setHtml( QString( QVariant( (const char*)(QResource( ":/NW_help.html" ).data()) ).toString() ) );

  help_browser->setObjectName( "NWHelpWindow" );
  help_browser->setWindowTitle( "NW/4 Help" );

  help_browser->resize( 640, 400 );
  help_browser->move( 100, 100 );

  help_browser->show();
};



