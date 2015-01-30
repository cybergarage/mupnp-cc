/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_PLATFORM_H_
#define _MUPMPCC_PLATFORM_H_

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#if !defined(mupnp_shared_ptr)

#if (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201103L)) || defined(__APPLE__)
#define HAVE_STD_SHRAEDPTR 1
#define mupnp_shared_ptr std::shared_ptr
#define mupnp_weak_ptr std::weak_ptr
#endif

#if !defined(HAVE_STD_SHRAEDPTR)
#include <boost/shared_ptr.hpp>
#define mupnp_shared_ptr boost::shared_ptr
#define mupnp_weark_ptr boost::weak_ptr
#endif

#endif

#endif
