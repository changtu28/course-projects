import java.util.Random;

import javax.swing.JOptionPane;

import org.omg.CORBA.Current;

/**
 * The superclass Pet.
 */
public class Pet {
	
	/** The name of the pet. */
	private String name;
	
	/** The species of the pet. */
	private String species;
	
	/** The weight of the pet. */
	private int weight;
	
	/** The actions of the pet. */
	private int actions;
	
	/** The happiness of the pet. */
	private int happiness;
	
	/** The hunger of the pet. */
	private int hunger;
	
	/** The tiredness of the pet. */
	private int tiredness;
	
	/** The healthiness of the pet. */
	private int healthiness;
	
	/** The is asleep status of the pet. */
	private boolean isAsleep;

	/** The is sick status of the pet. */
	private Boolean isSick;
	
	/** The is alive status of the pet. */
	private Boolean isAlive;
	
	/** The is misbehaving status of the pet. */
	private Boolean isMisbehaving;
	
	/** The cleanness of the pet. */
	private int cleanness;
	
	/** The favorite food of the pet. */
	private String favFood;
	
	/** The favorite toy of the pet. */
	private String favToy;
	
	/** The has been dead status of the pet. */
	private boolean hasBeenDead;

	/**
	 * Instantiates a new pet.
	 *
	 * @param myName the my name
	 * @param mySpecies the my species
	 */
	public Pet(String myName, String mySpecies) {
		name = myName;
		species = mySpecies;
		weight = 10;
		actions = 0;
		happiness = 50;
		hunger = 100;
		tiredness = 50;
		healthiness = 50;
		isSick = false;
		isAlive = true;
		isMisbehaving = false;
		cleanness = 50;
		favFood = "bread";
		favToy = "ball";
		hasBeenDead = false;

	}

	/**
	 * Gets the pet name.
	 *
	 * @return the pet name
	 */
	public String getName() {
		return name;
	}

	/**
	 * Sets the pet name.
	 *
	 * @param newName the new pet name
	 */
	public void setName(String newName) {
		name = newName;
	}

	/**
	 * Gets the pet species.
	 *
	 * @return the pet species
	 */
	public String getSpecies() {
		return species;
	}

	/**
	 * Gets the actions pet have completed.
	 *
	 * @return the actions
	 */
	public int getActions() {
		return actions;
	}

	/**
	 * Sets the actions pet have completed.
	 *
	 * @param n the new actions
	 */
	public void setActions(int n) {
		actions = n;
	}

	/**
	 * Gets the favorite food of the pet.
	 *
	 * @return the favorite food
	 */
	public String getFavFood() {
		return favFood;
	}

	/**
	 * Gets the favorite toy of the pet.
	 *
	 * @return the favorite toy
	 */
	public String getFavToy() {
		return favToy;
	}

	/**
	 * Gets the weight of the pet.
	 *
	 * @return the weight of the pet
	 */
	public int getWeight() {
		return weight;
	}

	/**
	 * Sets the weight of the pet.
	 *
	 * @param newWeight the new weight of the pet
	 */
	public void setWeight(int newWeight) {
		weight = newWeight;
	}

	/**
	 * Gets the happiness of the pet.
	 *
	 * @return the happiness of the pet
	 */
	public int getHappiness() {
		return happiness;
	}

	/**
	 * Sets the happiness of the pet.
	 *
	 * @param newHappiness the new happiness of the pet
	 */
	public void setHappiness(int newHappiness) {
		happiness = newHappiness;
	}

	/**
	 * Gets the hunger of the pet.
	 *
	 * @return the hunger of the pet
	 */
	public int getHunger() {
		return hunger;
	}

	/**
	 * Sets the hunger of the pet.
	 *
	 * @param newHunger the new hunger of the pet
	 */
	public void setHunger(int newHunger) {
		hunger = newHunger;
	}

