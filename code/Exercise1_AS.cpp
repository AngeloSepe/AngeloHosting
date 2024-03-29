//* Author: Angelo M. Sepe
//* Date: 10/11/2019
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define max size arrays
#define max_entries 100
#define max_search_char 64

// Structures allocation
struct database {
char id [32];
char name[64];
char age[10]; // age taken as a string since it's easier to manipulate, can be converted to int when necessary
char data[512];	 	
};
struct database list[512]; // max allocation
// global variables
int entry_counter=0; // entries counter for max row lenght


// Function prototypes
void readinput();
void printList();
void search_entry();
void list_sorting();

// Main
int main(){
	
	char menu_option;

    printf(" Exercise #1 (Data read and manipulation)\n");
    printf("------------------------------------------\n\n");

    do{
    printf("Main Menu\n");
    printf("a. Load the CSV file (the first line must be a header).\n");
    printf("b. Print the list.\n");
    printf("c. Search for an entry.\n");
    printf("d. Sort the list options.\n");
    printf("e. Quit.\n");
    printf("Please enter an option from the main menu: ");
    scanf(" %c", &menu_option);
    switch(menu_option){

    case 'a':
		readinput();
		printf("---------------------------------------------------------------------------------\n\n");
		break;
	case 'b':
		system("@cls||clear");
		printList();
		printf("---------------------------------------------------------------------------------\n\n");
		break;
	case 'c':
		system("@cls||clear");
    	search_entry();
    	printf("---------------------------------------------------------------------------------\n\n");
    	break;
    case 'd':
    	system("@cls||clear");
		list_sorting();
		printf("---------------------------------------------------------------------------------\n\n");
		break;
		}
	}while(menu_option !='e');	
}

//Function to read csv
void readinput(){ 
FILE *myfile=fopen("DATA.csv","r");

	if (myfile == NULL){
		printf("Cant Read File \n");	
	}
	
	rewind(myfile);
	char myline[200];
	fgets(myline,1024,myfile);
	char* delimiter = ";";
	
	int i=0;
	entry_counter=0;
	for (char c=getc(myfile); c != EOF; c=getc(myfile)){
		if (c == '\n'){
			entry_counter++;
		}
	}
	if (entry_counter<2){printf("No entries in the File! \n");return;}
	else{system("@cls||clear");printf("CSV Data loaded. \n");}
	rewind(myfile);

	// read entries and header [0]
	while(fgets(myline,200,(FILE*)myfile) !=NULL ){
			strcpy(list[i].id,strtok(myline,delimiter));
			strcpy(list[i].name,strtok(NULL,delimiter));
			strcpy(list[i].age,strtok(NULL,delimiter));
			strcpy(list[i].data,strtok(NULL,delimiter));
			i++;
	}
	
	fclose(myfile);	
}

//Function to print csv at screen
void printList(){

printf("---------------------------------------------------------------------------------\n");
for (int i = 0; i <= entry_counter; i++){
    if (list[i].id != 0)
    printf("%s\t\t\t%s\t\t\t%s\t%s",list[i].id,list[i].name,list[i].age,list[i].data);
    else
        break;
    }
}

