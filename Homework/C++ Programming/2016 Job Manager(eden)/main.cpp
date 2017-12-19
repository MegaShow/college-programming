#include "JobManager.h"
using namespace std;

int main() {
    JobManager *manager1 = JobManager::getInstance();
    JobManager *manager2 = JobManager::getInstance();
    int pris[5] = {234, 23, 23432, 1, 5};
    for (int i = 0; i < 5; i++) {
        manager1->addJob(pris[i]);
    }
    manager2->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager1->finishOneJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager2->finishOneJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager1->addJob();
    manager1->addJob(6666);
    manager1->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;
    manager2->clear();
    manager1->printJob();
    cout << "The number of job is: " << manager1->getNumOfJob() << endl;

    int jobNum, jobPriority, deleteNum;
    cin >> jobNum;
    for (int i = 0; i < jobNum; i++) {
        cin >> jobPriority;
        manager2->addJob(jobPriority);
    }
    manager1->sortJob();
    manager2->printJob();
    cin >> deleteNum;
    while (deleteNum--) {
        manager1->finishOneJob();
    }
    manager1->printJob();
    cout << "The number of job is: " << manager2->getNumOfJob() << endl;

    if (JobManager::deleteInstance()) cout << "Delete successfully!\n";
    else cout << "Delete failure!\n";

    if (JobManager::deleteInstance()) cout << "Delete successfully!\n";
    else cout << "Delete failure!\n";
}

