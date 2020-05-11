#include <iostream>
using namespace std;

class Polygon {
protected:
    float width, height;
public:
    void set_values(float a, float b)
    {
        width = a; height = b;
    }
    virtual float area()
    {
        return 0;
    }
    virtual float perimeter()
    {
        return 0;
    }
    virtual ~Polygon(){

    }
};

class Rectangle : public Polygon {
public:
    float area()
    {
        return width * height;
    }
    
    float perimeter()
    {
        return 2 * (width + height);
    }
    ~Rectangle()
    {
        cout << "The Rectangle Destructor" << "\n";
    }
};

class Triangle : public Polygon {
public:
    float area()
    {
        return (width * height / 2);
    }
    ~Triangle()
    {
        cout << "The Triangle Destructor" << "\n";
    }
    

};

int main() {
    Rectangle rect;
    Triangle trgl;
    float RectangleLength, RectangleBreadth,TriangleBase,TriangleHeight;
    Polygon poly;
    Polygon* poly1 = &rect;
    Polygon* poly2 = &trgl;
    int flag = 0;
    while (1)
    {
        cout << "Enter 1 to perform operations or 0 to quit" << "\n";
        cin >> flag;
        if (flag == 0)
            break;
        else
        {
            cout << "Enter the length and breadth values of the Rectangle" << "\n";
            cin >> RectangleLength >> RectangleBreadth;
            poly1->set_values(RectangleLength, RectangleBreadth);
            cout<<"The area of the rectangle is: "<<poly1->area()<<"\n";
            cout<<"The perimeter of the rectangle is: "<<poly1->perimeter()<<"\n";
            cout << "Enter the base and height values of the triangle" << "\n";
            cin >> TriangleBase >> TriangleHeight;
            cout << "The area of the Triangle is: " << poly2->area() << "\n";
        }

    }
   


  
    return 0;
}