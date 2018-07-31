/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Random;

import javax.swing.*;
import java.awt.event.*;
/**
 *
 * @author aishi
 */
class BasePanel{
    final double p1=100;
    JRadioButton b1,b2;
    ButtonGroup bg;
    
    BasePanel(){
        b1=new JRadioButton("Model1");
        b2=new JRadioButton("Model2");
        bg=new ButtonGroup();bg.add(b1);bg.add(b2);
        
    }
}
class AccPanel{
    
}
class OrderGUI extends JFrame{
    BasePanel bp;
    AccPanel ap;
    
    public OrderGUI(){
        super("Specification");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        bp=new BasePanel();
        ap=new AccPanel();
    }
    private class myListner implements ActionListener{
        public void actionPerformed(ActionEvent e){
            double total=0.0;
            
        }
    }
}
class GUI{
    public static void main(String args[]){
        
    }
}
