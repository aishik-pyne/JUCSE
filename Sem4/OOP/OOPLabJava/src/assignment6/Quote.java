package assignment6;

import java.io.*;
import java.util.*;
public class Quote {
    private String name;
    private int count; 
    private Random random;
    public Quote(String nm) throws IOException, FileNotFoundException {
            name = nm;
            BufferedReader br = new BufferedReader(new FileReader(nm));
            String line;
            random = new Random();
            count = 0;
            while((line = br.readLine()) != null)
                    if(line.isEmpty())
                            count++;
            br.close();
            random = new Random();
    }
    public String getName() {
            return name;
    }
    public int getCount() {
            return count;
    }
    public String read(int number) throws IOException, FileNotFoundException {
            BufferedReader br = new BufferedReader(new FileReader(name));
            String line = null;
            int i = 1;
            while(((line = br.readLine()) != null) && (i < number))
                    if(line.isEmpty())
                            i++;
            if(line == null) {
                    br.close();
                    return line;
            }
            String lines = line;
            while(((line = br.readLine()) != null) && (!line.isEmpty()))
                    lines += "\n" + line;
            br.close();
            return lines;
    }
    public String readRandom() throws IOException, FileNotFoundException {
            return read(random.nextInt(count));
    }
}