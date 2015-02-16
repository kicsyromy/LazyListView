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
#include "itempool.h"

#include <QQuickItem>
#include <QQmlComponent>

ItemPool::ItemPool()
{
}

ItemPool::~ItemPool()
{
    clear();
}

void ItemPool::newItem(QQmlComponent *component)
{
    // Get the proper context for the component
    QQmlContext *context = qmlContext(component);
    //Create a new item, add it to the map, and mark it as available
    m_items[qobject_cast<QQuickItem *>(component->create(context))] = AVAILABLE;
}

QQuickItem *ItemPool::getItem()
{
    // Get the first item marked as available
    QQuickItem *item = m_items.key(AVAILABLE);
    // Set it to unavailable
    m_items[item] = UNAVAILABLE;

    return item;
}

void ItemPool::releaseItem(QQuickItem *item)
{
    // Mark the item as available
    // Based on... faith??!?!
    m_items[item] = AVAILABLE;
}

void ItemPool::clear()
{
    for (auto it = m_items.begin(); it != m_items.end(); ++it)
    {
        delete it.key();
    }

    m_items.clear();
}
