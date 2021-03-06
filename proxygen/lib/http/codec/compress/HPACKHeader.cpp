/*
 *  Copyright (c) 2017, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#include <proxygen/lib/http/codec/compress/HPACKHeader.h>

namespace proxygen {

bool HPACKHeader::sAllowPathIndexing{true};

bool HPACKHeader::isIndexable() const {
  if (name.get() == ":path") {
    // no URL params
    if (!sAllowPathIndexing) {
      return false;
    }
    if (value.find('=') != std::string::npos) {
      return false;
    }
    if (value.find("jpg") != std::string::npos) {
      return false;
    }
  } else if (name.get() == "content-length" ||
             name.get() == "if-modified-since" ||
             name.get() == "last-modified") {
    return false;
  }
  return true;
}

std::ostream& operator<<(std::ostream& os, const HPACKHeader& h) {
  os << h.name << ": " << h.value;
  return os;
}

}
