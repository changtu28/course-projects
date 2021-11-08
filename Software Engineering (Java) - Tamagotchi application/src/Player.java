import java.util.ArrayList;

import javax.swing.JOptionPane;

/**
 * The Class Player.
 */
public class Player {
	
	/** The player name. */
	private String name;
	
	/** The number of pets that current player have. */
	private int numofPets;
	
	/** The total score of current player. */
	private int totalScore = 0;
	
	/** The number of rounds of the game, set up in First frame. */
	public static int rounds;
	
	/** The current day of current player. */
	private int currentDay = 1;
	
	/** The players list. */
	public ArrayList<Player> players = new ArrayList<Player>();
	
	/** The pets list of current player. */
	private ArrayList<Pet> pets;
	
	/** The foods list of current player. */
	private ArrayList<Food> foods = new ArrayList<Food>();
	
	/** The toys list of current player. */
	private ArrayList<Toy> toys = new ArrayList<Toy>();
	
	/** The balance of current player. */
	private int money = 500;

	/**
	 * Instantiates a new player.
	 *
	 * @param playerName the player name
	 * @param petNum the pet num
	 * @param pets the pets
	 */
	public Player(String playerName, int petNum, ArrayList<Pet> pets) {
		// TODO Auto-generated constructor stub
		this.name = playerName;
		this.numofPets = petNum;
		this.pets = pets;
		this.foods.add(new Bone("bone", 0));   //add bone to foods list, index at 0
		this.foods.add(new Bread("bread", 0)); //add bread to foods list, index at 1
		this.foods.add(new Corn("corn", 0));   //add corn to foods list, index at 2
		this.foods.add(new Fish("fish", 0));   //add fish to foods list, index at 3
		this.toys.add(new Ball("ball"));       //add ball to toys list, index at 0
		this.toys.add(new Doll("doll"));       //add doll to toys list, index at 1
		this.toys.add(new Robot("robot"));     //add robot to toys list, index at 2
		this.toys.add(new Frisbee("frisbee")); //add frisbee to toys list, index at 3 

	}

	/**
	 * Gets the name of player.
	 *
	 * @return the player name
	 */
	public String getName() {
		return name;
	}
	public int  getPetNum() {
		return numofPets;
	}

	/**
	 * Gets the pets list of current player.
	 *
	 * @return the pets
	 */
	public ArrayList<Pet> getPets() {
		return pets;
	}

	/**
	 * Sets the pets list of current player.
	 *
	 * @param pets the new pets
	 */
	public void setPets(ArrayList<Pet> pets) {
		this.pets = pets;
	}

	/**
	 * Gets the foods list of current player.
	 *
	 * @return the foods
	 */
	public ArrayList<Food> getFoods() {
		return foods;
	}

	/**
	 * Gets the toys list of current player.
	 *
	 * @return the toys
	 */
	public ArrayList<Toy> getToys() {
		return toys;
	}

	/**
	 * Gets the balance of current player.
	 *
	 * @return the money
	 */
	public int getMoney() {
		return money;
	}

	/**
	 * Sets the balance of current player.
	 *
	 * @param newMoney the new money
	 */
	public void setMoney(int newMoney) {
		money = newMoney;
	}

	/**
	 * Gets the current day of current player.
	 *
	 * @return the current day
	 */
	public int getCurrentDay() {
		return currentDay;
	}

	/**
	 * Sets the current day of current player.
	 *
	 * @param newCurrentDay the new current day
	 */
	public void setCurrentDay(int newCurrentDay) {
		currentDay = newCurrentDay;
	}

	/**
	 * Move to next day.
	 *
	 * @param currentDay the current day
	 * @param rounds the rounds
	 */
	public void movetoNextDay(int currentDay, int rounds) {
		if (getCurrentDay() < rounds) {         //check if next day beyond rounds
			setCurrentDay(getCurrentDay() + 1);
			for (Pet who : pets) {
				if(who.getIsAlive()==true){
					if (who.getIsSick() == true) {    //if pet is sick and not get treated, its healthiness drop 10
						if(who.getHealthiness()<0){
							who.setIsAlive(false);  //if healthiness drop to 0, pet will die
							int reply = JOptionPane.showConfirmDialog(null, getName()+ " is dead.Revive it?");
						    if (reply == JOptionPane.YES_OPTION) {//player can choose to revive the pet
						    	who.revive();                         //but only one chance
						    	who.setIsSick(false);
						    	who.setHealthiness(50);
						    }else{
						    	who.setCleaness(0);  //when choose not to revive
						    	who.setHappiness(0);
						    	who.setIsAlive(false);
						    	who.setHasBeenDead(true);
						    	who.setHunger(0);
						    	who.setTiredness(0);
						    	who.setWeight(0);
						    }
						}else{                               //when sick and alive
						    who.setHealthiness(who.getHealthiness() - 10);
							who.setActions(0);             //set completed actions of each pet to 0
							who.setCleaness(who.getCleanness() + 5); //increase each pet's cleanness by 5
							who.setHappiness(who.getHappiness() + 5);//increase each pet's happiness by 5
							who.setHunger(who.getHunger() + 5);      //increase each pet's hunger by 5
						} 
					}
				   else{                              //when not sick and alive
						who.setActions(0);             //set completed actions of each pet to 0
						who.setCleaness(who.getCleanness() + 5); //increase each pet's cleanness by 5
						who.setHappiness(who.getHappiness() + 5);//increase each pet's happiness by 5
						who.setHunger(who.getHunger() + 5);      //increase each pet's hunger by 5

				   }  
			   }else{

				who.setCleaness(0);
		    	who.setHappiness(0);
		    	who.setHunger(0);
		    	who.setTiredness(0);
		    	who.setWeight(0);
		   }
			
		}
	   }

	}

	/**
	 * Gets the total score of current player, which adds up all his pets' cleanness, happiness,
	 * healthiness and minus hunger and tiredness.
	 *
	 * @return the total score
	 */
	public int getTotalScore() { 
		for (Pet who : pets) {
			totalScore += who.getCleanness() + who.getHappiness()
					+ who.getHealthiness() - who.getHunger()
					- who.getTiredness();
		}
		return totalScore;
	}

}