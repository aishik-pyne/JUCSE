
package Random;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
public class Calculator implements ActionListener{


	char o;
	int ctr=0;
	String value="", cv="", oBtn;
	Double answer, v1, v2;
	Double NumberConverted;


	JFrame f;
	JPanel p1, p2, p3, p4, p5, p6;
	private TextField tField;
	private Menu EditMenu;
	private MenuBar menuBar;
	private MenuItem fmi1, fmi2, fmi3;
	private Button num0, num1, num2, num3, num4, num5, num6, num7, num8,num9;
	private Button bAdd, bSub, bMul, bDiv, bPer, bSqrt, bFrac, bInt, bDot,bCE, equals, backspace, clear;

	Calculator(){
			f = new JFrame("Calculator");

			menuBar = new MenuBar();
			EditMenu = new Menu ("Edit");

			fmi1 = new MenuItem(" Copy   ");
			fmi2 = new MenuItem(" Paste  ");
			fmi3 = new MenuItem(" Quit    ");

			EditMenu.add(fmi1);
			EditMenu.add(fmi2);
			EditMenu.addSeparator();
			EditMenu.add(fmi3);

			p1 = new JPanel();
			p2 = new JPanel();
			p3 = new JPanel();
			p4 = new JPanel();
			p5 = new JPanel();
			p6 = new JPanel();

			tField = new TextField(35);

			num0 = new Button 	("0");
			num1 = new Button 	("1");
			num2 = new Button 	("2");
			num3 = new Button 	("3");
			num4 = new Button 	("4");
			num5 = new Button 	("5");
			num6 = new Button 	("6");
			num7 = new Button 	("7");
			num8 = new Button 	("8");
			num9 = new Button 	("9");
			bAdd = new Button 	("+");
			bSub = new Button 	("-");
			bMul = new Button 	("x");
			bDiv = new Button 	("/");
			bPer = new Button 	("%");
			bSqrt = new Button 	("sqrt");
			bFrac = new Button 	("1/x");
			bInt = new Button 	("+/-");
			bDot = new Button 	(".");
			bCE = new Button 	("CE");
			equals = new Button 	("=");
			backspace = new Button 	("Backspace");
			clear = new Button	("C");
	}

	public void launchFrame(){

			tField.setText("0.");
			tField.setEnabled(false);

			menuBar.add(EditMenu);

			p2.add(backspace);
			p2.add(bCE);
			p2.add(clear);

			p3.add(num7);
			p3.add(num8);
			p3.add(num9);
			p3.add(bDiv);
			p3.add(bSqrt);

			p4.add(num4);
			p4.add(num5);
			p4.add(num6);
			p4.add(bMul);
			p4.add(bPer);

			p5.add(num1);
			p5.add(num2);
			p5.add(num3);
			p5.add(bSub);
			p5.add(bFrac);

			p6.add(num0);
			p6.add(bInt);
			p6.add(bDot);
			p6.add(bAdd);
			p6.add(equals);

			p2.setLayout(new GridLayout (1, 3, 2, 2) );
			p3.setLayout(new GridLayout (1, 3, 2, 2) );
			p4.setLayout(new GridLayout (1, 3, 2, 2) );
			p5.setLayout(new GridLayout (1, 3, 2, 2) );
			p6.setLayout(new GridLayout (1, 3, 2, 2) );

			f.setLayout(new GridLayout (6, 1) );
			f.setResizable(false);
			f.setSize(300,250);
			f.add(tField);
			f.add(p2);
			f.add(p3);
			f.add(p4);
			f.add(p5);
			f.add(p6);
                        f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			f.setVisible(true);
			f.setMenuBar(menuBar);
			f.pack();

		// ACTION LISTENERS
			clear.addActionListener(this);
			bCE.addActionListener(this);

			num0.addActionListener(this);
			num1.addActionListener(this);
			num2.addActionListener(this);
			num3.addActionListener(this);
			num4.addActionListener(this);
			num5.addActionListener(this);
			num6.addActionListener(this);
			num7.addActionListener(this);
			num8.addActionListener(this);
			num9.addActionListener(this);

			bAdd.addActionListener(this);
			bSub.addActionListener(this);
			bMul.addActionListener(this);
			bDiv.addActionListener(this);
			bPer.addActionListener(this);

			bInt.addActionListener(this);
			bSqrt.addActionListener(this);
			bFrac.addActionListener(this);
			bDot.addActionListener(this);

			equals.addActionListener(this);
			backspace.addActionListener(this);

			fmi1.addActionListener(this);
			fmi2.addActionListener(this);
			fmi3.addActionListener(this);
		}