	/**
	 * Gets the tiredness of the pet.
	 *
	 * @return the tiredness of the pet
	 */
	public int getTiredness() {
		return tiredness;
	}

	/**
	 * Sets the tiredness of the pet.
	 *
	 * @param newTiredness the new tiredness of the pet
	 */
	public void setTiredness(int newTiredness) {
		tiredness = newTiredness;
	}

	/**
	 * Gets the healthiness of the pet.
	 *
	 * @return the healthiness of the pet
	 */
	public int getHealthiness() {
		return healthiness;
	}

	/**
	 * Sets the healthiness of the pet.
	 *
	 * @param newHealthiness the new healthiness of the pet
	 */
	public void setHealthiness(int newHealthiness) {
		healthiness = newHealthiness;
	}

	/**
	 * Gets the cleanness of the pet.
	 *
	 * @return the cleanness of the pet
	 */
	public int getCleanness() {
		return cleanness;
	}

	/**
	 * Sets the cleaness of the pet.
	 *
	 * @param newCleaness the new cleaness of the pet
	 */
	public void setCleaness(int newCleaness) {
		cleanness = newCleaness;
	}

	/**
	 * Gets the checks if the pet is sick.
	 *
	 * @return the checks if the pet is sick
	 */
	public Boolean getIsSick() {
		return isSick;
	}

	/**
	 * Sets the checks if is sick.
	 *
	 * @param newIsSick the new checks if is sick
	 */
	public void setIsSick(Boolean newIsSick) {
		isSick = newIsSick;
	}

	/**
	 * Gets the checks if is asleep.
	 *
	 * @return the checks if is asleep
	 */
	public Boolean getIsAsleep() {
		return isAsleep;
	}

	/**
	 * Sets the checks if is asleep.
	 *
	 * @param newIsAsleep the new checks if is asleep
	 */
	public void setIsAsleep(Boolean newIsAsleep) {
		isAsleep = newIsAsleep;
	}

	/**
	 * Gets the checks if is misbehaving.
	 *
	 * @return the checks if is misbehaving
	 */
	public Boolean getIsMisBehaving() {
		return isMisbehaving;
	}

	/**
	 * Sets the checks if is misbehaving.
	 *
	 * @param newIsMisbehaving the new checks if is misbehaving
	 */
	public void setIsMisBehaving(Boolean newIsMisbehaving) {
		isMisbehaving = newIsMisbehaving;
	}

	/**
	 * Gets the checks if is alive.
	 *
	 * @return the checks if is alive
	 */
	public Boolean getIsAlive() {
		return isAlive;
	}

	/**
	 * Sets the checks if is alive.
	 *
	 * @param newIsAlive the new checks if is alive
	 */
	public void setIsAlive(boolean newIsAlive) {
		isAlive = newIsAlive;

	}

	/**
	 * Gets the checks for been dead.
	 *
	 * @return the checks for been dead
	 */
	public boolean getHasBeenDead() {
		return hasBeenDead;
	}

	/**
	 * Sets the checks for been dead.
	 *
	 * @param newhasBeenDead the new checks for been dead
	 */
	public void setHasBeenDead(boolean newhasBeenDead) {
		hasBeenDead = newhasBeenDead;
	}
	
