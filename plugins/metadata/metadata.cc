//
// Created by andy on 13-06-21.
//

#include "metadata.hh"

#include <gdk/gdk.h>

#include <scroom/unused.hh>

#include "../../gui/src/callbacks.hh"
#include "../../inc/scroom/imagemdinterface.hh"

////////////////////////////////////////////////////////////////////////
// Metadata
////////////////////////////////////////////////////////////////////////

Metadata::Ptr Metadata::create() { return Ptr(new Metadata()); }

////////////////////////////////////////////////////////////////////////
// PluginInformationInterface
////////////////////////////////////////////////////////////////////////

std::string Metadata::getPluginName() { return "Metadata"; }

std::string Metadata::getPluginVersion() { return "0.0"; }

void Metadata::registerCapabilities(ScroomPluginInterface::Ptr host)
{
  host->registerViewObserver("Metadata", shared_from_this<Metadata>());
}

////////////////////////////////////////////////////////////////////////
// ViewObserver
////////////////////////////////////////////////////////////////////////

Scroom::Bookkeeping::Token Metadata::viewAdded(ViewInterface::Ptr view)
{

  GtkToolItem* button         = gtk_tool_item_new();
  GtkWidget*   buttonMetadata = gtk_button_new_with_label("Metadata");
  gtk_widget_set_visible(buttonMetadata, true);
  gpointer presentation = view.get();
  gtk_container_add(GTK_CONTAINER(button), buttonMetadata);
  if(view->getCurrentPresentation().get() == nullptr){
    gtk_widget_set_sensitive(buttonMetadata, FALSE);
  }else{
    gtk_widget_set_sensitive(buttonMetadata, TRUE);
    g_signal_connect(static_cast<gpointer>(buttonMetadata), "pressed", G_CALLBACK(on_image_properties_activate),
                     presentation);
  }


  gdk_threads_enter();
  view->addToToolbar(button);
  gdk_threads_leave();
}
