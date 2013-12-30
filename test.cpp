#include <iostream>
#include <list>
using namespace std;

class Point {
    public:
    Point();
    Point(int xp, int yp) { x = xp; y = yp;}
    ~Point() {}
    int print_x() const { return x; }
    int print_y() const { return y; }
    private:
    int x, y;
};

int main (int argc, char **argv)
{
    cout << "main : -----------------  \n" << endl;
    Point p1(1,1);
    Point p2(2,2);
    Point p3(3,3);

    list<Point *> mylist;
    list<Point *>::const_iterator lp;

    mylist.push_back(&p1);
    mylist.push_back(&p2);
    mylist.push_back(&p3);

    for(lp = mylist.begin(); lp != mylist.end(); lp++) {
        cout << "item: " << (*lp)->print_x() << ", " << (*lp)->print_y()
<<  endl;
    }

    while(!mylist.empty())
    {
        Point *a = mylist.front();
        mylist.pop_front();
        delete a;
    }

    for(lp = mylist.begin(); lp != mylist.end(); lp++) {
        cout << "item: " << (*lp)->print_x() << ", " << (*lp)->print_y()
<<  endl;
    }

    cout << "Done." << endl;

    return 0;
}

main2()
{
   list<int> L;
   L.push_back(0);              // Insert a new element at the end
   L.push_front(0);             // Insert a new element at the beginning
   L.insert(++L.begin(),2);     // Insert "2" before position of first argument
                                // (Place before second argument)
   L.push_back(5);
   L.push_back(6);
 
   list<int>::iterator i;
 
   for(i=L.begin(); i != L.end(); ++i) cout << *i << " ";
   cout << endl;
   return 0;
}

