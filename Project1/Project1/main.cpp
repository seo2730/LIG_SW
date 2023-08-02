#include<iostream>
#include<string>

using namespace std;

//void Print(int chair_legs)
//{
//	if (chair_legs % 2 == 0)
//		cout << "True" << endl;
//	else
//		cout << "False" << endl;
//}
//
//int main()
//{
//	int chair_legs = 0;
//	cout << "������ �ٸ� ���� : ";
//	cin >> chair_legs;
//	cout << endl;
//	Print(chair_legs);
//	
//	return 0;
//}


//// ĸ��ȭ �ǽ� ////
//struct Rectangle
//{
//	int width;
//	int height;
//};
//
//
//
//int main()
//{
//	Rectangle Rectangle1 = { 1,2 };
//	Rectangle Rectangle2 = { 3,4 };
//
//	int rectangle1Perimeter = (Rectangle1.width + Rectangle1.height) * 2;
//	int rectangle2Perimeter = (Rectangle2.width + Rectangle2.height) * 2;
//
//}

//class Rectangle
//{
//public:
//	Rectangle(int _width, int _height) {
//		width = _width;
//		height = _height;
//	};
//	int Perimeter();
//	
//private:
//	int width;
//	int height;
//
//	int WidthHeightPlus();
//};
//
//int Rectangle::Perimeter()
//{
//	return WidthHeightPlus() * 2;
//};
//
//int Rectangle::WidthHeightPlus()
//{
//	return (width + height);
//};
//
//int main()
//{
//	Rectangle rectangle1(1, 2);
//	Rectangle rectangle2(3, 4);
//	cout << rectangle1.Perimeter() << endl;
//	cout << rectangle2.Perimeter() << endl;
//
//	return 0;
//}

////// ��� �ǽ� ////
//class Person
//{
//public:
//	void PrintName()
//	{
//		cout << firstName << " " << lastName << endl;
//	}
//
//	string firstName;
//	string lastName;
//};
//
//class Student : public Person
//{
//public:
//	string studentID;
//};
//
//int main()
//{
//	Student student;
//	student.firstName = "Gildong";
//	student.lastName = "Hong";
//	student.studentID = "ABCD1234";
//	student.PrintName();
//
//	return 0;
//}

//// �߻�ȭ �ǽ� ////
//class PrintInterface
//{
//public:
//	virtual void Print(int first, int second) abstract;
//};
//
//class Print1 : public PrintInterface
//{
//public:
//	void Print(int first, int second) override
//	{
//		cout << first << endl << second << endl;
//	}
//};
//
//class Print2 : public PrintInterface
//{
//public:
//	void Print(int first, int second) override
//	{
//		cout << first << ", " << second << endl;
//	}
//};
//
//int main()
//{
//	Print1 print1;
//	Print2 print2;
//	PrintInterface* printInterface = &print1;
//	printInterface->Print(1, 2);
//	printInterface = &print2;
//	printInterface->Print(1, 2);
//}

//// ������ �ǽ� ////
//class PrintInterface
//{
//public:
//	virtual ~PrintInterface(){}
//	virtual void Print(int first, int second) = 0;
//};
//
//class Print1 :public PrintInterface
//{
//public:
//	void Print(int first, int second) override
//	{
//		cout << first << endl << second << endl;
//	}
//};
//
//class Print2 :public PrintInterface
//{
//public:
//	void Print(int first, int second) override
//	{
//		cout << first << ", " << second << endl;
//	}
//};
//
//void PrintAndAdd(int first, int second, PrintInterface &print)
//{
//	print.Print(first, second);
//};
//
//int main()
//{
//	Print1 print1;
//	Print2 print2;
//	PrintAndAdd(1, 2, print1);
//	PrintAndAdd(1, 2, print2);
//}

//// �⺻ Ÿ�Կ� ���� ���� ���� ////
//class Card
//{
//private:
//	int card;
//
//public:
//	void GetCard(int _card)
//	{
//		card = _card;
//	}
//
//	int Shape()
//	{
//		return card / 13;
//	}
//
//	int Rank()
//	{
//		return card % 13;
//	}
//};
//
//int main()
//{
//	Card card;
//	card.GetCard(48);
//	cout << card.Shape() << endl;
//	cout << card.Rank() << endl;
//
//	return 0;
//}