	/**
	 * Feed action method.May increase pet happiness, healthiness, decrease hunger.May also invoke random
	 * events like misbehaving or sick.
	 *
	 * @param food the food
	 */
	public void feed(Food food) { //feed action
		int max = 100;
		int min = 0;
		Random rand = new Random();
		int randomNum = rand.nextInt((max - min) + 1) + min;//generate a random number for invoke random event
		if(getIsAlive()==false){
			JOptionPane.showMessageDialog(null, "pet is dead");
		}
		else if (getActions() == 2) {
			JOptionPane.showMessageDialog(null, getName()+ " has completed 2 actions today.");
		} else if (getIsAsleep() == true) {      //if asleep,wake up to feed or abort feed action
			JOptionPane.showMessageDialog(null, getName()+ " is asleep.Wake it up to complete this action.");
		} else if (randomNum > 25 && randomNum < 40) {    //if random within range,invoke misbehaving event
			setIsMisBehaving(true);
			int reply = JOptionPane.showConfirmDialog(null, getName()+ " is misBehaving.Punishment?");//player can
			if (reply == JOptionPane.YES_OPTION) {                //select to punish it or not
				punishment();
				setIsMisBehaving(false);
			}
		} else if (randomNum > 90) { //if random within range, invoke sick event
			setIsSick(true);
			if (getHealthiness() - 10 >= 0) {
				setHealthiness(getHealthiness() - 10);
				int reply = JOptionPane.showConfirmDialog(null, getName()+ " is sick.Treatment?");
				if (reply == JOptionPane.YES_OPTION) {      //player can choose to treat it,healthiness increase by 5
					treatment(Home.currentPlayer);
					setIsSick(false);
					setHealthiness(getHealthiness() + 5);
				}
			} else {
				setIsAlive(false);  //if healthiness drop to 0, pet wil die
				int reply = JOptionPane.showConfirmDialog(null, getName()+ " is dead.Revive it?");
				if (reply == JOptionPane.YES_OPTION) {//player can choose to revive the pet
					revive();                         //but only one chance
					setIsAlive(true);
					setHasBeenDead(true);

				} 
			}
			
		} else if (food.getStock() > 0) {           //if food stock enough,feed pet
			if (food.getName().equalsIgnoreCase(getFavFood())) {
				int newHappiness = getHappiness() + 10;
				setHappiness(newHappiness);
			} else {
				int newHappiness = getHappiness() + 5;
				setHappiness(newHappiness);
			}
			if (getHunger() - food.getNutrition() >= 0) {  //if full, set hunger to 0
				setHunger(getHunger() - food.getNutrition());
			} else {
	            JOptionPane.showMessageDialog(null, getName()+" is full");
			}
			setWeight(getWeight() + food.getNutrition());
			setActions(getActions() + 1);
			if (food.getNutrition() > 20) {  //if eat too much, cleanness gets lower
				if (getCleanness() - 15 >= 0) {
					setCleaness(getCleanness() - 15);
				} else {
					setCleaness(0);
				}
			}
			if (food.getStock() - 1 >= 0) {  //updates stock
				int newStock = food.getStock() - 1;
				food.setStock(newStock);
			} else {
				food.setStock(0);
			}

		} else {
			JOptionPane.showMessageDialog(null, food.getName()//warning if stock runs up
					+ " has been used up");
		}
	}

	/**
	 * Play action method.May increase pet healthiness,hunger and decrease cleanness
	 *
	 * @param toy the toy
	 */
	public void play(Toy toy) {
		if(getIsAlive()==false){
				JOptionPane.showMessageDialog(null, "Pet is dead");
			} 
		else if (getActions() == 2) {
			JOptionPane.showMessageDialog(null, getName()//abort if already completed 2 actions
					+ " has completed 2 actions today.");
		} else if (getIsAsleep() == true) {
			JOptionPane.showMessageDialog(null, getName()//abort if asleep or wake up to proceed
					+ " is asleep.Wake it up to complete this action.");
		}else {
			if (toy.getStock() > 0 ) {      //when toy stock enough,play
				if (toy.getName().equalsIgnoreCase(favToy)) {
					setHappiness(getHappiness() + 10);
				} else {
					setHappiness(getHappiness() + 5);
				}
				setHealthiness(getHealthiness() + 5);//play increase healthiness
				setHunger(getHunger() + 5);         //increase hunger
				setTiredness(getTiredness() + 5);   //and tiredness
				if (getCleanness() - 5 >= 0) {
					setCleaness(getCleanness() - 5);
				} else {
					setCleaness(0);
				}
				setActions(getActions() + 1);     //increase one action
				if (toy.getDamage() < 4) {       //toy damage increase by one, if damage>5, stock-1
					int newDamage = toy.getDamage() + 1;
					toy.setDamage(newDamage);
				} else {
					if (toy.getStock() - 1 >= 0) {//update toy stock
						int newStock = toy.getStock() - 1;
						toy.setStock(newStock);
						toy.setDamage(0);
					} else {
						toy.setStock(0);
					}
					JOptionPane.showMessageDialog(null,"This " + toy.getName() + " is broken.");
				}
			} else {
				JOptionPane.showMessageDialog(null, toy.getName()
						+ " has been used up");
			}
		}
	}

