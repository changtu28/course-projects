/**
 * The Ball Class, a subclass extends toy class.
 */
public class Ball extends Toy {
	
	/** The ball stock. */
	private int stock=0;
	
	/** The toy name. */
	private String name = "Ball";	
	
	/** The ball price. */
	private int price = 5;
	
	/** The ball damage. */
	private int damage = 0;
	
    /**
     * Instantiates a new ball.
     *
     * @param myName the my name
     */
    public Ball(String myName) {
		
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

