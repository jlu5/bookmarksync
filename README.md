# BookmarkSync


BookmarkSync is a simple program that manages GTK+ and KDE file manager bookmarks.

![Demo screenshot](bookmarksync.png "BookmarkSync main window")

## What problem does this project solve

In linux world there are several toolkits available for applications, such as GTK+ and KDE. Most users need to use applications from both toolkits. However, there is inconvenience at file picking moments. GTK+ file dialog lacks functionality such as file preview, and most importantly, it has its own bookmarks and recent locations list.

Modern linux systems solve this problem with XDG Desktop Portal technolody. It allows applications to invoke file dialog native for desktop environment, despite the toolkit used for application. This requires implementation from the developers of the application. There are still a lot of applications that do not support xdg desktop portal.

If you have to use such applications, you are frustrated every time because of outsynced bookmarks in file dialogs. This application allows you to automatically/manually make a synchronisation. At the end, you get more enjoyable desktop experience.

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

GTK+ stores bookmarks in `~/.config/gtk-3.0/bookmarks`, and KDE in `~/.local/share/user-places.xbel`. BookmarkSync manipulates the former as plaintext (as it's a fairly simple format), and the latter using the [KFilePlacesModel](https://api.kde.org/frameworks/kio/html/classKFilePlacesModel.html) API from KIO.
