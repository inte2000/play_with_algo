import java.util.*;
import java.io.*;


class GaussSeidel {
	public GaussSeidel() {
		super();
	}

    public void GaussSeidelEqn(double a[][], double b[], int n, double x[]) {
        double max_diff = 0.0;
        do {
            max_diff = 0.0;
            for (int i = 0; i < n; i++) {
                double sum = 0.0;
                for (int k = 0; k < n; k++) {
                    //对角线元素不计算
                    if (i != k)  {
                        sum += a[i][k] * x[k];
                    }
                }
                double xt = (b[i] - sum) / a[i][i];   //根据关系计算xi的新值
                if (Math.abs(xt - x[i]) > max_diff) {
                    max_diff = Math.abs(xt - x[i]);
                }
                x[i] = xt;
            }
        } while (max_diff > EqConst.PRECISION);
    }

}
