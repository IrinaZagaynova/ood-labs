#include <iostream>
#include <functional>

using namespace std;

using Strategy = function<void()>;

class Context
{
public:
	void Quack()
	{
		if (m_quackBehavior)
		{
			m_quackBehavior();
		}
	}
	void Fly()
	{
		if (m_flyBehavior)
		{
			m_flyBehavior(m_flightСounter);
		}
	}
	void Dance()
	{
		if (m_danceBehavior)
		{
			m_danceBehavior();
		}
	}
	void SetQuackBehavior(const Strategy& quackBehavior)
	{
		m_quackBehavior = quackBehavior;
	}
	void SetFlyBehavior(const function<void(size_t& flightCounter)>& flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}
	void SetDanceBehavior(const Strategy& danceBehavior)
	{
		m_danceBehavior = danceBehavior;
	}
private:
	function<void(size_t& flightCounter)> m_flyBehavior;
	Strategy m_quackBehavior;
	Strategy m_danceBehavior;
	size_t m_flightСounter = 0;
};

void FlyWithWings(size_t& flightСounter)
{
	cout << "I'm flying with wings!!" << endl;
	flightСounter++;
	cout << "Number of duck flights: " << flightСounter << endl;
}

void FlyNoWay(size_t& flightСounter) {}

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

void DanceNoWay() {};

class Duck
{
public:
	Duck(unique_ptr<Context>&& ctx)
		: m_ctx(move(ctx))
	{
	}
	void Quack()
	{
		m_ctx->Quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_ctx->Fly();
	}
	void Dance()
	{
		m_ctx->Dance();
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	unique_ptr<Context> m_ctx;
};

class MallardDuck : public Duck
{
public:
	MallardDuck(unique_ptr<Context>&& ctx)
		: Duck(move(ctx))
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
	RedheadDuck(unique_ptr<Context>&& ctx)
		: Duck(move(ctx))
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
	DecoyDuck(unique_ptr<Context>&& ctx)
		: Duck(move(ctx))
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
	RubberDuck(unique_ptr<Context>&& ctx)
		: Duck(move(ctx))
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
	ModelDuck(unique_ptr<Context>&& ctx)
		: Duck(move(ctx))
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
	Context mallardDuckCtx;
	mallardDuckCtx.SetFlyBehavior(FlyWithWings);
	mallardDuckCtx.SetQuackBehavior(QuackBehavior);
	mallardDuckCtx.SetDanceBehavior(DanceWaltzBehavior);
	MallardDuck mallardDuck(move(make_unique<Context>(mallardDuckCtx)));
	PlayWithDuck(mallardDuck);

	Context redheadDuckCtx;
	redheadDuckCtx.SetFlyBehavior(FlyWithWings);
	redheadDuckCtx.SetQuackBehavior(QuackBehavior);
	redheadDuckCtx.SetDanceBehavior(DanceMinuetBehavior);
	RedheadDuck redheadDuck(move(make_unique<Context>(redheadDuckCtx)));
	PlayWithDuck(redheadDuck);

	Context rubberDuckCtx;
	rubberDuckCtx.SetFlyBehavior(FlyNoWay);
	rubberDuckCtx.SetQuackBehavior(SqueakBehavior);
	rubberDuckCtx.SetDanceBehavior(DanceNoWay);
	RubberDuck rubberDuck(move(make_unique<Context>(rubberDuckCtx)));
	PlayWithDuck(rubberDuck);

	Context decoyDuckCtx;
	decoyDuckCtx.SetFlyBehavior(FlyNoWay);
	decoyDuckCtx.SetQuackBehavior(MuteQuackBehavior);
	decoyDuckCtx.SetDanceBehavior(DanceBehavior);
	DecoyDuck decoyDuck(move(make_unique<Context>(decoyDuckCtx)));
	PlayWithDuck(decoyDuck);

	Context modelDuckCtx;
	modelDuckCtx.SetFlyBehavior(FlyNoWay);
	modelDuckCtx.SetQuackBehavior(QuackBehavior);
	modelDuckCtx.SetDanceBehavior(DanceNoWay);
	ModelDuck modelDuck(move(make_unique<Context>(modelDuckCtx)));
	PlayWithDuck(modelDuck);

	return 0;
}
