
#include "algorithm.hpp"

#include <limits>

class MinComputer {
public:
   using Data = std::vector<int>;
   MinComputer(Data const & data) : _data{data}, _cur_min{std::numeric_limits<int>::max()} {}

   int compute_min() {
      for (auto const elem : _data) {
         if (_cur_min > elem) {
            _cur_min = elem;
         }
      }
      return _cur_min;
   }
private:
   Data const & _data;
   int _cur_min;
};

int compute_min(std::vector<int> const & data) {
   MinComputer m{data};
   return m.compute_min();
}
