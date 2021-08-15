#include <stdio.h>
#include <set>
#include "skiplist.h"

#define logger(fmt, ...) fprintf(stdout, fmt"\n", ##__VA_ARGS__)

using std::set;
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
  const int R = 500;
  Random rnd(1000);
  std::set<Key> keys;
  Comparator cmp;
  SkipList<Key, Comparator> list(cmp);
  for (int i = 0; i < N; i++) {
    Key key = rnd.Next() % R;
    if (keys.insert(key).second) {
      list.Insert(key);
      logger("insert %d", key);
    }
  }

  for (int i = 0; i < N; i++) {
    if (list.Contains(i)) {
      list.Remove(i);
      logger("after remove contains:%d", list.Contains(i));
    } else {
      logger("count:%d == 0", keys.count(i));
    }
  }	

  return 0;
}
