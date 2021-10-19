#include "testlib.h"
int a[1000010],x;
bool f[1000010];
int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  int m=ans.readInt(),l=ans.readInt();
  int n=inf.readInt();
  for(int i=1;i<=n;i++)a[i]=inf.readInt();
  if(ouf.readInt()!=m)quitf(_wa,"m is incorrect");
	if(ouf.readInt()!=l)quitf(_wa,"l is incorrect");
	while(m--){
		int g=INT_MIN;
		for(int i=1;i<=l;i++){
			x=ouf.readInt();
			if(x<1||x>n)quitf(_wa,"out of range");
			if(f[x])quitf(_wa,"same number found");
			f[x]=1;
			if(a[x]<g)quitf(_wa,"not LIS");
			g=a[x];
		}
	}
	quitf(_ok,"ok correct ans");
}
