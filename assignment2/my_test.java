public class Factorial{
    public static void main(String[] a){
	System.out.println(new Fac().ComputeFac(10));
    }
}

class Fac {

    public int ComputeFac(int num, boolean hello){
	int num_aux ;
	// SecondFac c;
	// b = a.ComputeFac(10);
	// b = a.ComputeFac();
	// b = a.ComputeFac(10,20,300);
	// c = new SecondFac();
	// num_aux = this;

	if (num < 1)
	    num_aux = 1 ;
	else 
	    num_aux = num * (this.ComputeFac(num-1, true)) ;
	return num_aux ;
    }

	public int ComputeFac2(int num2, boolean hello2){
	int num_aux2 ;
	if (num2 < 1)
	    num_aux2 = 1 ;
	else 
	    num_aux2 = num * (this.ComputeFac2(num2-1, 1)) ;
	return num_aux2 ;
    }

}


class SecondFac {

    public int SecondCompute(int num){
	int num_aux ;
	if (num < 1)
	    num_aux = 1 ;
	else 
	    num_aux = num * (this.SecondCompute(num-1)) ;
	return num_aux ;
    }

}