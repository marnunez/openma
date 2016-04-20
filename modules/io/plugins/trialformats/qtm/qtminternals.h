/* 
 * Open Source Movement Analysis Library
 * Copyright (C) 2016, Moveck Solution Inc., all rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 *     * Redistributions of source code must retain the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *     * Neither the name(s) of the copyright holders nor the names
 *       of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written
 *       permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __openma_io_qtminternals_h
#define __openma_io_qtminternals_h

#include "qtmhandler.h"
#include "openma/io/handlerplugin.h"
#include "openma/base/any.h"
#include "openma/base/macros.h" // _OPENMA_NOEXCEPT

#include <cstdint>
#include <string>
#include <array>
#include <vector>

namespace ma
{
namespace io
{
  class BinaryStream;
  class Buffer;
  
  struct QTMConfiguration
  {
    struct DictItemEntry
    {
      DictItemEntry(const std::string& n, int32_t t) : Name(n), Type(t) {};
      std::string Name;
      int32_t Type;
    };
  
    struct DictPropertyEntry
    {
      DictPropertyEntry(const std::string& n, const std::string& d, const std::array<int32_t,5>& f) : Name(n), Description(d), Flags(f) {};
      std::string Name;
      std::string Description; // not sure if this is really a description
      std::array<int32_t,5> Flags;
    };

    struct Property
    {
      Property() : DictEntry(nullptr), Value() {};
      DictPropertyEntry* DictEntry;
      Any Value;
    };
  
    struct Item
    {
      Item() : DictIndex(-1), GlobalIndex(-1), DictEntry(nullptr), Properties(), Extras(), Children() {};
      ~Item();
      const Property* property(const std::string& name) const _OPENMA_NOEXCEPT;
      int32_t DictIndex;
      int32_t GlobalIndex;
      DictItemEntry* DictEntry;
      std::vector<Property*> Properties;
      std::vector<Any> Extras;
      std::vector<Item*> Children;
    };
  
  
    QTMConfiguration() : DictItemEntries(), DictPropertyEntries(), RootItem(nullptr) {};
    ~QTMConfiguration();
  
    const Item* findItem(const std::string& name) const _OPENMA_NOEXCEPT;
  
    std::vector<DictItemEntry> DictItemEntries;
    std::vector<DictPropertyEntry> DictPropertyEntries;
    Item* RootItem;
  };

  // ----------------------------------------------------------------------- //

  struct QTMCompoundDocument
  {
    struct DictEntry
    {
      enum {Empty = 0x00, Storage = 0x01, Stream = 0x02, LockBytes = 0x03, Property = 0x04, RootStorage = 0x05};
      DictEntry() : name(), type(Empty), left_id(-1), right_id(-1), sub_id(-1), first_sid(-1), size(0) {};
      std::string name;
      int8_t type;
      int8_t color;
      int32_t left_id;
      int32_t right_id;
      int32_t sub_id;
      int32_t first_sid;
      uint32_t size;
    };
  
    QTMCompoundDocument();
    ~QTMCompoundDocument();
    void load(BinaryStream* stream);
    bool setBufferToEntry(Buffer* buffer, const std::string& path);
    DictEntry* findEntry(DictEntry* parent, const std::string& path) const;
    DictEntry* findLevelEntry(DictEntry* level, const std::string& name) const;
    int32_t sector_size;
    int32_t short_sector_size;
    int32_t num_sectors_SAT;
    int32_t first_sid_DIR;
    uint32_t standard_stream_minimum_size;
    int32_t first_sid_SSAT;
    int32_t num_sectors_SSAT;
    int32_t first_sid_MSAT;
    int32_t num_sectors_MSAT;
    int32_t* sids_MSAT;
    int32_t* sids_SAT;
    int32_t* sids_SSAT;
    int32_t* sids_DRE; // Directory - root entry
    std::vector<DictEntry*> dir_entries;
  };
};
};

#endif // __openma_io_qtminternals_h