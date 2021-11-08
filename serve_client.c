#include<pthread.h>

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;
//pthread_rwlock_init(lock, NULL);

void *downtime(){

	sleep(1);
	//TODO: 1st downtime: Do balanceTree here
	//balanceTree();

	sleep(1);
	//TODO: 2nd downtime: Do balanceTree here
	//balanceTree();

	sleep(1);
	//TODO: 3rd downtime: Do balanceTree here
	//balanceTree();

	return NULL;
}

//commands:
//Locking a resource for writing using the function --------------------------------------------
//int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
//Unlock the resource for writing using the function -------------------------------------------
//int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
//To lock the resource only for reading and not writing we can use the function ----------------
//int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
//The lock for reading can be unlocked by the function------------------------------------------
//int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);

void* ServeClient(char *client){
	
	//locks for writing so only one client can write at a time
	int pthread_rwlock_wrlock(pthread_rwlock_t *lock);
	char ch;
	FILE *fp;
	//char *split;

	//---------------------------------------------------
	// This part opens a file and reads line by line the commands, think it just needs to be opened for reading though. Make sure to lock it to stop concurrency issues
	// TODO: Open the file and read commands line by line
	//opens file ready for reading specified by the parameter input
	fp = fopen(client,"r");
	
	//reads one char from file
	ch = getc(fp);
	//split = strtok(ch, " ");
	//while the char is not equal to the end of the file execute the loop
	while(ch != EOF){
		/*switch(split[0]) {
			case "insertNode":
			//printf(client+ch+ theINteger);
				printf("InsertNode");
				break;
			
			case "deleteNode":
				printf("DeleteNode");
				break;
			
			case "countNodes":
				printf("countNodes");
				break;
			
			case "sumSubtree":
				printf("sumSubtree");
				break;
			
			default:
				printf("Invalid command");
		}*/
		printf("%s",client);
		printf("%c",ch);
		ch = getc(fp);
	}
	
	//printf("%s ",client);
	//printf("%d ", ch);
	//printf("\n");

	// TODO: match and execute commands

	// TODO: Handle command: "insertNode <some unsigned int value>"
	// print: "[ClientName]insertNode <SomeNumber>\n"
	// e.g. "[client1_commands]insertNode 1\n"

	// TODO: Handle command: "deleteNode <some unsigned int value>"
	// print: "[ClientName]deleteNode <SomeNumber>\n"
	// e.g. "[client1_commands]deleteNode 1\n"

	// TODO: Handle command: "countNodes"
	// print: "[ClientName]countNodes = <SomeNumber>\n"
	// e.g. "[client1_commands]countNodes 1\n"


	// TODO: Handle command: "sumSubtree"
	// print: "[ClientName]sumSubtree = <SomeNumber>\n"
	// e.g. "[client1_commands]sumSubtree 1\n"

	fclose(fp);
	//when finished it unlocks for writing
	int pthread_rwlock_unlock(pthread_rwlock_t *lock);
	return NULL;
}
