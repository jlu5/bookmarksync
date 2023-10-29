# BookmarkSync

[![latest release](https://img.shields.io/github/v/tag/jlu5/bookmarksync?sort=date)](https://github.com/jlu5/bookmarksync/tags)

**BookmarkSync** is a simple program that manages the bookmarks (pinned folders) in GTK+, KDE, and Qt 5's native file pickers. I built this tool because I was using GTK+ apps (GIMP, Audacity, etc.) on KDE and constantly got frustrated by the bookmarks lists not matching up.

![Demo screenshot](bookmarksync.png "BookmarkSync main window")

Note: BookmarkSync is one solution to this problem, though there are other alternatives too that may work depending on the program, such as [xdg-desktop-portal](https://github.com/flatpak/xdg-desktop-portal) or setting `QT_QPA_PLATFORMTHEME=gtk2` on GTK+ based desktop environments.

## CLI mode

As of v0.3.0 there is support for running sync from the command line: `$ bookmarksync --sync-from {gtk,kde,qt}`.

Note that this is not truly headless, as BookmarkSync still expects a display to exist. If your environment doesn't have one available, you can switch to a dummy display with some QT overrides: `$ QT_QPA_PLATFORMTHEME= QT_QPA_PLATFORM=offscreen ./bookmarksync <args>`

## Distribution packages

You can find bookmarksync in:

- Arch Linux AUR: [bookmarksync-git](https://aur.archlinux.org/packages/bookmarksync-git/)
- Debian via [Utopia Repository](https://deb.utopia-repository.org/): bookmarksync

## Build instructions

To compile BookmarkSync you will need qmake and the headers for KIO.

On Debian and derivatives, this is `apt install qtbase5-dev libkf5kio-dev`.

Then,

```shell
git clone https://github.com/jlu5/bookmarksync
cd bookmarksync/src
qmake
make -j$(nproc)
```

The resulting binary will be named `bookmarksync`.


Alternatively, you can build the project (`bookmarksync.pro`) using Qt Creator.


## Under the hood

- **GTK+** stores bookmarks in a simple plain text format at `~/.config/gtk-3.0/bookmarks`, which BookmarkSync manipulates as a plain text file.
- **KDE** stores bookmarks in XML form at `~/.local/share/user-places.xbel`. BookmarkSync uses [KFilePlacesModel](https://api.kde.org/frameworks/kio/html/classKFilePlacesModel.html) from KIO to edit these natively.
- **Qt** stores bookmarks in the Qt config file (INI format) at `~/.config/QtProject.conf`. BookmarkSync uses [QFileDialog](https://doc.qt.io/qt-5/qfiledialog.html#setSidebarUrls) methods (and hidden file dialog instances) to read and write to these.

### Known limitations

- Only KDE supports custom icons for places; syncing from others will erase all custom icons.
- Only GTK+ and KDE support remote locations like `sftp://` or `smb://` in bookmarks: syncing *from* Qt will remove all remote places from the list.
- Editing bookmarks from another program while BookmarkSync is running may cause things to go out of sync. This mainly affects the Qt backend, as the KDE and GTK+ backends tend to sync faster.
