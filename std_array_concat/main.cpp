#include <algorithm>
#include <iostream>
#include <array>

//https://stackoverflow.com/questions/42749032/concatenating-a-sequence-of-stdarrays

template<typename T, int N>
void print_array(std::array<T,N> in){
  for(auto e: in)
    std::cout<<e<<" ";
  std::cout<<"\n";
}

template<typename T, int N, int M>
auto concat(const std::array<T, N>& ar1, const std::array<T, M>& ar2)
{
    std::array<T, N+M> result;
    std::copy (ar1.cbegin(), ar1.cend(), result.begin());
    std::copy (ar2.cbegin(), ar2.cend(), result.begin() + N);
    return result;
}

int main(){


  std::array<char,3> a = {'a','b','c'};
  std::array<char,4> b = {'d','e','f'};

  print_array<char,a.size()>(a);
  print_array<char,b.size()>(b);
  
  /* concat */
  auto c= concat<char, a.size(), b.size()>(a, b);

  print_array<char,c.size()>(c);

}


