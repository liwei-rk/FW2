/*
 * MongoUUID.c
 *
 *  Created on: 2012-9-26
 *      Author: Administrator
 */

#include "MongoUUID.h"
#include <stdlib.h>
#include <time.h>

const uint64_t DEC_FILL = 1000000000000000L; // 15 0s
const uint32_t DEC_RG_SHARD = 100000000;
const uint64_t DEC_MAX_SEC = 10000000L; // 7 0s
uint32_t __last_ts__ = 0;

uint64_t gen_mongo_uuid(uint32_t ts) {
	uint64_t ret = 0;
	uint64_t month = ts & 0xFFC00000L;
	uint64_t sec = ts & 0x3FFFFFL;

	/** DECIMAL **/
	uint32_t now = (uint32_t) time(NULL);
	if (__last_ts__ != now) {
		srand(now);
		__last_ts__ = now;
	}
	uint64_t rdshard = DEC_MAX_SEC * (uint64_t) (rand() % DEC_RG_SHARD);
	ret = (month >> 22) * DEC_FILL + rdshard + sec;

	return ret;
}
