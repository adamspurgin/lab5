int main(){
  int n1 =0,n2=1; //First 2 numbers
  int fib=0;
  int i;

  //Calculate fibonacci sequence 1,2,3,5,8,13,21,34,55,89
  for(i=0;i<10;i++){
    fib=n1+n2;
    n1=n2;
    n2=fib;
  }
  return fib;
}

