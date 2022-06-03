#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct list {
 	char word[20];
	int piece;
	struct list *next;
};
typedef struct list List;

void readFile(char current[]);
void getWord(char text[],List **headOfList);
void controlText(char word[],List **headOfList);
void addList(char word[],int numberCounter,List **headOfList);
void printList(List* headOfList);
int searchText(char word[],List* headOfList);
void addListHead(List* newWords,List **headOfList);
void addListEnd(List* newWords,List *currentList);
void addListBetwenn(List* newWords,List *currentList);

char text[100];

int main(){
	List *headOfList = NULL;
	readFile(text);
	/*	
	// print full text ---
	int i ;
	while(text[i] !='\0'){
		printf("%c",text[i]);
		i++;
	}
	// print full text ---
	*/
	getWord(text,&headOfList);
	printList(headOfList);
	return 0;
}

void readFile(char text[]){
	FILE *readd = NULL;
	int i  = 0;
	int counter = 0;
	char word;
	if((readd = fopen("text.txt","r")) != NULL){
		while(!feof(readd)){
			fscanf(readd,"%c",&word);
			if(word >='A' &&  word <= 'Z'){ // Down Casing
				word = word +32;
			}
			text[i] = word;
			i++;	
		}
		
	}else{
		printf("The file could not be raed!!\n");
		fclose(readd);
		exit(EXIT_FAILURE);
	}
	
	
}

void getWord(char text[],List **headOfList){
	int i = 0;
	int j = 0;
	char word[20];
	while(text[i] != '\0'){
		if(text[i+1] == ' '){
			word[j]=text[i];
			word[j+1] = '\0';
			j = 0;
			controlText(word,headOfList); // read word and check text
		}else{
			if(text[i] != ' ' && text[i+1] != '\0'){
				word[j] = text[i];
				j++;	
			}
		}
		i++;
	}
}


void controlText(char word[],List **headOfList){
	char tempText[20];
	int i = 0;
	int j = 0;
	int numberCounter = 0;
	int counter = 0;
	while(text[i] != '\0'){  
		if(text[i+1] == ' '){
			tempText[j]=text[i];
			tempText[j+1] = '\0';
			j = 0;
			if(strcmp(tempText,word) == 0){ 
				numberCounter++; 
			}
		}else{
			if(text[i] != ' '){
				tempText[j] = text[i];
				j++;	
			}
		}
		i++;
	}
	if(searchText(word,*headOfList) == 0){ //  first add list word
		addList(word,numberCounter,headOfList); // add list
	}
}

void addList(char word[],int numberCounter,List **headOfList){
	List *currentList = (*headOfList); 
	List *newWords = (List*)malloc(sizeof(List)); 
	strcpy(newWords->word,word); 
	newWords->piece = numberCounter; 
	if(currentList == NULL){ // list equals empty 
			addListHead(newWords,headOfList);
    }else if (currentList -> next == NULL){ // list include 1 word
		if(currentList -> piece > numberCounter){ 
			addListEnd(newWords,currentList); // list add end 
		}else if(currentList -> piece < numberCounter){
			addListHead(newWords,headOfList); // list add first
		}
	}else{ // list more word include
		while(currentList !=NULL){
			if(currentList->piece > numberCounter ){ // 
				if(currentList -> next != NULL && currentList -> next -> piece < numberCounter){
					addListBetwenn(newWords,currentList);  
					break;
				}else if(currentList -> next != NULL && currentList -> next -> piece  ==  numberCounter){ 
					while( currentList -> next != NULL && currentList -> next -> piece == numberCounter  ){
						currentList = currentList -> next;
					}
			
					if(currentList -> next  == NULL){ 
						addListEnd(newWords,currentList); 
					}else{
						addListBetwenn(newWords,currentList); 
					}
					break;
				
				}else if(currentList -> next == NULL){
					addListEnd(newWords,currentList);
					break;
				}
			}else if (currentList -> piece  == numberCounter){ 
				while( currentList -> next != NULL && currentList -> next -> piece == numberCounter  ){ 
					currentList = currentList -> next;
				}
				if(currentList -> next  == NULL){
					addListEnd(newWords,currentList);
				}else{
					addListBetwenn(newWords,currentList); 
				}
				break;
			}else{
				addListHead(newWords,headOfList); 
				break;
			}
			currentList = currentList->next;
			}
		}
}
	
void addListHead(List* newWords,List **headOfList){
	if((*headOfList) == NULL){ 
		newWords->next = NULL; 
		(*headOfList) = newWords;
	}else{
		newWords->next = (*headOfList); 
		(*headOfList)= newWords;
	}
}

void addListEnd(List* newWords,List *currentList){
	newWords->next = NULL;
	currentList -> next = newWords;
}

void addListBetwenn(List* newWords,List *currentList){
	newWords -> next = currentList -> next;
	currentList -> next= newWords;
}

int searchText(char word[],List *headOfList){
	List *currentList = headOfList;
	while(currentList!= NULL && strcmp(currentList->word,word) != 0){
		currentList = currentList->next;
	}
	if(currentList == NULL){ 
		return 0; 
	}else{
		return -1; 
	}
}

void printList(List* headOfList){
	List* currentList = headOfList;
	int i;
	int counter = 1;
	//printf("\n");
	while(currentList !=NULL){
		printf("%d. ",counter);
		for(i = 0;i<strlen(currentList->word);i++){
		printf("%c",currentList->word[i]);
		}
		printf(":%d\n",currentList->piece);
		currentList = currentList -> next;
		counter++;
	}
}
