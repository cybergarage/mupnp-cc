class Mupnpxx < Formula
  homepage "http://www.cybergarage.org/do/view/Main/CyberLinkForCC"
  url "https://github.com/cybergarage/mUPnPCC/archive/3.0.0.tar.gz"
  sha1 "53c393abeecb5c449805f84c9a7b486a6fad8fee"

  depends_on "readline"
  depends_on "uhttp++"

  def install
    system "./configure", "--disable-debug",
                          "--disable-dependency-tracking",
                          "--disable-silent-rules",
                          "--prefix=#{prefix}"
    system "make", "install"
  end
end
