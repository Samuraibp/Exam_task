#include <iostream>
using namespace std;

class Member
{
	string Name;
	int distance;
	int height;
public:
	Member(): Name(""), distance(0), height(0) {}
	Member(string n, int d, int h): Name(n) {
		if (d < 0) {
			cout << "Invalid distance" << endl;
			distance = 0;
	    }
		if (h < 0)
		{
			cout << "Invalid height" << endl;
			height = 0;
		}
		distance = d;
		height = h;
	}
	virtual string GetName() { return Name; }
	int GetDistanse() { return distance; }
	int GetHeight() { return height; }
	virtual void run() = 0;
	virtual void jump() = 0;
	virtual ~Member() {}
};

class Human : public Member
{
public:
	Human(): Member() {}
	Human(string n, int d, int h): Member(n, d, h) {}
	void run() override
	{
		cout << "Human is rsunnig" << endl;
	}
	void jump() override
	{
		cout << "Human is jumping" << endl;
	}
	~Human() override {}
};

class Cat : public Member
{
public:
	Cat() : Member() {}
	Cat(string n, int d, int h) : Member(n, d, h) {}
	void run() override
	{
		cout << "Cat is rsunnig" << endl;
	}
	void jump() override
	{
		cout << "Cat is jumping" << endl;
	}
	~Cat() override {}
};

class Robot : public Member
{
public:
	Robot() : Member() {}
	Robot(string n, int d, int h) : Member(n, d, h) {}
	void run() override
	{
		cout << "Robot is rsunnig" << endl;
	}
	void jump() override
	{
		cout << "Robot is jumping" << endl;
	}
	~Robot() override {}
};

class Obstacle
{
public:
	virtual bool PassAnObstacle(Member* obj) = 0;
	virtual ~Obstacle() {}
};

class Wall : public Obstacle
{
	int height;
public:
	Wall(): height(0) {}
	Wall(int h): height(h) {}
	int GetWallH() { return height; }
	bool PassAnObstacle(Member* obj) override
	{
		obj->jump();
		if (obj->GetHeight() < GetWallH()) { cout << obj->GetName() << " Failed" << endl << endl; return false; }
		cout << obj->GetName() << " Passed the wall!" << endl;
		cout << endl;
		return true;
	}
	~Wall() override {}
};

class Treadmill : public Obstacle
{
	int distance;
public:
	Treadmill(): distance(0) {}
	Treadmill(int d)
	{
		if (d < 0) {
			cout << "Invalid distance" << endl;
			distance = 0;
		}
		distance = d;
	}
	int GetDistance() { return distance; }
	bool PassAnObstacle(Member* obj) override
	{
		obj->run();
		if (obj->GetDistanse() < GetDistance()) { cout << obj->GetName() << " Failed" << endl << endl; return false; }
		cout << obj->GetName() << " Ran a treadmill!" << endl;
		cout << endl;
		return true;
	}
	~Treadmill() override {}
};

int main()
{
	Member* members[3];

	members[0] = new Human("Jack", 5, 3);
	members[1] = new Cat("Barsick", 7, 5);
	members[2] = new Robot("Riper-2000", 15, 10);

	Obstacle* obstacle[2];

	obstacle[0] = new Wall(4);
	obstacle[1] = new Treadmill(8);

	for (size_t i = 0; i < 3; i++)
	{
		cout << "--- " << members[i]->GetName() << " ---" << endl;
		if (!obstacle[0]->PassAnObstacle(members[i])) {
			continue;
		}
		if (!obstacle[1]->PassAnObstacle(members[i])) {
			continue;
		}
		
	}

	for (int i = 0; i < 3; i++) delete members[i];
	for (int i = 0; i < 2; i++) delete obstacle[i];

}