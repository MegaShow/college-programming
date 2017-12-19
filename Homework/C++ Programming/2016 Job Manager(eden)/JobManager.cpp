// MegaShow
#include <string>
#include "JobManager.h"
using namespace std;

JobManager* JobManager::instance = NULL;

JobManager* JobManager::getInstance(){
	if(instance == NULL){
		instance = new JobManager();
	}
	return instance;
}

bool JobManager::deleteInstance(){
	if(instance == NULL)
		return false;
	delete instance;
	instance = NULL;
	return true;
}

void JobManager::addJob(int priority){
	Job* p = jobFrontPointer;
	if(p == NULL){
		jobFrontPointer = new Job(priority);
		return;
	}
	while(p->getNext() != NULL)
		p = p->getNext();
	p->setNext(new Job(priority));
}

void JobManager::finishOneJob(){
	if(jobFrontPointer == NULL)
		return;
	Job* tmp = jobFrontPointer;
	jobFrontPointer = jobFrontPointer->getNext();
	delete tmp;
}

void JobManager::sortJob(){
	for(Job* i = jobFrontPointer; i->getNext() != NULL; i = i->getNext()){
		Job* max = i;
		for(Job* j = i->getNext(); j != NULL; j = j->getNext()){
			if(max->getPriority() < j->getPriority())
				max = j;
			else if(max->getPriority() == j->getPriority() && max->getId() > j->getId())
				max = j;
		}
		int var = max->getPriority();
		max->setPriority(i->getPriority());
		i->setPriority(var);
		var = max->getId();
		max->setId(i->getId());
		i->setId(var);
	}
}

void JobManager::printJob(){
	string str;
	Job* p = jobFrontPointer;
	if(p == NULL){
		cout << "empty!" << endl;
		return;
	}
	while(p->getNext() != NULL){
		str += p->toString();
		str += "->";
		p = p->getNext();
	}
	str += p->toString();
	cout << str << endl;
}

int JobManager::getNumOfJob(){
	int var = 0;
	for(Job* p = jobFrontPointer; p != NULL; p = p->getNext())
		var++;
	return var;
}

void JobManager::clear(){
	Job* p = jobFrontPointer;
	while(p != NULL){
		Job* tmp = p;
		p = p->getNext();
		delete tmp;
	}
	jobFrontPointer = NULL;
}

JobManager::~JobManager(){
	clear();
}

JobManager::JobManager(){
	if(instance == NULL){
		instance = this;
		jobFrontPointer = NULL;
	}
}

JobManager::JobManager(const JobManager & j){
	return;
}
  
void JobManager::operator=(const JobManager & j){
	return;
}
