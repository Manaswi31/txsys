public class BasicSortInt
{
    public static void main (String[] args) {

	if (args.length==0) {
	    System.out.println ("Usage: java BasicSortInt <sort type>.");
	    System.out.println ("<sort type>: 0    bubble sort");
	    System.out.println ("<sort type>: 1    insert sort");
	    System.exit(0);
	}

	int[] values = {3, 1, 6, 2} ;
	for (int i =0; i<values.length; i++)
	    System.out.print(values[i]+" ");
	System.out.println();
	System.out.println();

	BasicSortInt sorter = new BasicSortInt();

	if (args[0].equals("0")) {
	    sorter.bubbleSort (values);
	} else if (args[0].equals("1")) {
	    sorter.insertSort (values);
	}
	for (int i=0; i<values.length; i++)
	    System.out.print (values[i] + " ");
	System.out.println();
    } //main

    public void BasicSortInt() {
	loopNumber = 0;
    }

    public void bubbleSort(int[] values) {
	int temp;
	boolean bubbleFlag = false;
	for (int i=0; i<values.length; i++) {
	    for (int j=0; j<values.length - 1; j++) {
		if (values[j] > values[j+1]) {
		    temp = values[j];
		    values[j] = values[j+1];
		    values[j+1] = temp;
		    bubbleFlag = true;
		} //if
		this.loopNumber++;
	    } //inner for

	    print(values);

	    if (! bubbleFlag)
		break;
	    else
		bubbleFlag = false;
	} //outer for
	System.out.println("bubbleSort: " + this.loopNumber);
    }

    public void insertSort(int[] values) {
	int temp;
	for (int i=0; i<values.length; i++) {
	    for (int j=0; j<values.length - 1; j++) {
		if (values[j] > values[j+1]) {
		    temp = values[j];
		    values[j] = values[j+1];
		    values[j+1] = temp;
		}
		this.loopNumber++;
	    }
	}
	System.out.println("insertSort: " + this.loopNumber);
    }

    public void print(int[] values) {
	for (int i=0; i<values.length; i++)
	    System.out.print (values[i] + " ");
	System.out.println();
    }

    private int loopNumber;

}
