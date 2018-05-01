public final class JavaThread {
    private JavaThread() {
        // Do nothing
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            int upper = Integer.parseInt(args[0]);
            if (upper < 0) {
                System.err.println(args[0] + " must be >= 0");
            } else {
                Sum sum = new Sum();
                Thread thrd = new Thread(new Summation(upper, sum));
                thrd.start();
                try {
                    thrd.join();
                    System.out.println("sum = " + sum.getSum());
                } catch (InterruptedException ie) {
                    System.err.println(ie.toString());
                }
            }
        } else {
            System.err.println("usage: java JavaThread <integer value>");
        }
    }
}

final class Sum {
    private int sum;

    public int getSum() {
        return sum;
    }

    public void setSum(int value) {
        this.sum = value;
    }
}

final class Summation implements Runnable {
    private int upper;
    private Sum sumValue;

    public Summation(int upper, Sum sumValue) {
        this.upper = upper;
        this.sumValue = sumValue;
    }

    public void run() {
        int sum = 0;
        for (int i = 1; i <= upper; i++) {
            sum += i;
        }
        sumValue.setSum(sum);
    }
}
