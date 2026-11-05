// ============================================================
//  SECTION 1: INCLUDES
// ============================================================
#include <iostream.h>
#include <conio.h>      // clrscr() and getch()


// ============================================================
//  SECTION 2: GeoShape  (the PARENT, an ABSTRACT class)
//
//  - It holds two numbers d1 and d2 (the dimensions of a shape).
//  - calculateArea() is a PURE VIRTUAL function: "= 0" means
//    "no body here, every child MUST write its own".
//  - Because of that, GeoShape is ABSTRACT:
//        GeoShape g;      <-- ERROR, we cannot make an object
//        GeoShape *p;     <-- OK, we CAN make a pointer
// ============================================================
class GeoShape
{
  protected:                        // children can use d1 and d2
    float d1;
    float d2;

  public:
    GeoShape()
    {
        d1 = 0;
        d2 = 0;
    }

    GeoShape(float a, float b)
    {
        d1 = a;
        d2 = b;
    }

    virtual float calculateArea() = 0;   // pure virtual function
};


// ============================================================
//  SECTION 3: Triangle  (CHILD of GeoShape, PUBLIC inheritance)
//  area = 0.5 * base * height
// ============================================================
class Triangle : public GeoShape
{
  public:
    Triangle(float b, float h) : GeoShape(b, h)
    {
    }

    float calculateArea()
    {
        return 0.5 * d1 * d2;
    }
};


// ============================================================
//  SECTION 4: Rect  (CHILD of GeoShape, PUBLIC inheritance)
//  area = width * height
// ============================================================
class Rect : public GeoShape
{
  public:
    Rect(float w, float h) : GeoShape(w, h)
    {
    }

    float calculateArea()
    {
        return d1 * d2;
    }
};


// ============================================================
//  SECTION 5: Circle  (CHILD of GeoShape, PUBLIC inheritance)
//  We send the radius twice, so d1 = d2 = radius
//  area = 3.14 * radius * radius
// ============================================================
class Circle : public GeoShape
{
  public:
    Circle(float r) : GeoShape(r, r)
    {
    }

    float calculateArea()
    {
        return 3.14 * d1 * d2;
    }
};


// ============================================================
//  SECTION 6: Square  (CHILD of Rect, PUBLIC inheritance)
//  A square is a rectangle with equal sides, so it only
//  sends the side twice to Rect. It uses Rect's calculateArea().
// ============================================================
class Square : public Rect
{
  public:
    Square(float side) : Rect(side, side)
    {
    }
};


// ============================================================
//  SECTION 7: STANDALONE FUNCTION  sumOfAreas
//  It is NOT inside any class.
//  It takes 3 POINTERS of the PARENT type (GeoShape*).
//  Each pointer can point to ANY child (Triangle, Rect, ...).
//  Because calculateArea() is virtual, the CHILD version runs
//  (this is Dynamic Binding / Late Binding).
// ============================================================
float sumOfAreas(GeoShape *p1, GeoShape *p2, GeoShape *p3)
{
    return p1->calculateArea() + p2->calculateArea() + p3->calculateArea();
}


// ============================================================
//  SECTION 8: MAIN (where the program starts)
// ============================================================
int main()
{
    clrscr();

    // ---------- Part A: make one object from each child ----------
    Circle   c(10);
    Rect     r(30, 40);
    Triangle t(100, 150);
    Square   s(60);

    // ---------- Part B: ONE parent pointer, many children ----------
    GeoShape *p;

    p = &c;
    cout << "\nCircle   area = " << p->calculateArea();     // Circle version

    p = &r;
    cout << "\nRect     area = " << p->calculateArea();     // Rect version

    p = &t;
    cout << "\nTriangle area = " << p->calculateArea();     // Triangle version

    p = &s;
    cout << "\nSquare   area = " << p->calculateArea();     // Square (uses Rect version)

    // ---------- Part C: use the standalone function ----------
    Triangle myT(20, 10);
    Rect     myR(2, 5);
    Circle   myc(5);

    cout << "\n\nSum of areas = " << sumOfAreas(&myT, &myR, &myc);

    // GeoShape g;     <-- if you remove the // you get an ERROR,
    //                     because GeoShape is abstract.

    getch();
    return 0;
}
