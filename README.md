*****************************************************
***************Assignment 3: Processes***************

Question1: q1.c Before running the code open system monitor in order to observe the CPU 
utilisation and the change occuring when process priorities are altered. Uncomment the 
lines where priorities are set.

Question 3: primefib.c The parent will create 2 children which will recursively generate 
four grandchildren and then 8 great grandchildren. The code currently supports input less 
than 10000 and generates the prime numbers and fibnocci numbers less than that no.

Question 4: pipe.c The parent generates four child processes. The first one reads input 
string, maps it to another string and sends it to parents which return it as output.
The second child takes name of file which is sent to parent which reads it through espeak.
Third child asks for file to be copied and fourth child prints CPU usage at regular intervals.
