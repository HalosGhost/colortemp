# Maintainer: Sam Stuewe <halosghost at archlinux dot info>

pkgname=colortemp-git
pkgver=0.r1.4d692cd
pkgrel=1

pkgdesc="A small tool to set a screen's color temperature"
url='https://github.com/HalosGhost/colortemp'
arch=('i686' 'x86_64')
license=('GPL3')

depends=('xorg-server' 'libxrandr')
makedepends=('git' 'tup' 'clang')

source=('git+https://github.com/HalosGhost/colortemp.git')
sha256sums=('SKIP')

pkgver () {
    cd colortemp
    printf '0.r%s.%s' "$(git rev-list --count HEAD)" "$(git log -1 --pretty=format:%h)"
}

build () {
    cd colortemp
    tup upd
}

package () {
    cd colortemp
    make DESTDIR="$pkgdir" PREFIX="/bin" install
}
