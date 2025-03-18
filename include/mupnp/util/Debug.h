/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_DEBUG_H_
#define _UHTTP_UTIL_DEBUG_H_

#include <stdio.h>
#include <string>
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
#include <fstream>
#include <iostream>
#include <sstream>
#endif

#include <mupnp/util/Exception.h>

namespace uHTTP {
class Debug {
  static bool enabled;

  public:
  static void on()
  {
    enabled = true;
  }

  static void off()
  {
    enabled = false;
  }

  static bool isOn()
  {
    return enabled;
  }

  static void message(const std::string& s)
  {
    if (enabled == true)
      printf("uHTTP message : %s\n", s.c_str());
  }

  static void message(std::string& s)
  {
    message(s.c_str());
  }

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  static void message(std::ostringstream& s)
  {
    message(s.str().c_str());
  }
#endif

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  static void message(const std::string& s, const std::string& fname)
  {
    if (enabled == true) {
      std::fstream fout(fname.c_str(), std::ios::out | std::ios::app);
      if (fout.fail())
        return;
      fout << "uHTTP message : " << s << std::endl;
      fout.close();
    }
  }
#endif

  static void warning(const std::string& s)
  {
    printf("uHTTP warning : %s\n", s.c_str());
  }

  static void warning(std::string& s)
  {
    warning(s.c_str());
  }

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  static void warning(std::ostringstream& s)
  {
    warning(s.str().c_str());
  }
#endif

  static void warning(uHTTP::Exception& e)
  {
    warning(e.getMessage());
  }

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  static void warning(const std::string& s, const std::string& fname)
  {
    std::fstream fout(fname.c_str(), std::ios::out | std::ios::app);
    if (fout.fail())
      return;
    fout << "uHTTP warning : " << s << std::endl;
    fout.close();
  }
#endif
};

}

#endif
