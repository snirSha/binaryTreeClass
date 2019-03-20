

#include <iostream>
using std::cout, std::endl;
#include "badkan.hpp"
#include "Tree.hpp"

int main() {
  ariel::Tree emptytree;
  ariel::Tree threetree; 
  ariel::Tree fourtree;
  ariel::Tree eighttree;

  threetree.insert(5);
  threetree.insert(7);
  threetree.insert(3);

  fourtree.insert(10);
  fourtree.insert(12);
  fourtree.insert(8);
  fourtree.insert(13);

  eighttree.insert(15);
  eighttree.insert(8);
  eighttree.insert(20);
  eighttree.insert(10);
  eighttree.insert(5);
  eighttree.insert(17);
  eighttree.insert(9);
  eighttree.insert(1);
  
  ariel::Tree mytree;  

  badkan::TestCase tc("Binary tree");
  tc
  .CHECK_EQUAL (emptytree.size(), 0)
  .CHECK_OK    (emptytree.insert(5))
  .CHECK_EQUAL (emptytree.size(), 1)
  .CHECK_EQUAL (emptytree.contains(5), true)
  .CHECK_OK    (emptytree.remove(5))
  .CHECK_EQUAL (emptytree.contains(5), false)
  .CHECK_THROWS(emptytree.remove(5))
  .CHECK_EQUAL (emptytree.size() ,0)
  
  .CHECK_EQUAL (threetree.size(), 3)
  .CHECK_EQUAL (threetree.root(), 5)
  .CHECK_EQUAL (threetree.parent(3), 5)
  .CHECK_EQUAL (threetree.parent(7), 5)
  .CHECK_EQUAL (threetree.left(5), 3)
  .CHECK_EQUAL (threetree.right(5), 7)
  .CHECK_THROWS(threetree.insert(3))
  .CHECK_THROWS(threetree.left(6))
  .CHECK_OK    (threetree.print())
  .print()
  ///////////////////checks on four nodes tree/////////////////////////////////
  
  .CHECK_EQUAL (fourtree.left(10), 8)
  .CHECK_EQUAL (fourtree.parent(12), 10)
  .CHECK_OK    (fourtree.remove(10))
  .CHECK_OK    (fourtree.insert(9))
  .CHECK_OK    (fourtree.remove(13))
  .CHECK_OK    (fourtree.remove(8))
  .CHECK_OK    (fourtree.remove(12))
  .CHECK_EQUAL (fourtree.size(),1)
  .CHECK_THROWS(fourtree.left(6))
  .CHECK_THROWS(fourtree.right(6))
  .CHECK_EQUAL (fourtree.contains(9), true)
  .CHECK_THROWS(fourtree.parent(9))
  .CHECK_OK    (fourtree.remove(9))
  .CHECK_THROWS(fourtree.root())
  .CHECK_THROWS(fourtree.left(5))
  .CHECK_THROWS(fourtree.right(1))
  .CHECK_OK    (fourtree.insert(9))
  .CHECK_THROWS(fourtree.insert(9))
  .CHECK_THROWS(fourtree.insert(9))
  .CHECK_THROWS(fourtree.insert(9))
  .CHECK_THROWS(fourtree.insert(9))
  .print()

///////////////////checks on eight nodes tree//////////////////////////////////

  .CHECK_OK    (eighttree.remove(17))
  .CHECK_OK    (eighttree.remove(20))
  .CHECK_THROWS(eighttree.remove(17))
  .CHECK_EQUAL (eighttree.left(8), 5)
  .CHECK_EQUAL (eighttree.right(8), 10)
  .CHECK_EQUAL (eighttree.parent(10), 8)
  .CHECK_EQUAL (eighttree.root(), 15)
  .CHECK_OK    (eighttree.remove(8))
  .CHECK_EQUAL (eighttree.right(9), 10)
  .CHECK_EQUAL (eighttree.left(9), 5)
  .print();


  cout << "You have " << tc.right() << " right answers and " << tc.wrong() << " wrong answers so your grade is " << tc.grade() << ". Great!" << endl;
}