	public void actionPerformed(ActionEvent a){


		try{
				/* |-------- Handling Exceptions ---------| */


			if(a.getSource()==num0){
				value+=0;
				tField.setText(value);
			}
			if(a.getSource()==num1){
				value+=1;
				tField.setText(value);
			}
			if(a.getSource()==num2){
				value+=2;
				tField.setText(value);
			}
			if(a.getSource()==num3){
				value+=3;
				tField.setText(value);
			}
			if(a.getSource()==num4){
				value+=4;
				tField.setText(value);
			}
			if(a.getSource()==num5){
				value+=5;
				tField.setText(value);
			}
			if(a.getSource()==num6){
				value+=6;
				tField.setText(value);
			}
			if(a.getSource()==num7){
				value+=7;
				tField.setText(value);
			}
			if(a.getSource()==num8){
				value+=8;
				tField.setText(value);
			}
			if(a.getSource()==num9){
				value+=9;
				tField.setText(value);
			}



/*	25Oct2005:	Designed and programmed by jfernandez.ph 	*/
/*	13Nov2005:	Designed and programmed by jfernandez.ph 	*/



			if (a.getSource() == bAdd){
				v1 = Double.parseDouble( tField.getText() );
				ctr=0;
				o = '+';
				value="";
				tField.setText("" +value);
			}

			if (a.getSource() == bSub){
					v1 = Double.parseDouble( tField.getText() );
					ctr=0;
					o = '-';
					value="";
					tField.setText("" +value);
			}

			if (a.getSource() == bMul){
					v1 = Double.parseDouble( tField.getText() );
					ctr=0;
					o = 'x';
					value="";
					tField.setText("" +value);
			}

			if (a.getSource() == bDiv){
					v1 = Double.parseDouble( tField.getText() );
					ctr=0;
					o = '/';
					value="";
					tField.setText("" +value);
			}

			if (a.getSource() == bPer){
					v1 = Double.parseDouble( tField.getText() );
					ctr=0;
					value="";
					answer = (v1/100);
					tField.setText("" +answer);
			}



/*	25Oct2005:	Designed and programmed by jfernandez.ph	 */
/*	13Nov2005:	Designed and programmed by jfernandez.ph 	*/



		/* |-- EQUALS ACTION --| */

			if(a.getSource()==equals){
						value="";
						v2 = Double.parseDouble(tField.getText());

					if(o=='+'){
						ctr=0;
						answer = v1 + v2;
						tField.setText("" +answer);
						value=""; v1=null; v2=null;
					}
					else if(o=='-'){
						ctr=0;
						answer = v1 - v2;
						tField.setText("" +answer);
						value=""; v1=null; v2=null;
					}
					else if(o=='x'){
						ctr=0;
						answer = v1 * v2;
						tField.setText("" +answer);
						value=""; v1=null; v2=null;
					}
					else if(o=='/'){
						ctr=0;
						answer = v1 / v2;
						tField.setText("" +answer);
						value=""; v1=null; v2=null;
					}
					else if(o=='%'){
						ctr=0;
						answer = v1 % v2;
						tField.setText("" +answer);
						value=""; v1=null; v2=null;
					}
					else{}
			}

		/* |-- EQUALS ACTION --| */



/*	25Oct2005:	Designed and programmed by jfernandez.ph	 */
/*	13Nov2005:	Designed and programmed by jfernandez.ph 	*/



			/*	|-- Clear --| */
			if(a.getSource()==clear){
				ctr=0;
				v1=null;
				v2=null;
				value="";
				answer=0.;
				tField.setText("0.");

			}

			if(a.getSource()==bCE){
				ctr=0;
				value="";
				tField.setText("0.");
			}


			/*	|-- Point --| */
			if(a.getSource() == bDot){
				if(ctr==0){
						value+=".";
						ctr+=1;
						tField.setText("" +value);
				}
				else{
					System.out.print("");
				}

			}



			/* |-- Back Space --| */
			if(a.getSource() == backspace){
					value = value.substring(0, value.length()-1 );
					tField.setText("" +value);
			}



			/* |-- Square Root --| */
			if(a.getSource() == bSqrt){
				ctr=0;
				value = "";
				v1 = Math.sqrt( Double.parseDouble( tField.getText() ) );
				tField.setText("" +v1);
			}



			/* |-- Integer --| */
			if(a.getSource() == bInt){
				ctr=0;
				NumberConverted = ( Double.parseDouble(tField.getText()) * -1 );
				value = "";
				tField.setText("" +NumberConverted);
			}



			/* |-- Reciprocal --| */
			if(a.getSource() == bFrac){
				ctr=0;
				value = "";
				Double NumberContainer = ( 1 / Double.parseDouble(tField.getText() ) );
				tField.setText("" +NumberContainer);
			}


	// ------------ Menu Item Actions ------------ //

			if(a.getSource() == fmi1){
				cv = tField.getText();
			}

			if(a.getSource() == fmi2){
				tField.setText("" +cv);
			}

			if(a.getSource() == fmi3){
				System.exit(0);
			}

		}	// End of Try


/* |-------- Attempting To Catch Runtime Errors ---------| */

		catch(StringIndexOutOfBoundsException str){}
		catch(NumberFormatException nfe){}
		catch(NullPointerException npe){}

	}	// END OF ACTION EVENTS



/*	25Oct2005:	Designed and programmed by jfernandez.ph 	*/
/*	13Nov2005:	Designed and programmed by jfernandez.ph 	*/


	public static void main (String args[]){
		Calculator s = new Calculator();
		s.launchFrame();
	}
}
