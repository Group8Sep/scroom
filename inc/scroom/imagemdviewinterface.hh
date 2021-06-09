/*
 * Scroom - Generic viewer for 2D data
 * Copyright (C) 2009-2021 Kees-Jan Dijkzeul
 *
 * SPDX-License-Identifier: LGPL-2.1
 */

#pragma once

#include <scroom/interface.hh>

const std::string METADATA_PROPERTY_NAME = "ImageMetadata";

class MetadataViewInterface
  : public virtual Scroom::Utils::Base
  , private Interface
{
public:
  using Ptr = boost::shared_ptr<MetadataViewInterface>;

/*public:
  **
   * Returns the average pixel values for each component, contained in the area.
   *
   * @param area selected area to get the pixel values from.
   *
  virtual PipetteLayerOperations::PipetteColor getPixelAverages(Scroom::Utils::Rectangle<int> area) = 0;
};
*/
