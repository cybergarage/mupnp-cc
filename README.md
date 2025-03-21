# mUPnP for C++

![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/cybergarage/mupnp-cc)
[![build](https://github.com/cybergarage/mupnp-cc/actions/workflows/make.yml/badge.svg)](https://github.com/cybergarage/mupnp-cc/actions/workflows/make.yml)
[![doxygen](https://github.com/cybergarage/mupnp-cc/actions/workflows/doxygen.yml/badge.svg)](http://cybergarage.github.io/mupnp-cc/)

mUPnP for C++ is a development package for UPnP™ [^1] (Universal Plug and Play) developers. It provides a set of APIs to create UPnP™ devices and control points quickly and easily. This README file provides an overview of the package, its contents, and instructions on how to set up and use it.

The UPnP™ architecture is designed to enable the discovery and control of networked devices and services, such as media servers and players, within a home network. UPnP™ is based on several standard protocols, including GENA, SSDP, SOAP, HTTPU, and HTTP. To create UPnP™ devices, you need to understand and implement these protocols.

![UPnP applications](doc/img/upnpapp.png)

mUPnP for C++ simplifies this process by handling these protocols automatically. It allows developers to focus on creating their devices and control points without worrying about the underlying protocol details.

## Building and Installation

mUPnP for C++ is distributed as an Automake project, and so you can install the libary from the source codes with the following commands:

```
cd mupnp-cc
./configure
make install
```

### macOS

For macOS platforms, you can easily install using Homebrew with the following `brew` commands:

```
brew tap cybergarage/homebrew
brew install mupnp++
```

## References

- [Programming Guide (Doxygen)](http://cybergarage.github.io/mupnp-cc/)

## Examples

- UPnP control point examples
  - UPnP controller for UPnP devices
    - [UPnP multicast dump utility](https://github.com/cybergarage/mupnp-cc/tree/master/examples/upnpdump)
  - UPnP controller for UPnP stardard devices
    - [UPnP/AV media server utility ](https://github.com/cybergarage/mupnp-cc/tree/master/examples/media/serverdump)
 
- UPnP device examples
  - UPnP stardard devices
    - [UPnP/AV media sever](https://github.com/cybergarage/mupnp-cc/tree/master/examples/media/server)
  - UPnP non-standard devices
    - [UPnP clock device](https://github.com/cybergarage/mupnp-cc/tree/master/examples/clock)
    - [UPnP television device](https://github.com/cybergarage/mupnp-cc/tree/master/examples/tv)
