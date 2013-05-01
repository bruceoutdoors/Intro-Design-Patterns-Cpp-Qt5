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

#include "qobjectbrowser.h"
#include "ui_qobjectbrowser.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QToolBar>
#include <QSettings>
#include <QTimer>
#include <stdio.h>


    QObjectBrowserControl::QObjectBrowserControl(QWidget *parent) : QWidget(parent),
    ui (new Ui_qobjectbrowser){
        ui->setupUi(this);

        m_obj=0;

        connect(ui->update_children_button,SIGNAL(clicked()),this,SLOT(on_update_children()));
        connect(ui->update_properties_button,SIGNAL(clicked()),this,SLOT(on_update_properties()));
        connect(ui->parent_button,SIGNAL(clicked()),this,SLOT(on_up_to_parent()));

        connect(ui->children_table,SIGNAL(cellDoubleClicked (int,int)),this,SLOT(on_children_table_cell_clicked(int,int)));

		set_object(parent);
	}
	QObjectBrowserControl::~QObjectBrowserControl() {
        delete ui;
		clear_signal_records();
	}
	void QObjectBrowserControl::clear() {
        ui->children_table->clearContents(); ui->children_table->setRowCount(1);
        ui->properties_table->clearContents(); ui->properties_table->setRowCount(1);
        ui->signals_table->clearContents(); ui->signals_table->setRowCount(1);
        ui->slots_table->clearContents(); ui->slots_table->setRowCount(1);
        ui->methods_table->clearContents(); ui->methods_table->setRowCount(1);

        ui->class_name->setText("");
        ui->base_class_name->setText("");

		clear_signal_records();

		repaint();

	}

	void QObjectBrowserControl::clear_signal_records() {
		int j;
        for (j=0; j<m_signal_records.count(); j++)
            delete m_signal_records[j];
        m_signal_records.clear();
	}
	bool QObjectBrowserControl::hasdescendent(QObject *obj) {
		while (obj) {
			if (obj==this) return true;
			obj=obj->parent();
		}
		return false;
	}
	void QObjectBrowserControl::on_object_destroyed() {
        m_obj=0;
		clear();
	}
	void QObjectBrowserControl::set_object(QObject *obj_in) {
        if (m_obj) {
            disconnect(m_obj,SIGNAL(destroyed()),this,SLOT(on_object_destroyed()));
		}
        m_obj=obj_in;

		clear();

        if (!m_obj) return;

        connect(m_obj,SIGNAL(destroyed()),this,SLOT(on_object_destroyed()));

        const QMetaObject *metaobj=m_obj->metaObject();
		if (!metaobj) return;
        ui->class_name->setText(metaobj->className());
		if (metaobj->superClass())
            ui->base_class_name->setText(metaobj->superClass()->className());
		else
            ui->base_class_name->setText("");

        if (m_obj->parent())
            ui->parent_button->setEnabled(true);
		else
            ui->parent_button->setEnabled(false);
        if ((m_obj->parent())&&(m_obj->parent()->metaObject()))
            ui->parent_class_name->setText(m_obj->parent()->metaObject()->className());
		else
            ui->parent_class_name->setText("");

		set_children();
		set_properties();
		set_signals();
		set_slots();
		set_methods();

        emit object_changed(m_obj);
	}
	void QObjectBrowserControl::set_children() {
        ui->children_table->clear();
        ui->children_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->children_table->setColumnCount(2);
        ui->children_table->setHorizontalHeaderLabels(QStringList() << tr("Type") << tr("Name") );

        if (!m_obj) return;

        QObjectList objlist=m_obj->children();

        ui->children_table->setRowCount(objlist.count());

		int j;
		QTableWidgetItem *item;
		for (j=0; j<objlist.count(); j++) {
			QString txt="[   ]";
			const QMetaObject *metaobj=objlist[j]->metaObject();
			if (metaobj) {
				txt=metaobj->className();
			}

			item=new QTableWidgetItem;
			item->setText(txt);
			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->children_table->setItem(j,0,item);

			item=new QTableWidgetItem;
			item->setText(objlist[j]->objectName());
			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->children_table->setItem(j,1,item);

		}
	}
	void QObjectBrowserControl::set_properties() {
        ui->properties_table->clear();
        ui->properties_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->properties_table->setColumnCount(3);
        ui->properties_table->setHorizontalHeaderLabels(QStringList() << tr("Type") << tr("Name") << tr("Value"));

        if (!m_obj) return;
        const QMetaObject *metaobj=m_obj->metaObject();
		if (!metaobj) return;


        ui->properties_table->setRowCount(metaobj->propertyCount());

		int j;
		QTableWidgetItem *item;
		for (j=0; j<metaobj->propertyCount(); j++) {
			QMetaProperty prop=metaobj->property(j);

			item=new QTableWidgetItem;
			item->setText(prop.typeName());
			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->properties_table->setItem(j,0,item);

			item=new QTableWidgetItem;
			item->setText(prop.name());
			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->properties_table->setItem(j,1,item);

			item=new QTableWidgetItem;
            item->setText(prop.read(m_obj).toString());
			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            ui->properties_table->setItem(j,2,item);
		}
	}
	void QObjectBrowserControl::set_signals() {
        ui->signals_table->clear();
		clear_signal_records();
        ui->signals_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->signals_table->setColumnCount(2);
        ui->signals_table->setHorizontalHeaderLabels(QStringList() << tr("Signal") << tr("Count")); // << tr("Connects"));

        if (m_obj==(QObject *)ui->signals_table) {
			//don't map the signals for the signal table, due to recursion
			return;
		}

        if (!m_obj) return;
        const QMetaObject *metaobj=m_obj->metaObject();
		if (!metaobj) return;

		int ct=0;
		int j;
		for (j=0; j<metaobj->methodCount(); j++)
			if (metaobj->method(j).methodType()==QMetaMethod::Signal)
				ct++;
        ui->signals_table->setRowCount(ct);

		QTableWidgetItem *item;
		ct=0;

		for (j=0; j<metaobj->methodCount(); j++) {
			QMetaMethod meth=metaobj->method(j);
			if (meth.methodType()==QMetaMethod::Signal) {
				QOB_signal_record *ptr=new QOB_signal_record;
                ptr->m_sigmapper=new QSignalMapper;
                ptr->m_sigmapper->setMapping(m_obj,ct);
				char holdstr[1000];
				sprintf(holdstr,"2%s",meth.signature());
                connect(m_obj,holdstr,ptr->m_sigmapper,SLOT(map()));
                connect(ptr->m_sigmapper,SIGNAL(mapped(int)),this,SLOT(on_signal_triggered(int)));
                m_signal_records.append(ptr);

				item=new QTableWidgetItem;
				item->setText(meth.signature());
				item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->signals_table->setItem(ct,0,item);
                // TODO: setItem (ct, 2, new item that shows the number of connections )


				ct++;
			}
		}
		update_signal_values();
	}
	void QObjectBrowserControl::update_signal_values() {
        if (!m_obj) return;
        const QMetaObject *metaobj=m_obj->metaObject();
		if (!metaobj) return;

		int ct=0;
		int j;
		for (j=0; j<metaobj->methodCount(); j++) {
			QMetaMethod meth=metaobj->method(j);
			if (meth.methodType()==QMetaMethod::Signal) {
				update_signal_value(ct);
				ct++;
			}
		}

	}
	void QObjectBrowserControl::update_signal_value(int sig_num) {
		QTableWidgetItem *item=new QTableWidgetItem;
        if ((sig_num>=0)&&(sig_num<m_signal_records.count())) {
            item->setText(QString::number(m_signal_records[sig_num]->m_count));
			item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
		}
        ui->signals_table->setItem(sig_num,1,item);



	}
	void QObjectBrowserControl::set_slots() {
        ui->slots_table->clear();
        ui->slots_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->slots_table->setColumnCount(2);
        ui->slots_table->setHorizontalHeaderLabels(QStringList() << "Type" << "Slot");

        if (!m_obj) return;
        const QMetaObject *metaobj=m_obj->metaObject();
		if (!metaobj) return;

		int ct=0;
		int j;
		for (j=0; j<metaobj->methodCount(); j++)
			if (metaobj->method(j).methodType()==QMetaMethod::Slot)
				ct++;
        ui->slots_table->setRowCount(ct);

		ct=0;
		QTableWidgetItem *item;
		for (j=0; j<metaobj->methodCount(); j++) {
			QMetaMethod meth=metaobj->method(j);
			if (meth.methodType()==QMetaMethod::Slot) {
				item=new QTableWidgetItem;

				QString typeName = meth.typeName();
				if( typeName.isEmpty() )
					typeName = "void";

				item->setText(typeName);
				item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->slots_table->setItem(ct,0,item);
				item=new QTableWidgetItem;
				item->setText(meth.signature());
				item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->slots_table->setItem(ct,1,item);

				ct++;
			}
		}
	}
	void QObjectBrowserControl::set_methods() {
        ui->methods_table->clear();
        ui->methods_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
        ui->methods_table->setColumnCount(2);
        ui->methods_table->setHorizontalHeaderLabels(QStringList() << "Type" << "Slot");

        if (!m_obj) return;
        const QMetaObject *metaobj=m_obj->metaObject();
		if (!metaobj) return;

		int ct=0;
		int j;
		for (j=0; j<metaobj->methodCount(); j++)
			if (metaobj->method(j).methodType()==QMetaMethod::Method)
				ct++;
        ui->methods_table->setRowCount(ct);

		ct=0;
		QTableWidgetItem *item;
		for (j=0; j<metaobj->methodCount(); j++) {
			QMetaMethod meth=metaobj->method(j);
			if (meth.methodType()==QMetaMethod::Method) {
				item=new QTableWidgetItem;
				item->setText(meth.typeName());
				item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->methods_table->setItem(ct,0,item);

				item=new QTableWidgetItem;
				item->setText(meth.signature());
				item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                ui->methods_table->setItem(ct,1,item);

				ct++;
			}
		}
	}

	void QObjectBrowserControl::on_signal_triggered(int signal_num) {
        if ((signal_num<0)||(signal_num>=m_signal_records.count()))
			return;
        m_signal_records[signal_num]->m_count++;
		update_signal_value(signal_num);
	}
	void QObjectBrowserControl::on_update_children() {
		set_children();
	}
	void QObjectBrowserControl::on_update_properties() {
		set_properties();
	}
	void QObjectBrowserControl::on_up_to_parent() {
        if ((m_obj)&&(m_obj->parent()))
            set_object(m_obj->parent());
	}

	void QObjectBrowserControl::on_children_table_cell_clicked(int row, int column) {
		Q_UNUSED(column);
        if (!m_obj) return;
        QObjectList objlist=m_obj->children();
		if (row<objlist.count()) {
			set_object(objlist[row]);
		}
	}


	QOB_signal_record::QOB_signal_record() {
        m_sigmapper=0;
        m_count=0;
	}
	QOB_signal_record::~QOB_signal_record() {
        if (m_sigmapper) delete m_sigmapper;
        m_sigmapper=0;
	}

    QObjectBrowser::QObjectBrowser(QWidget* parent) : QWidget(parent),
    m_control (new QObjectBrowserControl),
    m_tree (new QObjectTree) {
        m_last_focus_window=0;
        setObjectName("QObjectBrowser");
        setWindowTitle(tr("QObject Browser"));
//		setWindowFlags(windowFlags()|Qt::WindowStaysOnTopHint);
//		setWindowFlags(windowFlags()|Qt::WindowStaysOnTopHint|Qt::X11BypassWindowManagerHint);

        m_tree->setModel(&m_model);
        QVBoxLayout *layout = new QVBoxLayout(this);
        setLayout(layout);
        QToolBar *update_toolbar=new QToolBar(tr("Update"));
        layout->addWidget(update_toolbar);

		QSplitter *splitter=new QSplitter(Qt::Horizontal,this);
        layout->addWidget(splitter);
        splitter->addWidget(m_tree.data());
        splitter->addWidget(m_control.data());
		splitter->setStretchFactor(0,1);
		splitter->setStretchFactor(1,0);

        m_tree->update();

		QPushButton *update_button=new QPushButton(QString("Update"),this);
		update_toolbar->addWidget(update_button);
		connect(update_button, SIGNAL(clicked()), this, SLOT(on_update()));

        QPushButton *dump_button = new QPushButton(QString("DumpObject"), this);
        update_toolbar->addWidget(dump_button);
        connect(dump_button, SIGNAL(clicked()), this, SLOT(dumpObject()));

		QPushButton *focus_button=new QPushButton(QString("Browse Focus Widget"),this);
		update_toolbar->addWidget(focus_button);
		connect(focus_button, SIGNAL(clicked()), this, SLOT(on_browse_focus()));


        connect(m_tree.data(),SIGNAL(show_widget()),this,SLOT(on_show_widget()));
        connect(m_tree.data(),SIGNAL(hide_widget()),this,SLOT(on_hide_widget()));
        connect(m_tree.data(),SIGNAL(focus_widget()),this,SLOT(on_focus_widget()));
        connect(m_tree.data(),SIGNAL(current_item_changed()),this,SLOT(on_current_item_changed()));
        connect(m_control.data(),SIGNAL(object_changed(QObject *)),this,SLOT(on_object_changed(QObject *)));
		connect(qApp,SIGNAL(focusChanged ( QWidget *, QWidget *)),this,SLOT(on_focus_changed( QWidget *, QWidget *)));

		QTimer *timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(on_update()));
		//connect(timer, SIGNAL(timeout()), this, SLOT(on_current_item_changed()));
		timer->start(3000);
        restoreSettings();
	}

    void QObjectBrowser::closeEvent(QCloseEvent * e) {
        saveSettings();
        emit hidden();
        QWidget::closeEvent(e);
    }

    void QObjectBrowser::saveSettings() {
        QSettings s;
        s.setValue("obrowser/geometry", geometry());
    }

    void QObjectBrowser::restoreSettings() {
        QSettings s;
        QRect geom = s.value("obrowser/geometry", geometry()).toRect();
        setGeometry(geom);
    }

	void QObjectBrowser::set_object(QObject *obj) {
        if (!m_model.find_item(m_model.rootItem,obj))  //object is not valid
            m_control->set_object(0);
		else
            m_control->set_object(obj);
	}

	void QObjectBrowser::on_current_item_changed() {
        QModelIndex index=m_tree->currentIndex();
		if (!index.isValid()) return;
		QObjectTreeItem *item = static_cast<QObjectTreeItem*>(index.internalPointer());
		if (!item) return;
        set_object(item->m_obj);
	}
	void QObjectBrowser::on_object_changed(QObject *obj) {
        QModelIndex index=m_model.getindex(obj);
        m_tree->setCurrentIndex(index);
        m_tree->scrollTo(index);
	}
	void QObjectBrowser::on_update() {
        m_model.refresh();


	}
	void QObjectBrowser::on_focus_changed( QWidget *old, QWidget *now) {
		Q_UNUSED(old);
		if (!now) return;
		QWidget *ptr=now;
		while (ptr) {
			if (ptr==this) return;
			ptr=ptr->parentWidget();
		}
        m_last_focus_window=now;
	}
	void QObjectBrowser::on_browse_focus() {
        if (m_last_focus_window)
            set_object(m_last_focus_window);
		else
			set_object(qApp->focusWidget());
	}

	QObject *QObjectBrowser::get_current_object() {
        QModelIndex index=m_tree->currentIndex();
		if (!index.isValid()) return 0;
		QObjectTreeItem *item = static_cast<QObjectTreeItem*>(index.internalPointer());
		if (!item) return 0;
        return item->m_obj;
	}
	
	void QObjectBrowser::on_show_widget() {
		QObject *obj=get_current_object();
		if (!obj) return;
		if (!obj->isWidgetType()) return;
		QWidget *W=(QWidget *)obj;
		W->show();
	}
	
	void QObjectBrowser::on_hide_widget() {
		QObject *obj=get_current_object();
		if (!obj) return;
		if (!obj->isWidgetType()) return;
		QWidget *W=(QWidget *)obj;
		W->hide();
        emit hidden();
	}
	void QObjectBrowser::on_focus_widget() {
		QObject *obj=get_current_object();
		if (!obj) return;
		if (!obj->isWidgetType()) return;
		QWidget *W=(QWidget *)obj;
		W->activateWindow();
		W->setFocus(Qt::ActiveWindowFocusReason);
	}
    void QObjectBrowser::dumpObject() {
	    QObject *obj = get_current_object();
        obj->dumpObjectInfo();
    }
