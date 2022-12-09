#include "workTimeLib.hpp"

#ifdef __WORK_TIME_CLASS
void workTime::start()
{
	startPoint = std::chrono::high_resolution_clock::now();
}

void workTime::stop()
{
	endPoint = std::chrono::high_resolution_clock::now();
	duration = endPoint - startPoint;
}

void workTime::restart()
{
	start();
}

std::string workTime::getStringTime()
{
	{
		std::string time = std::to_string(duration.count());
		return time;
	}
}

std::ostream& operator<<(std::ostream& os, const workTime& wt)
{
	os << wt.duration.count() << "s";
	return os;
}

workTime& workTime::operator=(const workTime& other)
{
	startPoint = other.startPoint;
	endPoint = other.endPoint;
	duration = other.duration;
	return *this;
}

std::chrono::duration<float> workTime::getDuration()
{
	return duration;
}
#endif // __WORK_TIME_CLASS

#ifdef __TIME_DURATION_CLASS
timeDuration::timeDuration()
{
	duration = std::chrono::duration<float>(0);
}

std::ostream& operator<<(std::ostream& os, const timeDuration& wt)
{
	os << wt.duration.count() << "s";
	return os;
}

timeDuration& timeDuration::operator=(const timeDuration& other)
{
	duration = other.duration;
	return *this;
}

timeDuration& timeDuration::operator=(float other)
{
	duration = std::chrono::duration<float>(other);
	return *this;
}

std::chrono::duration<float> timeDuration::getTime()
{
	return duration;
}

float timeDuration::getSeconds()
{
	return duration.count();
}

float timeDuration::getMinutes()
{
	return duration.count() / 60;
}

float timeDuration::getHours()
{
	return duration.count() / 3600;
}

float timeDuration::getDays()
{
	return duration.count() / 86400;
}

bool timeDuration::operator>(timeDuration& other)
{
	return duration > other.duration;
}

bool timeDuration::operator<(timeDuration& other)
{
	return duration < other.duration;
}

bool timeDuration::operator>=(timeDuration& other)
{
	return duration >= other.duration;
}

bool timeDuration::operator<=(timeDuration& other)
{
	return duration <= other.duration;
}

bool timeDuration::operator==(timeDuration& other)
{
	return duration == other.duration;
}

bool timeDuration::operator!=(timeDuration& other)
{
	return duration != other.duration;
}

timeDuration timeDuration::operator+(timeDuration& other)
{
	timeDuration result;
	result.duration = duration + other.duration;
	return result;
}

timeDuration& timeDuration::operator+=(timeDuration& other)
{
	duration += other.duration;
	return *this;
}

timeDuration timeDuration::operator-(timeDuration& other)
{
	timeDuration result;
	result.duration = duration - other.duration;
	return result;
}

timeDuration& timeDuration::operator-=(timeDuration& other)
{
	duration -= other.duration;
	return *this;
}

std::string timeDuration::getStringTime()
{
	{
		std::string time = std::to_string(duration.count());
		return time;
	}
}

#ifdef __WORK_TIME_CLASS
timeDuration& timeDuration::operator=(workTime& other)
{
	duration = other.getDuration();
	return *this;
}

bool timeDuration::operator>(workTime& other)
{
	return duration > other.getDuration();
}

bool timeDuration::operator<(workTime& other)
{
	return duration < other.getDuration();
}

bool timeDuration::operator>=(workTime& other)
{
	return duration >= other.getDuration();
}

bool timeDuration::operator<=(workTime& other)
{
	return duration <= other.getDuration();
}

bool timeDuration::operator==(workTime& other)
{
	return duration == other.getDuration();
}

bool timeDuration::operator!=(workTime& other)
{
	return duration != other.getDuration();
}

timeDuration timeDuration::operator+(workTime& other)
{
	timeDuration result;
	result.duration = duration + other.getDuration();
	return result;
}

timeDuration timeDuration::operator-(workTime& other)
{
	timeDuration result;
	result.duration = duration - other.getDuration();
	return result;
}

timeDuration& timeDuration::operator+=(workTime& other)
{
	duration += other.getDuration();
	return *this;
}

timeDuration& timeDuration::operator-=(workTime& other)
{
	duration -= other.getDuration();
	return *this;
}
#endif // __WORK_TIME_CLASS
#endif // __TIME_DURATION_CLASS