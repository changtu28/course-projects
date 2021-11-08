
/**
 * The Class Bread that extends Food class.
 */
public class Bread extends Food {
	
	/** The food name. */
	private String name = "bread";
	
	/** The bread nutrition. */
	private int nutrition = 8;
	
	/** The bread price. */
	private int price = 2;
	
	/** The bread stock. */
	private int stock=0;

	/**
	 * Instantiates a new bread.
	 *
	 * @param myName the my name
	 * @param myStock the my stock
	 */
	public Bread(String myName, int myStock) {
		super(myName, myStock);
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
