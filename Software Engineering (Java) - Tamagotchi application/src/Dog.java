
/**
 * The Class Dog is a subclass extending Pet class.
 */
public class Dog extends Pet{
	
	/** The dog's name. */
	private String name;
	
	/** Actions been completed by dog. */
	private int actions;
	
	/** Happiness of the dog. */
	private int happiness=50;
	
	/** Hunger of the dog. */
	private int hunger=100;
	
	/** The tiredness of the dog. */
	private int tiredness=50;
	
	/** The healthiness the dog. */
	private int healthiness=50;
	
	/** The is asleep status of the dog. */
	private boolean isAsleep=false;
	
	/** The is sick status of the dog. */
	private boolean isSick=false;
	
	/** The is alive status of the dog. */
	private boolean isAlive=true;
	
	/** The is misbehaving status of the dog. */
	private boolean isMisbehaving=false;
	
	/** The cleanness of the dog. */
	private int cleanness=50;
	
	/** The has been dead status of the dog. */
	private boolean hasBeenDead=false;
	
	/** The species of the dog. */
	private String species = "dog";
    
    /** The favorite food of the dog. */
    private String favFood = "bone";
    
    /** The favorite toy of the dog. */
    private String favToy = "ball";
    
    /** The weight of the dog. */
    private int weight = 40;
	
	/**
	 * Instantiates a new dog.
	 *
	 * @param myName the my name
	 * @param mySpecies the my species
	 */
	Dog(String myName, String mySpecies) {
		super(myName, mySpecies);
		// TODO Auto-generated constructor stub
	}
	
	/* (non-Javadoc)
	 * @see Pet#getName()
	 */
	public String getName(){
		return name;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setName(java.lang.String)
	 */
	public void setName(String newName){
		name = newName;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getSpecies()
	 */
	public String getSpecies(){
		return species;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getActions()
	 */
	public int getActions(){
		return actions;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setActions(int)
	 */
	public void setActions(int n){
		actions = n;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getFavFood()
	 */
	public String getFavFood(){
		return favFood;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getFavToy()
	 */
	public String getFavToy(){
		return favToy;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getWeight()
	 */
	public int getWeight(){
		return weight;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setWeight(int)
	 */
	public void setWeight(int newWeight){
		weight = newWeight;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getHappiness()
	 */
	public int getHappiness() {
		return happiness;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setHappiness(int)
	 */
	public void setHappiness(int newHappiness){
		happiness = newHappiness;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getHunger()
	 */
	public int getHunger() {
		return hunger;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setHunger(int)
	 */
	public void setHunger(int newHunger){
		hunger = newHunger;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getTiredness()
	 */
	public int getTiredness(){
		return tiredness;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setTiredness(int)
	 */
	public void setTiredness(int newTiredness){
		tiredness = newTiredness;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getHealthiness()
	 */
	public int getHealthiness(){
		return healthiness;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setHealthiness(int)
	 */
	public void setHealthiness(int newHealthiness){
		healthiness = newHealthiness;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getCleanness()
	 */
	public int getCleanness(){
		return cleanness;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setCleaness(int)
	 */
	public void setCleaness(int newCleaness){
		cleanness = newCleaness;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getIsSick()
	 */
	public Boolean getIsSick(){
		return isSick;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setIsSick(java.lang.Boolean)
	 */
	public void setIsSick(Boolean newIsSick) {
        isSick= newIsSick;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getIsAsleep()
	 */
	public Boolean getIsAsleep(){
		return isAsleep;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setIsAsleep(java.lang.Boolean)
	 */
	public void setIsAsleep(Boolean newIsAsleep){
		isAsleep = newIsAsleep;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getIsMisBehaving()
	 */
	public Boolean getIsMisBehaving(){
		return isMisbehaving;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setIsMisBehaving(java.lang.Boolean)
	 */
	public void setIsMisBehaving(Boolean newIsMisbehaving) {
		isMisbehaving = newIsMisbehaving;
	}
	
	/* (non-Javadoc)
	 * @see Pet#getIsAlive()
	 */
	public Boolean getIsAlive(){
		return isAlive;
	}
    
    /**
     * Sets the alive.
     */
	public void setIsAlive(boolean newIsAlive) {
		isAlive = newIsAlive;

	}

	
	/* (non-Javadoc)
	 * @see Pet#getHasBeenDead()
	 */
	public boolean getHasBeenDead(){
		return hasBeenDead;
	}
	
	/* (non-Javadoc)
	 * @see Pet#setHasBeenDead(boolean)
	 */
	public void setHasBeenDead(boolean newhasBeenDead){
		hasBeenDead = newhasBeenDead;
	}

	
}
