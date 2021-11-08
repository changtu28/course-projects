import static org.junit.Assert.*;

import org.junit.Test;

public class FoodTest {

	@Test
	public void testArritbutes() {
		Food newFood = new Food("fish", 1);
		assertEquals("fish", newFood.getName());
		assertEquals(10, newFood.getPrice());
		assertEquals(20, newFood.getNutrition());
		assertEquals(1, newFood.getStock());
	}
}