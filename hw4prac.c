#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


//structure prototype
struct address_t {
        int oct1;
        int oct2;
        int oct3;
        int oct4;
        char alias[10];
};


//global varibales, only 2 declared
struct address_t addressArray[100];
FILE *outputReport;


//user-defined functions
char *getDateAndTime();
void readDataFile();
void generateLocalityRpt(struct address_t addressArray[100], int amount);



//main function
int main() {

        //creating variables for main function
        char name[32];
        char named[80];
        FILE *filePointer;


        //take in user's name
        printf("Enter your name: ");
        fgets(name,sizeof(name),stdin);

        //redirecting name input into another variable
        sprintf(named,"%s", name);


	//using filePointer to open the locality report for writing
        filePointer=fopen("222_Locality_Report", "w");

        //return an error message if the file doesn't open properly
        if(filePointer==NULL) {
                printf("Error opening file: 222_Locality_report");
                return (1);
                                }


        //output statements for the file
        fprintf(filePointer,"%s%s", named, getDateAndTime());
        fprintf(filePointer, "CS222 Network Locality Report\n");
      


        fclose(filePointer);
        //fclose(inputReport);  
        readDataFile();


        return (0);
}


void readDataFile() {
        FILE *inputReport;
        FILE *write;
        int i = 0, j = 0, k= 0, z;
     
        char talias[10];
	char ip[64];
        int tip[4] = {0};
        static struct address_t addressArray[100];

	//open Cs222_Inet.txt for reading
        inputReport=fopen("CS222_Inet.txt", "r");
	//open 222_Locality_Report for appending
        write=fopen("222_Locality_Report", "a");

       
   
	//loop until the end of file is reached
	while(fgets(ip, sizeof ip, inputReport) != NULL) {
		
		
		//scan method used to parse data read from file
		sscanf(ip, "%d.%d.%d.%d %s", tip, tip+1, tip+2, tip+3, talias);

		//to make sure that it is not reading the sentinel record
		if((tip[0]!=0) && (tip[1] != 0)) {
			addressArray[k].oct1 = tip[0];	
			addressArray[k].oct2 = tip[1];
			addressArray[k].oct3 = tip[2];
			addressArray[k].oct4 = tip[3];
			strcpy(addressArray[k].alias , talias);
		
		}
		//increment
		k++;
	}
	//calling the generateLocalityRpt function
	generateLocalityRpt(addressArray, k-1);
}

void generateLocalityRpt(struct address_t addressArray[100], int amount) {
	int i = 0, j = 0, counter=0, local = 0, k=0, kcount = 0;
	int val1, val2, idx = 0;
	int larray[amount][2];
	
	//opening 222_Locality_Report for appending
	outputReport = fopen("222_Locality_Report", "a");


	//put total amounts into the file
        fprintf(outputReport, "Address total: %d\n", amount);
        
	
	//for loop to check how many values are distinct
	for (i=0; i< amount; i++) {
	
		counter = 0; //reset the counter
		for (j = i+1; j<amount; j++) {

			//comparison of first two integers of the addresses
			if((addressArray[j].oct1 == addressArray[i].oct1) &&
				(addressArray[j].oct2 == addressArray[i].oct2)) {
					counter++; //add to the counter if there's a match
			}
		}

		//if the counter remained zero, add to local
		if(counter == 0) {
			local++;
		}		
	}

	//add localities amount into file
        fprintf(outputReport, "Localities: %d\n\n", local);
				
	//trying out to find distinct vals for larray
	larray[0][0] = addressArray[0].oct1;
	larray[0][1] = addressArray[0].oct2;

	//iterate to compare the addressArray with the larray(2d)
	for(i=1; i<amount; i++) {
		idx = 0;
		for(j=0; j<amount; j++) {
			//if both the first two integers are a match
			if((addressArray[i].oct1 == larray[j][0]) && 
				(addressArray[i].oct2 == larray[j][1])) {
					//printf("Locality already in\n");
					//printf("%d.%d\n", larray[j][0], larray[j][1]);
					idx++;
					break;
		}
		}

		//if the index counter remained 0, add to larray
		if(idx == 0) {
			larray[i][0] = addressArray[i].oct1;
			larray[i][1] = addressArray[i].oct2;
		}
			
	}

	
		
	int counta;
	//new loop to make sure the locality is not empty	
	for(i=0; i < amount; i++) {
		
		counta = 0;
		for(j=0; j<amount; j++) {
			//here, increase the counter if a match is found in larray
			if((larray[i][0] == addressArray[j].oct1) &&
				larray[i][1] == addressArray[j].oct2) {
					counta++;

					//if the counter is just 1, print the locality
					if(counta == 1) {
						fprintf(outputReport, "%d.", larray[i][0]);
						fprintf(outputReport, "%d\n", larray[i][1]);						}
					//then print out aliases, if bigger than 0
					fprintf(outputReport, "%s\n", addressArray[j].alias);
					}
			
				}
		//extra statement so space is not added for empty localities
		if(counta > 0) {
			fprintf(outputReport, "\n");
		}
		
				}
	


	/*
	//this is my original output function
	//does not only take distinct elements
	for(i=0;i < amount; i++) {

		//initializing some values
		val1 = addressArray[i].oct1;
		val2 = addressArray[i].oct2;
		kcount = 0;
		

			
		//print into file the locality (not distinct)
       	        fprintf(outputReport, "%d", addressArray[i].oct1);
       	        fprintf(outputReport, ".");
       	        fprintf(outputReport, "%d\n", addressArray[i].oct2);
       	       
		//loop for if the locality matches
		for(j=0; j<amount; j++) {
			
			//if it is a match, print the alias to the file
			if((val1 == addressArray[j].oct1) &&
				(val2 == addressArray[j].oct2)) {
					fprintf(outputReport, "%s\n", addressArray[j].alias);
			}
	}
	fprintf(outputReport,"\n");	
	}*/	
	

	fclose(outputReport);
}


//time function to return the current time
char *getDateAndTime() {
        time_t t;
        time(&t);
        return ctime(&t);
}


