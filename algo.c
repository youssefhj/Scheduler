#include <stdio.h>
#include <stdlib.h>
#include "algo.h"

/*
 *****************************
 **  Function Implemtation  **
 *****************************
 */


/*
 * Return TRUE if the two string passed as a parameter are matching
 * Otherwise it return FALSE
 */
Boolean areStringMatching(char* optionString,char *algo)
{
	char *pOtString,*pAlgo;

	toLowerCase(optionString);

	for(pOtString = optionString , pAlgo = algo ; *pAlgo != '\0' ; pOtString++ ,pAlgo++)
		if(*pOtString != *pAlgo )
			return FALSE;

	return TRUE;
}



/*
 * Add all the process data in the end of the linkedList ..
 * if algo parametre match the 'ppf' then we add priority..
 * It return a pointer of the first node ..
 */
ProcessInfo * addProcessInfo(ProcessInfo *head,char *algo)
{
	ProcessInfo *pHead = head;
	ProcessInfo *newNoeud = NULL;

	//ALLOCATION FOR newNoeud
	newNoeud = (ProcessInfo *)calloc(1,sizeof(ProcessInfo));

	puts("\t\t********** Enter all process information **********  \n");
	printf("(1) *Process Name : ");
	scanf(" %c",&newNoeud->processName);

	//Convert the process name into upperCase ..
	if(newNoeud->processName >= 'a' && newNoeud->processName <= 'z')
		newNoeud->processName -= 32;

	printf("\n(2) *Execution Time : ");
	scanf("%d",&newNoeud->executionTime);

	printf("\n(3) *Arrival Date :");
	scanf("%d",&newNoeud->arrivalDate);

	if(areStringMatching(algo,"-ppf"))
	{
		printf("\n(4) *Priority : ");
		scanf("%d",&newNoeud->priority);
	}


	system("clear");

	newNoeud->nextProcessInfo = NULL;

	if(head == NULL)
		return newNoeud;

	while(pHead->nextProcessInfo != NULL)
		pHead = pHead->nextProcessInfo;


	pHead->nextProcessInfo = newNoeud;

	return head;

}


/*
 * Sort happen according to the algo String :
 * 		if algo is fcfs then sort by arrival date ..
 * 		if algo is sjf  then sort by execution time ..
 * 		if algo is ppf then  sort by  priority ..
 *
 * Return a pointer of the first node ..
 *
 * This function do up sorting ..
 */
void sortByAlgoChoise(ProcessInfo *firstNode ,ProcessInfo *lastNode,char* algo)
{
	ProcessInfo *pNext,*pPrevious;

	pPrevious = firstNode;



	while((pPrevious->nextProcessInfo) != lastNode)
	{
		pNext = pPrevious->nextProcessInfo;

		ProcessInfo *tmpNoeud = NULL;

		//ALLOCATION FOR tmpNoeud
		tmpNoeud = (ProcessInfo *)calloc(1,sizeof(ProcessInfo));

		while(pNext != lastNode)
		{


			if((pPrevious->arrivalDate) > (pNext->arrivalDate) && areStringMatching(algo,"fcfs"))
			{
				tmpNoeud->processName = pNext->processName;
				tmpNoeud->arrivalDate = pNext->arrivalDate;
				tmpNoeud->executionTime = pNext->executionTime;

				pNext->processName = pPrevious->processName;
				pNext->arrivalDate = pPrevious->arrivalDate;
				pNext->executionTime = pPrevious->executionTime;

				pPrevious->processName = tmpNoeud->processName;
				pPrevious->arrivalDate = tmpNoeud->arrivalDate;
				pPrevious->executionTime =  tmpNoeud->executionTime ;


			}
			if(( (pPrevious->executionTime) > (pNext->executionTime) ) && areStringMatching(algo,"sjf"))
			{


				tmpNoeud->processName = pNext->processName;
				tmpNoeud->arrivalDate = pNext->arrivalDate;
				tmpNoeud->executionTime = pNext->executionTime;

				pNext->processName = pPrevious->processName;
				pNext->arrivalDate = pPrevious->arrivalDate;
				pNext->executionTime = pPrevious->executionTime;

				pPrevious->processName = tmpNoeud->processName;
				pPrevious->arrivalDate = tmpNoeud->arrivalDate;
				pPrevious->executionTime =  tmpNoeud->executionTime;


			}
			if((pPrevious->priority) > (pNext->priority) && areStringMatching(algo,"ppf"))
			{
				tmpNoeud->processName = pNext->processName;
				tmpNoeud->arrivalDate = pNext->arrivalDate;
				tmpNoeud->executionTime = pNext->executionTime;
				tmpNoeud->priority = pNext->priority;

				pNext->processName = pPrevious->processName;
				pNext->arrivalDate = pPrevious->arrivalDate;
				pNext->executionTime = pPrevious->executionTime;
				pNext->priority = pPrevious->priority;

				pPrevious->processName = tmpNoeud->processName;
				pPrevious->arrivalDate = tmpNoeud->arrivalDate;
				pPrevious->executionTime =  tmpNoeud->executionTime ;
				pPrevious->priority = tmpNoeud->priority;


			}
			pNext = pNext->nextProcessInfo;

		}
		pPrevious = pPrevious->nextProcessInfo;
	}

}


