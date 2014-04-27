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

#ifndef _VIEW_HH
#define _VIEW_HH

#include <stdlib.h>

#include <map>
#include <string>
#include <cmath>

#include <glade/glade.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo.h>

#include <scroom/scroominterface.hh>
#include <scroom/viewinterface.hh>
#include <scroom/presentationinterface.hh>
#include <scroom/utilities.hh>

#include "sidebarmanager.hh"
#include "progressbarmanager.hh"

struct Measurement
{
public:
  GdkPoint start;
  GdkPoint end;

public:
  Measurement(int x, int y) { start.x=x; start.y=y; end=start; }
  Measurement(GdkPoint start) : start(start), end(start) {}

  bool endsAt(GdkPoint p) { return end.x==p.x && end.y==p.y; }

  int width() { return abs(end.x-start.x); }
  int height() { return abs(end.y-start.y); }
  double length() { return std::sqrt(std::pow(double(width()),2) + std::pow(double(height()),2)); }
};

class View : public ViewInterface, public Scroom::Utils::Base
{
public:
  typedef boost::shared_ptr<View> Ptr;

private:
  GladeXML* scroomXml;
  PresentationInterface::Ptr presentation;
  SidebarManager sidebarManager;
  GtkWindow* window;
  GtkWidget* menubar;
  GtkWidget* drawingArea;
  int drawingAreaWidth;
  int drawingAreaHeight;
  GdkRectangle presentationRect;
  GtkVScrollbar* vscrollbar;
  GtkHScrollbar* hscrollbar;
  GtkAdjustment* vscrollbaradjustment;
  GtkAdjustment* hscrollbaradjustment;
  GtkRuler* hruler;
  GtkRuler* vruler;
  GtkComboBox* zoomBox;
  GtkListStore* zoomItems;
  GtkProgressBar* progressBar;
  GtkStatusbar* statusBar;
  GtkToolbar* toolBar;
  GtkToolItem* toolBarSeparator;
  GtkEntry* xTextBox;
  GtkEntry* yTextBox;
  GtkWidget* statusArea;
  GtkWidget* toolbarArea;
  unsigned toolBarCount;
  int statusBarContextId;
  int zoom;
  int x;
  int y;
  Measurement* measurement;

  gint modifiermove;
  GdkPoint cachedPoint;

  ProgressBarManager::Ptr progressBarManager;
  
  std::map<PresentationInterface::WeakPtr,GtkWidget*> presentations;

private:
  enum LocationChangeCause
    {
      SCROLLBAR,
      TEXTBOX,
      OTHER
    };
  
private:
  View(GladeXML* scroomXml);

public:
  static Ptr create(GladeXML* scroomXml, PresentationInterface::Ptr presentation);

  virtual ~View();

  void redraw(cairo_t* cr);
  void hide();
  bool hasPresentation();
  void setPresentation(PresentationInterface::Ptr presentation);

  void updateScrollbar(GtkAdjustment* adj, int zoom, int value,
                       int presentationStart, int presentationSize, int windowSize);
  void updateScrollbars();
  void updateZoom();
  void updateRulers();
  void updateTextbox();

  ////////////////////////////////////////////////////////////////////////
  // Scroom events
  
  void on_newInterfaces_update(const std::map<NewInterface::Ptr, std::string>& newInterfaces);
  void on_presentation_created(PresentationInterface::Ptr p);
  void on_presentation_destroyed();
  void on_configure();
  void on_window_size_changed(int newWidth, int newHeight);
  void on_zoombox_changed();
  void on_zoombox_changed(int newZoom, int mousex, int mousey);
  void on_textbox_value_changed(GtkEditable* editable);
  void on_scrollbar_value_changed(GtkAdjustment* adjustment);
  void on_scrollwheel(GdkEventScroll* event);
  void on_buttonPress(GdkEventButton* event);
  void on_buttonRelease(GdkEventButton* event);
  void on_motion_notify(GdkEventMotion* event);
  void setFullScreen();
  void unsetFullScreen();

  ////////////////////////////////////////////////////////////////////////
  // ViewInterface

  virtual void invalidate();
  virtual ProgressStateInterface::Ptr getProgressInterface();
  virtual void addSideWidget(std::string title, GtkWidget* w);
  virtual void removeSideWidget(GtkWidget* w);
  virtual void addToToolbar(GtkToolItem* ti);
  virtual void removeFromToolbar(GtkToolItem* ti);

  ////////////////////////////////////////////////////////////////////////
  // Helpers

private:
  GdkPoint windowPointToPresentationPoint(GdkPoint wp);
  GdkPoint presentationPointToWindowPoint(GdkPoint pp);
  GdkPoint eventToPoint(GdkEventButton* event);
  GdkPoint eventToPoint(GdkEventMotion* event);
  void drawCross(cairo_t* cr, GdkPoint p);
  void setStatusMessage(const std::string& message);
  void displayMeasurement();
  void updateNewWindowMenu();
  void updateXY(int x, int y, LocationChangeCause source);
};

#endif
