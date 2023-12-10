#ifndef ALGO_H_
#define ALGO_H_

	struct processinfo
	{
		char processName;
		int executionTime;
		int arrivalDate;
		int priority;
		int responseTime;
		int waitingTime;

		struct processinfo * nextProcessInfo;

	};
	typedef struct processinfo ProcessInfo;

	typedef int Boolean ;


	#define TRUE 1
	#define FALSE 0

	/*
	 *****************************
	 **    Function Signature   **
	 *****************************
	 */


	ProcessInfo * addProcessInfo(ProcessInfo *,char *);
	void sortByAlgoChoise(ProcessInfo *,ProcessInfo *, char*);
	void setResponseWaitingTime(ProcessInfo * );


	Boolean areStringMatching(char *,char *);
	void toLowerCase(char * );

	//For all displays ..
	void displayManuel(void);
	void erreurMessage(void);
	void displayGanttChart(ProcessInfo *,char *);
	void diplayWaitingResponeTime(ProcessInfo *);
	void displayProcessInfo(ProcessInfo *,char *);

	//The manager of my programm..
	void optionManager(char *);

	//Shulder algorithm ..
	void fcfsAlgo(ProcessInfo *);
	void sjfAlgo(ProcessInfo *);
	void ppfAlgo(ProcessInfo *);



#endif