/*
 * Diplay the Gantt chart according to scheduling policy ..
 */
void displayGanttChart(ProcessInfo *head,char * algo)
{

	ProcessInfo *pHead = head;
	int numAxeTime,position;

	position = 0;

	numAxeTime = head->arrivalDate;

	char *axeProcessString = (char *)calloc(1,sizeof(char *));


	while(pHead != NULL)
	{

		*(axeProcessString + position) = '|';
		int dec = pHead->executionTime;

		while(dec)
		{
			position++;
			axeProcessString = (char *)realloc(axeProcessString,(position + 1)*sizeof(char ));
			*(axeProcessString + position) = pHead->processName;
			dec--;
		}
		position++;
		axeProcessString = (char *)realloc(axeProcessString,(position + 1)*sizeof(char ));
		pHead = pHead->nextProcessInfo;
	}

	*(axeProcessString + position ) = '|';
	*(axeProcessString + (position + 1) ) = '\0';

	if(areStringMatching(algo,"fcfs"))
		printf("#        GANTT CHART : First Come First Served       #\n\n");

	else
		if(areStringMatching(algo,"sjf"))
			printf("#           GANTT CHART : Short Job First           #\n\n");

		else
			printf("#        GANTT CHART : Pririty Process First        #\n\n");



	printf("\t\t%s\n",axeProcessString);

	char *pAxeProcessString = axeProcessString;

	pHead = head;


	printf("\t\t%d", numAxeTime);

	pAxeProcessString++;
	position = 1;

	while(pHead != NULL)
	{


		numAxeTime = pHead->executionTime + numAxeTime;
		for(pAxeProcessString = axeProcessString + position  ; *pAxeProcessString !='\0'; pAxeProcessString++,position++)
		{
			if(*pAxeProcessString != '|'){
				printf("%c",32);

			}
			else{
				printf("%d", numAxeTime);
				position++;
				break;
			}
		}

		pHead = pHead->nextProcessInfo;

	}
	printf("\n\n");

}


/*
 * Display the Performance Criteria of the Shulder Algo ..
 */
void diplayWaitingResponeTime(ProcessInfo *head)
{

	ProcessInfo *pHead = head;
	float trm,tam;
	int howManyProcess = 0;

	trm = tam = 0;

	printf("#                 Performance  Criteria             #\n\n");
	printf("##############################################################\n");
	printf("#  Process Name   |     Response Time   |     Waiting Time   #\n");
	printf("##############################################################\n");
	while(pHead != NULL)
	{

		printf("+        %c         |          %d          |           %d       +\n",pHead->processName,pHead->responseTime,pHead->waitingTime);
		printf("+------------------------------------------------------------+\n");
		trm += pHead->responseTime;
		tam += pHead->waitingTime;
		howManyProcess++;
		pHead = pHead->nextProcessInfo;
	}

	trm = trm/howManyProcess;
	tam = tam/howManyProcess;

	printf("\n\t** TRM = %.2f\t ; ** TAM  = %.2f\n",trm,tam);

}


/*
 * Display Process info enter by user ..
 * Process Name , Execution Time , Arrival Time
 * ?Optinnal >> Priority (according to scheduling policy)
 */
