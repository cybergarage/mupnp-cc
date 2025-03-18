/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_RANDOM_H_
#define _UHTTP_UTIL_RANDOM_H_

namespace uHTTP {
class Random {
  public:
  Random();
  Random(unsigned int min, unsigned int max);
  ~Random();

  unsigned int rand();

  private:
  int minRange;
  int maxRange;
};

}

#endif
