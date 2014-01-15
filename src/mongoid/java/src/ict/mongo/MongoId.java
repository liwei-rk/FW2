package ict.mongo;

import java.util.Random;

public class MongoId {

	/**
	 * 
	 * @param timestamp
	 *            32-bit epoch timestamp /seconds
	 * @return
	 */
	public static long genMongoUUID(long timestamp) {
		long month = timestamp & 0xFFC00000L;
		long ret = 0;
		long sec = timestamp & 0x3FFFFFL;

		/** DECIMAL **/
		long rdshard = DEC_MAX_SEC * (long) random(DEC_RG_SHARD);
		ret = (month >>> 22) * DEC_FILL + rdshard + sec;

		return ret;
	}

	static final long DEC_FILL = 1000000000000000L;
	static final int DEC_RG_SHARD = 100000000;
	static final long DEC_MAX_SEC = 10000000L; // 7 0s

	static final Random rand = new Random();

	private synchronized static int random(int max) {
		return rand.nextInt(max);
	}
}
