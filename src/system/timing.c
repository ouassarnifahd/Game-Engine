#include "system/timing.h"

timer timer_start(int id, const char* tag) {
    timer t;
    t.id = id;
    t.start = SDL_GetTicks();
    t.split = SDL_GetTicks();
    t.end = 0;
    debug("Timer %d '%s' Start: %f", id, tag, 0.0f);
    return t;
}

timer timer_split(timer t, const char* tag) {
    long curr = SDL_GetTicks();
    double difference = (double)(curr - t.split) / 1000.0;
    debug("Timer %d '%s' Split: %f", t.id, tag, difference);
    t.split = curr;
    return t;
}

timer timer_stop(timer t, const char* tag) {
    long curr = SDL_GetTicks();
    double difference = (double)(curr - t.start) / 1000.0f;
    debug("Timer %d '%s' End: %f", t.id, tag, difference);
    t.end = SDL_GetTicks();
    return t;
}

static int timestamp_counter = 0;

void timestamp(char* out) {
    time_t ltime;
    struct tm *time_val;
    ltime = time(NULL);
    time_val = localtime(&ltime);
    sprintf(out, "%d%d%d%d%d%d%d", time_val->tm_mday, time_val->tm_mon, time_val->tm_year, time_val->tm_hour, time_val->tm_min, time_val->tm_sec, timestamp_counter);
    timestamp_counter++;
}
