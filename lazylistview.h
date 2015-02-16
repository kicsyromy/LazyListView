/*
 * LazyListView
 * Copyright (C) 2015 Romeo Calota <kicsyromy@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LAZYLISTVIEW_H
#define LAZYLISTVIEW_H

#include <QQuickItem>
#include <QQmlComponent>
#include <QScopedPointer>
#include <QSharedPointer>

class QQuickFlickable;
class ItemPool;

class LazyListView : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(int orientation READ getOrientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(QQmlComponent * delegate READ getDelegate WRITE setDelegate NOTIFY delegateChanged)
    Q_PROPERTY(QObject * model READ getModel WRITE setModel NOTIFY modelChanged)

public:
    LazyListView();
    ~LazyListView();

public:
    int getOrientation() const;
    void setOrientation(int orientation);

    QQmlComponent * getDelegate() const;
    void setDelegate(QQmlComponent *delegate);

    QObject *getModel() const;
    void setModel(QObject *model);

signals:
    void orientationChanged();
    void delegateChanged();
    void modelChanged();

private:
    void createListItems(QQmlComponent *component);
    void rearangeListItems();

private:
    QScopedPointer<QQuickFlickable> m_flickable;
    int m_cacheSize;
    QScopedPointer<ItemPool> m_itemPool;
    QObject *m_model; // This limits model types... can't be an int for instance
    QList<QQuickItem *> m_visibleItems; // Maybe as a LinkedList this would be more efficient?
    QQmlComponent *m_delegate;
};

#endif // LAZYLISTVIEW_H
