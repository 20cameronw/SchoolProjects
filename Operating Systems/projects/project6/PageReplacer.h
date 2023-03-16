#ifndef PAGEREPLACER_H
#define PAGEREPLACER_H

#include <string>
#include <queue>

using namespace std;

//This is the header file for the PageReplacer Class
//This class is used to simulate different page replacement algorithms
//Algoritgms include: FIFO, LRU, OPT, and RAND
class PageReplacer
{
    private:
        string algorithmType;
        int numFrames;
        int *referenceArray;
        int referenceArraySize;
        int maxPageNumber;

        //helpers
        bool existsInQueue(queue<int>, int) const;
        bool existsInArray(int*, int) const;
        int findFutureIndex(int, int) const;

    public:
        //Constructor
        PageReplacer(string, int, string);
        //Destructor
        ~PageReplacer();

        //Setters
        void setAlgorithmType(string);
        void setNumFrames(int);
        void setReferenceArray(string);

        //Page replacement algorithms
        int FIFO(int) const;
        int LRU(int) const;
        int OPT(int) const;
        int RAND(int) const;

        //runner
        void run() const;
};

#endif // PAGEREPLACER_H