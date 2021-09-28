Using `test.sh` I measured the average turaround time and wait time
for 3 different scheduling algorithms.\
Results are:
* **First come first served:** TAT-38sec, WT-32sec
* **Shortest job algorithm:**  TAT-28sec, WT-22sec
* **Round robin algorithm:**   TAT-49sec, WT-44sec

We can conclude that **shortest job** algorithm has the best performance
in terms of average turaround time and wait time.
But it obviously has huge problems. Firsly, most of the time it's impossible
to know the running time of the program in advance. Secondly,
long processes might wait for huge amounts of time before they run.

**First come first served** alrogithm is more fair, but has worse performance
in terms of wait and turnaround time. 
It's main problem is that in multiprogramming systems of today,
a lot of programs run at the same time, so a program might have
to wait a long time before all other processes finish.

**Round robin** algorithm is the most fair, because all processes get
a chance to run. Unless a lot of processes arrive at the same time,
or the quantum is too high,
no process has to wait for too long to get a chance to run.

Example usage of `test.sh`:\
`./test.sh ex1.out`

