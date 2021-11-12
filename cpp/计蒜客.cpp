#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxn 1000010
const int p=998244353;
int n,k;
int jc[maxn],jcinv[maxn];
int ksm(int a,int b){
	int ans=1;
	for(;b;b>>=1,a=a*a%p)
	if(b&1)ans=ans*a%p;
	return ans;
}
int C(int n,int m){
	return jc[n]*jcinv[n-m]%p*jcinv[m]%p;
}
signed main(){
	freopen("mex.in","r",stdin);
	freopen("mex.out","w",stdout);
	cin>>n>>k;
	jc[0]=jcinv[0]=1;
	for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%p;
	jcinv[n]=ksm(jc[n],p-2);
	for(int i=n-1;i;i--)jcinv[i]=jcinv[i+1]*(i+1)%p;
	cout<<C(n,k-1)*ksm(C(n,k),p-2)%p;
}