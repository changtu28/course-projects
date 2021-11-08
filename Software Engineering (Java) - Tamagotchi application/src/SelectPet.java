import java.awt.EventQueue;
import java.awt.Image;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JButton;

import java.awt.Font;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.ArrayList;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

/**
 * The Class SelectPet.In this frame user enter player names, 
 * select each player's pets and name the pets
 */
public class SelectPet extends JFrame {

	/** The content pane. */
	private JPanel contentPane;
	
	/** The text field to get input of  player name. */
	private JTextField textPlayerName;
	
	/** The text field to get input of number of pets the player want. */
	private JTextField textPetNum;
	
	/**  The button representing cat. */
	private JButton btnCat;
	
	/** The button representing dog. */
	private JButton btnDog;
	
	/** The button representing rabbit. */
	private JButton btnRabbit;
	
	/** The button representing duck. */
	private JButton btnDuck;
	
	/** The button representing pig. */
	private JButton btnPig;
	
	/** The button representing hamster. */
	private JButton btnHamster;
	
	/** The player name. */
	private String playerName;
	
	/** The pet number. */
	private int petNum;
	
	/** The new player. */
	private Player newPlayer;
	
	/**After getting the species the player want create a new pet. */
	private Pet newPet;
	
	/** The pet name assigned to the new pet. */
	private String petName;
	
	/** The players list. */
	public static ArrayList<Player> players = new ArrayList<Player>();
	
	/** The pets list represents all the pets that one player owns. */
	private ArrayList<Pet> pets = new ArrayList<Pet>();
	
	/** The all pets list represents the pets that all the players own
	 * for checking if there is pet name repeats. */
	public static ArrayList<Pet> allPets = new ArrayList<Pet>();
	
	/** The label pet name. */
	private JLabel lblPetName;
	
	/** The text field to get input of  pet name. */
	private JTextField textPetName;
	
	/** The button ok to confirm the naming of current pet. */
	private JButton btnOk;

