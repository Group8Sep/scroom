/*
 * Scroom - Generic viewer for 2D data
 * Copyright (C) 2009-2014 Kees-Jan Dijkzeul
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License, version 2, as published by the Free Software Foundation.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _SCROOMINTERFACE_HH
#define _SCROOMINTERFACE_HH

#include <gtk/gtk.h>

#include <string>
#include <list>

#include <boost/shared_ptr.hpp>

#include <scroom/presentationinterface.hh>
#include <scroom/viewinterface.hh>
#include <scroom/bookkeeping.hh>


class NewPresentationInterface
{
public:
  typedef boost::shared_ptr<NewPresentationInterface> Ptr;

public:
  virtual ~NewPresentationInterface() {}
  
  virtual PresentationInterface::Ptr createNew()=0;
};

class NewAggregateInterface
{
public:
  typedef boost::shared_ptr<NewAggregateInterface> Ptr;

public:
  virtual ~NewAggregateInterface() {}

  virtual Aggregate::Ptr createNew()=0;
};

class OpenPresentationInterface
{
public:
  typedef boost::shared_ptr<OpenPresentationInterface> Ptr;

public:
  virtual ~OpenPresentationInterface() {}

  virtual std::list<GtkFileFilter*> getFilters()=0;
  
  virtual PresentationInterface::Ptr open(const std::string& fileName)=0;
};

class PresentationObserver
{
public:
  typedef boost::shared_ptr<PresentationObserver> Ptr;

public:
  virtual ~PresentationObserver() {}

  virtual void presentationAdded(PresentationInterface::Ptr p)=0;
  virtual void presentationDeleted()=0;
};

class ViewObserver
{
public:
  typedef boost::shared_ptr<ViewObserver> Ptr;

public:
  virtual ~ViewObserver() {}

  virtual Scroom::Bookkeeping::Token viewAdded(ViewInterface::Ptr v)=0;
};

class ScroomPluginInterface
{
public:
  typedef boost::shared_ptr<ScroomPluginInterface> Ptr;

public:
  virtual ~ScroomPluginInterface() {}

  virtual void registerNewPresentationInterface(const std::string& identifier, NewPresentationInterface::Ptr newPresentationInterface)=0;
  virtual void registerNewAggregateInterface(const std::string& identifier, NewAggregateInterface::Ptr newAggregateInterface)=0;
  virtual void registerOpenPresentationInterface(const std::string& identifier, OpenPresentationInterface::Ptr openPresentationInterface)=0;
  virtual void registerViewObserver(const std::string& identifier, ViewObserver::Ptr observer)=0;
  virtual void registerPresentationObserver(const std::string& identifier, PresentationObserver::Ptr observer)=0;
};


#endif
