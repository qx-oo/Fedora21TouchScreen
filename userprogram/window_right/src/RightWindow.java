import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JWindow;


public class RightWindow extends JWindow{
	
	public RightWindow() {
		ImageIcon img1 = new ImageIcon("./r_image/Music.png");
		ImageIcon img2 = new ImageIcon("./r_image/Pausebutton.png");
		ImageIcon img3 = new ImageIcon("./r_image/First.png");
		ImageIcon img4 = new ImageIcon("./r_image/Last.png");
		ImageIcon img5 = new ImageIcon("./r_image/Delete.png");
		
		JButton jb1 = new JButton(img1);//music window
//		this.setIcon("image/Music.png", jb1);
		JButton jb2 = new JButton(img2);//Pausebutton button
//		this.setIcon("image/Pausebutton.png", jb2);
		JButton jb3 = new JButton(img3);//First window
//		this.setIcon("image/First.png", jb3);
		JButton jb4 = new JButton(img4);//
//		this.setIcon("image/Last.png", jb4);
		JButton jb5 = new JButton(img5);//
//		this.setIcon("image/Delete.png", jb5);
		
		jb1.setContentAreaFilled(false);//set color null
		jb2.setContentAreaFilled(false);
		jb3.setContentAreaFilled(false);
		jb4.setContentAreaFilled(false);
		jb5.setContentAreaFilled(false);
		
		this.setLayout(new GridLayout(5,1,0,0));
		this.add(jb1);
		this.add(jb2);
		this.add(jb3);
		this.add(jb4);
		this.add(jb5);
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		RightWindow  rightwd = new RightWindow();
		rightwd.setSize(150, 742);
		rightwd.setLocation(1216, 36);
		rightwd.getContentPane().setBackground(new Color(23,106,183,255));
		rightwd.setVisible(true);
	}
	
	public void setIcon(String file,JButton com) {
        ImageIcon ico=new ImageIcon(file);
        Image temp= ico.getImage().getScaledInstance(150,742/5,ico.getImage().SCALE_DEFAULT);
        ico=new ImageIcon(temp);
        com.setIcon(ico);
    }
	

}