//// �Լ� �и� �ǽ� ////
//double GetTaxRate(const std::string& country)
//{
//	// �Ʒ� ������ �ڵ带 �ۼ��ϼ���
//	if (country == "US")
//	{
//		return 0.07;
//	}
//	else if (country == "EU")
//	{
//		return 0.20;
//	}
//	else
//	{
//		return 0.0;
//	}
//	//
//}
//
//double CalculateTotalOrderCost(const double price, std::string country)
//{
//	double totalCost = price;
//	totalCost += totalCost * GetTaxRate(country);
//	return totalCost;
//}
//
//int main()
//{
//	std::cout << "Total Cost : " << CalculateTotalOrderCost(100, "US") << std::endl;
//}

//// Ŭ���� �и� �ǽ� ////
//class TaxCalculator
//{
//public:
//    double GetTaxRate(const double price, std::string country)
//    {
//        // �Ʒ� ������ �ڵ带 �ۼ��ϼ���
//        if (country == "US")
//        {
//            return TaxCalculator::GetUSTaxRate(price);
//        }
//        else if (country == "EU")
//        {
//            return TaxCalculator::GetEUTaxRate(price);
//        }
//        else
//        {
//            return 0;
//        }
//        //
//    }
//
//private:
//    double GetUSTaxRate(const double price)
//    {
//        // �Ʒ� ������ �ڵ带 �ۼ��ϼ���
//        if (price >= 100.0)
//            return 0.1;
//        else
//            return 0.07;
//        //
//    }
//    double GetEUTaxRate(const double price)
//    {
//        // �Ʒ� ������ �ڵ带 �ۼ��ϼ���
//        if (price >= 100.0)
//            return 0.25;
//        else
//            return 0.2;
//        //
//    }
//};
//
//double CalculateTotalOrderCost(const double price, std::string country)
//{
//    TaxCalculator taxCalculator;
//    double totalCost = price;
//    totalCost += totalCost * taxCalculator.GetTaxRate(price, country);
//    return totalCost;
//}
//
//int main()
//{
//    std::cout << "Total Cost : " << CalculateTotalOrderCost(100, "US") << std::endl;
//}

//// ���� ���� �ǽ� ////
//#include <iostream>
//
//class AutomaticDoor
//{
//public:
//	// �Ʒ� ������ �ڵ带 �ۼ��ϼ���
//	bool IsClosed() const {
//		return state == State::closed;
//	};
//	//
//
//private:
//	enum class State
//	{
//		closed = 1,
//		opening,
//		open,
//		closing
//	};
//
//	State state = State::closed;
//};
//
//int main()
//{
//	AutomaticDoor automaticDoor;
//	if (automaticDoor.IsClosed())
//	{
//		std::cout << "Door is closed!" << std::endl;
//	}
//}

//// �߻�ȭ�� ������ ���� �ǽ� ////
//#include <cmath>
//
//struct Position
//{
//	double x = 0.0;
//	double y = 0.0;
//};
//
//// �Ʒ� ������ �ڵ带 �ۼ��ϼ���
//class IRangeCalculator
//{
//public:
//	virtual double Range(Position from, Position to)=0;
//};
////
//
//class Ship : public IRangeCalculator
//{
//public:
//	double Range(Position from, Position to) override
//	{
//		return std::hypot(to.x - from.x, to.y - from.y);
//	}
//
//	bool SetShipPosition(Position position)
//	{
//		bool result = false;
//		if (Range({ 0.0, 0.0 }, position))
//		{
//			result = false;
//			this->position = position;
//		}
//		return result;
//	}
//	Position ShipPosition()
//	{
//		return position;
//	}
//
//private:
//	Position position;
//};
//
//class Drawer
//{
//public:
//	void DrawRangeBetweenPosition(Position postiion1, Position postiion2, IRangeCalculator &rangeCalculator)
//		{
//			std::cout << rangeCalculator.Range(postiion1, postiion2) << '\n';
//		}
//};
//
//int main()
//{
//	Ship ship;
//	Drawer drawer;
//	drawer.DrawRangeBetweenPosition({ 1.0, 1.0 }, { 2.0, 2.0 }, ship);
//}

