// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "skiplist.h"
#include <stdio.h>
#include <set>
#include "util/testharness.h"
#include "util/arena.h"
#include "util/random.h"

using namespace leveldb;
using namespace std;
typedef uint64_t Key;

struct Comparator {
  int operator()(const Key& a, const Key& b) const {
    if (a < b) {
      return -1;
    } else if (a > b) {
      return +1;
    } else {
      return 0;
    }
  }
};

int main(int argc, char **argv) {
  const int N = 20;
  const int R = 120;
  Random rnd(1000);
  std::set<Key> keys;
  Arena arena;
  Comparator cmp;
  SkipList<Key, Comparator> list(cmp, arena);
  for (int i = 0; i < N; i++) {
    Key key = rnd.Next() % N;
    printf("key=%u\n", key);
    if (keys.insert(key).second) {
      list.Insert(key);
    }
  }

  for (int i = 0; i < N; i++) {
    if (list.Contains(i)) {
      printf("[true] %d,count:%d\n", i, keys.count(i));
    } else {
      printf("[false] %d,count:%d\n", i, keys.count(i));
    }
  }
}
