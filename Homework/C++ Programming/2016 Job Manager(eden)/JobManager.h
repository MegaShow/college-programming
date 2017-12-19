#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <iostream>
#include "Job.h"

// disallow copy constructor and assignment operator
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

class JobManager {
    public:
        // get the unique instance
        static JobManager* getInstance();
        static bool deleteInstance();

        void addJob(int priority = 0);
        void finishOneJob();
        void sortJob();
        void printJob();
        int getNumOfJob();
        void clear();

    private:
        Job * jobFrontPointer;
        ~JobManager();
        JobManager();
        static JobManager* instance;
        DISALLOW_COPY_AND_ASSIGN(JobManager);
};

#endif
