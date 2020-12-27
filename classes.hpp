#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;



template <class T>
struct Factory
{
    public:

    int classid = 0;
    int count = 0;
    pair<T, T> a[4];

    Factory(){
        for (int i = 0; i < this->count; i++)
        {
            this->a[i].first = 0;
            this->a[i].second = 0;
        }
        
    }

    Factory(const Factory<T> &s){
        this->count = s.count;
        this->classid = s.classid;
        for (int i = 0; i < count; i++)
        {
            this->a[i].first = s.a[i].first;
            this->a[i].second = s.a[i].second;
        }
    }

    void virtual Print(){
        printf("Factory\n");
        for (int i = 0; i < this->count; i++)
        {
            printf("Вершина №%d: ", i+1);
            cout<<this->a[i].first<<" "<<this->a[i].second<<endl;
        }
    }


    ~Factory(){}
};

template <class T>
struct Rectangle : public Factory<T>
{
    Rectangle(){
        this->count = 4;
        this->classid = 2;
    }

    Rectangle(const Rectangle<T> &s){
        this->count = s.count;
        this->classid = s.classid;
        for (int i = 0; i < this->count; i++)
        {
            this->a[i].first = s.a[i].first;
            this->a[i].second = s.a[i].second;
        }
    }

    Rectangle(T x1, T y1, T x2, T y2){ //диагональные вершины
        this->classid = 2;
        this->count = 4;
        this->a[0].first = x1;
        this->a[0].second = y1;
        this->a[2].first = x2;
        this->a[2].second = y2;
        
        this->a[1].first = x2;
        this->a[1].second = y1;
        
        this->a[3].first = x1;
        this->a[3].second = y2;
    }

    void virtual Print(){
        printf("Прямоугольник: \n");
        for (int i = 0; i < this->count; i++)
        {
            printf("Вершина №%d: ", i+1);
            cout<<this->a[i].first<<" "<<this->a[i].second<<endl;
        }
        
    }

    ~Rectangle(){}
};

template <class T>
struct Triangle : public Factory<T>
{
    Triangle(){
        this->count = 3;
        this->classid = 1;
    }

    Triangle(const Triangle<T> &s){
        this->count = s.count;
        this->classid = s.classid;
        for (int i = 0; i < this->count; i++)
        {
            this->a[i].first = s.a[i].first;
            this->a[i].second = s.a[i].second;
        }
    }
    
    Triangle(T x, T y, T x1, T y1)
    {
        this->classid = 1;
        double angle = 3.14 / 180.0 * (360 / 3);
        this->count = 3;
        for (int i = 0; i < 3; i++)
        {
            this->a[i].first = x;
            this->a[i].second = y;
            T nextX = ((x1 - x) * cos(angle) + (y1 - y) * -sin(angle)) + x1;
            T nextY = ((x1 - x) * sin(angle) + (y1 - y) * cos(angle)) + y1;
            x = x1;
            y = y1;
            x1 = nextX;
            y1 = nextY;
        }
    }

    void Print(){
        printf("Треугольник: \n");
        for (int i = 0; i < this->count; i++)
        {
            printf("Вершина №%d: ", i+1);
            cout<<this->a[i].first<<" "<<this->a[i].second<<endl;
        }
        
    }

    ~Triangle(){}
};

template <class T>
struct Square : public Rectangle<T>{

    Square(){
        this->count = 4;
        this->classid = 3;
    }
    
    Square(T x1, T y1, T x2, T y2){ //диагональные вершины
        this->classid = 3;
        this->count = 4;
        if(x2-x1 != y2-y1){
            printf("Вершины квадрата введены неверно\n");
            return;
        }
        this->a[0].first = x1;
        this->a[0].second = y1;
        this->a[2].first = x2;
        this->a[2].second = y2;
        
        this->a[1].first = x2;
        this->a[1].second = y1;
        
        this->a[3].first = x1;
        this->a[3].second = y2;
    }

     Square(const Square<T> &s){
        this->count = s.count;
        this->classid = s.classid;
        for (int i = 0; i < this->count; i++)
        {
            this->a[i].first = s.a[i].first;
            this->a[i].second = s.a[i].second;
        }
    }

    void Print(){
        printf("Квадрат: \n");
        for (int i = 0; i < this->count; i++)
        {
            printf("Вершина №%d: ", i+1);
            cout<<this->a[i].first<<" "<<this->a[i].second<<endl;
        }
        
    }
};