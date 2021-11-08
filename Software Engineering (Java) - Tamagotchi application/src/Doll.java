/**
 * The Class Doll is a subclass extending Toy class.
 */
public class Doll extends Toy {
	
	/** The toy name. */
	private String name = "doll";	
	
	/** The doll price. */
	private int price = 10;
	
	/** The doll damage. */
	private int damage = 0;
	
	/** The doll stock. */
	private int stock=0;
	
    /**
     * Instantiates a new doll.
     *
     * @param myName the my name
     */
    public Doll(String myName) {
		
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
