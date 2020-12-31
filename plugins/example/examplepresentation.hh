/*
 * Scroom - Generic viewer for 2D data
 * Copyright (C) 2009-2020 Kees-Jan Dijkzeul
 *
 * SPDX-License-Identifier: LGPL-2.1
 */

#pragma once

#include <scroom/presentationinterface.hh>

class ExamplePresentation : public PresentationInterface
{
private:
  cairo_pattern_t* pattern;

  void fillPattern();

public:
  ExamplePresentation();
  virtual ~ExamplePresentation();
  ExamplePresentation(const ExamplePresentation&) = delete;
  ExamplePresentation(ExamplePresentation&&)      = delete;
  ExamplePresentation operator=(const ExamplePresentation&) = delete;
  ExamplePresentation operator=(ExamplePresentation&&) = delete;

  Scroom::Utils::Rectangle<double> getRect() override;
  void                             open(ViewInterface::WeakPtr viewInterface) override;
  void redraw(ViewInterface::Ptr const& vi, cairo_t* cr, Scroom::Utils::Rectangle<double> presentationArea, int zoom) override;
  void close(ViewInterface::WeakPtr vi) override;
  bool getProperty(const std::string& name, std::string& value) override;
  bool isPropertyDefined(const std::string& name) override;
  std::string getTitle() override;
};