	/**
	 * Sleep action method.May reduce pet tiredness.
	 */
	public void sleep() {
		if(getIsAlive()==false){
			JOptionPane.showMessageDialog(null, "Pet is dead");
		}
		else if (getActions() == 2) {
			JOptionPane.showMessageDialog(null, getName()
					+ " has completed 2 actions today.");
		} else if(getIsAsleep()==true){
			JOptionPane.showMessageDialog(null, "Pet is already asleep");
		}
		else{
			setIsAsleep(true);
			if (getTiredness() - 5 >= 0) {      //sleep reduce tiredness
				setTiredness(getTiredness() - 5);
				setActions(getActions() + 1); //increase action by one
			} else {
				setTiredness(0);
			}
		}
	}

	/**
	 * Wake up action method. When pet asleep, wake it up to carry out other actions.
	 */
	public void wakeUp() {
	    if(getIsAlive()==false){
			JOptionPane.showMessageDialog(null, "Pet is dead");
		}
	    else if (getIsAsleep() == true) {
			setIsAsleep(false);
		} else {
			JOptionPane.showMessageDialog(null, getName() + "is already awake.");
		}
	}

	/**
	 * Toilet action method.May increase cleanness, and reduce weight
	 */
	public void toilet() {
		if(getIsAlive()==false){
			JOptionPane.showMessageDialog(null, "Pet is dead");
		}
		else if (getActions() == 2) {
			JOptionPane.showMessageDialog(null, getName()
					+ " has completed 2 actions today.");
		} else if (getIsAsleep() == true) {
			JOptionPane.showMessageDialog(null, getName()
					+ " is asleep.Wake it up to complete this action.");
		} else {
			setCleaness(getCleanness() + 3);
			setWeight(getWeight() - 5);
			setHappiness(getHappiness() + 2);
			setActions(getActions() + 1);
		}
	}

	/**
	 * Punishment action method.When pet is misbehaving, punishment will change status to not misbehaving
	 * but reduce its happiness
	 */
	public void punishment() {
		setHappiness(getHappiness() - 3);
		setIsMisBehaving(false);
	}

	/**
	 * Treatment action method.When pet is sick, treatment will change status to not sick
	 * but will cost player money by 5
	 *
	 * @param player the player
	 */
	public void treatment(Player player) {
		int newMoney = player.getMoney() - 5;
		player.setMoney(newMoney);
		setHealthiness(getHealthiness() + 5);
		setHappiness(getHappiness() + 3);
		setIsSick(false);
	}

	/**
	 * Revive action method.When pet is dead,player can revive it
	 * but player only have one chance
	 */
	public void revive() {
		if (getHasBeenDead() == false) {
			setHasBeenDead(true);
			JOptionPane.showMessageDialog(null, getSpecies() + getName()
					+ " is revived!");
			setIsAlive(true);
			setHunger(getHunger() + 20);
			setTiredness(getTiredness() - 20);
			setCleaness(getCleanness() + 20);
		} else {
			setHasBeenDead(true);
	    	setCleaness(0);
	    	setHappiness(0);
	    	setHunger(0);
	    	setTiredness(0);
	    	setWeight(0);
	    	setIsAlive(false);
			JOptionPane.showMessageDialog(null, "Your pet is dead.You have run out of chances to revive it.");
		}
	}


}