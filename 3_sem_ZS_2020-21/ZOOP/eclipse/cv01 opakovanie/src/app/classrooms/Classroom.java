package app.classrooms;
import java.util.ArrayList;
import app.persons.Student;

public class Classroom {

	private int NumberOfStudents;
	public int Grade;
	public String NameOfClassTeacher;
	public ArrayList<Student> ListOfStudents = new ArrayList<Student>();
	
	
	public Classroom() {
		
	}
	
	public void CreateAndSaveStudent(String name, int age)
	{
		ListOfStudents.add(new Student(name, age));
	}
	
	public void AddStudentToClass(Student student)
	{
		ListOfStudents.add(student);
	}
	
	public void RemoveStudentFromClass(Student student)
	{
		ListOfStudents.remove(student);
	}
	
	public void PresentWholeClass() {
		for(int i = 0; i<ListOfStudents.size(); i++)
		{
			ListOfStudents.get(i).PresentYourself();
		}
	}
	
	public int GetNumberOfStudents() {
		this.NumberOfStudents = ListOfStudents.size();
		return NumberOfStudents;
	}
		
}