//Function to search in the database
void search_entry(){
	int index_list[max_search_char]; int index=0;
	char toSearch[max_search_char];
	int temp_idx=0;
	char Search_sel='0';
	int len;	
	
	printf("Press 1 to look up by ID or 2 by Name: ");
	scanf (" %c",&Search_sel);// get keyboard input
	

	switch(Search_sel)// loop the database with strcompare by case
	{ 
	
		case '1':
			printf("\nInsert ID to look up: ");		
			scanf (" %s",&toSearch);
			len=strlen(toSearch); 
			if (toSearch[len-1]=='\n'){
			toSearch[len-1]=0; // cut the new line after a string
			}
			for (int i = 1; i <= entry_counter; i++){ 
	     			if (strcmpi(list[i].id,toSearch)==0) {
	        		 index_list[index]=i;
	         		//printf("\nFound in entry n. %i and put in index_list n. %i",index_list[index],index);
	         		index++;
	    	 											}
			 }
	    	 break;
     
		 case '2':
	     	printf("\nInsert Name to look up: ");		
			scanf (" %s",&toSearch);
			len =strlen(toSearch); 
			if (toSearch[len-1]=='\n'){
			toSearch[len-1]=0; // cut the new line after a string
			}
	     	for (int i = 1; i <= entry_counter; i++){ 
		     	if (strcmpi(list[i].name,toSearch)==0) {
		         index_list[index]=i;
		         index++;
		     	}}
	     	break;
	     	
	    default:
	         printf("Invalid Query or No Data available\n" );
	         break;
			 }

	if (index==0){printf("Item Not found!\n" ); return;
	}
	if (index>0){// print table
	printf("\nFound %i items matching the query\n",index);
	printf("\n|%10s |%10s |%10s |%10s\n", list[0].id, list[0].name,list[0].age,list[0].data);
	printf("---------------------------------------------------------------------------------\n");
		for (int j=0; j<index; j++){	
			temp_idx=index_list[j];
	   		 printf("\n|%10s |%10s |%10s |%10s", list[temp_idx].id, list[temp_idx].name,list[temp_idx].age,list[temp_idx].data);
				}
	
				}
}

//Functin to sort list
void list_sorting(){
	char Sort_select='0';char Sort_select2='0';
	int n=entry_counter+1; // Max n. of entries from global
	int j; bool print_enable=false;
    database temp;
    
	printf("\nNumber of entries in the %i\n",n);
	printf("Select Sort Column, type 1 for ID or 2 to sort by Name:");
	scanf (" %c",&Sort_select);
	if (Sort_select=='1'){
	printf("Select Sort methods, type 1 for Ascending or 2 Descending:");
	scanf ("\n%c",&Sort_select2);}
	else if(Sort_select=='2'){ printf("Sorting NAME by ascending order...\n");}
	

switch (Sort_select){
	case '1': // ID sorting
		switch(Sort_select2){
			case '1': // ascending order
			    printf("Sorting ID by ascending order...\n");
				for(int i = 1; i < n; i++){
	        	j	 = i - 1;
	        	while( j > 0 && strcmp( list[j+1].id, list[j].id ) < 0 )
	        	{
	            temp =  list[j + 1];
	            list[j+1] = list[j];
	            list[j] = temp;
	            j--;
	        		}
    			}
    			print_enable=true;
    			break;
			case '2': // descending order
				printf("Sorting ID by descending order...\n");;
				for(int i = 1; i < n; i++){
	        	j	 = i - 1;
	        	while( j > 0 && strcmp( list[j+1].id, list[j].id ) > 0 )
	        	{
	            temp =  list[j + 1];
	            list[j+1] = list[j];
	            list[j] = temp;
	            j--;
	        		}
    			}
    			print_enable=true;
				break;
			default:
				printf("Invalid Selection!\n");	
				break;
		}
	break;	
	case '2': // Name Sorting (only ascending/alphabetically)	
				for(int i = 1; i < n; i++){
	        	j	 = i - 1;
	        	while( j > 0 && strcmp( list[j+1].name, list[j].name ) < 0 )
	        	{
	            temp =  list[j + 1];
	            list[j+1] = list[j];
	            list[j] = temp;
	            j--;
	        		}
    			}
    			print_enable=true;
		break;
	default :
		printf("\n Invalid Selection! or no data available\n");
		break;
}
    
if (print_enable){
	    printf("\n-------------------------------------------------------------------------------\n");
	    for(int i=0;i<=n;i++)
	    {
	        printf("%s\t\t\t%s\t\t\t%s\t%s",list[i].id,list[i].name,list[i].age,list[i].data);
	    }
	}
else{
	return;
}	
}






	

