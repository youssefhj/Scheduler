## Scheduling:
In the linux class we learned about scheduler, and how this piece of software manage and distribute CPU time among processes. So after this class an idea comes to my mind why not implementing this concept using C langages.

I implemented three types:</br>
    ***FCFS*** : First Come First Served</br>
    ***SJF***  : Short Job First</br>
    ***PPF***  : Priority Process First</br>

After running this program the GANTT CHART will appear on the screen
showing how much time the process was allocated in the cpu.

I break down this project in 4 files :

| File | Description |
| --- | --- |
| sa.c |Its the main file |
| algo.c | Contain the implementation of functions written in ***algo.h*** |
| algo.h | Contain the signature of functions implemented in ***algo.c*** |
| makefile | A file helps us to compile the entire project

## How to run this project :

Perform the following steps to run this project correctly :

1. Download my repo in your computer.
2. To run the project:
    
    *make sure the ***make*** command is installed*
    ```bash 
    $ sudo apt-get install make
    ```

    *to build the executable file called ***sa.exe*** :*
    ```bash 
    $ make
    ```

    *read the manual:*
    ```bash 
    $ ./sa.exe --man
    ```
    *after specifie your desire algorithm:*
    ```bash
    $ ./sa.exe {-fcfs | -sjf | -ppf}
    ```