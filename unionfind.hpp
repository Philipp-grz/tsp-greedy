#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <cstddef>
#include <cassert>
#include <vector>

#include "graph.hpp"

class UnionFind {
public:
   using Id = std::size_t;

   UnionFind(Id num_elems);

   Id root(Id elem) const;
   void merge(Id a, Id b);

private:
   struct ElemInfo {
      Id _parent;
      int rank;
   };
   std::vector<ElemInfo> _data;
};


void test_uf() {
   using Id = UnionFind::Id;
   Id const num = 5;

   UnionFind uf{num};

   for (Id i{0}; i < num; ++i) {
      assert(uf.root(i) == i);
   }

   uf.merge(1, 2);
   assert(uf.root(1) == uf.root(2));
}


class MyFancyAlgorithm {
public:
   MyFancyAlgorithm(Graph const & g) : _graph(g), _uf{_graph.num_nodes()} {}


private:
   Graph const & _graph;
   UnionFind _uf;
};

#endif
