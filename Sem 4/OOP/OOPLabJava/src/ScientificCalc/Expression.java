/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ScientificCalc;
import java.math.BigInteger;
import java.util.*;
import java.io.*;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
/**
 *
 * @author The Guardian
 */
public class Expression {
    //private int[] nextIndex;
    StringBuffer exp;
    
    //CONSTRUCTORS
    Expression(){
        exp=new StringBuffer("");
        //nextIndex=new int[exp.length()];
        //Arrays.fill(nextIndex, 0);
    }
    Expression(String expression){
        this.exp=new StringBuffer(expression);        
        //nextIndex=new int[exp.length()];
        //Arrays.fill(nextIndex, 0);
    }
    Expression(StringBuffer expression){
        this.exp=expression;        
        //nextIndex=new int[exp.length()];
        //Arrays.fill(nextIndex, 0);
    }
    
    //EXPRESSION MODIFICAION
    public String get(){
        return this.exp.toString();
    }
    public void set(String expression){
        this.exp=new StringBuffer(expression);
    }
    public void reset(){
        this.exp=new StringBuffer("");
    }
    public void appendEnd(char c){
        this.exp.append(c);
    }
    public void delEnd(){
        this.exp.deleteCharAt(this.exp.length()-1);
    }
    public String solve()throws ScriptException {
        ScriptEngineManager mgr = new ScriptEngineManager();
        ScriptEngine engine = mgr.getEngineByName("JavaScript");
        try{
            return engine.eval(this.exp.toString()).toString();
        } catch (ScriptException se) {
            return "Wrong Input";
        }
    }
    
    
    
    public static void main(String args[])throws IOException,ScriptException {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        ScriptEngineManager mgr = new ScriptEngineManager();
        ScriptEngine engine = mgr.getEngineByName("JavaScript");
        String foo =br.readLine();
        try{
            System.out.println(engine.eval(foo));
        } catch (ScriptException se) {
            System.out.print("Wrong expression");
        }
   
    }
}
