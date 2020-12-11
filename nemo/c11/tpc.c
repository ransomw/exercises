#include <u.h>
#include <libc.h>
#include <thread.h>

/* this is a version of the bounded buffer problem from c10/pc.c
 * using the thread library.
 */

enum {Nmsgs = 4};

/* libthread's Channel is a bounded buffer.
 * the send() and recv() functions are used to write to and read from
 * the buffer.  like yield(), these functions also cause the thread
 * they're called from to cede control to another scheduled thread,
 * if any.
 */
Channel *bufc;

/* both send() and recv() expect message data locations to read or
 * write to as void pointers.  the channel has an associated message
 * size, so libthread can know how many bytes to read from or write to
 * the memory location specified by a void pointer.
 *
 * pointers may be sent through channels -- i.e. the void pointer may
 * by a pointer to a pointer -- to allow variable-sized messages.
 */
void
producer(void *arg)
{
	char *id = arg;
	char *msg;
	int i;

	for(i = 0; i < 5; i++) {
		msg = smprint("%s%d", id, i);
//		print("\nsending %s\n", msg);
		send(bufc, &msg);
//		print("\n%s sent\n", msg);
	}
	send(bufc, nil);
	threadexits(nil);
}

void
consumer(void *arg)
{
	char *id = arg;
	char *msg;
	do {
//		print("\n%s recving\n", id);
		recv(bufc, &msg);
		if(msg != nil) {
			print("%s%s ", id, msg);
			free(msg);
		}
	} while(msg != nil);
	threadexits(nil);
}

void
threadmain(int, char *[])
{
	/* channels are initilized with a message size and
	 * a buffer size (maximum number of messages)
	 */
	bufc = chancreate(sizeof(char *), Nmsgs);
	threadcreate(producer, "a", 8*1024);
	threadcreate(producer, "b", 8*1024);
	threadcreate(consumer, "x", 8*1024);
	consumer("y");
}