void displayProcessInfo(ProcessInfo *head, char * algo)
{


	ProcessInfo *pHead = head;

	printf("#                  Process Table                    #\n\n");
	if(!areStringMatching(algo,"-ppf")){
		printf("##############################################################\n");
		printf("#  Process Name     |     Execution Time   |  Arrival Time   #\n");
		printf("##############################################################\n");
	}else
	{
		printf("####################################################################\n");
		printf("# Process Name  |   Execution Time  |  Arrival Time |  Priority    #\n");
		printf("####################################################################\n");
	}


	while(pHead != NULL )
	{
		if(!areStringMatching(algo,"-ppf"))
		{

			printf("+        %c         |          %d          |           %d       +\n",pHead->processName,pHead->executionTime,pHead->arrivalDate);
		    printf("+------------------------------------------------------------+\n");
		}else
		{

			printf("+      %c        |         %d         |        %d       |       %d     +\n",pHead->processName,pHead->executionTime,pHead->arrivalDate,pHead->priority);
			printf("+------------------------------------------------------------------+\n");
		}

		pHead = pHead->nextProcessInfo;
		printf("\n");
	}

	return;

}


/*
 * This function solve the problem if the user enter an exesting option
 * but in UpperCase or both Upper-Lower in the same option ..
 *
 * It convert any String into lowerCase if controlSignal = 0 else into upperCase..
 */
void toLowerCase(char *str )
{
	char *pStr;

	for(pStr = str;*pStr != '\0' ;pStr++)
		if(*pStr >= 'A' && *pStr <= 'Z')
			*pStr += 32;


}



/*
 * Display the manuel
 * discription and usage of this program ..
 */
void displayManuel(void)
{
	printf("NAME : \n");
	printf("\tsa\n");
	printf("\t|_|____Shulder\n");
	printf("\t  |_______Algorithm\n\n");

	printf("USAGE :\n");
	printf("\tsa [OPTION]...\n\n");

	printf("DESCRIPTION:\n");
	printf("\tShulder Algorithm can be used to shulder some processes\n");
	printf("\taccording to the politique of shuldring without CPU requisition.\n\n");
	printf("\tOption to implement this commande :\n\n");
	printf("\t--man (manuel)\n\n");
	printf("\t-fcfs\n");
	printf("\t |_|_|_|___Fisrt\n");
	printf("\t   |_|_|_____Come\n");
	printf("\t     |_|_______First\n");
	printf("\t       |_________Served\n\n");

	printf("\t-sjf\n");
	printf("\t |_|_|_|___Short\n");
	printf("\t   |_|_|_____Job\n");
	printf("\t       |_______First\n\n");


	printf("\t-ppf\n");
	printf("\t |_|_|_|___Priority\n");
	printf("\t   |_|_|_____Process\n");
	printf("\t       |_______First\n\n");

}


/*
 * Display an error message when user enter an option dosen't exist ..
 */
void erreurMessage(void)
{
	printf("\n!!!!!!!!!!!! Erreur !!!!!!!!!!!!\n");
	printf("\t*Use the option [--man] for some help\n\n");

}



/*
 * Set the response and the waiting time for each node ..
 */
void setResponseWaitingTime(ProcessInfo * head)
{
	//Calcul of the response time & waiting time:
	ProcessInfo *pHead = head;

	int finDate = 0;
	while(pHead != NULL)
	{
		finDate += pHead->executionTime;

		pHead->responseTime = finDate - pHead->arrivalDate ;
		pHead->waitingTime = pHead ->responseTime - pHead->executionTime;

		pHead = pHead->nextProcessInfo;
	}
}


/*
 * Fisrt Come First Served > Shulder Algorithm ..
 * Dispaly the Gant chart according to the table enter by user ..
 */
void fcfsAlgo(ProcessInfo *head)
{
	displayGanttChart(head,"fcfs");
	setResponseWaitingTime(head);
}


/*
 * Short Job First > Shulder Algorithm ..
 * Dispaly the Gant chart according to the table enter by user ..
 */
