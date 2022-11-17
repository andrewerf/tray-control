pkgname=tray-control
pkgver=0.0.0
pkgrel=1
arch=('x86_64')
depends=('systemd'
         'fmt'
         'dbus'
         'sdbus-cpp')
pkgdesc="Simple CLI tool to show items in systray and activate them. Build on top of DBus"
url="https://github.com/andrewerf/tray-control"
source=('git+https://github.com/andrewerf/tray-control.git'
        'git+https://github.com/Neargye/magic_enum.git'
        'git+https://github.com/jarro2783/cxxopts.git')
md5sums=('SKIP'
         'SKIP'
         'SKIP')
license=('GPL3')

prepare(){
    cd $pkgname
    git submodule init
    git config submodule.magic_enum.url 3rdparty/magic_enum
    git config submodule.cxxopts.url 3rdparty/cxxopts
    git submodule update --init
}

build() {
    cd $pkgname
    mkdir -p build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
}

package() {
    cd $pkgname/build
    DESTDIR="$pkgdir/" cmake --install .
}