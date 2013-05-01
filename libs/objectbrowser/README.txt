*******************************************************
*** QObjectBrowser                                    *
*** Created by Jeremy Magland on 13 June 2007         *
*** Modified by krawek on 15 June 2007                *
*** Modified by magland on 18 June 2007 - widget tree *
*** Modified by magland on 19 June 2007               
*** Modified by Alan Ezust in July 2010, May 2011
    Requires Qt 4.6 due to use of QScopedPointer.
    Builds on windows as a library exporting symbols.
    Added toggle-view action: QObjectBrowserAction
        which lazily creates the qobjectbrowser only when requested. 
    Made ObjectBrowser an embeddable QWidget instead of a main window.
    Use alternate properties for objectname in tree view.
    Allows you to add extra objects to the QObjectTreeModel
    Shows qApp in list of objects. 
    
*******************************************************
Originally based on code from here:
http://www.qtcentre.org/threads/7539-QObjectBrowser

QObjectBrowser is a utility for inspecting
QWidgets and QObjects at run time.

*******************************************************
Installation:
	run qmake and make from the main objectbrowser directory.
	* library will be created in parent directory

*******************************************************
Usage #1: In your application do the following:
	QObjectBrowser *browser=new QObjectBrowser;
	browser->showNormal();
*******************************************************
Usage #2: The line below adds a toggleable action to a menu
          to show/hide the browser:   
    viewMenu->addAction(new QObjectBrowserAction(this));

License: GPL

Feel free to modify the source, and post your contributions
to the QtCentre forum... or send them directly to me, and
I will post.

J. Magland
