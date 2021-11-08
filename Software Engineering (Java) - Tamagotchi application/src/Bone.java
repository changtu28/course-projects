
/**
 * The Class Bone extends Food class.
 */
public class Bone extends Food{
	
	/** The bone stock. */
	private int stock=0;
	
	/** The food name. */
	private String name = "Bone";
	
	/** The food nutrition. */
	private int nutrition = 15;
	
	/** The bone price. */
	private int price = 5;
	
	/**
	 * Instantiates a new bone.
	 *
	 * @param myName the my name
	 * @param myStock the my stock
	 */
	public Bone(String myName,int myStock) {
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
