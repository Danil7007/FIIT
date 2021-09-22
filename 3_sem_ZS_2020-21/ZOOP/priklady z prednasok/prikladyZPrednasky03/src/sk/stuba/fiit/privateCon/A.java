package sk.stuba.fiit.privateCon;

public class A {
	private static volatile A instance = new A();
	
	private A() {
		System.out.println("Konstruktor A");
	}
	
	public static A getInstace() {
		return instance;
	}
}
