
/**
 * The superclass Toy.
 */
public class Toy {

	/** The toy name. */
	private String name;
	
	/** The toy price. */
	private int price;
	
	/** The toy damage. */
	private int damage;
	
	/** The toy stock. */
	private int stock;

	
	/**
	 * Instantiates a new toy.
	 *
	 * @param myName the my name
	 */
	public Toy(String myName){
		name = myName;
	    price = 10;
		damage = 0;
		stock = 1;
		
	}
	
	/**
	 * Gets the toy name.
	 *
	 * @return the name
	 */
	public String getName(){
		return name;
	}
	
	/**
	 * Gets the toy price.
	 *
	 * @return the price
	 */
	public int getPrice(){
		return price;
	}

	
	/**
	 * Gets the toy damage.
	 *
	 * @return the damage
	 */
	public int getDamage(){
		return damage;
	}
	
	/**
	 * Sets the toy damage.
	 *
	 * @param newDamage the new damage
	 */
	public void setDamage(int newDamage){
		damage = newDamage;
	}
	
	/**
	 * Gets the toy stock.
	 *
	 * @return the stock
	 */
	public int getStock(){
		return stock;
	}
	
	/**
	 * Sets the toy stock.
	 *
	 * @param newStock the new stock
	 */
	public void setStock(int newStock){
		stock = newStock;
	}
	
	
}
