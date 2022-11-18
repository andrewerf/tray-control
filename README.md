# tray-control

This is a simple CLI tool to show items in system tray and activate them.

## Usage

There are two commands in this package: `tray-show` and `tray-activate`.

```
$ tray-show -h
Show items in the system tray
Usage:
  tray-show [OPTION...]

  -h, --help     Print help and exit
  -v, --verbose  Show full info about each item
```

```
$ tray-activate -h
Activate items from the system tray
Usage:
  tray-activate [OPTION...]

  -h, --help       Print help and exit
  -i, --id arg     Find items by id
  -t, --title arg  Find items by title
  -x arg           X coord (default: 0)
  -y arg           Y coord (default: 0)
```

`tray-show` prints all the items in the system tray. For instance:
```
$ tray-show -v
Category: ApplicationStatus
Title: TelegramDesktop
Id: TelegramDesktop
Status: Active
IconName: 

Category: ApplicationStatus
Title: Fleep
Id: Fleep
Status: Active
IconName: 
```

`tray-activate` activates all the items matching the specified id or title. Please note that either id or title should be specified (but not both).
`-x` and `-y` args are the coordinates passed to activate call.
System tray item should consider them for displaying sub menus or other stuff (but often they are ignored by applications).

For more information about SystemTrayItems please see: [StatusNotifierItem](https://www.freedesktop.org/wiki/Specifications/StatusNotifierItem/StatusNotifierItem/).

## Dependencies
This tool depends on `systemd-libs`, `sdbus-cpp` and `fmt`.
There also submodule dependencies: `cxxopts` and `magic_enum` but you should generally not worry about them since they are included as submodules into this repo.

## Installation
### Archlinux
Check out the repo and use [makepkg](https://wiki.archlinux.org/title/makepkg):
```shell
git checkout https://github.com/andrewerf/tray-control.git
cd tray-control
makepkg -si
```
I hope I'll add this tool to AUR in the near future.

### Other linux
Checkout the repo and build with cmake + make:
```shell
git checkout https://github.com/andrewerf/tray-control.git
cd tray-control
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
cmake --install .
```

This will (by default) install two files: `/usr/local/bin/tray-show` and `/usr/local/bin/tray-activate`.
Use `CMAKE_INSTALL_PREFIX` to change the installation folder.