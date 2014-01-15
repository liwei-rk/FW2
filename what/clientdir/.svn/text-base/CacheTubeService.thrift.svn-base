namespace cpp cachetube.thrift
namespace java cachetube.thrift


struct Message {
	1: string queue_name,   /* message topic */ 
	2: i64 message_id,      /* message ID (is string type in TimeTunnel) */
	3: string source_ip,    /* message source IP */
	4: i64 created_time,    /* message created time */
	5: string content = "", /* message content */
}

exception Failure {
	1: i32 error_code,       /* error_code, 0 for normal exit */
	2: string description,   /* error description */
}

service CacheTubeService {
	void post(1:string queue_name, 2:list<Message> messages) throws (1:Failure f),
	list<Message> get(1:string queue_name) throws (1:Failure f),
}
