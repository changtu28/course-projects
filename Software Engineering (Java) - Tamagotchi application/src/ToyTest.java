import static org.junit.Assert.*;

import org.junit.Test;

public class ToyTest {

	@Test
	public void testArritbutes() {
		Toy newToy = new Toy("robot");
		assertEquals("robot", newToy.getName());
		assertEquals(10, newToy.getPrice());
		assertEquals(0, newToy.getDamage());
		assertEquals(1, newToy.getStock());
	}

}