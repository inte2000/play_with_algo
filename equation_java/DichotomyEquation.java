import java.util.*;
import java.io.*;


class DichotomyEquation {
	public DichotomyEquation() {
		super();
	}

    public double Dichotomy(double a, double b, Function f) {
        double mid = (a + b) / 2.0;
        while((b - a) > EquationConst.PRECISION)
        {
            if(f.Func(a) * f.Func(mid) < 0.0)
            {
                b = mid;
            }
            else
            {
                a = mid;
            }
            mid = (a + b) / 2.0;
        }

        return mid;
    }

}
