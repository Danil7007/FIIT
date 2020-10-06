package app.persons;

public class Student {

	public String Name;
	public int Age;
	public float StudyAvg;
	
	public Student(String name, int age)
	{
		 Name = name; 
		 Age = age;
	}
	
	
	public Student() {
		
	}
	
	public void PresentYourself() {
		System.out.println("My name is " + this.Name + "and my age is " + this.Age);
	}
	
}
