/*
 * declaration for class Job..
 */
#ifndef JOB_H

#include<string>
using namespace std;

class Job {
    public:
        explicit Job(int priority = 0);
        void setId(int id);
        int getId() const;
        void setPriority(int priority);
        int getPriority() const;
        void setNext(Job *job);
        Job *getNext() const;
        string toString();
    private:
        static int number;
        int id;
        int priority;
        Job *nextJob;
};

#endif
