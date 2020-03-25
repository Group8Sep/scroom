/*
 * Scroom - Generic viewer for 2D data
 * Copyright (C) 2009-2020 Kees-Jan Dijkzeul
 *
 * SPDX-License-Identifier: LGPL-2.1
 */

#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <scroom/global.hh>
#include <scroom/memoryblobs.hh>

class Tile
{
public:
  typedef boost::shared_ptr<Tile> Ptr;
  typedef boost::weak_ptr<Tile> WeakPtr;

  int width;
  int height;
  int bpp;
  Scroom::MemoryBlobs::RawPageData::Ptr data;

public:
  Tile(int width, int height, int bpp, Scroom::MemoryBlobs::RawPageData::Ptr data)
    : width(width), height(height), bpp(bpp), data(data)
  {}

  static Tile::Ptr create(int width, int height, int bpp, Scroom::MemoryBlobs::RawPageData::Ptr data)
  { return Ptr(new Tile(width, height, bpp, data)); }
};

class ConstTile
{
public:
  typedef boost::shared_ptr<ConstTile> Ptr;
  typedef boost::weak_ptr<ConstTile> WeakPtr;

  int width;
  int height;
  int bpp;
  Scroom::MemoryBlobs::RawPageData::ConstPtr data;

public:
  ConstTile(int width, int height, int bpp, Scroom::MemoryBlobs::RawPageData::ConstPtr data)
    : width(width), height(height), bpp(bpp), data(data)
  {}

  static ConstTile::Ptr create(int width, int height, int bpp, Scroom::MemoryBlobs::RawPageData::ConstPtr data)
  { return Ptr(new ConstTile(width, height, bpp, data)); }
};

