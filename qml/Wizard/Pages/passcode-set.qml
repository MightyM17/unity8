/*
 * Copyright (C) 2014-2016 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.4
import Lomiri.Components 1.3
import Ubuntu.SystemSettings.SecurityPrivacy 1.0
import ".." as LocalComponents
import "../../Components"

/**
 * See the main passwd-type page for an explanation of why we don't actually
 * directly set the password here.
 */

LocalComponents.Page {
    id: passcodeSetPage
    objectName: "passcodeSetPage"
    customTitle: true
    backButtonText: i18n.tr("Cancel")

    // If we are entering this page, clear any saved password and get focus
    onEnabledChanged: if (enabled) lockscreen.clear(false)

    function confirm() {
        root.password = lockscreen.passphrase;
        confirmTimer.start()
    }

    Timer {
        id: confirmTimer
        interval: LomiriAnimation.SnapDuration
        onTriggered: pageStack.load(Qt.resolvedUrl("passcode-confirm.qml"));
    }

    Lockscreen {
        id: lockscreen
        anchors {
            fill: content
        }

        infoText: i18n.tr("Choose passcode")
        foregroundColor: textColor

        // Note that the number four comes from PAM settings,
        // which we don't have a good way to interrogate.  We
        // only do this matching instead of PAM because we want
        // to set the password via PAM in a different place
        // than this page.  See comments at top of passwd-type file.
        errorText: i18n.tr("Passcode must be 4 characters long")

        showEmergencyCallButton: false
        showCancelButton: false
        alphaNumeric: false
        minPinLength: 4
        maxPinLength: 4

        onEntered: {
            if (passphrase.length >= 4) {
                passcodeSetPage.confirm();
            } else {
                lockscreen.clear(true);
            }
        }
    }
}
