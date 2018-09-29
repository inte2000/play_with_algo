
import java.util.*;
import java.io.*;



public class Main {

 	public static void main(String[] args) {
		TrapeziumIntegration ti = new TrapeziumIntegration();
		double x = ti.Trapezium(new TestFunction(), 0.000000001, 1.0, 10000);
            System.out.println("Trapezium Integration  (10000 steps):");
            System.out.printf("x = %12.8f\n", x);
            
		x = ti.VsTrapezium(new TestFunction(), 0.000000001, 1.0, 0.000000001);
            System.out.println("VsTrapezium Integration  (EPS = 0.000000001):");
            System.out.printf("x = %12.8f\n", x);
            
		SimpsonIntegration si = new SimpsonIntegration();
		x = si.Simpson(new TestFunction(), 0.000000001, 1.0, 10000);
            System.out.println("Simpson Integration  (10000 steps):");
            System.out.printf("x = %12.8f\n", x);
            
		x = si.VsSimpson(new TestFunction(), 0.000000001, 1.0, 0.000000001);
            System.out.println("VsSimpson Integration  (EPS = 0.000000001):");
            System.out.printf("x = %12.8f\n", x);
            
            
	}
}
