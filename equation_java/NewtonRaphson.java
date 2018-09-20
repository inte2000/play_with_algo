import java.util.*;
import java.io.*;


class NewtonRaphson {
	public NewtonRaphson() {
		super();
	}

    public double Newton(double x0, Function f) {
        double x = EquationConst.INVALID_VALUE;
        int count = 0;
        do
        {
            double x1 = x0 - f.Func(x0) / CalcDerivative(f, x0); //应用迭代公式
            if (Math.abs(x1 - x0) < EquationConst.PRECISION)
            {
                x = x1;
                break;
            }
            x0 = x1;  //更新迭代变量
            count++;
        } while (count < EquationConst.MAX_RUN_LOOP);

        return x;
    }

    private double CalcDerivative(Function f, double x)  {
        return (f.Func(x + 0.000005) - f.Func(x - 0.000005)) / 0.00001;
    }

}
