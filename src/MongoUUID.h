/*
 * MongoUUID.h
 *
 *  Created on: 2012-9-26
 *      Author: Administrator
 */

#ifndef MONGOUUID_H_
#define MONGOUUID_H_

#include <stdint.h>

/**
 *@param timestamp: epoch timestamp
 *@return 64-bit uuid
 */
uint64_t gen_mongo_uuid(uint32_t timestamp);

#endif /* MONGOUUID_H_ */
