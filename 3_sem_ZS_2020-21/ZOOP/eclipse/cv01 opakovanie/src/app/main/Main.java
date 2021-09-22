package app.main;

import app.classrooms.Classroom;
import app.persons.Student;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Classroom first = new Classroom();
		
		first.CreateAndSaveStudent("Janko", 19);

		first.PresentWholeClass();
		
		System.out.println(first.GetNumberOfStudents());
	}

}
