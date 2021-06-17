//
// Created by andy on 13-06-21.
//

#include "metadata.hh"

#include <gdk/gdk.h>

#include "../../gui/src/callbacks.hh"

////////////////////////////////////////////////////////////////////////
// Metadata
////////////////////////////////////////////////////////////////////////

/**
 * Creates a pointer to a metadata object
 *
 * @return Pointer to metadata object
 */
Metadata::Ptr Metadata::create() { return Ptr(new Metadata()); }

////////////////////////////////////////////////////////////////////////
// PluginInformationInterface
////////////////////////////////////////////////////////////////////////

/**
 * Gets the name of metadata plugin
 *
 * @return std::string "Metadata"
 */
std::string Metadata::getPluginName() { return "Metadata"; }

/**
 * Gets the version number of metadata plugin
 *
 * @return std::string "0.0"
 */
std::string Metadata::getPluginVersion() { return "0.0"; }

/**
 * Register plugin to observers
 *
 * @param host Pointer to scroom plugin interface
 * @return std::string "0.0"
 */
void Metadata::registerCapabilities(ScroomPluginInterface::Ptr host)
{
  host->registerViewObserver("Metadata", shared_from_this<Metadata>());
}

////////////////////////////////////////////////////////////////////////
// ViewObserver
////////////////////////////////////////////////////////////////////////

/**
 * Shows an image metadata button in the view that can be activated by clicking.
 *
 * @param view Screen or view that is displayed
 * @post Metadata button is shown in toolbar
 * @return Scroom::Bookkeeping::Token token for bookkeeping of scroom
 */
Scroom::Bookkeeping::Token Metadata::viewAdded(ViewInterface::Ptr view)
{
  GtkToolItem* button         = gtk_tool_item_new();
  GtkWidget*   buttonMetadata = gtk_button_new_with_label("Metadata");
  gtk_widget_set_visible(buttonMetadata, true);
  gpointer presentation = view.get();
  gtk_container_add(GTK_CONTAINER(button), buttonMetadata);
  // connect signal to the button for when it is being pressed
  g_signal_connect(static_cast<gpointer>(buttonMetadata), "pressed", G_CALLBACK(on_image_properties_activate), presentation);

  gdk_threads_enter();
  view->addToToolbar(button); // adds metadata button next to other tools in toolbar
  gdk_threads_leave();

  return Scroom::Bookkeeping::Token();
}
