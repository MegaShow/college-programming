// MegaShow
#include <sstream>
#include "Job.h"

int Job::number = 0;

Job::Job(int priority){
	this->priority = priority;
	this->id = number;
	number++;
	nextJob = NULL;
}

void Job::setId(int id){
	this->id = id;
}

int Job::getId() const{
	return id;
}

void Job::setPriority(int priority){
	this->priority = priority;
}

int Job::getPriority() const{
	return priority;
}

void Job::setNext(Job *job){
	nextJob = job;
}

Job *Job::getNext() const{
	return nextJob;
}

string Job::toString(){
	stringstream ss;
	ss << "[" << id << ":" << priority << "]";
	string str;
	ss >> str;
	return str;
}