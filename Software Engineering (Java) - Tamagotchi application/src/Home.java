import java.awt.EventQueue;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import javax.swing.JLabel;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/**
 * The Class Home in which user can switch current player.
 */
public class Home extends JFrame {

	/** The content pane. */
	private JPanel contentPane;
	
	/** The current player. */
	public static Player currentPlayer;

	/**
	 * Launch the application.
	 *
	 * @param args the arguments
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Home frame = new Home();
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
	public Home() {
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);

		final Image img = new ImageIcon(this.getClass().getResource(
				"/profile-icon1.png")).getImage();

		JButton btnPlayer1 = new JButton("");        //player1 button
		btnPlayer1.setIcon(new ImageIcon(img));
		btnPlayer1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				currentPlayer = SelectPet.players.get(0);
				dispose();
				Menu frame4 = new Menu();
				frame4.setVisible(true);
			}
		});
		btnPlayer1.setBounds(22, 67, 100, 100);
		contentPane.add(btnPlayer1);

		JButton btnPlayer2 = new JButton("");       //player2 button
		btnPlayer2.setIcon(new ImageIcon(img));
		btnPlayer2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				currentPlayer = SelectPet.players.get(1);
				dispose();
				Menu frame4 = new Menu();
				frame4.setVisible(true);
			}
		});
		btnPlayer2.setBounds(148, 67, 100, 100);
		contentPane.add(btnPlayer2);
		if (SelectPet.players.size() >= 2) { // only display when players size
												// equal or larger than 2
			btnPlayer2.setVisible(true);
		} else {
			btnPlayer2.setVisible(false);
		}

		JButton btnPlayer3 = new JButton("");
		btnPlayer3.setIcon(new ImageIcon(img));
		btnPlayer3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				currentPlayer = SelectPet.players.get(2);
				dispose();
				Menu frame4 = new Menu();
				frame4.setVisible(true);
			}
		});
		btnPlayer3.setBounds(274, 67, 100, 100); //player3 button
		contentPane.add(btnPlayer3);
		if (SelectPet.players.size() == 3) { // only display when players size
												// equal to 3
			btnPlayer3.setVisible(true);
		} else {
			btnPlayer3.setVisible(false);
		}

		JLabel lblSelectCurrentPlayer = new JLabel(      //Select current player label
				"Please select the current player");
		lblSelectCurrentPlayer.setBounds(22, 6, 249, 50);
		contentPane.add(lblSelectCurrentPlayer);

		JLabel lblPlayer1 = new JLabel(SelectPet.players.get(0).getName()); //player1 label,showing player1's name
		lblPlayer1.setBounds(30, 179, 88, 23);
		contentPane.add(lblPlayer1);

		JLabel lblPlayer2 = new JLabel("");       //player2 label,showing player2's name
		if (SelectPet.players.size() >= 2) {
			lblPlayer2.setText(SelectPet.players.get(1).getName());
		}
		lblPlayer2.setBounds(162, 179, 88, 23);
		contentPane.add(lblPlayer2);

		JLabel lblPlayer3 = new JLabel(""); //		player3 label,showing player3's name     
		if (SelectPet.players.size() == 3) {
			lblPlayer3.setText(SelectPet.players.get(2).getName());
		}
		lblPlayer3.setBounds(286, 179, 88, 23);
		contentPane.add(lblPlayer3);

	}
}