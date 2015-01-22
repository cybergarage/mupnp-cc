class Mupnpxx < Formula
  homepage "http://www.cybergarage.org/do/view/Main/CyberLinkForCC"
  url "https://github.com/cybergarage/mUPnPCC/archive/3.0.1.tar.gz"
  sha1 "78c8f6e105106447d456a89691791f15e5f28c93"

  depends_on "autoconf" => :build
  depends_on "automake" => :build
  depends_on "readline"
  depends_on "uhttp++"

  def install
    system "./bootstrap"
    system "./configure_macosx", "--disable-debug",
                                 "--disable-dependency-tracking",
                                 "--disable-silent-rules",
                                 "--prefix=#{prefix}"
    system "make"
    system "make", "install"
  end
end
