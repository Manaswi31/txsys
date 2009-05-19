public class BubbleSortInt
{
    public static void main (String[] argv) {
	int[] values = {3, 1, 6, 2} ;
	sort (values);
	for (int i=0; i<values.length; i++)
	    System.out.print (values[i] + " ");
	System.out.println();
    }

    public static void sort(int[] values) {
	int temp;
	for (int i=0; i<values.length; i++)
	    for (int j=0; j<values.length - 1; j++) {
		if (values[j] > values[j+1]) {
		    temp = values[j];
		    values[j] = values[j+1];
		    values[j+1] = temp;
		}
	    }
    }

}
