/**
 * The Class Robot is a subclass extending Toy class.
 */
public class Robot extends Toy {
	
	/** The name of the toy. */
	private String name = "robot";
	
	/** The robot price. */
	private int price = 7;
	
	/** The robot damage. */
	private int damage = 0;
	
	/** The robot stock. */
	private int stock=0;

	/**
	 * Instantiates a new robot.
	 *
	 * @param myName the my name
	 */
	public Robot(String myName) {
		super(myName);

	}
	
	/* (non-Javadoc)
	 * @see Toy#getName()
	 */
	public String getName(){
		return name;
	}
	
	/* (non-Javadoc)
	 * @see Toy#getPrice()
	 */
	public int getPrice(){
		return price;
	}
	
	/* (non-Javadoc)
	 * @see Toy#getDamage()
	 */
	public int getDamage(){
		return damage;
	}
	
	/* (non-Javadoc)
	 * @see Toy#setDamage(int)
	 */
	public void setDamage(int newDamage){
		damage = newDamage;
	}
	
	/* (non-Javadoc)
	 * @see Toy#getStock()
	 */
	public int getStock(){
		return stock;
	}
	
	/* (non-Javadoc)
	 * @see Toy#setStock(int)
	 */
	public void setStock(int newStock){
		stock = newStock;
	}
}
