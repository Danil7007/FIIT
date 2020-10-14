package sk.stuba.fiit.fromRandomInterval;

import java.util.Random;

public class FromRandomInterval {
	
	public static void main(String [] args) {
		int i;
		
		for(i=0; i<100; i++) {
			System.out.println(randomByInterval(10,20));
		}	
	}

	public static int randomByInterval(int min, int max) {
		Random rnd = new Random();
		int randomNumber = rnd.nextInt((max - min) + 1) + min;
		return randomNumber;
	}
}
