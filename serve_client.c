#include<pthread.h>
pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER;


void *downtime(){

	sleep(1);
	//TODO: 1st downtime: Do balanceTree here
	root_balanced = balanceTree(root);
	freeSubtree(root);
	root = root_balanced;
	freeSubtree(root_balanced);
	

	sleep(1);
	//TODO: 2nd downtime: Do balanceTree here
	root_balanced = balanceTree(root);
	freeSubtree(root);
	root = root_balanced;
	freeSubtree(root_balanced);

	sleep(1);
	//TODO: 3rd downtime: Do balanceTree here
	root_balanced = balanceTree(root);
	freeSubtree(root);
	root = root_balanced;
	freeSubtree(root_balanced);
	

	return NULL;
}


//STUFF FROM WEEK 4 POWERPOINTS
//for just reading: pthread_rwlock_rdlock(&lock);
//for read-write access: pthread_rwlock_wrlock(&lock);
//for unlocking: pthread_rwlock_unlock(&lock);

//read lock is used for functions that don't modify the BST
//write lock is used for functions that do modify the BST

void* ServeClient(char *client){
	char ch;
	FILE *fp;
	
	
	//---------------------------------------------------
	// This part opens a file and reads line by line the commands, think it just needs to be opened for reading though. Make sure to lock it to stop concurrency issues
	// TODO: Open the file and read commands line by line
	//opens file ready for reading specified by the parameter input
	fp = fopen(client,"r");
	
	//checks a file has been opened
	if(fp==NULL){
		printf("Cannot open files\n");
		exit(-1);	
	}
	
	//locks for writing
	//pthread_rwlock_wrlock(&lock);
	
	//this is the read lock
	pthread_rwlock_rdlock(&lock);
	ch = getc(fp);
	pthread_rwlock_unlock(&lock);
	
	char num[40];
	char str[40];
	int i;
	int j;
	//while the char is not equal to the end of the file execute the loop
	//printf("%s ", client);
	
	//in this part I need to split up char into "insertNode" and 1 so then it can be called as insertNode(root, 1); and same for other functions
	//gets individual characters so "i" "n" "s" "e" "r" "t" etc
	
	while(ch != EOF){
		//printf("%c", ch);
		//checks if char is a letter, adds to letter array
		if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ){
			str[i] = ch;
			i++;
		}
		//checking if char is a number. Adds to number array
		else if(ch >= '0' && ch <= '9'){
			num[j] = ch;
			j++;
		}
		else if(ch == ' '){
			str[i] = '\0';
			i++;
		}
		//if char is the end of the line then execute the command
		else if(ch == '\n'){
		        num[j] = '\0';
		        j++;
			if(strcmp(str,"insertNode")==0){
				pthread_rwlock_wrlock(&lock);
				int y = atoi(num);
				/*if(root == NULL){
					printf("IT IS NULL BEFORE");
					//root = insertNode(root, y);
				}
				else{
					insertNode(root, y);
				}*/
				insertNode(root,y);
				//printf("HERE");
				printf("[%s]insertNode %u\n",client,y);
				pthread_rwlock_unlock(&lock);
			}
			else if(strcmp(str,"deleteNode")==0){
				pthread_rwlock_wrlock(&lock);
				int y = atoi(num);
				deleteNode(root, y);	
				printf("[%s]deleteNode %u\n",client,y);
				pthread_rwlock_unlock(&lock);
			}
			else if(strcmp(str,"countNodes")==0){
				pthread_rwlock_rdlock(&lock);
				int c = countNodes(root);
				printf("[%s]countNodes = %u\n",client,c);
				pthread_rwlock_unlock(&lock);
			}
			else if(strcmp(str,"sumSubtree")==0){
				pthread_rwlock_rdlock(&lock);
				int s = sumSubtree(root);
				printf("[%s]sumSubtree = %u\n",client,s);
				pthread_rwlock_unlock(&lock);
			}
			else{
				//printf("INVALID");
			}
			i=0;
			j=0;
			strcpy(str, "");
			strcpy(num, "");
		}
	        pthread_rwlock_rdlock(&lock);
		ch = getc(fp);
		pthread_rwlock_unlock(&lock);
	}
	//unlocks
	//pthread_rwlock_unlock(&lock);
	
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
