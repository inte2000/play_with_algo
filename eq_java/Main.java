
import java.util.*;
import java.io.*;



public class Main {
      private static double[][] _an = { { 5.0, 2.0, 1.0 }, { -1.0, 4.0, 2.0 }, { 2.0, -3.0, 10.0 } };  
      private static double[] _bn = { -12.0, 20.0, 3.0 };
      
 	public static void main(String[] args) {
            double[] x1 = new double[EqConst.VEC_N];
		Jacobi de = new Jacobi();
		de.JacobiEqn(_an, _bn, EqConst.VEC_N, x1);
        
            System.out.println("Jacobi Equation: ");
            for(int i = 0; i < EqConst.VEC_N; i++) {
                System.out.printf("x[%d] = %4.2f\n",i, x1[i]);
            }
            
            double[] x2 = new double[EqConst.VEC_N];
            GaussSeidel gs = new GaussSeidel();
            gs.GaussSeidelEqn(_an, _bn, EqConst.VEC_N, x2);
            
            System.out.println("Gauss Seidel Equation: ");
            for(int i = 0; i < EqConst.VEC_N; i++) {
                System.out.printf("x[%d] = %4.2f\n",i, x2[i]);
            }
	}
}
