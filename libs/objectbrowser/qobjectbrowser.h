/****************************************************************************
 This file is part of ChainLink
 Copyright (C) 2007 Jeremy Magland (Jeremy.Magland@gmail.com)

 ChainLink is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 ChainLink is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with ChainLink; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/


#ifndef QOBJECTBROWSER_H
#define QOBJECTBROWSER_H
#include "obexport.h"

#include <QWidget>
#include <QDialog>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QSignalMapper>
#include <QMainWindow>
#include <QSplitter>
#include <QTreeWidget>
#include "qobjecttree.h"
class Ui_qobjectbrowser;


/** A record that keeps count of how many times a signal was emitted */
class QOB_signal_record {
public:
    QSignalMapper *m_sigmapper;
    long m_count;

	QOB_signal_record();
	virtual ~QOB_signal_record();
};

/** A Designer widget - see qobjectbrowser.ui
  */
class QObjectBrowserControl : public QWidget {
	Q_OBJECT
public:
    QList<QOB_signal_record *> m_signal_records;
    QObject *m_obj;

    explicit QObjectBrowserControl(QWidget *parent = 0);
	virtual ~QObjectBrowserControl();


	void clear_signal_records();
	void clear();
	void set_object(QObject *obj_in);
	void set_children();
	void set_properties();
	void set_signals();
	void update_signal_values();
	void update_signal_value(int sig_num);
	void set_slots();
	void set_methods();
    bool hasdescendent(QObject *m_obj);
public slots:
	void on_signal_triggered(int signal_num);
	void on_update_children();
	void on_update_properties();
	void on_up_to_parent();
	void on_children_table_cell_clicked(int row, int column);
	void on_object_destroyed();
signals:
    void object_changed(QObject *m_obj);

private:
    Ui_qobjectbrowser* ui;
};

/** A Object Browser, traversing the tree of QObjects
    that is your application, with maximal possible
    metadata details. A useful runtime debugging tool.
    
    This file is part of ChainLink
    Copyright (C) 2007 Jeremy Magland (Jeremy.Magland@gmail.com)
    Parts modified 2011 Alan Ezust
*/

class OBJECTBROWSER_EXPORT QObjectBrowser : public QWidget {
	Q_OBJECT
public:
    explicit QObjectBrowser(QWidget* parent=0);

    QScopedPointer<QObjectBrowserControl> m_control;
    QScopedPointer<QObjectTree> m_tree;
    QObjectTreeModel m_model;
    QWidget* m_last_focus_window;

    void closeEvent(QCloseEvent*);   
    void set_object(QObject* obj);
    bool valid_object(QObject* obj);
	QObject* get_current_object();
public slots:
	void on_current_item_changed();
	void on_object_changed(QObject *obj);
	void on_update();
    void dumpObject();
	void on_focus_changed( QWidget *old, QWidget *now);
	void on_browse_focus();

	void on_show_widget();
	void on_hide_widget();
	void on_focus_widget();
signals:
    void hidden();
protected:
    void restoreSettings();
    void saveSettings();
};


#endif

