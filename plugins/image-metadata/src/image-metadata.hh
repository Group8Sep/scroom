/*
 * Scroom - Generic viewer for 2D data
 * Copyright (C) 2009-2021 Kees-Jan Dijkzeul
 *
 * SPDX-License-Identifier: LGPL-2.1
 */

#pragma once

#include <atomic>
#include <mutex>

#include <scroom/imagemdviewinterface.hh>
#include <scroom/plugininformationinterface.hh>
#include <scroom/threadpool.hh>
#include <scroom/utilities.hh>
#include <scroom/viewinterface.hh>


/**
 * This MetadataHandler class will probably need adjustments, currently mostly copied from the pipette tool.
 */
class MetadataHandler
  : public ToolStateListener
  , public PostRenderer
  , virtual public Scroom::Utils::Base
{
public:
  using Ptr = boost::shared_ptr<MetadataHandler>;

/* *private:
  Selection::Ptr         selection{nullptr};
  bool                   enabled{false};
  std::atomic_flag       wasDisabled = ATOMIC_FLAG_INIT;
  std::mutex             jobMutex;
  ThreadPool::Queue::Ptr currentJob{ThreadPool::Queue::createAsync()};
*/

public:
  static Ptr create();

public:
  ////////////////////////////////////////////////////////////////////////
  // PostRenderer

  //void render(ViewInterface::Ptr const& vi, cairo_t* cr, Scroom::Utils::Rectangle<double> presentationArea, int zoom) override;

  ////////////////////////////////////////////////////////////////////////
  // ToolStateListener

  void onEnable() override;
  void onDisable() override;

  ////////////////////////////////////////////////////////////////////////


class ImageMetadata
  : public PluginInformationInterface
  , public ViewObserver
  , virtual public Scroom::Utils::Base
{
public:
  using Ptr = boost::shared_ptr<ImageMetadata>;

private:
  ImageMetadata() = default;

public:
  static Ptr create();

public:
  ////////////////////////////////////////////////////////////////////////
  // PluginInformationInterface

  std::string getPluginName() override;
  std::string getPluginVersion() override;
  void        registerCapabilities(ScroomPluginInterface::Ptr host) override;

  ////////////////////////////////////////////////////////////////////////
  // ViewObserver

  Scroom::Bookkeeping::Token viewAdded(ViewInterface::Ptr v) override;

  ////////////////////////////////////////////////////////////////////////
};
