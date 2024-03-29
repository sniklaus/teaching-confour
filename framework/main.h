#ifndef MAIN_H_LOCK
#define MAIN_H_LOCK

#include <assert.h>
#include <limits.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "cjson.h"
#include "mongoose.h"
#include <zmq.h> // sudo apt-get install -y libzmq3-dev

#include "four.h"
#include "test.h"
#include "webserver.h"
#include "zeromq.h"

extern int main_intWebserver;
extern int main_intZeromq;

static inline int minimum(int intA, int intB) {
    if (intA < intB) {
        return intA;
    }
    
    return intB;
}

static inline int maximum(int intA, int intB) {
    if (intA > intB) {
        return intA;
    }
    
    return intB;
}

static inline unsigned long long milliseconds() {
    struct timeval objTimeval = { };
    
    gettimeofday(&objTimeval, NULL);
    
    return (objTimeval.tv_sec * 1000) + (objTimeval.tv_usec / 1000);
}

#endif
