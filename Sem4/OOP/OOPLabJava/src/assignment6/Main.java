/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package assignment6;

public class Main {
	private Quote quote;
	public static void main(String args[]) {
		Main obj = new Main();
		try {
			obj.quote = new Quote("C:\\Users\\The Guardian\\Google Drive\\JUCSE\\Sem 4\\OOP\\OOPLabJava\\src\\assignment6\\Quote.txt");
			System.out.println(obj.quote.readRandom());
		}
		catch(Exception e) {
			System.out.println(e.toString() + ": try again");
		}
	}
}
