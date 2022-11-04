# philosophers

This is a solution to the classic threading problem of the philosophers dinner.

### important things about the problem

* One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
* The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
* There are also forks on the table. There are as many forks as philosophers.
* Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
* When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
* Every philosopher needs to eat and should never starve.
* Philosophers don’t speak with each other.
* Philosophers don’t know if another philosopher is about to die.
* No need to say that philosophers should avoid dying!
* Every philosopher is a thread.
* Forks should be protected by mutexes.

### content learned

* Threads are processes that execute at the same time. The execution can be paralel or concurrent.
* Paralel works in multi core machines with simultaneous threads in different cores.
* Concurrent threads run in a single core one at a time alternating really fast so it appears to be running at the the sime time.
* Race conditions happens when two threads access a memory at the same time, one reading and another writing.
* Mutex locks (mutual exclusion locks) is a computing abstraction that allows one thread to prevent other threads from proceed working until the mutex is unlocked.
