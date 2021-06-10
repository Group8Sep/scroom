#include <stdio.h>

#include <scroom/scroomplugin.hh>
#include <scroom/unused.hh>

#include "image-metadata.hh"

PluginInformationInterface::Ptr getPluginInformation() { return ImageMetadata::create(); }
