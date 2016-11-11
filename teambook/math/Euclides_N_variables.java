import java.math.BigInteger;
import java.util.Scanner;
public class k {
	static long x, y;
	public static void solve(long a, long b) {
		if (b == 0) {
			x = 1; y = 0; return;
		}
		solve(b, a % b);
		long x1 = y;
		long y1 = x - (a / b) * y;
		x = x1;
		y = y1;
	}
	public static long gcd (long a, long b){
		if (a == 0 || b == 0) return a + b;
		long c = a % b;
		while(c != 0){
			a = b;
			b = c;
			c = a % b;
		}
		return b;
	}
	static int maxn = 55;
	static long coef[] = new long[maxn];
	static BigInteger ans[] = new BigInteger[maxn];
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int caso = 1;
		while (true) {
			int n;
			long K;
			n = in.nextInt();
			K = in.nextLong();
			if (n == 0 && K == 0) break;
			long allgcd = 0;
			for (int i = 0; i < n; i++){
				coef[i] = in.nextInt();
				allgcd = gcd(allgcd, coef[i]);
			}
			System.out.print("Case #"+ caso+":"); caso++;
			if (K % allgcd != 0){
				System.out.print(" Stupid keypad!");
			} else {
				if (n == 1)
					System.out.print(" "+(K/coef[0]));
				else {
					solve(coef[0], coef[1]);
					ans[0] = BigInteger.valueOf(x);
					ans[1] = BigInteger.valueOf(y);
					long lastgcd = gcd(coef[0], coef[1]);
					for (int i = 2; i < n; i++) {
						solve(lastgcd, coef[i]);
						for (int j = 0; j < i; j++)
							ans[j] = ans[j].multiply(BigInteger.valueOf(x));
						ans[i] = BigInteger.valueOf(y);
						lastgcd = gcd(lastgcd, coef[i]);
					}
					long mul = K / allgcd;
					for (int i = 0; i < n; i++)
						ans[i] = ans[i].multiply(BigInteger.valueOf(mul));
					for (int i = 0; i < n; i++)
						System.out.print(" "+ans[i]);
				}
			}
			System.out.println("");
		}
	}
}
/*
3 7
1 3 5
1 3
6
0 0

*/
