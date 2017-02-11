/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Random;

/**
 *
 * @author The Guardian
 */
class Clicker implements Runnable{
    Thread t;
    long count=0;
    boolean running=true;
    Clicker(String nameThread,int p){
        t=new Thread(this);
        t.setName(nameThread);
        t.setPriority(p);
    }
    @Override
    public void run(){
        while(running){
            count++;
        }
    }
    public void start(){
        t.start();
    }
    public void stop(){
        running=false;
    }
}
public class HiLoPri {
    public static void main(String args[]){
        Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
        Clicker hi=new Clicker("Hi",Thread.MAX_PRIORITY-1);
        Clicker lo=new Clicker("Lo",Thread.MIN_PRIORITY+1);
        
        hi.start();
        lo.start();
        try{
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            System.out.println("Main thread interrupted.");           
        }
        
        hi.stop();
        lo.stop();
        try {
            hi.t.join();
            lo.t.join();
        } catch (InterruptedException e) {
            System.out.println("InterruptedException caught");
        }

        System.out.println("Lo count="+lo.count);
        System.out.println("Hi count="+hi.count);
    }
}
