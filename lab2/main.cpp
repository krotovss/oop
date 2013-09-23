#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const double pi = 3.14159265359;

class Shape
{
public:
	virtual double area() const = 0;

	virtual double perimeter() const = 0;

	virtual int info() const = 0;
};

class Circle : public Shape
{
private :
	double radius;

public:
	Circle(double r) : radius(r) {}

	double area() const
	{
		return pi * radius * radius;
	}

	double perimeter() const
	{
		return 2 * pi * radius;
	}

	int info() const
	{
		std::cout << "Circle" << " radius = " << radius;
		std::cout << std::endl;
		std::cout << "area = " << area() << " perimeter = " << perimeter();
		std::cout << std::endl;

		return 0;
	}

};

class RightTriangle : public Shape
{
private:
	double cathetus_a;
	double cathetus_b;

public:
	RightTriangle(double a, double b)
	{
		cathetus_a = a;
		cathetus_b = b;
	}

	double area() const
	{
		return cathetus_a * cathetus_b / 2;
	}

	double perimeter() const
	{
		return cathetus_a + cathetus_b + sqrt(cathetus_a * cathetus_a + cathetus_b * cathetus_b);
	}

	int info() const
	{
		std::cout << "Right Triangle" << " cathetus_a = " << cathetus_a << " cathetus_b = " << cathetus_b;
		std::cout << std::endl;
		std::cout << "area = " << area() << " perimeter = " << perimeter();
		std::cout << std::endl;

		return 0;
	}
};

class Square : public Shape
{
private:
	double side;

public:
	Square(double a)
	{
		side = a;
	}

	double area() const
	{
		return side * side;
	}

	double perimeter() const
	{
		return 4 * side;
	}

	int info() const
	{
		std::cout << "Square" << " side = " << side;
		std::cout << std::endl;
		std::cout << "area = " << area() << " perimeter = " << perimeter();
		std::cout << std::endl;

		return 0;
	}
};

bool compare_area(Shape* a, Shape* const b)
{
	return a->area() < b->area();
}

bool compare_perimetr(Shape* const a, Shape* const b)
{
	return a->perimeter() < b->perimeter();
}

int main()
{
	std::ifstream in("input.txt");
	
	unsigned int n = 0;
	in >> n;
	std::vector<Shape*> v(n);

	for (size_t i = 0; i < v.size(); ++i)
	{
		double a;
		std::string type;
		in >> type >> a;

		if (type == "Circle")
		{
			v[i] = new Circle(a);
		} 
		else if (type == "Square")
		{
			v[i] = new Square(a);
		}
		else
		{
			double b;
			in >> b;
			v[i] = new RightTriangle(a, b);
		}
	}

	std::sort(v.begin(), v.end(), compare_area);

	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i]->info();
	}

	std::sort(v.begin(), v.end(), compare_perimetr);

	std::cout << std::endl << "Minimum perimeter:" << std::endl;
	v[0]->info();

	return 0;
}