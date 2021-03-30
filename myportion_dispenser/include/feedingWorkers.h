#ifndef FEEDING_WORKERS_H
#define FEEDING_WORKERS_H

#include "pes.h"
#include "auger.h"
#include "bowl.h"
#include "motors.h"
#include "dataStructs.h"

void handleIncrementalFeeding();
void dispenseInBowl(int bowlNumber, int numberOfPortions);
bool bowlIsFull();
void dispensePortion();
void moveToBowl(int bowlNumber);
int getCurrentPosition();
void bowlCounterClockWiseOneCompartment();
void bowlClockWiseOneCompartment();

void zeroBowl();

void handleIncrementalFeeding() {
    static int timeLastChecked = -1;
    if (timeLastChecked == -1)
    {   
        timeLastChecked = 0;
        // TODO
        // timeLastChecked = now;
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            int feedTime = dataValues.petSchedules[i].feedTimes[j].time;
            if (feedTime != -1 && (feedTime - timeLastChecked) > 0)
            {
                int numPortions = dataValues.petSchedules[i].feedTimes[j].numPortions;
                dispenseInBowl(i, numPortions);
            }
        }
    }
    // TODO Update time last checked
    // timeLastChecked = now;
}

bool CANCEL_DISPENSING = false;
bool IS_DISPENSING = false;

void dispenseInBowl(int bowlNumber, int numberOfPortions) {
    moveToBowl(bowlNumber);
    IS_DISPENSING = true;
    for (int i = 0; i < numberOfPortions; i++)
    {
        dispensePortion();
        if (bowlIsFull() || CANCEL_DISPENSING)
            break;
    }
    CANCEL_DISPENSING = false;
    moveToBowl(0);
    IS_DISPENSING = false;
}

bool bowlIsFull() {
    PESpending = false;
    if (getPESVal() == 1)
    {
        return true;
    }
    return false;
}

#define NUMBEROFSTEPSPERPORTION 50

void dispensePortion() {
    wakeSTPRs();
    fwdSTPRs();
    stpAGR(NUMBEROFSTEPSPERPORTION);
    slpSTPRs();
}

int numToMove(int destBowlNumber) {
    destBowlNumber - getCurrentPosition();
}
void moveToBowl(int bowlNumber) {
    if (numToMove(bowlNumber) == 0)
    {
        return;
    } else if (numToMove(bowlNumber) < 0) {
        do
        {
            bowlClockWiseOneCompartment();
        } while (numToMove(bowlNumber) != 0);
    } else if (numToMove(bowlNumber) > 0) {
        do
        {
            bowlCounterClockWiseOneCompartment();
        } while (numToMove(bowlNumber) > 0);
    }
}

/// 0 is blank, bowls 1-5
static int currentPosition = 0;

int getCurrentPosition() {
    return currentPosition;
}

#define NUMBEROFSTEPSPERCOMPARTMENT 25

void bowlCounterClockWiseOneCompartment() {
    wakeSTPRs();
    fwdSTPRs();
    stpBWL(NUMBEROFSTEPSPERCOMPARTMENT);
    slpSTPRs();
    currentPosition -= 1;
}

void bowlClockWiseOneCompartment() {
    wakeSTPRs();
    bwdSTPRs();
    stpBWL(NUMBEROFSTEPSPERCOMPARTMENT);
    slpSTPRs();
    currentPosition += 1;
}

void zeroBowl() {
    // TODO
}

#endif