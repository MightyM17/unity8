/*
 * Copyright 2013-2016 Canonical Ltd.
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
 */

#pragma once

#include <memory>
#include <lomiri/shell/launcher/LauncherModelInterface.h>
#include <lomiri/shell/application/ApplicationManagerInterface.h>

#include <QAbstractListModel>

class LauncherItem;
class GSettings;
class DBusInterface;
class ASAdapter;

using namespace lomiri::shell::launcher;
using namespace lomiri::shell::application;

class LauncherModel: public LauncherModelInterface
{
   Q_OBJECT

public:
    LauncherModel(QObject *parent = nullptr);
    ~LauncherModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    Q_INVOKABLE lomiri::shell::launcher::LauncherItemInterface* get(int index) const override;
    Q_INVOKABLE void move(int oldIndex, int newIndex) override;
    Q_INVOKABLE void pin(const QString &appId, int index = -1) override;
    Q_INVOKABLE void quickListActionInvoked(const QString &appId, int actionIndex) override;
    Q_INVOKABLE void setUser(const QString &username) override;
    Q_INVOKABLE QString getUrlForAppId(const QString &appId) const;

    lomiri::shell::application::ApplicationManagerInterface* applicationManager() const override;
    void setApplicationManager(lomiri::shell::application::ApplicationManagerInterface *appManager) override;

    bool onlyPinned() const override;
    void setOnlyPinned(bool onlyPinned) override;

    int findApplication(const QString &appId);

public Q_SLOTS:
    void requestRemove(const QString &appId) override;
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void alert(const QString &appId);

private:
    void storeAppList();

    void unpin(const QString &appId);

    int findHiddenApplication(const QString &appId);

private Q_SLOTS:
    void countChanged(const QString &appId, int count);
    void countVisibleChanged(const QString &appId, bool count);
    void progressChanged(const QString &appId, int progress);

    void applicationAdded(const QModelIndex &parent, int row);
    void applicationRemoved(const QModelIndex &parent, int row);
    void focusedAppIdChanged();
    void updateSurfaceList();
    void updateSurfaceListForApp(ApplicationInfoInterface *app);
    void updateSurfaceListForSurface();

    void onVisibleChanged(bool visible);

private:
    QList<LauncherItem*> m_list;
    QList<LauncherItem*> m_hiddenList;

    GSettings *m_settings;
    DBusInterface *m_dbusIface;
    ASAdapter *m_asAdapter;

    ApplicationManagerInterface *m_appManager;

    friend class LauncherModelTest;
};
