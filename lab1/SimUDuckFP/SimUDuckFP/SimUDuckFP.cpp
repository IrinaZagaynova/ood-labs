#include <iostream>
#include <functional>

using namespace std;

using FlyStrategy = function<void()>;
using DanceStrategy = function<void()>;
using QuackStrategy = function<void()>;

FlyStrategy FlyWithWings()
{
	int flightСounter = 0;
	return [flightСounter]() mutable
	{
		flightСounter++;
		cout << "I'm flying with wings!!" << endl;
		cout << "Number of duck flights: " << flightСounter << endl;
	};
}

void FlyNoWay() 
{
	cout << "I don't fly" << endl;
}

void QuackBehavior()
{
	cout << "Quack Quack!!!" << endl;
}

void SqueakBehavior()
{
	cout << "Squeek!!!" << endl;
}

void MuteQuackBehavior() {}

void DanceBehavior()
{
	cout << "I'm dancing" << endl;
}

void DanceWaltzBehavior()
{
	cout << "I'm dancing a waltz" << endl;
}

void DanceMinuetBehavior()
{
	cout << "I'm dancing a minuet" << endl;
}

void DanceNoWay() 
{
	cout << "I don't quack" << endl;
};

class Duck
{
public:
	Duck(const FlyStrategy& flyBehavior,
		const QuackStrategy& quackBehavior,
		const DanceStrategy& danceBehavior)
		: m_flyBehavior(flyBehavior), m_quackBehavior(quackBehavior), m_danceBehavior(danceBehavior)
	{		
	}
	void Quack()
	{
		m_quackBehavior();
	}
	void Fly()
	{
		m_flyBehavior();
	}
	void Dance()
	{
		m_danceBehavior();
	}
	void SetQuackBehavior(const QuackStrategy& quackBehavior)
	{
		m_quackBehavior = quackBehavior;
	}
	void SetFlyBehavior(const FlyStrategy& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	void SetDanceBehavior(const DanceStrategy& danceBehavior)
	{
		m_danceBehavior = danceBehavior;
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	QuackStrategy m_quackBehavior;
	FlyStrategy m_flyBehavior;
	DanceStrategy m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings(), QuackBehavior, DanceWaltzBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings(), QuackBehavior, DanceMinuetBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuackBehavior, DanceBehavior)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueakBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, QuackBehavior, DanceNoWay)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);

	return 0;
}
