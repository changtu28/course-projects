import static org.junit.Assert.*;
import java.util.ArrayList;

import org.junit.Test;

public class PlayerTest {

	@Test
	public void testArrtributes() {
		ArrayList<Pet> pets = new ArrayList<Pet>();
		Player newPlayer = new Player("rain", 2, pets);
		assertEquals("rain", newPlayer.getName());
		assertEquals(pets, newPlayer.getPets());
	}

	@Test
	public void testFoodlist() {
		ArrayList<Pet> pets = new ArrayList<Pet>();
		Player newPlayer = new Player("rain", 2, pets);
		assertEquals("bread", newPlayer.getFoods().get(1).getName());
	}

	@Test
	public void testToylist() {
		ArrayList<Pet> pets = new ArrayList<Pet>();
		Player newPlayer = new Player("rain", 2, pets);
		assertEquals("Ball", newPlayer.getToys().get(0).getName());
	}

	@Test
	public void testmoney() {
		ArrayList<Pet> pets = new ArrayList<Pet>();
		Player newPlayer = new Player("rain", 2, pets);
		assertEquals(500, newPlayer.getMoney());
	}

	@Test
	public void testcurday() {
		ArrayList<Pet> pets = new ArrayList<Pet>();
		Player newPlayer = new Player("rain", 2, pets);
		assertEquals(1, newPlayer.getCurrentDay());
	}

	@Test
	public void testmovetoNextDay() {
		Pet newpet = new Pet("ab", "cat");
		ArrayList<Pet> pets = new ArrayList<Pet>();
		pets.add(newpet);
		Player newPlayer = new Player("rain", 2, pets);
		newpet.setIsSick(true);
		newPlayer.movetoNextDay(1, 3);
		assertEquals(0, newpet.getActions());
		assertEquals(55, newpet.getCleanness());
		assertEquals(55, newpet.getHappiness());
		assertEquals(105, newpet.getHunger());
		assertEquals(40, newpet.getHealthiness());
		assertEquals(2, newPlayer.getCurrentDay());
	}

	@Test
	public void testfinalScore() {
		Pet newpet = new Pet("ab", "cat");
		ArrayList<Pet> pets = new ArrayList<Pet>();
		pets.add(newpet);
		Player newPlayer = new Player("rain", 2, pets);
		newpet.setHappiness(100);
		assertEquals(50, newPlayer.getTotalScore());
	}
}