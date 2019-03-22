
int sumf();
int mymain(void) {
  int a1=1;
  int a2=2;
  int a3=3;
  int a4=4;
  int a5=5;
  int a6=6;
  int su;
  su = sumf(a1,a2,a3,a4,a5,a6);
  while(1);
}
int sumf(int b1,int b2,int b3,int b4,int b5,int b6)
{
  int c = b1+b3+b5+b2+b4+b6;
  return c;
}
