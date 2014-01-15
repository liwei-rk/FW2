/*
 * test.c
 *
 *  Created on: 2012-9-26
 *      Author: Administrator
 */

#include "MongoUUID.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
	uint32_t ts = time(NULL);
	int i = 0;
	for (; i < 50; i++) {
		printf("ts = %d, uuid = %ld\n", ts, gen_mongo_uuid(ts));
		printf("ts = %d, uuid = %ld\n", ts, (long long)gen_mongo_uuid(ts));
		ts += rand() % 30;
	}
	return 0;
}
