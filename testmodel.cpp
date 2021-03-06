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

#include "testmodel.h"

TestModel::TestModel() :
    QAbstractListModel()
{
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 10;
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(index)

    switch (role)
    {
    case Role1:
        return "First role";
        break; // redundant... but looks nicer
    case Role2:
        return "Second role";
        break; // redundant... but looks nicer
    case Role3:
        return "Third role";
        break; // redundant... but looks nicer
    }

    return "Bad role"; // Again redundant... but the compiler doesn't complain this way
}

QHash<int, QByteArray> TestModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Role1] = "role1";
    roles[Role2] = "role2";
    roles[Role3] = "role3";

    return roles;
}
