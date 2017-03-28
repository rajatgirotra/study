/*
 * Please read Philosopher.java first
 * Now we can set up a version of the program that will deadlock:
 */

// {Args: 0 5 timeout}
import java.util.concurrent.*;
public class DeadlockingDiningPhilosophers {
	public static void main(String[] args) throws Exception {
		int ponder = 0;
		
		if(args.length > 0)
			ponder = Integer.parseInt(args[0]);
		
		int size = 5;
		
		if(args.length > 1)
			size = Integer.parseInt(args[1]);
		
		ExecutorService exec = Executors.newCachedThreadPool();
		Chopstick[] sticks = new Chopstick[size];
		for(int i = 0; i < size; i++)
			sticks[i] = new Chopstick();
		
		for(int i = 0; i < size; i++)
			exec.execute(new Philosopher(sticks[i], sticks[(i+1) % size], i, ponder));
		
		if(args.length == 3 && args[2].equals("timeout"))
			TimeUnit.SECONDS.sleep(5);
		
		else {
			System.out.println("Press ‘Enter’ to quit");
			System.in.read();
		}
		exec.shutdownNow();
	}
}

/*
You will observe that if the Philosophers spend very little time thinking, they will all be competing 
for the Chopsticks while they try to eat, and deadlock will happen much more quickly.

The first command-line argument adjusts the ponder factor, to affect the amount of time each Philosopher
spends thinking. If you have lots of Philosophers or they spend a lot of time thinking, you may never 
see deadlock even though it remains a possibility. A command-line argument of zero tends to make the 
program deadlock fairly quickly.

Good time to read the conditions that lead to a deadlock from your operating systems book:
1. Mutual Exclusion
2. No preemption
3. Circular Wait.
4. Hold and Wait

To prevent a deadlock in this case, one solution is to prevent Circular wait.
If we setup the last philosopher in such a way that he picks up the left chopstick first and then the 
right chopstick, we prevent a circular wait from happening, thereby preventing the deadlock.

This is only solution to the problem. There could many more by preventing other conditions.
Please read FixedDiningPhilosophers.java
*/