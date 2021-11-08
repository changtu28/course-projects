
/**
 * The Class Fish is a subclass extending Food class.
 */
public class Fish extends Food {
	
	/** The food name. */
	private String name = "Fish";
	
	/** The fish nutrition. */
	private int nutrition = 12;
	
	/** The fish price. */
	private int price = 8;
	
	/** The fish stock. */
	private int stock=0;

	/**
	 * Instantiates a new fish.
	 *
	 * @param myName the my name
	 * @param myStock the my stock
	 */
	public Fish(String myName,int myStock) {
		super(myName,myStock);
		// TODO Auto-generated constructor stub
	}
	
	/* (non-Javadoc)
	 * @see Food#getName()
	 */
	public String getName(){
		return name;
	}
	
	/* (non-Javadoc)
	 * @see Food#getPrice()
	 */
	public int getPrice(){
		return price;
	}
	
	/* (non-Javadoc)
	 * @see Food#getNutrition()
	 */
	public int getNutrition(){
		return nutrition;
	}
	
	/* (non-Javadoc)
	 * @see Food#getStock()
	 */
	public int getStock(){
		return stock;
	}
	
	/* (non-Javadoc)
	 * @see Food#setStock(int)
	 */
	public void setStock(int newStock){
		stock = newStock;
	}

}
