/*
 * Copyright 2013 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Michael Zanetti <michael.zanetti@canonical.com>
 */

// Qt
#include <QtQml/qqml.h>

// self
#include "plugin.h"

// local
#include "launchermodel.h"
#include "launcheritem.h"
#include "appdrawermodel.h"

using namespace lomiri::shell::launcher;

static QObject* modelProvider(QQmlEngine* /* engine */, QJSEngine* /* scriptEngine */)
{
    return new LauncherModel();
}

void UnityLauncherPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("Unity.Launcher"));

    qmlRegisterUncreatableType<LauncherModelInterface>(uri, 0, 1, "LauncherModelInterface", QStringLiteral("Abstract Interface. Cannot be instantiated."));
    qmlRegisterUncreatableType<LauncherItemInterface>(uri, 0, 1, "LauncherItemInterface", QStringLiteral("Abstract Interface. Cannot be instantiated."));
    qmlRegisterUncreatableType<QuickListModelInterface>(uri, 0, 1, "QuickListInterface", QStringLiteral("Abstract Interface. Cannot be instantiated."));

    qmlRegisterSingletonType<LauncherModel>(uri, 0, 1, "LauncherModel", modelProvider);
    qmlRegisterUncreatableType<LauncherItem>(uri, 0, 1, "LauncherItem", QStringLiteral("Can't create new Launcher Items in QML. Get them from the LauncherModel."));
    qmlRegisterUncreatableType<QuickListModel>(uri, 0, 1, "QuickListModel", QStringLiteral("Can't create a QuickListModel in QML. Get them from the LauncherItems."));
    qmlRegisterType<AppDrawerModel>(uri, 0, 1, "AppDrawerModel");
}