//// �Լ� ������, std::function, ���ø� (Template) ���� �ǽ� ////
//#include <cmath>
//#include <iostream>
//
//struct Position
//{
//	double x = 0.0;
//	double y = 0.0;
//};
//
//class Ship
//{
//public:
//	double Range(Position from, Position to)
//	{
//		return std::hypot(to.x - from.x, to.y - from.y);
//	}
//
//	bool SetShipPosition(Position position)
//	{
//		bool result = false;
//		if (Range({ 0.0, 0.0 }, position))
//		{
//			result = false;
//			this->position = position;
//		}
//		return result;
//	}
//
//	Position ShipPosition()
//	{
//		return position;
//	}
//
//private:
//	Position position;
//};
//
//template<class T>
//class Drawer
//{
//public:
//	void DrawRangeBetweenPosition(Position postiion1, Position postiion2, T)
//		{
//			std::cout << Range(postiion1, postiion2) << '\n';
//		}
//};
//
//template<class T>
//int main()
//{
//	Drawer drawer;
//	Ship ship;
//	drawer.DrawRangeBetweenPosition({ 1.0, 1.0 }, { 2.0, 2.0 }, ship);
//}

//// ���� ����� �����ϴ� Ŭ������ �и� �ǽ� ////
//#include <cmath>
//#include <iostream>
//
//struct Position
//{
//	double x = 0.0;
//	double y = 0.0;
//};
//
//// �Ʒ� ������ �ڵ带 �ۼ��ϼ���
//class RangeCalculator
//{
//public:
//	double Range(Position from, Position to)
//	{
//		return std::hypot(to.x - from.x, to.y - from.y);
//	}
//};
////
//
//class Ship
//{
//public:
//	bool SetShipPosition(Position position)
//	{
//		bool result = false;
//		if (RangeCalculator().Range({ 0.0, 0.0 }, position))
//		{
//			result = false;
//			this->position = position;
//		}
//		return result;
//	}
//
//	Position ShipPosition()
//	{
//		return position;
//	}
//
//private:
//	Position position;
//};
//
//class Drawer
//{
//public:
//	void DrawRangeBetweenPosition(Position postiion1, Position postiion2)
//	{
//		RangeCalculator rangeCalculator;
//		std::cout << rangeCalculator.Range(postiion1, postiion2) << '\n';
//	}
//};
//
//int main()
//{
//	Drawer drawer;
//	drawer.DrawRangeBetweenPosition({ 1.0, 1.0 }, { 2.0, 2.0 });
//}

//// ���� ����� ȣ���ϴ� Ŭ������ �и� �ǽ� ////
//#include <cmath>
//#include <iostream>
//
//struct Position
//{
//	double x = 0.0;
//	double y = 0.0;
//};
//
//class Ship
//{
//public:
//	double Range(Position from, Position to)
//	{
//		return std::hypot(to.x - from.x, to.y - from.y);
//	}
//
//	bool SetShipPosition(Position position)
//	{
//		bool result = false;
//		if (Range({ 0.0, 0.0 }, position))
//		{
//			result = true;
//			this->position = position;
//		}
//		return result;
//	}
//
//	Position ShipPosition()
//	{
//		return position;
//	}
//
//private:
//	Position position;
//};
//
//class Drawer
//{
//public:
//	void DrawRange(double range)
//	{
//		std::cout << range << '\n';
//	}
//};
//
//// �Ʒ� ������ �ڵ带 �ۼ��ϼ���
//class Map
//{
//public:
//	void DrawRangeBetweenPosition(Position postion1, Position postion2)
//	{
//		Ship ship;
//		Drawer drawer;
//		drawer.DrawRange(ship.Range(postion1, postion2));
//	}
//};
////
//
//int main()
//{
//	Map map;
//	map.DrawRangeBetweenPosition({ 1.0, 1.0 }, { 2.0, 2.0 });
//}

//// Class Designer �ǽ� ////
class B
{
public:
	int Function2();
};

class A
{
public:
	int Function1(int left, int right);

private:
	B b;
};

int main()
{

}
