# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: Your Name <youremail@domain.com>
pkgname=caser-git
pkgver=1.0.1
pkgrel=1
epoch=
pkgdesc="Converts file names to a standard casing scheme."
arch=('x86_64')
url=""
license=('GPL')
groups=()
depends=()
makedepends=()
checkdepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
install=
changelog=
source=("$pkgname-$pkgver.tar.gz::https://github.com/Shadetheartist/caser/releases/download/${pkgver}/caser-${pkgver}.tar.gz")
noextract=()
sha256sums=('SKIP')
validpgpkeys=()

build() {
	cd "caser-$pkgver"
	./configure --prefix=/usr
	make
}

package() {
	cd "caser-$pkgver"
	make DESTDIR="$pkgdir/" install
}
