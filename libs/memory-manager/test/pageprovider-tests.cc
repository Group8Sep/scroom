/*
 * Scroom - Generic viewer for 2D data
 * Copyright (C) 2009-2012 Kees-Jan Dijkzeul
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
#include <scroom/memoryblobs.hh>

#include <boost/test/unit_test.hpp>

#include <boost/foreach.hpp>

#include <string.h>



//////////////////////////////////////////////////////////////

using namespace Scroom::MemoryBlobs;

BOOST_AUTO_TEST_SUITE(PageProvider_Tests)

BOOST_AUTO_TEST_CASE(Provider_provides_any_number_of_independent_blocks_of_a_given_size)
{
  const size_t size = 256;
  const size_t count = 16;
  const size_t testCount = 48;

  PageProvider::Ptr provider = PageProvider::create(count, size);
  PageList pages;

  uint8_t data = 0;
  for(size_t i=0; i<testCount; i++)
  {
    Page::Ptr p = provider->getFreePage();
    pages.push_back(p);
    
    RawPageData::Ptr raw = p->get();
    BOOST_REQUIRE(raw.get());

    memset(raw.get(), data, size);
    data++;
  }

  provider.reset();
  
  data=0;
  uint8_t expected[size];
  BOOST_FOREACH(Page::Ptr p, pages)
  {
    RawPageData::Ptr raw = p->get();
    BOOST_REQUIRE(raw.get());

    memset(expected, data, size);
    BOOST_CHECK(!memcmp(expected, raw.get(), size));
    data++;
  }
}

BOOST_AUTO_TEST_SUITE_END()
