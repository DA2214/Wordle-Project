#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shifts,
    size_t day,
    size_t slot
);

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
    size_t n = avail.size();
    size_t k = avail[0].size();

    sched = DailySchedule(n, vector<Worker_T>(dailyNeed, INVALID_ID));
    vector<size_t> shifts(k, 0);

    if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0)){
        return true;
    } else {
        sched.clear();
        return false;
    }


}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shifts,
    size_t day,
    size_t slot
)
{
    size_t n = avail.size();
    size_t k = avail[0].size();

    //sched.size might not be correct
    if (day == n) return true;

    if (slot == dailyNeed) return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);

    for (size_t i = 0; i < k; ++i){
        if (!avail[day][i]) continue;
        if (shifts[i] >= maxShifts) continue;
        if (find(sched[day].begin(), sched[day].begin() + slot, i) != sched[day].begin() + slot) continue;

        sched[day][slot] = i;
        shifts[i]++;
        
        if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day, slot + 1)){
            return true;
        }

        shifts[i]--;
    }

    return false;
}

