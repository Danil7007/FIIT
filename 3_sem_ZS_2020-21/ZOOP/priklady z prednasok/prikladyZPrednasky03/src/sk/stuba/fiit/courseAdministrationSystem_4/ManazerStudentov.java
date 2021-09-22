package sk.stuba.fiit.courseAdministrationSystem_4;

import java.util.ArrayList;

public class ManazerStudentov {
	
	Student [] ps = new Student[100];
	static ArrayList<Student> aps = new ArrayList<>();
	
	public static void pridajStudenta(Student s) {
		aps.add(s);
	}
	
	public void vypisZoznam() {
		for(Student fecs : aps)
			System.out.println(fecs);
	}
	
	public static void main(String [] args) {
		
		new Student();
		Student jano = new Student();
		Student fero = new Student();

		/*
		jano.birthDay = 1;
		fero.birthDay = 2;
		
		jano.firstName = "Jano";
		
		System.out.println(jano.firstName);
		
		pridajStudenta(jano);
		
		jano.move(new Poloha());
		*/
	}
	

}
