

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    size_t dailyNeed,
    size_t maxShifts,
    int days, 
    int workers, 
    int dIndex, 
    int wIndex, 
    const AvailabilityMatrix& avail, 
    DailySchedule& sched, 
    vector<int> mTracker, 
    vector<int> nTracker);

bool isValid(
    size_t dailyNeed, 
    size_t maxShifts, 
    vector<int> mTracker, 
    vector<int> nTracker);

bool finalisValid(
    size_t dailyNeed, 
    size_t maxShifts, 
    vector<int> mTracker, 
    vector<int> nTracker);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    sched.resize(avail.size());
    vector<int> mTracker(int(avail[0].size()), 0);
    vector<int> nTracker(int(avail.size()), 0);
    return scheduleHelper(dailyNeed, maxShifts, nTracker.size(), mTracker.size(), 0, 0, avail, sched, mTracker, nTracker);        
}

bool scheduleHelper(
    size_t dailyNeed,
    size_t maxShifts,
    int days, 
    int workers, 
    int dIndex, 
    int wIndex, 
    const AvailabilityMatrix& avail, 
    DailySchedule& sched, 
    vector<int> mTracker, 
    vector<int> nTracker)
{
    if(dIndex == days-1 && wIndex == workers){
        return finalisValid(dailyNeed, maxShifts, mTracker, nTracker);
    }

    if(wIndex == workers){
        dIndex++;
        wIndex = 0;
    }

    if(avail[dIndex][wIndex] == 0){
        return scheduleHelper(dailyNeed, maxShifts, days, workers, dIndex, wIndex+1, avail, sched, mTracker, nTracker);
    }

    sched[dIndex].push_back(wIndex);
    nTracker[dIndex]++;
    mTracker[wIndex]++;
    if(isValid(dailyNeed, maxShifts, mTracker, nTracker)){
        if(scheduleHelper(dailyNeed, maxShifts, days, workers, dIndex, wIndex+1, avail, sched, mTracker, nTracker)){
            return true;
        }
    }
    sched[dIndex].pop_back();
    nTracker[dIndex]--;
    mTracker[wIndex]--;
    return scheduleHelper(dailyNeed, maxShifts, days, workers, dIndex, wIndex+1, avail, sched, mTracker, nTracker);

}

bool isValid(
    size_t dailyNeed, 
    size_t maxShifts,  
    vector<int> mTracker, 
    vector<int> nTracker)
{
    for(int i = 0; i < mTracker.size(); i++){
        if(mTracker[i] > maxShifts){
            return false;
        }
    }
    for(int i = 0; i < nTracker.size(); i++){
        if(nTracker[i] > dailyNeed){
            return false;
        }
    }
    return true;
}

bool finalisValid(
    size_t dailyNeed, 
    size_t maxShifts, 
    vector<int> mTracker, 
    vector<int> nTracker){
    for(int i = 0; i < mTracker.size(); i++){
        if(mTracker[i] > maxShifts){
            return false;
        }
    }
    for(int i = 0; i < nTracker.size(); i++){
        if(nTracker[i] != dailyNeed){
            return false;
        }
    }
    return true;
}
