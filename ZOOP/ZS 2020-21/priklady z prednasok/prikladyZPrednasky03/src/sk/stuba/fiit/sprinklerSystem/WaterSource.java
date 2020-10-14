package sk.stuba.fiit.sprinklerSystem;

public class WaterSource {
	private String s;

	WaterSource() {
		System.out.println("WaterSource()");
		s = new String("Constructed");
	}

	public String toString() {
		return s;
	}

}
