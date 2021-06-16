/*
 * Scroom - Generic viewer for 2D data
 * Copyright (C) 2009-2021 Kees-Jan Dijkzeul
 *
 * SPDX-License-Identifier: LGPL-2.1
 */

#include <scroom/presentationinterface.hh>
#include <scroom/viewinterface.hh>

void PresentationBase::open(ViewInterface::WeakPtr vi)
{
  viewAdded(vi);

  std::list<Viewable::Ptr> const observers = getObservers();

  for(Viewable::Ptr const& observer: observers)
  {
    observer->open(vi);
  }
}

void PresentationBase::close(ViewInterface::WeakPtr vi)
{
  std::list<Viewable::Ptr> const observers = getObservers();

  for(Viewable::Ptr const& observer: observers)
  {
    observer->close(vi);
  }

  viewRemoved(vi);
}

void PresentationBase::observerAdded(Viewable::Ptr const& viewable, Scroom::Bookkeeping::Token const&)
{
  std::set<ViewInterface::WeakPtr> views = getViews();

  for(ViewInterface::WeakPtr const& view: views)
  {
    viewable->open(view);
  }
}
void PresentationBase::showMetadata() {
  printf("test meta data");
  GtkWidget*  dialog;
  GtkWidget*  label;
  GtkBuilder* builder;
  GtkWidget*  box;

  builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "popup.builder", NULL);
  printf("Creating the properties window.\n");
  dialog = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(dialog), "Properties");
  gtk_window_set_decorated(GTK_WINDOW(dialog), TRUE);
  gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);
  gtk_builder_connect_signals(builder, dialog);
  g_object_unref(G_OBJECT(builder));
  label = gtk_label_new("NOT IMPLEMENTED");
  box   = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(box), label, false, false, 0);
  gtk_box_pack_start(GTK_BOX(box), gtk_label_new("vanuit presentationinterface!"), false, false, 0);
  gtk_container_add(GTK_CONTAINER(dialog), box);
  gtk_widget_show_all(dialog);
  gtk_widget_grab_focus(dialog);
}
