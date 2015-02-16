/*
 * LazyListView
 * Copyright (C) 2015 Romeo Calota <kicsyromy@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "lazylistview.h"

#include <private/qquickflickable_p.h>
#include <private/qquickanchors_p.h>
#include <private/qquickanchors_p_p.h>
#include <QQmlEngine>

#include "itempool.h"

#include <QDebug>

#define CACHE_SIZE      20

inline QQuickFlickable::FlickableDirection convertFromOrientation(Qt::Orientation orientation);
inline Qt::Orientation convertToOrientation(QQuickFlickable::FlickableDirection direction);

LazyListView::LazyListView() :
    m_flickable(new QQuickFlickable(this)),
    m_cacheSize(CACHE_SIZE),
    m_itemPool(new ItemPool())
{
    QQuickAnchors * flickable_anchor = qvariant_cast<QQuickAnchors *>(m_flickable->property("anchors"));
    flickable_anchor->setFill(this);

    m_flickable->setFlickableDirection(QQuickFlickable::VerticalFlick);
}

LazyListView::~LazyListView()
{
}

int LazyListView::getOrientation() const
{
    return convertToOrientation(m_flickable->flickableDirection());
}

void LazyListView::setOrientation(int orientation)
{
    QQuickFlickable::FlickableDirection direction = convertFromOrientation((Qt::Orientation)orientation);

    if (direction != m_flickable->flickableDirection())
    {
        m_flickable->setFlickableDirection(direction);

        rearangeListItems();

        emit orientationChanged();
    }
}

QQmlComponent *LazyListView::getDelegate() const
{
    return m_delegate;
}

void LazyListView::setDelegate(QQmlComponent *delegate)
{
    createListItems(delegate);
    rearangeListItems();
}

void LazyListView::createListItems(QQmlComponent *component)
{
    // Clear previously cached items
    m_itemPool->clear();
    m_visibleItems.clear();

    // Create m_cacheSize number of items from the delegate
    // TODO: figure out how to use roleNames() ??
    for (int i = 0; i < m_cacheSize; ++i)
    {
        // Create a new item within the item pool
        // This might be exposing a bit too much info
        // of something that is supposed to be internal info...
        // you can do better then this...
        m_itemPool->newItem(component);

        QQuickItem *item = m_itemPool->getItem();
        qDebug() << "Item at" << i << "is" << item;

        item->setParent(m_flickable->contentItem());
        item->setParentItem(m_flickable->contentItem());

        m_visibleItems.append(item);
    }
}

void LazyListView::rearangeListItems()
{
    // Reset flickable to default values
    m_flickable->setContentHeight(0);
    m_flickable->setContentWidth(0);

    int bufferSize = m_visibleItems.size();

    for (int i = 0; i < bufferSize; ++i)
    {
        QQuickItem *item = m_visibleItems.at(i);

        // Reset item position
        item->setX(0);
        item->setY(0);

        // Based on orientation set the correct position for each item
        if (m_flickable->flickableDirection() == QQuickFlickable::VerticalFlick)
        {
            // Stack them under each other
            item->setY(i * item->height());
        }
        else
        {
            // Place them next to each other
            item->setX(i * item->width());
        }
    }

    // Set the proper content size based on orientation
    if (m_flickable->flickableDirection() == QQuickFlickable::VerticalFlick)
    {
        m_flickable->setContentHeight(bufferSize * m_visibleItems.at(0)->height());
    }
    else
    {
        m_flickable->setContentWidth(bufferSize * m_visibleItems.at(0)->width());
    }
}

/*
 * Helper functions
 */

inline QQuickFlickable::FlickableDirection convertFromOrientation(Qt::Orientation orientation)
{
    switch (orientation)
    {
        case Qt::Vertical:
            return QQuickFlickable::VerticalFlick;
        case Qt::Horizontal:
            return QQuickFlickable::HorizontalFlick;
    }

    return QQuickFlickable::VerticalFlick;
}

inline Qt::Orientation convertToOrientation(QQuickFlickable::FlickableDirection direction)
{
    switch (direction)
    {
        default:
            return Qt::Vertical;
        case QQuickFlickable::AutoFlickDirection:
        case QQuickFlickable::HorizontalAndVerticalFlick:
            return Qt::Vertical;
        case QQuickFlickable::VerticalFlick:
            return Qt::Vertical;
        case QQuickFlickable::HorizontalFlick:
            return Qt::Horizontal;
    }

    return Qt::Vertical;
}
