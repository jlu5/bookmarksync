# bookmarksync

BookmarkSync is a simple program that manages GTK+ and KDE bookmarks.

![Demo screenshot](bookmarksync.png "BookmarkSync main window")

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

GTK+ stores bookmarks in `~/.config/gtk-3.0/bookmarks`, and KDE in `~/.local/share/user-places.xbel`. BookmarkSync manipulates the former as plaintext (as it's a fairly simple format), and the latter using the [KFilePlacesModel](https://api.kde.org/frameworks/kio/html/classKFilePlacesModel.html) API from KIO.
