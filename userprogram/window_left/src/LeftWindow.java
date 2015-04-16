import java.awt.Color;
import java.awt.GridLayout;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JWindow;


public class LeftWindow extends JWindow{

	public LeftWindow(){
//		ImageIcon img1 = new ImageIcon("image/cmd.png");
//		ImageIcon img2 = new ImageIcon("image/mail.png");
//		ImageIcon img3 = new ImageIcon("image/music.png");
//		ImageIcon img4 = new ImageIcon("image/eclipse_blu.png");
//		ImageIcon img5 = new ImageIcon("image/desktop_blu.png");
		JButton jb1 = new JButton();//console window
		this.setIcon("./l_image/code_blu.png", jb1);
		JButton jb2 = new JButton();//home button
		this.setIcon("./l_image/gmail_blu.png", jb2);
		JButton jb3 = new JButton();//mail window
		this.setIcon("./l_image/network_blu.png", jb3);
		JButton jb4 = new JButton();//
		this.setIcon("./l_image/html_blu.png", jb4);
		JButton jb5 = new JButton();//
		this.setIcon("./l_image/eclipse_blu.png", jb5);
//		jb1.setBorderPainted(false);
//		jb2.setBorderPainted(false);
//		jb3.setBorderPainted(false);
//		jb4.setBorderPainted(false);
//		jb5.setBorderPainted(false);
		
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
		LeftWindow leftwd = new LeftWindow();
		leftwd.setSize(150, 742);
		leftwd.setLocation(0, 36);
//		leftwd.setBackground(new Color(255,255,255,0));
		//leftwd.getContentPane().setBackground(Color.gray);
		leftwd.setVisible(true);
	}
	
	public void setIcon(String file,JButton com) {
        ImageIcon ico=new ImageIcon(file);
        Image temp= ico.getImage().getScaledInstance(150,742/5,ico.getImage().SCALE_DEFAULT);
        ico=new ImageIcon(temp);
        com.setIcon(ico);
    } 

}
