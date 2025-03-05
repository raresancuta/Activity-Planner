#pragma once

#include <algorithm>
#include <vector>
using std::vector;
class Observer {
public:
	virtual void update() = 0;
};

class Observable {
	vector<Observer*>interesati;
protected:
	void notify();
public:
	void addObserver(Observer* o);
	void removeObserver(Observer* o);
};