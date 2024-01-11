#include "stack.hpp"
#include <iostream>

#include "map.hpp"

// int main ()
// {
//   ft::map<char,int> mymap;

//   mymap['x'] = 100;
//   mymap['y'] = 200;
//   mymap['z'] = 300;
//   mymap['f'] = 150;

//   // show content:
//   ft::map<char,int>::reverse_iterator rit;
//   for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
//     std::cout << rit->first << " => " << rit->second << '\n';

//   return 0;
// }

#include <iostream>
#include <map>

// int main ()
// {
//   ft::map<char,int> mymap;
//   ft::map<char,int>::iterator it;

//   mymap['a']=50;
//   mymap['b']=100;
//   mymap['c']=150;
//   mymap['d']=200;

//   it = mymap.find('b');
//   if (it != mymap.end())
//     mymap.erase (it);

//   // print content:
//   std::cout << "elements in mymap:" << '\n';
//   std::cout << "a => " << mymap.find('a')->second << '\n';
//   std::cout << "c => " << mymap.find('c')->second << '\n';
//   std::cout << "d => " << mymap.find('d')->second << '\n';

//   return 0;
// }

#include <iostream>
#include <map>

int main ()
{
  ft::map<char,int> mymap;

  std::pair<char, int>

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  // show content:
  ft::map<char,int>::const_reverse_iterator rit;
  for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';

  return 0;
}