#include<pthread.h>

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;
void* ServerCLien(char *client);
int counter =0;

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


void* ServeClient(char *client){
	
	char ch;
	FILE *fp;

	//---------------------------------------------------
	// This part opens a file and reads line by line the commands, think it just needs to be opened for reading though. Make sure to lock it to stop concurrency issues
	// TODO: Open the file and read commands line by line
	
	lock(&mutex1);
	counter++;
	//opens file ready for reading specified by the parameter input
	fp = fopen(client,"r");
	
	//reads one char from file
	ch = getc(fp);
	//while the char is not equal to the end of the file execute the loop
	while(ch != EOF){
		switch(ch) {
			//case "insertNode":
			//printf(client+ch+ theINteger);
			
			//case "deleteNode":
			
			//case "countNodes":
			
			//case "sumSubtree":
			
			default:
				printf("Invalid command");
		}
		printf("%d",ch);
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
	return NULL;
}
