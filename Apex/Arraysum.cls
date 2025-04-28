public class Arraysum {
    private void printsum(List<Integer>lst){
		System.debug('The resultant sum of the two arrays is ' + lst);
    }
    public void getsum(List<Integer>lst1 , List<Integer>lst2){
        Integer n = Math.max(lst1.size(),lst2.size());
        
        List<Integer>ans = new Integer[n];
        
        for(Integer i=0;i<Math.min(lst1.size(),lst2.size());i++){
			ans[i] = lst1[i] + lst2[i];
        }
        
        if(lst1.size()<lst2.size()){
			for(Integer i=lst1.size();i<lst2.size();i++) ans[i] = lst2[i];
        }
        else{
            for(Integer i=lst2.size();i<lst1.size();i++) ans[i] = lst1[i];
        }
        
        printsum(ans);
    }
}