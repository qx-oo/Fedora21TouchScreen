package org.qingxian.notebook;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class IOFile {
	private File file;
	
	public void initFile(String filename){
		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
		String date = df.format(new Date());
		file = new File("/home/qx-oo/notebook/"+date+"_"+filename);
		
	}
	
	public void createFile(){
		try {
			file.createNewFile();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			System.out.println("创建失败");
			e.printStackTrace();
		}
	}
	
	public void writeFile(String text){
		FileWriter fw;
		try {
			fw = new FileWriter(file);
			fw.write(text);
			fw.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
//	public static void main(String[] argv){
//		IOFile i = new IOFile();
//		i.initFile("xixi");
//		i.createFile();
//		i.writeFile("你好啊，我真的知道了");
//	}
}
