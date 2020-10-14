package sk.stuba.fiit.fromRandomInterval;

import java.util.Random;

public class SecureAndRandomlyString {

	public static final String DATASOURCE = "Zakladyobjektovo-orientovaneho_programovania";

	public static void main(String[] args) {

		SecureAndRandomlyString srs = new SecureAndRandomlyString();
		System.out.println(srs.rnd(new Random(), DATASOURCE, 10));
	}
	
	String rnd(Random random, String characters, int lenght) {
		char[] text = new char[lenght];

		for (int i = 0; i < lenght; i++) {
			text[i] = characters.charAt(random.nextInt(characters.length()));
		}

		return new String(text);

	}
}
