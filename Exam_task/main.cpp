#include <iostream>
using namespace std;

class Participant
{
	string Name;
	int distance;
	int height;
public:
	Participant(): Name(""), distance(0), height(0) {}
	Participant(string n, int d, int h): Name(n) {
		distance = (d < 0) ? 0 : d;
		height = (h < 0) ? 0 : h;
	}
	virtual string GetName() const { return Name; }
	int GetDistance() const { return distance; }
	int GetHeight() const { return height; }
	virtual void run() = 0;
	virtual void jump() = 0;
	virtual ~Participant() {}
};

class Human : public Participant
{
	int age;
public:
	Human(): Participant(), age(0) {}
	Human(string n, int a, int d, int h): Participant(n, d, h), age(a) {}
	int GetAge() { return age; }
	void run() override
	{
		cout << "Human is runnig" << endl;
	}
	void jump() override
	{
		cout << "Human is jumping" << endl;
	}
	~Human() override {}
};

class Cat : public Participant
{
	string color;
public:
	Cat() : Participant(), color("") {}
	Cat(string n, string c, int d, int h) :  Participant(n, d, h), color(c) {}
	string GetColor()  { return color; }
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

class Robot : public Participant
{
	string material;
public:
	Robot() : Participant(), material("") {}
	Robot(string n, string m, int d, int h) : Participant(n, d, h), material(m) {}
	string GetMaterial() const { return material; }
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
	virtual bool PassAnObstacle(Participant* obj) = 0;
	virtual string GetObstacleName() = 0;
	virtual ~Obstacle() {}
};

class Wall : public Obstacle
{
	int height;
public:
	Wall(): height(0) {}
	Wall(int h) {
		height = (h < 0) ? 0 : h;
	}
	int GetWallH() { return height; }
	string GetObstacleName() override { return "Wall"; }
	bool PassAnObstacle(Participant* obj) override
	{
		obj->jump();
		if (obj->GetHeight() < GetWallH()) {
			cout << "Participant[" << obj->GetName() << "] failed obstacle["
				<< GetObstacleName() << "] at height[" << GetWallH()
				<< "]. Passed[" << obj->GetHeight() << "]" << endl;
			return false;
		}
		else {
			cout << "Participant[" << obj->GetName() << "] passed obstacle["
				<< GetObstacleName() << "] at height[" << GetWallH() << "]" << endl;
			return true;
		}
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
		distance = (d < 0) ? 0 : d;
	}
	int GetDistance() { return distance; }
	string GetObstacleName() override { return "Treadmill"; }
	bool PassAnObstacle(Participant* obj) override
	{
		obj->run();
		if (obj->GetDistance() < GetDistance()) {
			cout << "Participant[" << obj->GetName() << "] failed obstacle["
				<< GetObstacleName() << "] at distance[" << GetDistance()
				<< "]. Passed[" << obj->GetDistance() << "]" << endl;
			return false;
		}
		else {
			cout << "Participant[" << obj->GetName() << "] passed obstacle["
				<< GetObstacleName() << "] at distance[" << GetDistance() << "]" << endl;
			return true;
		}
	}
	~Treadmill() override {}
};

int main()
{
	Participant* members[3];

	members[0] = new Human("Jack", 25, 5, 3);
	members[1] = new Cat("Barsick", "Black", 7, 5);
	members[2] = new Robot("Riper-2000", "Iron", 15, 10);

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