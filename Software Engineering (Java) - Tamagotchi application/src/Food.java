
/**
 * The superclass Food.
 */
public class Food {
	
	/** The name. */
	private String name;
	
	/** The stock. */
	private Integer stock;
	
	/** The nutrition. */
	private int nutrition;
	
	/** The price. */
	private int price;
	
	/**
	 * Instantiates a new food.
	 *
	 * @param myName the my name
	 * @param myStock the my stock
	 */
	public Food(String myName, int myStock){
		name = myName;
		stock = myStock;
		price = 10;
		nutrition = 20;
	}
	
	/**
	 * Gets the food name.
	 *
	 * @return the food name
	 */
	public String getName(){
		return name;
	}

	/**
	 * Gets the food price.
	 *
	 * @return the food price
	 */
	public int getPrice(){
		return price;
	}
	
	/**
	 * Gets the food nutrition.
	 *
	 * @return the food nutrition
	 */
	public int getNutrition(){
		return nutrition;
	}
	
	/**
	 * Gets the food stock.
	 *
	 * @return the food stock
	 */
	public int getStock(){
		return stock;
	}
	
	/**
	 * Sets the new foodstock.
	 *
	 * @param newStock the new stock
	 */
	public void setStock(int newStock){
		stock = newStock;
	}

}
