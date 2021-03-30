#ifndef DATA_STRUCTS_H
#define DATA_STRUCTS_H

typedef struct feedTime
{
    int time = -1;
    int numPortions = -1;
};

typedef struct petSchedule
{
    int tagID = 0;
    feedTime feedTimes[5];
};

struct dataFromDatabase {
    long int feederId; // TODO PULL THE Serial from the same place the Wifi pulls it.
    petSchedule petSchedules[5];
} dataValues;

#endif