import static org.junit.Assert.*;

import java.util.ArrayList;

import org.junit.Test;


public class PetTest {

	@Test
	public void testAttributes() {
		Pet newPet = new Pet("Meow", "cat");
		newPet.setHasBeenDead(true);
		newPet.setIsSick(true);
		assertEquals("Meow", newPet.getName());
		assertEquals("cat", newPet.getSpecies());
		assertEquals(0, newPet.getActions());
		assertEquals(100, newPet.getHunger());
		assertEquals(50, newPet.getHappiness());
		assertEquals(10, newPet.getWeight());
		assertEquals(true, newPet.getHasBeenDead());
		assertEquals(true, newPet.getIsSick());
	}
	
	@Test
	public void testFeedAction(){
		Pet newPet = new Pet("Lucky", "dog");
		Bone newBone = new Bone("bone", 2);
		newPet.setActions(2);
		newPet.feed(newBone);
		assertEquals(50, newPet.getHappiness());
		assertEquals(10, newPet.getWeight());
	}
	@Test
	public void testPlayAction(){
		Pet newPet = new Pet("Mickey", "hamster");
		ArrayList<Pet>pets = new ArrayList<Pet>();
		pets.add(newPet);
		Player newPlayer = new Player("Sam", 1, pets);
		newPlayer.getToys().get(0).setStock(3);
		newPet.play(newPlayer.getToys().get(0));
		assertEquals(60, newPet.getHappiness());
	    assertEquals(55, newPet.getHealthiness());
	    assertEquals(105, newPet.getHunger());
	    assertEquals(55, newPet.getTiredness());
	    assertEquals(45, newPet.getCleanness());

	}

	@Test
	public void testSleepAction(){
		Pet newPet = new Pet("Rick", "rabbit");
		newPet.setActions(1);
		newPet.setTiredness(7);
		newPet.sleep();
		assertEquals(2, newPet.getTiredness());
		assertEquals(2, newPet.getActions());	
		assertEquals(true, newPet.getIsAsleep());
		
	}
	
	@Test
	public void testWakeUpAction(){
		Pet newPet = new Pet("Morty", "duck");
		newPet.setIsAsleep(true);
		newPet.wakeUp();
		assertEquals(false, newPet.getIsAsleep());
	
	}
	
	@Test
	public void testToiletAction(){
		Pet newPet = new Pet("red", "pig");
        newPet.setActions(0);
        newPet.setIsAsleep(false);
        newPet.toilet();
        assertEquals(53, newPet.getCleanness());
        assertEquals(5, newPet.getWeight());
        assertEquals(52, newPet.getHappiness());
        assertEquals(1, newPet.getActions());
	}
	
	@Test
	public void testPunishmentAction(){
		Pet newPet = new Pet("red", "pig");
        newPet.punishment();
        assertEquals(47, newPet.getHappiness());
			
	}
	
	@Test
	public void testTreatmentAction(){
		Pet newPet = new Pet("Mickey", "hamster");
		newPet.setIsSick(true);
		ArrayList<Pet>pets = new ArrayList<Pet>();
		pets.add(newPet);
		Player newPlayer = new Player("Sam", 1, pets);
		newPet.treatment(newPlayer);
		assertEquals(495, newPlayer.getMoney());
		assertEquals(55, newPet.getHealthiness());
		assertEquals(53, newPet.getHappiness());
		assertEquals(false, newPet.getIsSick());
	}
	
	@Test
	public void testReviveAction(){
		Pet newPet = new Pet("Mickey", "hamster");
		newPet.setIsAlive(false);
        newPet.setHasBeenDead(false);
        newPet.revive();
		assertEquals(true, newPet.getIsAlive());
		assertEquals(120, newPet.getHunger());
		assertEquals(30, newPet.getTiredness());
		assertEquals(70, newPet.getCleanness());
	}
}
