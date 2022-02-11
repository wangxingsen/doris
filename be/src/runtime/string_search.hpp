// This is taken from the python search string function doing string search (substring)
// using an optimized boyer-moore-horspool algorithm.
// http://hg.python.org/cpython/file/6b6c79eba944/Objects/stringlib/fastsearch.h
//
// PYTHON SOFTWARE FOUNDATION LICENSE VERSION 2
// --------------------------------------------
//
// 1. This LICENSE AGREEMENT is between the Python Software Foundation
// ("PSF"), and the Individual or Organization ("Licensee") accessing and
// otherwise using this software ("Python") in source or binary form and
// its associated documentation.
//
// 2. Subject to the terms and conditions of this License Agreement, PSF
// hereby grants Licensee a nonexclusive, royalty-free, world-wide
// license to reproduce, analyze, test, perform and/or display publicly,
// prepare derivative works, distribute, and otherwise use Python
// alone or in any derivative version, provided, however, that PSF's
// License Agreement and PSF's notice of copyright, i.e., "Copyright (c)
// 2001, 2002, 2003, 2004, 2005, 2006 Python Software Foundation; All Rights
// Reserved" are retained in Python alone or in any derivative version
// prepared by Licensee.
//
// 3. In the event Licensee prepares a derivative work that is based on
// or incorporates Python or any part thereof, and wants to make
// the derivative work available to others as provided herein, then
// Licensee hereby agrees to include in any such work a brief summary of
// the changes made to Python.
//
// 4. PSF is making Python available to Licensee on an "AS IS"
// basis. PSF MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR
// IMPLIED. BY WAY OF EXAMPLE, BUT NOT LIMITATION, PSF MAKES NO AND
// DISCLAIMS ANY REPRESENTATION OR WARRANTY OF MERCHANTABILITY OR FITNESS
// FOR ANY PARTICULAR PURPOSE OR THAT THE USE OF PYTHON WILL NOT
// INFRINGE ANY THIRD PARTY RIGHTS.
//
// 5. PSF SHALL NOT BE LIABLE TO LICENSEE OR ANY OTHER USERS OF PYTHON
// FOR ANY INCIDENTAL, SPECIAL, OR CONSEQUENTIAL DAMAGES OR LOSS AS
// A RESULT OF MODIFYING, DISTRIBUTING, OR OTHERWISE USING PYTHON,
// OR ANY DERIVATIVE THEREOF, EVEN IF ADVISED OF THE POSSIBILITY THEREOF.
//
// 6. This License Agreement will automatically terminate upon a material
// breach of its terms and conditions.
//
// 7. Nothing in this License Agreement shall be deemed to create any
// relationship of agency, partnership, or joint venture between PSF and
// Licensee. This License Agreement does not grant permission to use PSF
// trademarks or trade name in a trademark sense to endorse or promote
// products or services of Licensee, or any third party.
//
// 8. By copying, installing or otherwise using Python, Licensee
// agrees to be bound by the terms and conditions of this License
// Agreement.

#pragma once

#include <cstring>
#include <functional>
#include <vector>

#include "common/logging.h"
#include "runtime/string_value.h"

namespace doris {

class StringSearch {
public:
    virtual ~StringSearch() {}
    StringSearch() : _pattern(nullptr) {}

    StringSearch(const StringValue* pattern) : _pattern(pattern) {}

    // search for this pattern in str.
    //   Returns the offset into str if the pattern exists
    //   Returns -1 if the pattern is not found
    int search(const StringValue* str) const {
        if (!str || !_pattern || _pattern->len == 0) {
            return -1;
        }

        auto it = std::search(str->ptr, str->ptr + str->len,
                              std::default_searcher(_pattern->ptr, _pattern->ptr + _pattern->len));
        if (it == str->ptr + str->len) {
            return -1;
        } else {
            return it - str->ptr;
        }
    }

private:
    const StringValue* _pattern;
};

} // namespace doris
