public class Area {
	
    public void Square(Integer x){
        Integer A = x*x;
		System.debug('Area of Square with side ' + x + ' is '+ A);
    }
    
    public void Circle(Integer x){
        Double A = x*x*3.1415;
		System.debug('Area of Circle with radius ' + x + ' is '+ A);
    }
    
    public void Rectangle(Integer x,Integer y){
        Integer A = x*y;
		System.debug('Area of Rectangle with sides ' + x + ' and '+ y + ' is '+ A);
    }
    
    public void Triangle(Integer x,Integer y){
        Double A = 0.5*x*y;
		System.debug('Area of Triangle with sides ' + x + ' and ' + y + ' is '+ A);
    }
}