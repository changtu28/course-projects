import java.awt.EventQueue;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.Font;
import java.awt.Color;
import java.awt.Image;

import javax.swing.JTextField;
import javax.swing.JButton;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.ArrayList;
import javax.swing.SwingConstants;

/**
 * The Class FirstFrame.User to enter rounds and the number of players here
 */
public class FirstFrame {

	/** The first frame of the game.Get day and player number inputs from users */
	private JFrame frame1;

	/** The textfield to enter how many days to play. */
	private JTextField textDay;

	/** The textField to enter the number of players. */
	private JTextField textNumofPlayers;

	/**
	 * The second frame of the game will be visible when this button be pressed,
	 * meanwhile closing first frame
	 */
	private JButton btnNext;

	/** The number of days to play the game. */
	public static int day;

	/**
	 * The number of players to play the game
	 * 
	 */
	public static int numofPlayers;

	/** The btn help shows the instructions of the game. */
	private JButton btnHelp;

	/**
	 * Launch the application.
	 *
	 * @param args
	 *            the arguments
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					FirstFrame window = new FirstFrame();
					window.frame1.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public FirstFrame() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame1 = new JFrame();
		frame1.getContentPane().setBackground(new Color(255, 228, 196));
		frame1.setSize(500, 400);
		frame1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame1.getContentPane().setLayout(null);

		JLabel lblGameTitle = new JLabel(" Tamagotchi"); // Game title
		lblGameTitle.setBounds(103, 28, 269, 104);
		lblGameTitle.setForeground(Color.PINK);
		lblGameTitle.setFont(new Font("Helvetica", Font.BOLD, 34));
		frame1.getContentPane().add(lblGameTitle);

		final JLabel lblHowManyDays = new JLabel(
				"How many days to play?");// ask user for
															// number of rounds
		lblHowManyDays.setFont(new Font("Helvetica", Font.PLAIN, 13));
		lblHowManyDays.setBounds(128, 144, 270, 44);
		frame1.getContentPane().add(lblHowManyDays);

		textDay = new JTextField(); // textfield to get input of number of
									// rounds
		textDay.setBounds(129, 180, 130, 26);
		frame1.getContentPane().add(textDay);
		textDay.setColumns(10);

		final JLabel lblHowManyPlayers = new JLabel("How many players(1~3)?");// ask user for number of players																				
		lblHowManyPlayers.setFont(new Font("Dialog", Font.PLAIN, 12));
		lblHowManyPlayers.setBounds(129, 200, 265, 50);
		frame1.getContentPane().add(lblHowManyPlayers);

		textNumofPlayers = new JTextField();
		textNumofPlayers.setBounds(129, 236, 130, 26);// textfield to get input of number of players
		frame1.getContentPane().add(textNumofPlayers);
		textNumofPlayers.setColumns(10);

		btnNext = new JButton("next");
		btnNext.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int flag = 0;
				try{
					lblHowManyDays.setText("How many days to play?");
					lblHowManyDays.setForeground(Color.BLACK);
					day = Integer.parseInt(textDay.getText());
	                flag = 1;
				}catch(NumberFormatException e1){
					lblHowManyDays.setForeground(Color.RED);
					flag = 0;
					textDay.setText("");
					lblHowManyDays.setText("How many days to play?"+"(Type error!)");// check inputs are number only
				}
				try {
					lblHowManyPlayers.setText("How many players(1~3)?");
					lblHowManyPlayers.setForeground(Color.BLACK);
					numofPlayers = Integer.parseInt(textNumofPlayers.getText());
					if (numofPlayers > 0 && numofPlayers <= 3&&flag == 1) { // when day and numofPlayers within range move to next
													             // frame.otherwise show warning message
						frame1.dispose();
						SelectPet frame2 = new SelectPet();
						frame2.setVisible(true);
					}else{
						lblHowManyPlayers.setForeground(Color.RED);
						textNumofPlayers.setText("");
						JOptionPane.showMessageDialog(null,
								"Please enter a number between 1 and 3");
					}
				} catch (NumberFormatException e1) {
					lblHowManyPlayers.setText("How many players(1~3)?"+"(Type error!)");
					lblHowManyPlayers.setForeground(Color.RED);// check inputs are number only
					textNumofPlayers.setText("");
				}

			}
		});
		btnNext.setBounds(139, 285, 73, 29);
		frame1.getContentPane().add(btnNext);

		final Image imgHelp = new ImageIcon(this.getClass().getResource(
				"/help-icon.png")).getImage();

		btnHelp = new JButton("");
		btnHelp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String message = "Tamagotchi is a game in which several player will have to look after several virtual pets: "
						+ "\nfeed it, play with it, make sure they fulfill their needs, sleeps....all the dedication that "
						+ "\n you would offer a real pet."
						+ "\n shop: with initial money of 500 dollars, you have to buy foods and toys for your pets."
						+ "\n feed: feed the pet with the food you buy. if the pet be fed their favourite food,  it will "
						+ "\n extremely increase pet's happiness. "
						+ "\n and there's also a random event for the feed action which will occurs the pet sick or misbehave."
						+ "\n play: let pet play with the toys, all the toy purchased have a durability."
						+ "\n sleep: recover the tiredness "
						+ "\n shower: reduce the cleaness "
						+ "\n There will be 2 action per pet limited everyday the final score will display after the last round "
						+ "\n or if all of the pets died for any player.";
				JOptionPane.showMessageDialog(null, message);
			}
		});
		btnHelp.setForeground(Color.PINK);
		btnHelp.setBackground(Color.PINK);
		btnHelp.setIcon(new ImageIcon(imgHelp));
		btnHelp.setBounds(377, 298, 67, 50);
		frame1.getContentPane().add(btnHelp);
	}

}