	/**
	 * Launch the application.
	 *
	 * @param args the arguments
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					SelectPet frame = new SelectPet();
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
	public SelectPet() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(500, 400);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		final JLabel lblPlayerName = new JLabel("Enter a player's name:");
		lblPlayerName.setBounds(6, 6, 200, 50);
		contentPane.add(lblPlayerName);

		textPlayerName = new JTextField();
		textPlayerName.setBounds(174, 19, 114, 26);
		contentPane.add(textPlayerName);
		textPlayerName.setColumns(10);

		final JLabel lblpetNum = new JLabel("How many pets to have:");
		lblpetNum.setBounds(6, 43, 200, 50);
		contentPane.add(lblpetNum);

		textPetNum = new JTextField(); // be aware of tab!Don't use tab to move to next blank
		textPetNum.addMouseListener(new MouseAdapter() {
			@Override
			public void mousePressed(MouseEvent arg0) {
				playerName = textPlayerName.getText();
				for (Player who : players) {
					if (who.getName().equals(playerName)) {
						JOptionPane.showMessageDialog(null,
								"This name has been used,please use another");
						textPlayerName.setText("");
						playerName = textPlayerName.getText();
					}
				}
			}
		});
		textPetNum.setBounds(195, 57, 51, 26);
		contentPane.add(textPetNum);
		textPetNum.setColumns(10);

		JButton btnOkSelectPets = new JButton("Ok, select pets!"); // press to select pets
		btnOkSelectPets.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					petNum = Integer.parseInt(textPetNum.getText());
					if (petNum > 0 && petNum <= 3) {             //only after "ok,select pets!"button pressed
						btnCat.setVisible(true);                 //will pets button become visible
						btnDog.setVisible(true);
						btnRabbit.setVisible(true);
						btnDuck.setVisible(true);
						btnPig.setVisible(true);
						btnHamster.setVisible(true);
						newPlayer = new Player(playerName, petNum, pets);
						players.add(newPlayer);
					} else {
						JOptionPane.showMessageDialog(null,
								"Please enter a number between 1 and 3");//check if number entered within range
						textPetNum.setText("");
					}
				} catch (NumberFormatException e1) {
					JOptionPane.showMessageDialog(null,
							"Please enter a valid number");//check if input is a number
					textPetNum.setText("");
				}
			}
		});
		btnOkSelectPets.setFont(new Font("Lucida Grande", Font.PLAIN, 11));
		btnOkSelectPets.setBounds(6, 82, 137, 29);
		contentPane.add(btnOkSelectPets);

	   final JButton btnNext = new JButton("next"); // press next to enter next player's info
		btnNext.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (players.size() < FirstFrame.numofPlayers) {//proceed when added players number less than required
					dispose();
					SelectPet frame = new SelectPet();
					frame.setVisible(true);
				} else {                        //when added players number equal to the number required, 
					dispose();                  //close SelectPets frame, open Home frame
					Home frame2 = new Home();
					frame2.setVisible(true);
				}
			}
		});
		btnNext.setBounds(393, 316, 75, 29);
		contentPane.add(btnNext);
		btnNext.setVisible(false);

		class MyActionListener implements ActionListener { // an customized actionListener for pet buttons
			private JButton btn;                           //when pressed, the corresponding pet species is
			private String species;                        //selected

			public MyActionListener(JButton btn, String species) {
				this.btn = btn;
				this.species = species;
			}

			public void actionPerformed(ActionEvent e) {
				if(pets.size()==petNum-1){      
					btnNext.setVisible(true);
				}
				if (pets.size() >= petNum) {
					JOptionPane.showMessageDialog(null,
							"You have selected enough pets.");
				} else {
					lblPetName.setVisible(true);
					textPetName.setVisible(true);
					btnOk.setVisible(true);
					btn.setIcon(null);
					btn.setText(species); // when a pet button is pressed
					switch (species) {                  // the icon image is replaced by 
					case "cat":                        //text that the corresponding species 
						newPet = new Cat("", species); //is selected
						break;
					case "dog":
						newPet = new Dog("", species);
						break;
					case "rabbit":
						newPet = new Rabbit("", species);
						break;
					case "duck":
						newPet = new Duck("", species);
						break;
					case "pig":
						newPet = new Pig("", species);
						break;
					case "hamster":
						newPet = new Hamster("", species);
						break;
					default:
						newPet = new Pet("", species);
					}
					pets.add(newPet);          //add new pet to current player's pet list
					allPets.add(newPet);       //add new pet to all pet list
				}
			}
		}

		btnCat = new JButton(""); // button for cat
		btnCat.addActionListener(new MyActionListener(btnCat, "cat"));
		Image imgCat = new ImageIcon(this.getClass().getResource(
				"/kitten-icon.png")).getImage();
		btnCat.setIcon(new ImageIcon(imgCat));
		btnCat.setBounds(6, 123, 100, 100);
		contentPane.add(btnCat);
		btnCat.setVisible(false);

		btnDog = new JButton(""); // button for dog
		btnDog.addActionListener(new MyActionListener(btnDog, "dog"));
		Image imgDog = new ImageIcon(this.getClass().getResource(
				"/dog-icon.png")).getImage();
		btnDog.setIcon(new ImageIcon(imgDog));
		btnDog.setBounds(118, 123, 100, 100);
		contentPane.add(btnDog);
		btnDog.setVisible(false);

		btnRabbit = new JButton(""); // button for rabbit
		btnRabbit.addActionListener(new MyActionListener(btnRabbit, "rabbit"));
		Image imgRabbit = new ImageIcon(this.getClass().getResource(
				"/bunny-icon.png")).getImage();
		btnRabbit.setIcon(new ImageIcon(imgRabbit));
		btnRabbit.setBounds(230, 123, 100, 100);
		contentPane.add(btnRabbit);
		btnRabbit.setVisible(false);

		btnDuck = new JButton(""); // button for duck
		btnDuck.addActionListener(new MyActionListener(btnDuck, "duck"));
		Image imgDuck = new ImageIcon(this.getClass().getResource(
				"/duck-icon.png")).getImage();
		btnDuck.setIcon(new ImageIcon(imgDuck));
		btnDuck.setBounds(6, 245, 100, 100);
		contentPane.add(btnDuck);
		btnDuck.setVisible(false);

		btnPig = new JButton(""); // button for pig
		btnPig.addActionListener(new MyActionListener(btnPig, "pig"));
		Image imgPig = new ImageIcon(this.getClass().getResource(
				"/pig-icon.png")).getImage();
		btnPig.setIcon(new ImageIcon(imgPig));
		btnPig.setBounds(118, 245, 100, 100);
		contentPane.add(btnPig);
		btnPig.setVisible(false);

		btnHamster = new JButton(""); // button for hamster
		btnHamster
				.addActionListener(new MyActionListener(btnHamster, "hamster"));
		Image imgHamster = new ImageIcon(this.getClass().getResource(
				"/hamster-icon.png")).getImage();
		btnHamster.setIcon(new ImageIcon(imgHamster));
		btnHamster.setBounds(230, 245, 100, 100);
		contentPane.add(btnHamster);
		btnHamster.setVisible(false);

		lblPetName = new JLabel("Enter the pet's name:");// label asking
																// for pet's
																// name
		lblPetName.setBounds(300, 9, 200, 44);
		contentPane.add(lblPetName);
		lblPetName.setVisible(false);

		textPetName = new JTextField(); // textfield for pet's name
		textPetName.setBounds(300, 45, 130, 26);
		contentPane.add(textPetName);
		textPetName.setColumns(10);
		textPetName.setVisible(false);

		btnOk = new JButton("Ok"); // press Ok to confirm pet's name
		btnOk.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				petName = textPetName.getText();
				newPet.setName(petName);
				if (allPets.size() > 1) {
					allPets.remove(allPets.size() - 1); //remove the last added item to avoid report repeating with itself;
					for (Pet who : allPets) {
						if (who.getName().equals(petName)) {
							JOptionPane.showMessageDialog(null,
											"This name has been used,please use another");
							textPetName.setText("");
						}
					}
					newPet.setName(petName);
					allPets.add(newPet);
				}
			}
		});
		btnOk.setBounds(433, 43, 53, 29);
		contentPane.add(btnOk);
		btnOk.setVisible(false);
	}
}