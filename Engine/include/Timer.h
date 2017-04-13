#ifndef TIMER_H
#define TIMER_H

class Timer
{
	public:
		Timer(void);
		void Update(float dt);
		void Restart(void);
		float Get(void);
	private:
		float time;
};

#endif // TIMER_H
