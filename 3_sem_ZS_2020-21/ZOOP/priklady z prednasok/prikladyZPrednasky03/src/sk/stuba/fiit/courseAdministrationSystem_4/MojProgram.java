package sk.stuba.fiit.courseAdministrationSystem_4;

public class MojProgram {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Student jano = new Student("Jano");
		System.out.println(jano.getFirstName());
		Student peter1 = new Student("Peter", 100);
		System.out.println(peter1.getEnergia());
		Student fero = new Student();
		//Student dano = new Student(100, 100);
		Student peter2 = new Student(peter1);

		peter1.vypis();
		
		System.out.println(Student.pocitadlo);
		//System.out.println(peter!..pocitadlo);
		
		new Teacher().posliStudentaNaErasmus(jano);

	}

}
