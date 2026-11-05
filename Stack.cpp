
#include <iostream.h>   
#include <conio.h>      // gives us clrscr() (clean screen) and getch() (wait for a key)


// ============================================================
//  SECTION 2: THE CLASS (the blueprint of a Stack)
//
//  A Stack is like a pile of plates:
//    - you put a plate on TOP        -> push
//    - you take a plate from the TOP -> pop
//    - the last plate you put is the first one you take (LIFO).
//
//  "template <class T>" means: T is a mystery type.
//  When we write Stack<int>, T becomes int.
//  When we write Stack<char>, T becomes char.
//  So we write the class ONCE and it works for ANY type.
// ============================================================
template <class T>
class Stack
{
    // --------------------------------------------------------
    //  2.1 PRIVATE PART: the data hidden inside the stack
    //  (only the stack's own functions can touch these)
    // --------------------------------------------------------
private:
    int top;              // number of items now in the stack
                          // (also the index of the next free place)
    int size;             // maximum number of items the stack can hold
    T *ptr;               // pointer to the array that stores the items
    static int counter;   // counts how many stacks exist
                          // (shared by ALL stacks of the same type)

    // --------------------------------------------------------
    //  2.2 PUBLIC PART: the buttons the user is allowed to press
    //  (here we only write the names, the work is written later)
    // --------------------------------------------------------
public:
    Stack();                  // constructor: makes an empty stack of size 10
    Stack(int n);             // constructor: makes an empty stack of size n
    ~Stack();                 // destructor: cleans the memory when stack dies
    static int getCounter();  // tells how many stacks exist
    Stack(Stack<T> &s);       // copy constructor: makes a new stack
                              // as a copy of another stack
    void push(T x);           // put an item on top
    T pop();                  // take the top item out and give it back
    Stack<T>& operator=(Stack<T> &s);   // assignment:  a = b;

    // --------------------------------------------------------
    //  2.3 FRIEND FUNCTION
    //  It is NOT part of the class, but we give it a special
    //  permission to look at the private data.
    //  It prints all items from the first one to the top one.
    // --------------------------------------------------------
    friend void viewContent(Stack<T> s)
    {
        for (int i = 0; i < s.top; i++)
            cout << s.ptr[i] << " ";
    }
};


// ============================================================
//  SECTION 3: STATIC VARIABLE STARTING VALUE
//  A static variable needs its starting value written ONCE
//  outside the class. We start the counter from 0.
// ============================================================

// static variable initialization
template <class T>
int Stack<T>::counter = 0;


// ============================================================
//  SECTION 4: CONSTRUCTORS (they run when a stack is born)
// ============================================================

// ---- 4.1 Default constructor: Stack<int> s;  -> size 10 ----
template <class T>
Stack<T>::Stack()
{
    top = 0;               // stack is empty
    size = 10;             // default capacity is 10 items
    ptr = new T[size];     // reserve memory for 10 items
    counter++;             // one more stack exists
}

// ---- 4.2 Constructor with size: Stack<int> s(5); -> size 5 ----
template <class T>
Stack<T>::Stack(int n)
{
    top = 0;               // stack is empty
    size = n;              // capacity is what the user asked for
    ptr = new T[size];     // reserve memory for n items
    counter++;             // one more stack exists
}


// ============================================================
//  SECTION 5: DESTRUCTOR (it runs when a stack dies)
//  We give the reserved memory back, otherwise it is lost
//  (this problem is called a memory leak).
// ============================================================
template <class T>
Stack<T>::~Stack()
{
    delete[] ptr;          // give the memory back
    counter--;             // one less stack exists
}


// ============================================================
//  SECTION 6: STATIC FUNCTION
//  Called with the class name, no object needed:
//  Stack<int>::getCounter()
// ============================================================
template <class T>
int Stack<T>::getCounter()
{
    return counter;        // tell how many stacks exist now
}


// ============================================================
//  SECTION 7: COPY CONSTRUCTOR
//  Runs when we build a new stack from an old one, for example:
//      Stack<int> b(a);
//  or when a stack is sent to a function BY VALUE.
//
//  We make a brand NEW array and copy the items one by one,
//  so the two stacks do NOT share the same memory (deep copy).
// ============================================================
template <class T>
Stack<T>::Stack(Stack<T> &s)
{
    top = s.top;                  // same number of items as the old stack
    size = s.size;                // same capacity as the old stack
    ptr = new T[size];            // our OWN new array
    for (int i = 0; i < top; i++)
        ptr[i] = s.ptr[i];        // copy every item from the old array
    counter++;                    // a new stack was created
}


// ============================================================
//  SECTION 8: PUSH (put an item on top)
// ============================================================
template <class T>
void Stack<T>::push(T x)
{
    if (top < size)        // is there still an empty place?
        ptr[top++] = x;    // put x in the free place, then move top up by 1
}


// ============================================================
//  SECTION 9: POP (take the top item out)
// ============================================================
template <class T>
T Stack<T>::pop()
{
    if (top > 0)           // is the stack not empty?
        top--;             // move top down by 1 (the top item is now removed)
    return ptr[top];       // give back that removed item
}


// ============================================================
//  SECTION 10: ASSIGNMENT OPERATOR
//  Runs when both stacks ALREADY exist and we write:  a = b;
//  It throws away a's old items and copies b's items into a.
// ============================================================
template <class T>
Stack<T>& Stack<T>::operator=(Stack<T> &s)
{
    if (this != &s)                   // protect from a = a (copying itself)
    {
        delete[] ptr;                 // throw away the old array
        top = s.top;                  // copy number of items
        size = s.size;                // copy capacity
        ptr = new T[size];            // make a new array
        for (int i = 0; i < top; i++)
            ptr[i] = s.ptr[i];        // copy every item
    }
    return *this;                     // give back the stack itself
}


// ============================================================
//  SECTION 11: MAIN (where the program starts)
// ============================================================
int main()
{
    clrscr();                         // clean the screen

    // ---------- Part A: a stack of integers ----------
    Stack<int> s1(5);                 // integer stack that holds 5 items
    cout << "\nNumber of Integer Stacks is: " << Stack<int>::getCounter();   // prints 1

    s1.push(10);                      // stack: 10
    s1.push(3);                       // stack: 10 3
    s1.push(2);                       // stack: 10 3 2   (2 is on top)

    cout << "\n1st integer: " << s1.pop();   // takes out 2
    cout << "\n2nd integer: " << s1.pop();   // takes out 3

    // ---------- Part B: a stack of characters ----------
    Stack<char> s2;                   // character stack, default size 10
    cout << "\nNumber of Character Stacks is: " << Stack<char>::getCounter();   // prints 1

    s2.push('q');                     // stack: q
    s2.push('r');                     // stack: q r
    s2.push('s');                     // stack: q r s   (s is on top)

    cout << "\nContent: ";
    viewContent(s2);                  // prints: q r s

    cout << "\n1st character: " << s2.pop();   // takes out s
    cout << "\n2nd character: " << s2.pop();   // takes out r

    getch();                          // wait for a key before closing
    return 0;
}
