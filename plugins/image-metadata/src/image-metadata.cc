#include "image-metadata.hh"

#include <cmath>

#include <gdk/gdk.h>

#include <scroom/unused.hh>

////////////////////////////////////////////////////////////////////////
// Metadata viewer
////////////////////////////////////////////////////////////////////////

ImageMetadata::Ptr ImageMetadata::create() { return Ptr(new ImageMetadata()); }

std::string ImageMetadata::getPluginName() { return "ImageMetadata"; }

std::string ImageMetadata::getPluginVersion() { return "0.0"; }


//Register to observer
void ImageMetadata::registerCapabilities(ScroomPluginInterface::Ptr host)
{
  host->registerViewObserver("ImageMetadata", shared_from_this<ImageMetadata>());
}

// adds metadata to view
Scroom::Bookkeeping::Token ImageMetadata::viewAdded(ViewInterface::Ptr view)
{
  //ImageMetadataHandler::Ptr handler = ImageMetadataHandler::create();
  //view->registerSelectionListener(handler);
  //view->registerPostRenderer(handler);

  // to implement addToToolbar function
  //view->addToToolbar()


  return Scroom::Bookkeeping::Token();
}

/////////////////////////////////
//   Metadata handler
/////////////////////////////

// MetadataHandler::Ptr MetadataHandler::create() { return Ptr(new MetadataHandler()); }


////////////////////////////////////////////////////////////////////////
/// // PostRenderer
////////////////////////////////////////////////////////////////////////

// void MetadataHandler::render(){}

