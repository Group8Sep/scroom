/*
 * Scroom - Generic viewer for 2D data
 * Copyright (C) 2009-2018 Kees-Jan Dijkzeul
 *
 * SPDX-License-Identifier: LGPL-2.1
 */

#ifndef _WORKINTERFACE_H
#define _WORKINTERFACE_H

class WorkInterface
{
public:
  
  virtual ~WorkInterface()
  {
  }

  virtual bool doWork()=0;
};


#endif
