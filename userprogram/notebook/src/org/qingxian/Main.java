package org.qingxian;

import org.qingxian.notebook.NoteBook;
import org.qingxian.notebook.SignSocket;

public class Main {
	public static void main(String[] argv){
		NoteBook noteBook = new NoteBook();
		noteBook.setVisible(true);
		SignSocket signSocket = new SignSocket();
		signSocket.setNoteBook(noteBook);
		new Thread(signSocket).start();
	}
}
