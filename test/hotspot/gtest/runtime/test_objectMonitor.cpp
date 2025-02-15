/*
 * Copyright (c) 2018, 2025, Oracle and/or its affiliates. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 */

#include "runtime/objectMonitor.hpp"
#include "runtime/vm_version.hpp"
#include "unittest.hpp"

TEST_VM(ObjectMonitor, sanity) {
  uint cache_line_size = VM_Version::L1_data_cache_line_size();

  if (cache_line_size != 0) {

    EXPECT_EQ(in_bytes(ObjectMonitor::metadata_offset()), 0)
        << "_metadata at a non 0 offset. metadata_offset = "
        << in_bytes(ObjectMonitor::metadata_offset());

    EXPECT_GE((size_t) in_bytes(ObjectMonitor::owner_offset()), cache_line_size)
        << "the _metadata and _owner fields are closer "
        << "than a cache line which permits false sharing.";

    EXPECT_GE((size_t) in_bytes(ObjectMonitor::recursions_offset() - ObjectMonitor::owner_offset()), cache_line_size)
        << "the _owner and _recursions fields are closer "
        << "than a cache line which permits false sharing.";
  }
}
