/* 1003 Representing time using class */

class Time{
private:
	int min, sec;
public:
	// Constructed Function
	Time();
	Time(int initMin, int initSec);
	// Get Message
	int Minutes();
	int Seconds();
	int TotalSeconds();
	// Boolean Comparison
	bool Equal(Time c);
	bool GreaterThan(Time c);
	bool LessThan(Time c);
	// Time Operating
	void Add(Time c);
	void Subtract(Time c);
};

Time::Time(){ min = 0; sec = 0; }
Time::Time(int initMin, int initSec){ 
	min = initMin + initSec / 60;
	sec = initSec % 60;
}

int Time::Minutes(){ return min; }
int Time::Seconds(){ return sec; }
int Time::TotalSeconds(){ return min*60+sec; }

bool Time::Equal(Time c){
	if(TotalSeconds() == c.TotalSeconds())
		return true;
	return false;
}

bool Time::GreaterThan(Time c){
	if(TotalSeconds() > c.TotalSeconds())
		return true;
	return false;
}

bool Time::LessThan(Time c){
	if(TotalSeconds() < c.TotalSeconds())
		return true;
	return false;
}

void Time::Add(Time c){
	int time = TotalSeconds() + c.TotalSeconds();
	min = time / 60;
	sec = time % 60;
}

void Time::Subtract(Time c){
	int time = TotalSeconds() - c.TotalSeconds();
	if(time <= 0){
		min = 0;
		sec = 0;
	}
	else{
		min = time / 60;
		sec = time % 60;
	}
}