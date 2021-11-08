import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Image;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.plaf.basic.BasicTabbedPaneUI;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JTabbedPane;
import javax.swing.JLabel;
import javax.swing.JButton;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;
import java.awt.Color;
import javax.swing.SwingConstants;

/**
 * The Class Menu that carries out shopping, feeding, playing actions,etc and displaying final scores.
 */
public class Menu extends JFrame {

	/** The content pane. */
	private JPanel contentPane;
	
	/** The current pet confirmed by pressing the pet button in the left column. */
	private Pet currentPet = Home.currentPlayer.getPets().get(0);
	
	/** The food index. */
	private int foodIndex;
	
	/** The toy index. */
	private int toyIndex;

	/**
	 * Launch the application.
	 *
	 * @param args the arguments
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Menu frame = new Menu();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	public Menu() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(700, 500);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		final JLabel lblPlayerName = new JLabel("player name");   //Greeting!Display current player and current day
		lblPlayerName.setText("Hi, " + Home.currentPlayer.getName()
				+ "! This is Day " + Home.currentPlayer.getCurrentDay());
		lblPlayerName.setBounds(6, 8, 200, 50);
		contentPane.add(lblPlayerName);

		JButton btnHome = new JButton("Switch player"); //press this button to switch to Home frame and select another 
		btnHome.setFont(new Font("Lucida Grande", Font.PLAIN, 11));//player as current player
		btnHome.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				dispose();
				Home frame4 = new Home();
				frame4.setVisible(true);
			}
		});
		btnHome.setBounds(0, 52, 119, 29);
		contentPane.add(btnHome);

		final Image imgShop = new ImageIcon(this.getClass().getResource(       
				"/shop-icon.png")).getImage();
		final Image imgFood = new ImageIcon(this.getClass().getResource(
				"/food-icon.png")).getImage();
		final Image imgPlay = new ImageIcon(this.getClass().getResource(
				"/sport-icon.png")).getImage();
		final Image imgSleep = new ImageIcon(this.getClass().getResource(
				"/sleep-icon.png")).getImage();
		final Image imgBathroom = new ImageIcon(this.getClass().getResource(
				"/toilet-icon.png")).getImage();
		final Image imgStatus = new ImageIcon(this.getClass().getResource(
				"/info-icon.png")).getImage();
		final Image imgNextDay = new ImageIcon(this.getClass().getResource(
				"/nextDay-icon.png")).getImage();
		final Image imgCat = new ImageIcon(this.getClass().getResource(
				"/kitten-icon.png")).getImage();
		final Image imgDog = new ImageIcon(this.getClass().getResource(
				"/dog-icon.png")).getImage();
		final Image imgRabbit = new ImageIcon(this.getClass().getResource(
				"/bunny-icon.png")).getImage();
		final Image imgDuck = new ImageIcon(this.getClass().getResource(
				"/duck-icon.png")).getImage();
		final Image imgPig = new ImageIcon(this.getClass().getResource(
				"/pig-icon.png")).getImage();
		final Image imgHamster = new ImageIcon(this.getClass().getResource(
				"/hamster-icon.png")).getImage();
		final Image imgBone = new ImageIcon(this.getClass().getResource(
				"/bone-icon.png")).getImage();
		final Image imgBread = new ImageIcon(this.getClass().getResource(
				"/bread-icon.png")).getImage();
		final Image imgFish = new ImageIcon(this.getClass().getResource(
				"/fish-icon.png")).getImage();
		final Image imgCorn = new ImageIcon(this.getClass().getResource(
				"/corn-icon.png")).getImage();
		final Image imgBall = new ImageIcon(this.getClass().getResource(
				"/ball-icon.png")).getImage();
		final Image imgDoll = new ImageIcon(this.getClass().getResource(
				"/doll-icon.png")).getImage();
		final Image imgRobot = new ImageIcon(this.getClass().getResource(
				"/robot-icon.png")).getImage();
		final Image imgFrisbee = new ImageIcon(this.getClass().getResource(
				"/frisbee-icon.png")).getImage();
		final Image imgBalance = new ImageIcon(this.getClass().getResource(
				"/cash-icon.png")).getImage();
		final Image imgSleep2 = new ImageIcon(this.getClass().getResource(
				"/sleep2-icon.png")).getImage();
		final Image imgWakeUp = new ImageIcon(this.getClass().getResource(
				"/wakeUp-icon.png")).getImage();
		final Image imgToilet = new ImageIcon(this.getClass().getResource(
				"/hottub-icon.png")).getImage();

		final JTabbedPane tabbedPane = new JTabbedPane();    //override the calculateTabHeight method to adjust the 
//		tabbedPane.setUI(new BasicTabbedPaneUI() {         //tab size so that the image icons can fit in
//			@Override
//			protected int calculateTabHeight(int tabPlacement, int tabIndex,
//					int fontHeight) {
//				return 70; 
//			}
//		});
		// final JTabbedPane tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		tabbedPane.setForeground(new Color(135, 206, 250));
		tabbedPane.setFont(new Font("Lucida Grande", Font.PLAIN, 70));
		tabbedPane.setBounds(131, 70, 563, 365);
		contentPane.add(tabbedPane);

		 String titles[] = { "status", "shop", "feed", "play", "sleep", "bathroom" };//add titles and indices to each tab 
		    for (int i = 0, n = titles.length; i < n; i++) {                         //for later use of changeListener
		      getContentPane().add(tabbedPane, titles[i]);
		    }

	
		
		JLabel lblStatus = new JLabel();                 //status tab that shows curentPet status
		lblStatus.setPreferredSize(new Dimension(60, 60));
		lblStatus.setIcon(new ImageIcon(imgStatus));
		final JPanel panelStatus = new JPanel();
		tabbedPane.addTab("", panelStatus);
		tabbedPane.setTabComponentAt(0, lblStatus);
		panelStatus.setLayout(null);

		final JLabel lblName = new JLabel("Name:" + currentPet.getName());//name label
		lblName.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblName.setBounds(20, 22, 214, 16);
		panelStatus.add(lblName);

		final JLabel lblSpecies = new JLabel("Species:"
				+ currentPet.getSpecies());
		lblSpecies.setFont(new Font("Lucida Grande", Font.PLAIN, 15));//species label
		lblSpecies.setBounds(20, 50, 239, 16);
		panelStatus.add(lblSpecies);

		final JLabel lblFavouriteFood = new JLabel("Favourite food:"//favorite food label
				+ currentPet.getFavFood());
		lblFavouriteFood.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblFavouriteFood.setBounds(20, 78, 239, 16);
		panelStatus.add(lblFavouriteFood);

		final JLabel lblFavouriteToy = new JLabel("Favourite toy:" //favorite toy label
				+ currentPet.getFavToy());
		lblFavouriteToy.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblFavouriteToy.setBounds(20, 106, 239, 16);
		panelStatus.add(lblFavouriteToy);

		final JLabel lblWeight = new JLabel("Weight:" + currentPet.getWeight());//weight label
		lblWeight.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblWeight.setBounds(20, 134, 183, 16);
		panelStatus.add(lblWeight);
        
		String hasBeenDead;
		if(currentPet.getHasBeenDead()==true){
			hasBeenDead = "Yes";
		}else{
			hasBeenDead = "No";
		}
		final JLabel lblHasBeenDead = new JLabel("Has been dead:"     //hasBeenDead label.Each pet has one chance to be revived
				+ currentPet.getHasBeenDead());
		lblHasBeenDead.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblHasBeenDead.setBounds(20, 162, 239, 16);
		panelStatus.add(lblHasBeenDead);

		final JLabel lblTiredness = new JLabel("Tiredness:"        //tiredness label
				+ currentPet.getTiredness());
		lblTiredness.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblTiredness.setBounds(20, 190, 251, 16);
		panelStatus.add(lblTiredness);

		final JLabel lblHunger = new JLabel("Hunger:" + currentPet.getHunger());//hunger label.hunger relates to
		lblHunger.setFont(new Font("Lucida Grande", Font.PLAIN, 15));           //healthiness.if hunger too low pet may die
		lblHunger.setBounds(292, 134, 188, 16);
		panelStatus.add(lblHunger);

		final JLabel lblCleanness = new JLabel("Cleanness:"      //cleanness label.Playing may reduce cleanness.
				+ currentPet.getCleanness());                    //Going to bathroom raise cleanness
		lblCleanness.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblCleanness.setBounds(292, 23, 188, 16);
		panelStatus.add(lblCleanness);

		final JLabel lblHappiness = new JLabel("Happiness:"      //happiness label. Feed and play may increase happiness
				+ currentPet.getHappiness());
		lblHappiness.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblHappiness.setBounds(292, 51, 188, 16);
		panelStatus.add(lblHappiness);

		String isSick;                                
		if(currentPet.getIsSick()==true){
			isSick = "Yes";
		}else{
			isSick = "No";
		}
		final JLabel lblIsSick = new JLabel("Is sick:" + isSick);//isSick label, telling if pet is sick or not
		lblIsSick.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblIsSick.setBounds(292, 79, 188, 16);
		panelStatus.add(lblIsSick);

		String isMisbehaving;                                
		if(currentPet.getIsMisBehaving()==true){
			isMisbehaving = "Yes";
		}else{
			isMisbehaving = "No";
		}
		final JLabel lblIsMisbehaving = new JLabel("Is misbehaving:"//isMisbehaving label
				+ isMisbehaving);
		lblIsMisbehaving.setFont(new Font("Lucida Grande", Font.PLAIN, 15));
		lblIsMisbehaving.setBounds(292, 107, 208, 16);
		panelStatus.add(lblIsMisbehaving);
		
	    ChangeListener changeListener = new ChangeListener() {    // A changeListener that updates target tab panel responding to tab switches 
		      public void stateChanged(ChangeEvent changeEvent) {
				lblName.setText("Name:" + currentPet.getName());
				lblSpecies.setText("Species:" + currentPet.getSpecies());
				lblCleanness.setText("Cleanness:" + currentPet.getCleanness());
				lblFavouriteFood.setText(("Favourite food:" + currentPet
						.getFavFood()));
				lblFavouriteToy.setText(("Favourite toy:" + currentPet
						.getFavToy()));
				lblHappiness.setText("Happiness:" + currentPet.getHappiness());
				lblHasBeenDead.setText("Has been dead:"
						+ currentPet.getHasBeenDead());
				lblHunger.setText("Hunger:" + currentPet.getHunger());
				String isMisbehaving;                                
				if(currentPet.getIsMisBehaving()==true){
					isMisbehaving = "Yes";
				}else{
					isMisbehaving = "No";
				}
				lblIsMisbehaving.setText("Is misbehaving:"
						+ isMisbehaving);
				String isSick;                                
				if(currentPet.getIsSick()==true){
					isSick = "Yes";
				}else{
					isSick = "No";
				}
				lblIsSick.setText("Is sick:" + isSick);
				lblTiredness.setText("Tiredness:" + currentPet.getTiredness());
				lblWeight.setText("Weight:" + currentPet.getWeight());
		      }
		    };
		    tabbedPane.addChangeListener(changeListener);

		JLabel lblShop = new JLabel();                 //shop tab
		lblShop.setPreferredSize(new Dimension(60, 60));
		lblShop.setIcon(new ImageIcon(imgShop));
		JPanel panelShop = new JPanel();
		tabbedPane.addTab("", panelShop);
		tabbedPane.setTabComponentAt(1, lblShop);
		panelShop.setLayout(null);

		JLabel lblBone = new JLabel("");      //Bone label
		lblBone.setIcon(new ImageIcon(imgBone));
		lblBone.setBounds(6, 16, 70, 80);
		panelShop.add(lblBone);

		JLabel lblFish = new JLabel("");      //Fish label
		lblFish.setIcon(new ImageIcon(imgFish));
		lblFish.setBounds(109, 16, 70, 80);
		panelShop.add(lblFish);

		JLabel lblBread = new JLabel("");      //Bread label
		lblBread.setIcon(new ImageIcon(imgBread));
		lblBread.setBounds(214, 16, 70, 80);
		panelShop.add(lblBread);

		JLabel lblCorn = new JLabel("");       //Corn label
		lblCorn.setIcon(new ImageIcon(imgCorn));
		lblCorn.setBounds(319, 16, 70, 80);
		panelShop.add(lblCorn);

		JLabel lblBonePrice = new JLabel("price: $5"); //Bone price label
		lblBonePrice.setBounds(6, 97, 61, 16);
		panelShop.add(lblBonePrice);

		JLabel lblFishPrice = new JLabel("price: $8"); //Fish price label
		lblFishPrice.setBounds(109, 97, 61, 16);
		panelShop.add(lblFishPrice);

		JLabel lblBreadPrice = new JLabel("price: $2"); //Bread price label
		lblBreadPrice.setBounds(214, 97, 61, 16);
		panelShop.add(lblBreadPrice);

		JLabel lblCornPrice = new JLabel("price: $7"); //Corn price label
		lblCornPrice.setBounds(319, 97, 61, 16);
		panelShop.add(lblCornPrice);

		final JLabel lblBalance = new JLabel("$"    //balance label showing current player's balance
				+ Home.currentPlayer.getMoney());
		lblBalance.setBounds(409, 6, 127, 60);
		lblBalance.setFont(new Font("Lucida Grande", Font.PLAIN, 20));
		lblBalance.setIcon(new ImageIcon(imgBalance));
		panelShop.add(lblBalance);

		final JLabel lblBoneStock = new JLabel("stock:"  //Bone stock label
				+ Home.currentPlayer.getFoods().get(0).getStock());
		lblBoneStock.setBounds(19, 106, 61, 16);
		final JLabel lblFishStock = new JLabel("stock:"  //Fish stock label
				+ Home.currentPlayer.getFoods().get(3).getStock());
		lblFishStock.setBounds(117, 106, 61, 16);
		final JLabel lblBreadStock = new JLabel("stock:" //Bread stock label
				+ Home.currentPlayer.getFoods().get(1).getStock());
		lblBreadStock.setBounds(221, 106, 61, 16);
		final JLabel lblCornStock = new JLabel("stock:"  //Corn stock label
				+ Home.currentPlayer.getFoods().get(2).getStock());
		lblCornStock.setBounds(324, 106, 61, 16);

		class MyActionListener2 implements ActionListener { // an customized actionListener
															// for buy food buttons
			private String foodName;

			public MyActionListener2(String foodName) {
				this.foodName = foodName;
			}

			public void actionPerformed(ActionEvent e) {
				switch (foodName) {    //return selected food's index
				case "bone":
					foodIndex = 0;
					break;
				case "bread":
					foodIndex = 1;
					break;
				case "corn":
					foodIndex = 2;
					break;
				case "fish":
					foodIndex = 3;
					break;
				default:
					foodIndex = 0;
				}

				int newMoney = Home.currentPlayer.getMoney()
						- Home.currentPlayer.getFoods().get(foodIndex).getPrice();
				if (newMoney >= 0) {
					int newStock = Home.currentPlayer.getFoods().get(foodIndex).getStock();
					Home.currentPlayer.getFoods().get(foodIndex).setStock(newStock + 1);//update stock
					Home.currentPlayer.setMoney(newMoney);
					lblBalance.setText("$" + Home.currentPlayer.getMoney());  //update balance
					switch (foodIndex) {
					case 0:
						lblBoneStock.setText("stock:"+ Home.currentPlayer.getFoods().get(0).getStock());
						break;
					case 1:
						lblBreadStock.setText("stock:"+ Home.currentPlayer.getFoods().get(1).getStock());
						break;
					case 2:
						lblCornStock.setText("stock:"+ Home.currentPlayer.getFoods().get(2).getStock());
						break;
					case 3:
						lblFishStock.setText("stock:"+ Home.currentPlayer.getFoods().get(3).getStock());
						break;
					default:
						foodIndex = 0;
					}
				} else {
					JOptionPane.showMessageDialog(null,Home.currentPlayer.getName() // won't carrying out buy
									+ "has run out of money.");                  //action when short of money
				}
			}
		}

		final JLabel lblBallStock = new JLabel("stock:"       //ball stock label    
				+ Home.currentPlayer.getToys().get(0).getStock());
		lblBallStock.setBounds(17, 110, 61, 16);

		final JLabel lblDollStock = new JLabel("stock:"       //doll stock label
				+ Home.currentPlayer.getToys().get(1).getStock());
		lblDollStock.setBounds(124, 113, 61, 16);

		final JLabel lblRobotStock = new JLabel("stock:"      //robot stock label
				+ Home.currentPlayer.getToys().get(2).getStock());
		lblRobotStock.setBounds(222, 113, 61, 16);

		final JLabel lblFrisbeeStock = new JLabel("stock:"    //frisbee stock label
				+ Home.currentPlayer.getToys().get(3).getStock());
		lblFrisbeeStock.setBounds(323, 113, 61, 16);

		final JLabel lblBallDamage = new JLabel("damage:"    //ball damage label
				+ Home.currentPlayer.getToys().get(0).getDamage());
		lblBallDamage.setBounds(17, 132, 94, 16);

		final JLabel lblDollDamage = new JLabel("damage:"     //doll damage label
				+ Home.currentPlayer.getToys().get(1).getDamage());
		lblDollDamage.setBounds(124, 132, 94, 16);

		final JLabel lblRobotDamage = new JLabel("damage:"    //robot damage label
				+ Home.currentPlayer.getToys().get(2).getDamage());
		lblRobotDamage.setBounds(222, 132, 94, 16);

		final JLabel lblFrisbeeDamage = new JLabel("damage:"  //frisbee damage label
				+ Home.currentPlayer.getToys().get(3).getDamage());
		lblFrisbeeDamage.setBounds(323, 132, 94, 16);

		class MyActionListener3 implements ActionListener { // an customized actionListener
															// for buy toy buttons
			private String toyName;

			public MyActionListener3(String toyName) {
				this.toyName = toyName;
			}

			public void actionPerformed(ActionEvent e) {
				switch (toyName) {    //return selected toy's index
				case "ball":
					toyIndex = 0;
					break;
				case "doll":
					toyIndex = 1;
					break;
				case "robot":
					toyIndex = 2;
					break;
				case "frisbee":
					toyIndex = 3;
					break;
				default:
					toyIndex = 0;
				}

				int newMoney = Home.currentPlayer.getMoney()
						- Home.currentPlayer.getToys().get(toyIndex).getPrice();
				if (newMoney >= 0) {
					int newStock = Home.currentPlayer.getToys().get(toyIndex).getStock();//update stock
					Home.currentPlayer.getToys().get(toyIndex).setStock(newStock + 1);
					Home.currentPlayer.setMoney(newMoney);
					lblBalance.setText("$" + Home.currentPlayer.getMoney());//update balance
					switch (toyIndex) {
					case 0:
						lblBallStock.setText("stock:"+ Home.currentPlayer.getToys().get(0).getStock());
						break;
					case 1:
						lblDollStock.setText("stock:"+ Home.currentPlayer.getToys().get(1).getStock());
						break;
					case 2:
						lblRobotStock.setText("stock:"+ Home.currentPlayer.getToys().get(2).getStock());
						break;
					case 3:
						lblFrisbeeStock.setText("stock:"+ Home.currentPlayer.getToys().get(3).getStock());
						break;
					default:
						foodIndex = 0;
					}
				} else {
					JOptionPane.showMessageDialog(null,
							Home.currentPlayer.getName()+ "has run out of money.");
				}
			}
		}

		JButton btnBuyBone = new JButton("Buy");    //buy bone button
		btnBuyBone.addActionListener(new MyActionListener2("bone"));
		btnBuyBone.setFont(new Font("Lucida Grande", Font.PLAIN, 14));
		btnBuyBone.setBounds(0, 118, 70, 29);
		panelShop.add(btnBuyBone);

		JButton btnBuyFish = new JButton("Buy");    //buy fish button
		btnBuyFish.addActionListener(new MyActionListener2("fish"));
		btnBuyFish.setFont(new Font("Lucida Grande", Font.PLAIN, 14));
		btnBuyFish.setBounds(109, 119, 70, 29);
		panelShop.add(btnBuyFish);

		JButton btnBuyBread = new JButton("Buy");   //buy bread button
		btnBuyBread.addActionListener(new MyActionListener2("bread"));
		btnBuyBread.setFont(new Font("Lucida Grande", Font.PLAIN, 14));
		btnBuyBread.setBounds(205, 119, 70, 29);
		panelShop.add(btnBuyBread);

		JButton btnBuyCorn = new JButton("Buy");    //buy corn button
		btnBuyCorn.addActionListener(new MyActionListener2("corn"));
		btnBuyCorn.setFont(new Font("Lucida Grande", Font.PLAIN, 14));
		btnBuyCorn.setBounds(307, 119, 70, 29);
		panelShop.add(btnBuyCorn);

		JLabel lblBall = new JLabel("");        //buy ball button
		lblBall.setIcon(new ImageIcon(imgBall));
		lblBall.setBounds(6, 143, 70, 80);
		panelShop.add(lblBall);

		JLabel lblDoll = new JLabel("");       //buy doll button
		lblDoll.setIcon(new ImageIcon(imgDoll));
		lblDoll.setBounds(109, 143, 70, 80);
		panelShop.add(lblDoll);

		JLabel lblRobot = new JLabel("");     //buy robot button
		lblRobot.setIcon(new ImageIcon(imgRobot));
		lblRobot.setBounds(205, 143, 70, 80);
		panelShop.add(lblRobot);

		JLabel lblFrisbee = new JLabel(""); //buy frisbee button
		lblFrisbee.setIcon(new ImageIcon(imgFrisbee));
		lblFrisbee.setBounds(307, 143, 70, 80);
		panelShop.add(lblFrisbee);

		JLabel lblBallPrice = new JLabel("price: $5"); // ball price label
		lblBallPrice.setBounds(6, 218, 61, 16);
		panelShop.add(lblBallPrice);

		JLabel lblDollPrice = new JLabel("price: $10"); //doll price label
		lblDollPrice.setBounds(109, 218, 70, 16);
		panelShop.add(lblDollPrice);

		JLabel lblRobotPrice = new JLabel("price: $7"); //robot price label
		lblRobotPrice.setBounds(214, 218, 61, 16);
		panelShop.add(lblRobotPrice);

		JLabel lblFrisbeePrice = new JLabel("price: $15"); //Frisbee price label
		lblFrisbeePrice.setBounds(307, 218, 73, 16);
		panelShop.add(lblFrisbeePrice);

		JButton btnBuyBall = new JButton("Buy");        //buy ball button
		btnBuyBall.addActionListener(new MyActionListener3("ball"));
		btnBuyBall.setFont(new Font("Lucida Grande", Font.PLAIN, 14));
		btnBuyBall.setBounds(0, 235, 70, 29);
		panelShop.add(btnBuyBall);

		JButton btnBuyDoll = new JButton("Buy");        //buy doll button
		btnBuyDoll.addActionListener(new MyActionListener3("doll"));
		btnBuyDoll.setFont(new Font("Lucida Grande", Font.PLAIN, 14));
		btnBuyDoll.setBounds(109, 235, 70, 29);
		panelShop.add(btnBuyDoll);

		JButton btnBuyRobot = new JButton("Buy");       //buy robot button
		btnBuyRobot.addActionListener(new MyActionListener3("robot"));
		btnBuyRobot.setFont(new Font("Lucida Grande", Font.PLAIN, 14));
		btnBuyRobot.setBounds(205, 235, 70, 29);
		panelShop.add(btnBuyRobot);

		JButton btnBuyFrisbee = new JButton("Buy");      //buy frisbee button
		btnBuyFrisbee.addActionListener(new MyActionListener3("frisbee"));
		btnBuyFrisbee.setFont(new Font("Lucida Grande", Font.PLAIN, 14));
		btnBuyFrisbee.setBounds(307, 235, 70, 29);
		panelShop.add(btnBuyFrisbee);

		JLabel lblFood = new JLabel();              //food tab
		lblFood.setPreferredSize(new Dimension(60, 60));
		lblFood.setIcon(new ImageIcon(imgFood));
		JPanel panelFood = new JPanel();
		tabbedPane.addTab("", panelFood);
		panelFood.setLayout(null);
		tabbedPane.setTabComponentAt(2, lblFood);

		panelFood.add(lblBoneStock);
		panelFood.add(lblFishStock);
		panelFood.add(lblBreadStock);
		panelFood.add(lblCornStock);

		final JButton btnPet1 = new JButton("");
		final JButton btnPet2 = new JButton("");
		final JButton btnPet3 = new JButton("");


		class MyActionListener4 implements ActionListener { // an customized
															// actionListener
															// for feed buttons
			private String foodName;

			public MyActionListener4(String foodName) {
				this.foodName = foodName;
			}

			public void actionPerformed(ActionEvent e) {
				if (currentPet.getActions() < 2) {     //only proceed when current pet haven't completed 2 actions
					switch (foodName) {
					case "bone":
						currentPet.feed(Home.currentPlayer.getFoods().get(0));
						lblBoneStock.setText("stock:"+ Home.currentPlayer.getFoods().get(0).getStock());
						break;
					case "bread":
						currentPet.feed(Home.currentPlayer.getFoods().get(1));
						lblBreadStock.setText("stock:"+ Home.currentPlayer.getFoods().get(1).getStock());
						break;
					case "corn":
						currentPet.feed(Home.currentPlayer.getFoods().get(2));
						lblCornStock.setText("stock:"+ Home.currentPlayer.getFoods().get(2).getStock());
						break;
					case "fish":
						currentPet.feed(Home.currentPlayer.getFoods().get(3));
						lblFishStock.setText("stock:"+ Home.currentPlayer.getFoods().get(3).getStock());
						break;
					}
					lblBalance.setText("$"+ Home.currentPlayer.getMoney());
				} else {
					JOptionPane.showMessageDialog(null, currentPet.getName()+ " has finished 2 actions today");
				}
			}
		}

		JButton btnFeedBone = new JButton("");      //feed bone button
		btnFeedBone.addActionListener(new MyActionListener4("bone"));
		btnFeedBone.setIcon(new ImageIcon(imgBone));
		btnFeedBone.setBounds(19, 19, 78, 80);
		panelFood.add(btnFeedBone);

		JButton btnFeedFish = new JButton("");     //feed fish button
		btnFeedFish.addActionListener(new MyActionListener4("fish"));
		btnFeedFish.setIcon(new ImageIcon(imgFish));
		btnFeedFish.setBounds(117, 19, 78, 80);
		panelFood.add(btnFeedFish);

		JButton btnFeedBread = new JButton("");   //feed bread button
		btnFeedBread.addActionListener(new MyActionListener4("bread"));
		btnFeedBread.setIcon(new ImageIcon(imgBread));
		btnFeedBread.setBounds(221, 19, 78, 80);
		panelFood.add(btnFeedBread);

		JButton btnFeedCorn = new JButton("");     //feed corn button
		btnFeedCorn.addActionListener(new MyActionListener4("corn"));
		btnFeedCorn.setIcon(new ImageIcon(imgCorn));
		btnFeedCorn.setBounds(326, 19, 78, 80);
		panelFood.add(btnFeedCorn);

		class MyActionListener5 implements ActionListener { // an customized
															// actionListener
															// for play buttons
			private String toyName;

			public MyActionListener5(String toyName) {
				this.toyName = toyName;
			}

			public void actionPerformed(ActionEvent e) {
				if (currentPet.getActions() < 2) {//only proceed when current pet haven't completed 2 actions
					switch (toyName) {
					case "ball":
						currentPet.play(Home.currentPlayer.getToys().get(0));
						lblBallStock.setText("stock:"+ Home.currentPlayer.getToys().get(0).getStock());
						lblBallDamage.setText("damage:"+ Home.currentPlayer.getToys().get(0).getDamage());
						break;
					case "doll":
						currentPet.play(Home.currentPlayer.getToys().get(1));
						lblDollStock.setText("stock:"+ Home.currentPlayer.getToys().get(1).getStock());
						lblDollDamage.setText("damage:"+ Home.currentPlayer.getToys().get(1).getDamage());
						break;
					case "robot":
						currentPet.play(Home.currentPlayer.getToys().get(2));
						lblRobotStock.setText("stock:"+ Home.currentPlayer.getToys().get(2).getStock());
						lblRobotDamage.setText("damage:"+ Home.currentPlayer.getToys().get(2).getDamage());
						break;
					case "frisbee":
						currentPet.play(Home.currentPlayer.getToys().get(3));
						lblFrisbeeStock.setText("stock:"+ Home.currentPlayer.getToys().get(3).getStock());
						lblFrisbeeDamage.setText("damage:"+ Home.currentPlayer.getToys().get(3).getDamage());
						break;
					}
				} else {
					JOptionPane.showMessageDialog(null, currentPet.getName()+ " has finished 2 actions today");
				}
			}
		}

		JLabel lblPlay = new JLabel();        //play tab
		lblPlay.setPreferredSize(new Dimension(60, 60));
		lblPlay.setIcon(new ImageIcon(imgPlay));
		JPanel panelPlay = new JPanel();
		tabbedPane.addTab("", panelPlay);
		panelPlay.setLayout(null);
		tabbedPane.setTabComponentAt(3, lblPlay);

		JButton btnPlayBall = new JButton(""); //play ball button
		btnPlayBall.addActionListener(new MyActionListener5("ball"));
		btnPlayBall.setIcon(new ImageIcon(imgBall));
		btnPlayBall.setBounds(17, 21, 75, 80);
		panelPlay.add(btnPlayBall);

		JButton btnPlayDoll = new JButton("");  //play doll button
		btnPlayDoll.addActionListener(new MyActionListener5("doll"));
		btnPlayDoll.setIcon(new ImageIcon(imgDoll));
		btnPlayDoll.setBounds(124, 21, 75, 80);
		panelPlay.add(btnPlayDoll);

		JButton btnPlayRobot = new JButton(""); //play robot button
		btnPlayRobot.addActionListener(new MyActionListener5("robot"));
		btnPlayRobot.setIcon(new ImageIcon(imgRobot));
		btnPlayRobot.setBounds(222, 21, 75, 80);
		panelPlay.add(btnPlayRobot);

		JButton btnPlayFrisbee = new JButton(""); //play frisbee button
		btnPlayFrisbee.addActionListener(new MyActionListener5("frisbee"));
		btnPlayFrisbee.setIcon(new ImageIcon(imgFrisbee));
		btnPlayFrisbee.setBounds(323, 21, 75, 80);
		panelPlay.add(btnPlayFrisbee);

		panelPlay.add(lblBallStock);
		panelPlay.add(lblDollStock);
		panelPlay.add(lblRobotStock);
		panelPlay.add(lblFrisbeeStock);
		panelPlay.add(lblBallDamage);
		panelPlay.add(lblDollDamage);
		panelPlay.add(lblRobotDamage);
		panelPlay.add(lblFrisbeeDamage);

		JLabel lblSleep = new JLabel();                     //sleep tab
		lblSleep.setPreferredSize(new Dimension(60, 60));
		lblSleep.setIcon(new ImageIcon(imgSleep));
		JPanel panelSleep = new JPanel();
		tabbedPane.addTab("", panelSleep);
		panelSleep.setLayout(null);

		JLabel lblGoToSleep = new JLabel("Go to sleep");  //Go to sleep label
		lblGoToSleep.setBounds(59, 208, 107, 21);
		panelSleep.add(lblGoToSleep);

		JButton btnGoToSleep = new JButton(""); //Go to sleep button
		btnGoToSleep.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(currentPet.getIsAlive()==false){
					JOptionPane.showMessageDialog(null, "Pet is dead");
				}
				else if(currentPet.getActions()<2&&currentPet.getIsAsleep()==false){
					int reply = JOptionPane.showConfirmDialog(null, "Let "+currentPet.getName()+" go to sleep?");
					if(reply==JOptionPane.YES_OPTION){
						currentPet.sleep();
					}
				}else{
					JOptionPane.showMessageDialog(null, currentPet.getName()+" has completed 2 actions today");
				}
			}
		});		
		btnGoToSleep.setIcon(new ImageIcon(imgSleep2));
		btnGoToSleep.setBounds(52, 83, 115, 113);
		panelSleep.add(btnGoToSleep);

		JButton btnWakeUp = new JButton("");     //Wake up button
		btnWakeUp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(currentPet.getIsAlive()==false){
					JOptionPane.showMessageDialog(null, "Pet is dead");
				}else{
	            int reply = JOptionPane.showConfirmDialog(null, "Wake up "+currentPet.getName()+"?");
				if(reply==JOptionPane.YES_OPTION){
		            currentPet.wakeUp();
				}
				}
			}
		});	
		btnWakeUp.setIcon(new ImageIcon(imgWakeUp));
		btnWakeUp.setBounds(357, 83, 115, 113);
		panelSleep.add(btnWakeUp);

		JLabel lblWakeUp = new JLabel("Wake up");  //wake up label
		lblWakeUp.setBounds(357, 210, 107, 21);
		panelSleep.add(lblWakeUp);

		JLabel lblToilet = new JLabel();         //toilet tab
		lblToilet.setPreferredSize(new Dimension(60, 60));
		lblToilet.setIcon(new ImageIcon(imgBathroom));
		JPanel panelToilet = new JPanel();
		tabbedPane.addTab("", panelToilet);
		tabbedPane.setTabComponentAt(5, lblToilet);
		panelToilet.setLayout(null);

		JButton btnToilet = new JButton(""); //toilet button
		btnToilet.setIcon(new ImageIcon(imgToilet));
		btnToilet.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(currentPet.getIsAlive()==false){
					JOptionPane.showMessageDialog(null, "Pet is dead");
				}
				else if(currentPet.getActions()<2){
	            int reply = JOptionPane.showConfirmDialog(null, "Let "+currentPet.getName()+" go to bathroom?");
				if(reply==JOptionPane.YES_OPTION){
		            currentPet.toilet();
				}
				}else{
					JOptionPane.showMessageDialog(null, currentPet.getName()+" has completed 2 actions today");
				}
			}
		});	
		btnToilet.setIcon(new ImageIcon(imgToilet));
		btnToilet.setBounds(216, 49, 114, 120);
		panelToilet.add(btnToilet);

		JLabel lblGoToBathroom = new JLabel("Go to bathroom"); //go to bathroom label
		lblGoToBathroom.setBounds(215, 181, 144, 27);
		panelToilet.add(lblGoToBathroom);
		tabbedPane.setTabComponentAt(4, lblSleep);

		class MyActionListener implements ActionListener { // an customized
															// actionListener
															// for pet buttons
			private Integer index;

			public MyActionListener(int index) {
				this.index = index;
			}

			public void actionPerformed(ActionEvent e) {
				currentPet = Home.currentPlayer.getPets().get(index);
				lblName.setText("Name:" + currentPet.getName());
				lblSpecies.setText("Species:" + currentPet.getSpecies());
				lblCleanness.setText("Cleanness:" + currentPet.getCleanness());
				lblFavouriteFood.setText(("Favourite food:" + currentPet
						.getFavFood()));
				lblFavouriteToy.setText(("Favourite toy:" + currentPet
						.getFavToy()));
				lblHappiness.setText("Happiness:" + currentPet.getHappiness());
				lblHasBeenDead.setText("Has been dead:"
						+ currentPet.getHasBeenDead());
				lblHunger.setText("Hunger:" + currentPet.getHunger());
				String isMisbehaving;                                
				if(currentPet.getIsMisBehaving()==true){
					isMisbehaving = "Yes";
				}else{
					isMisbehaving = "No";
				}
				lblIsMisbehaving.setText("Is misbehaving:"
						+ isMisbehaving);
				String isSick;                                
				if(currentPet.getIsSick()==true){
					isSick = "Yes";
				}else{
					isSick = "No";
				}
				lblIsSick.setText("Is sick:" + isSick);
				lblTiredness.setText("Tiredness:" + currentPet.getTiredness());
				lblWeight.setText("Weight:" + currentPet.getWeight());

			}
		}

		JButton btnNextDay = new JButton(""); //Move to next day button
		btnNextDay.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if(Home.currentPlayer.getCurrentDay()<FirstFrame.day){
	            int reply = JOptionPane.showConfirmDialog(null, "Are you sure to move to next day?");
					if(reply==JOptionPane.YES_OPTION){                //update status when moving to next day
			            Home.currentPlayer.movetoNextDay(Home.currentPlayer.getCurrentDay(), FirstFrame.day);
                        lblPlayerName.setText("Hi, " + Home.currentPlayer.getName()
                				+ "! This is Day " + Home.currentPlayer.getCurrentDay());
              				lblName.setText("Name:" + currentPet.getName());
              				lblSpecies.setText("Species:" + currentPet.getSpecies());
              				currentPet.setCleaness(currentPet.getCleanness());
              				lblCleanness.setText("Cleanness:" + currentPet.getCleanness());
              				lblFavouriteFood.setText(("Favourite food:" + currentPet
              						.getFavFood()));
              				lblFavouriteToy.setText(("Favourite toy:" + currentPet
              						.getFavToy()));
              				currentPet.setHappiness(currentPet.getHappiness());
              				lblHappiness.setText("Happiness:" + currentPet.getHappiness());
              				lblHasBeenDead.setText("Has been dead:"
              						+ currentPet.getHasBeenDead());
              				currentPet.setHunger(currentPet.getHunger());
              				lblHunger.setText("Hunger:" + currentPet.getHunger());
            				String isMisbehaving;                                
            				if(currentPet.getIsMisBehaving()==true){
            					isMisbehaving = "Yes";
            				}else{
            					isMisbehaving = "No";
            				}
            				String isSick;                                
            				if(currentPet.getIsSick()==true){
            					isSick = "Yes";
            				}else{
            					isSick = "No";
            				}
              				lblIsMisbehaving.setText("Is misbehaving:"
              						+ isMisbehaving);
              				lblIsSick.setText("Is sick:" + isSick);
              				lblTiredness.setText("Tiredness:" + currentPet.getTiredness());
              				lblWeight.setText("Weight:" + currentPet.getWeight());
					}
				}else{
					JOptionPane.showMessageDialog(null, "Game Over!\n"+Home.currentPlayer.getName()+"'s final score is "+Home.currentPlayer.getTotalScore());
					if(SelectPet.players.size()>1){                   //when finished all rounds, end game, display score
					SelectPet.players.remove(Home.currentPlayer);     //remove current player
					dispose();
					Home newframe = new Home();
					newframe.setVisible(true);
					}else{
							dispose();
					}				
				}
			}
		});
		btnNextDay.setIcon(new ImageIcon(imgNextDay));
		btnNextDay.setBounds(594, 8, 92, 54);
		contentPane.add(btnNextDay);
		
		String species1 = Home.currentPlayer.getPets().get(0).getSpecies(); //pet Button1
		switch (species1) {
		case "cat":
			btnPet1.setIcon(new ImageIcon(imgCat));
			break;
		case "dog":
			btnPet1.setIcon(new ImageIcon(imgDog));
			break;
		case "rabbit":
			btnPet1.setIcon(new ImageIcon(imgRabbit));
			break;
		case "duck":
			btnPet1.setIcon(new ImageIcon(imgDuck));
			break;
		case "pig":
			btnPet1.setIcon(new ImageIcon(imgPig));
			break;
		case "hamster":
			btnPet1.setIcon(new ImageIcon(imgHamster));
			break;
		default:
			btnPet1.setIcon(null);
		}
		btnPet1.addActionListener(new MyActionListener(0));
		btnPet1.setBounds(6, 93, 100, 100);
		contentPane.add(btnPet1);


		btnPet2.setBounds(6, 204, 100, 100);       //pet button2
		contentPane.add(btnPet2);
		if (Home.currentPlayer.getPets().size() >= 2) { // only display when
														// pets size equal or
														// larger than 2
			String species2 = Home.currentPlayer.getPets().get(1).getSpecies();
			switch (species2) {
			case "cat":
				btnPet2.setIcon(new ImageIcon(imgCat));
				break;
			case "dog":
				btnPet2.setIcon(new ImageIcon(imgDog));
				break;
			case "rabbit":
				btnPet2.setIcon(new ImageIcon(imgRabbit));
				break;
			case "duck":
				btnPet2.setIcon(new ImageIcon(imgDuck));
				break;
			case "pig":
				btnPet2.setIcon(new ImageIcon(imgPig));
				break;
			case "hamster":
				btnPet2.setIcon(new ImageIcon(imgHamster));
				break;
			default:
				btnPet2.setIcon(null);
			}
			btnPet2.addActionListener(new MyActionListener(1));
			btnPet2.setVisible(true);
		} else {
			btnPet2.setVisible(false);
		}

		btnPet3.setBounds(6, 316, 100, 100); //pet button3
		contentPane.add(btnPet3);
		if (Home.currentPlayer.getPets().size() == 3) { // only display when
														// pets size equal to 3
			String species3 = Home.currentPlayer.getPets().get(2).getSpecies();
			switch (species3) {
			case "cat":
				btnPet3.setIcon(new ImageIcon(imgCat));
				break;
			case "dog":
				btnPet3.setIcon(new ImageIcon(imgDog));
				break;
			case "rabbit":
				btnPet3.setIcon(new ImageIcon(imgRabbit));
				break;
			case "duck":
				btnPet3.setIcon(new ImageIcon(imgDuck));
				break;
			case "pig":
				btnPet3.setIcon(new ImageIcon(imgPig));
				break;
			case "hamster":
				btnPet3.setIcon(new ImageIcon(imgHamster));
				break;
			default:
				btnPet3.setIcon(new ImageIcon(imgHamster));
			}
			btnPet3.addActionListener(new MyActionListener(2));
			btnPet3.setVisible(true);
		} else {
			btnPet3.setVisible(false);
		}

	}
}