package org.qingxian.notebook;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

public class SignSocket implements Runnable{
	private final int port = 8888;
	private ServerSocket server;
	private Socket socket;
	private String sign;
	private NoteBook noteBook;
	
	public void signControl(){
		noteBook.closeNotebook();
	}

	@Override
	public void run() {
		
		try {
			server = new ServerSocket(port);
			socket = server.accept();
			BufferedReader br = new BufferedReader(
					new InputStreamReader(socket.getInputStream()));
			sign = br.readLine();
			System.out.println("接收的数据是 ： "+sign);
			if(sign.equals("close")){
				this.signControl();
				}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public NoteBook getNoteBook() {
		return noteBook;
	}

	public void setNoteBook(NoteBook noteBook) {
		this.noteBook = noteBook;
	}

}
