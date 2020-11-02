// map::find
#include <iostream>
#include <map>


int main ()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator it;

  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;

  // show content:
  std::cout << "mymap.size() is " << mymap.size() << '\n';
  std::cout << "mymap contains:\n";
  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it){
    std::cout << it->first << " => " << it->second << '\n';
  }

  std::cout<<"\n";
  
  //if b exist, erase b
  it = mymap.find('b');
  if (it != mymap.end()){
    mymap.erase (it);
    std::cout<<"erase b\n";
  }

  std::cout<<"\n";
  // print content:
  std::cout << "mymap.size() is " << mymap.size() << '\n';
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

  std::cout<<"\n";

  for (char c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else
      std::cout << " is not an element of mymap.\n";
  }


  return 0;
}
