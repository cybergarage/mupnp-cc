# mUPnP for C++

![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/cybergarage/mupnp-cc)
[![build](https://github.com/cybergarage/mupnp-cc/actions/workflows/make.yml/badge.svg)](https://github.com/cybergarage/mupnp-cc/actions/workflows/make.yml)

## Overview

mUPnP for C++ is a development package for UPnP™ developers. mUPnP
controls these protocols automatically, and supports to create your
devices and control points quickly.

UPnP™ \* architecture is an open network to enable discovery and control
of networked devices and services, such as media servers and players at
home.

UPnP™ \* protocols are based on many standard, such as GENA, SSDP, SOAP,
HTTPU and HTTP. Therefore you have to understand and implement these
protocols to create your devices of UPnP™.

![UPnP Applications](doc/img/upnpapp.png)

\* UPnP ™ is a certification mark of the UPnP™ Implementers Corporation.

## Building and Installation

µHTTP for C++ for C depend on [µHTTP for C++](https://github.com/cybergarage/uhttp-cc), ando so you need to install [µHTTP for C++](https://github.com/cybergarage/uhttp-cc) first.
Next, µHTTP for C++ for C is distributed as an Automake project, and so you can install the library from the source codes with the following commands:

```
./boostrap
./configure
make install
```

### macOS

For macOS platforms, you can easily install using Homebrew without [µHTTP for C++](https://github.com/cybergarage/uhttp-cc) setup with the following `brew` commands:

```
brew tap cybergarage/homebrew
brew install mupnp++
```

## References

- [Programming Guide](doc/mupnpcxxproguide.pdf)
- [Doxygen](http://cybergarage.github.io/mupnp-cc/)

## Examples

- UPnP control point examples
  - UPnP controller for UPnP devices
    - [UPnP multicast dump utility](examples/upnpdump)
  - UPnP controller for UPnP stardard devices
    - [UPnP/AV media server utility ](examples/media/serverdump)
 
- UPnP device examples
  - UPnP stardard devices
    - [UPnP/AV media sever](examples/media/server)
  - UPnP non-standard devices
    - [UPnP clock device](examples/clock)
    - [UPnP television device](examples/tv)
