package org.qingxian.notebook;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class NoteBook extends JFrame {
	
	//文件存储
	private IOFile ioFile;

	private static final long serialVersionUID = 1L;

	private JLabel jLabel1;
	private JTextField jTextField;
	private JTextArea jTextArea;
	private JPanel j1;

	public NoteBook() {
		this.setUndecorated(true);// wipe off title
		this.setLayout(new BorderLayout());
		this.setSize(500, 300);
		this.setLocation(400, 150);
		this.setBackground(new Color(23, 106, 183, 255));
		// this.setLayout(new GridLayout(2,1,0,0));
		this.initComponent();
		this.KeyListener();
		//init
		//

		this.add(j1, BorderLayout.NORTH);
		this.add(jTextArea, BorderLayout.CENTER);
	}

//	public static void main(String[] argvs) {
//		NoteBook noteBook = new NoteBook();
//		noteBook.setVisible(true);
//	}
	
	private void initComponent(){
		j1 = new JPanel();
		j1.setLayout(new BorderLayout());
		jLabel1 = new JLabel("Title");
		jTextField = new JTextField(20);
		jTextField.setBackground(new Color(23, 106, 183, 255));
		Font font1 = new Font(null , Font.PLAIN, 30 );
		jLabel1.setFont(font1);
		jTextField.setFont(font1);
		j1.add(jLabel1, BorderLayout.WEST);
		j1.add(jTextField, BorderLayout.CENTER);

		jTextArea = new JTextArea();
		Font font2 = new Font(null , Font.PLAIN, 15 );
		jTextArea.setFont(font2);
	}
	
	public void closeNotebook(){
		String text = jTextField.getText();
		if(text.equals("")){
			System.exit(0);
		}
		ioFile = new IOFile();
		ioFile.initFile(text);
		ioFile.writeFile(jTextArea.getText());
		System.exit(0);
	}

	private void KeyListener() {
		jTextField.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ALT)
					jTextArea.requestFocus();
			}
		});
		jTextArea.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				if (e.getKeyCode() == KeyEvent.VK_ALT)
					jTextField.requestFocus();
			}
		});
	}
}
