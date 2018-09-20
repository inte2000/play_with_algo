
import java.util.*;
import java.io.*;



public class Main {

 	public static void main(String[] args) {
		DichotomyEquation de = new DichotomyEquation();
		double x = de.Dichotomy(-0.8, 12.0, new TestFunction());
            System.out.println("Dichotomy find " + x + " in [-0.8, 12.0]");
            
            NewtonRaphson nr = new NewtonRaphson();
            x = nr.Newton(-8.0, new TestFunction());
            System.out.println("NewtonRaphson find " + x + " in [-0.8, 8.0]");
            x = nr.Newton(8.0, new TestFunction());
            System.out.println("NewtonRaphson find " + x + " in [-0.8, 8.0]");
	}
}