void sjfAlgo(ProcessInfo *head)
{
	ProcessInfo *pHeadPrevious,*pHeadNext;

	pHeadPrevious =  head;
	pHeadNext  = head->nextProcessInfo;
	int howManyNode = 0;
	int priviousUnitTime = pHeadPrevious->arrivalDate;


	while(TRUE)
	{
		while(pHeadNext != NULL)
		{
			if( ( (pHeadPrevious->executionTime) + priviousUnitTime) > pHeadNext->arrivalDate){
				howManyNode++;
				pHeadNext = pHeadNext->nextProcessInfo;

			}

			else{
				priviousUnitTime += pHeadPrevious->executionTime;
				break;
			}

		}



		if(howManyNode == 1)
			pHeadPrevious = pHeadPrevious->nextProcessInfo;
		else{

			sortByAlgoChoise(pHeadPrevious->nextProcessInfo,pHeadNext,"sjf");

			//new value of priviousUnitTime
			ProcessInfo * ptr = pHeadPrevious->nextProcessInfo;
			while(ptr != pHeadNext){
				priviousUnitTime += ptr->executionTime;
				ptr = ptr->nextProcessInfo;
			}

			pHeadPrevious = pHeadNext;
			if(pHeadNext == NULL)
			{
				setResponseWaitingTime(head);
				displayGanttChart(head,"sjf");
				return;
			}
			else pHeadNext  = pHeadNext->nextProcessInfo;
		}

		howManyNode = 0;
		if(pHeadNext == NULL)
		{
			setResponseWaitingTime(head);
			displayGanttChart(head,"sjf");
			return;
		}
	}
}



/*
 * Priority Process First > Shulder Algorithm ..
 * Dispaly the Gant chart according to the table enter by user ..
 */
void ppfAlgo(ProcessInfo *head)
{
	ProcessInfo *pHeadPrevious,*pHeadNext;

		pHeadPrevious =  head;
		pHeadNext  = head->nextProcessInfo;
		int howManyNode = 0;
		int priviousUnitTime = pHeadPrevious->arrivalDate;


		while(TRUE)
		{
			while(pHeadNext != NULL)
			{
				if( ( (pHeadPrevious->executionTime) + priviousUnitTime) > pHeadNext->arrivalDate){
					howManyNode++;
					pHeadNext = pHeadNext->nextProcessInfo;

				}

				else{
					priviousUnitTime += pHeadPrevious->executionTime;
					break;
				}

			}



			if(howManyNode == 1)
				pHeadPrevious = pHeadPrevious->nextProcessInfo;
			else{

				sortByAlgoChoise(pHeadPrevious->nextProcessInfo,pHeadNext,"ppf");

				//new value of priviousUnitTime
				ProcessInfo * ptr = pHeadPrevious->nextProcessInfo;
				while(ptr != pHeadNext){
					priviousUnitTime += ptr->executionTime;
					ptr = ptr->nextProcessInfo;
				}

				pHeadPrevious = pHeadNext;
				if(pHeadNext == NULL)
				{
					setResponseWaitingTime(head);
					displayGanttChart(head,"ppf");
					return;
				}
				else pHeadNext  = pHeadNext->nextProcessInfo;
			}

			howManyNode = 0;
			if(pHeadNext == NULL)
			{
				setResponseWaitingTime(head);
				displayGanttChart(head,"ppf");
				return;
			}
		}
}


/*
 * This fucntion manage all the options exist in the menu ,
 * and it start the Shulder algorithme according to the optionString ..
 */
void optionManager(char *optionString)
{
	system("clear");
	ProcessInfo *head = NULL;

	if(areStringMatching(optionString,"--man")){
		displayManuel();
		return;
	}
	
	char choice = 'n';
	if(areStringMatching(optionString,"-fcfs") || areStringMatching(optionString,"-sjf")
			|| areStringMatching(optionString,"-ppf"))
	{
		do
		{

			head = addProcessInfo(head,optionString);
			printf("\t\t+++++++++ You want to add more [Y/N] .. +++++++++\n");
			scanf(" %c",&choice);
			system("clear");
		}while(choice == 'Y' || choice == 'y');

		sortByAlgoChoise(head,NULL,"fcfs");
		displayProcessInfo(head,optionString);

	}
	
	if(areStringMatching(optionString,"-fcfs"))
	{
		fcfsAlgo(head);
		diplayWaitingResponeTime(head);
		return;
	}

	if(areStringMatching(optionString,"-sjf"))
	{
		sjfAlgo(head);
		diplayWaitingResponeTime(head);
		return;
	}
	if(areStringMatching(optionString,"-ppf"))
	{
		ppfAlgo(head);
		diplayWaitingResponeTime(head);
		return;
	}
	erreurMessage();
}



