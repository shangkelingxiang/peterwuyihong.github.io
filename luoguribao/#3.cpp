#include<iostream>
#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
#define debug(x) cerr<<#x<<' '<<x<<endl
#ifndef ONLINE_JUDGE
	#define pia getchar
#else
	#define pia nc
#endif
char nc(){
  	static char buf[1<<25],*p=buf,*q=buf;
  	if(p==q&&(q=(p=buf)+fread(buf,1,1<<25,stdin),p==q))return EOF;
  	return *p++;
}
template<class T>void read(T&x){
	short f=1;x=0;
	char ch=pia();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=pia();
	}while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=pia();
	}x*=f;
}
template<class T>void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+48);
}
#define int long long
#define maxn 100010
#define DEBUG 0
int n,m,a[maxn];
int tag[maxn];
vector<int>u[5000];
int opt,l,r,k;
int L[maxn],R[maxn],pos[maxn];
int blo,tot;
int mn=LLONG_MAX,mx=LLONG_MIN;
int calc(int l,int r,int val){
	int p=pos[l],q=pos[r];
	int res=0;
	if(DEBUG)p=q=0;
	if(p==q){
		for(int i=l;i<=r;i++)
			res+=a[i]+tag[p]<=val;
	}else{
		for(int i=l;i<=R[p];i++)
			res+=a[i]+tag[p]<=val;
		for(int i=L[q];i<=r;i++)
			res+=a[i]+tag[q]<=val;
		for(int i=p+1;i<=q-1;i++){
			if(1){
				if(*u[i].begin()>val-tag[i]);
				else if(*--u[i].end()<=val-tag[i])res+=(int)u[i].size();
				else res+=upper_bound(u[i].begin(),u[i].end(),val-tag[i])-u[i].begin();
			}else{
				res+=upper_bound(u[i].begin(),u[i].end(),val-tag[i])-u[i].begin();
			}
		}
	}
	return res;
}
int ask(int l,int r,int k){
	int lb=mn,rb=mx,mid;
	while(lb<=rb){
		mid=(lb+rb)>>1;
		if(calc(l,r,mid)<k)lb=mid+1;
		else rb=mid-1;
	}
	return lb;
}
void change(int l,int r,int k){
	if(k<0)mn+=k;else mx+=k;
	int p=pos[l],q=pos[r];
	if(DEBUG)p=q=0;
	if(p==q){
		for(int i=l;i<=r;i++)a[i]+=k;
		for(int i=L[p];i<=R[p];i++)a[i]+=tag[p];
		tag[p]=0;
		u[p].clear();
		for(int i=L[p];i<=R[p];i++)u[p].push_back(a[i]);
		sort(u[p].begin(),u[p].end());
		return;
	}
	for(int i=l;i<=R[p];i++)a[i]+=k;
	for(int i=L[p];i<=R[p];i++)a[i]+=tag[p];
	for(int i=L[q];i<=r;i++)a[i]+=k;
	for(int i=L[q];i<=R[q];i++)a[i]+=tag[q];
	tag[p]=tag[q]=0;
	u[p].clear(),u[q].clear();
	for(int i=L[p];i<=R[p];i++)u[p].push_back(a[i]);
	for(int i=L[q];i<=R[q];i++)u[q].push_back(a[i]);
	sort(u[p].begin(),u[p].end());
	sort(u[q].begin(),u[q].end());
	for(int i=p+1;i<=q-1;i++)tag[i]+=k;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]),mn=min(mn,a[i]),mx=max(mx,a[i]);
	blo=sqrt(n);
	tot=n/blo;
	if(n%blo)tot++;
	for(int i=1;i<=tot;i++){
		L[i]=R[i-1]+1;
		R[i]=L[i]+blo-1;
	}R[tot]=n;
	for(int i=1;i<=n;i++)pos[i]=(i-1)/blo+1;
	for(int i=1;i<=n;i++)u[pos[i]].push_back(a[i]);
	for(int i=1;i<=tot;i++)sort(u[i].begin(),u[i].end());
	while(m--){
		read(opt),read(l),read(r),read(k);
		if(opt==1)write(ask(l,r,k)),putchar('\n');
		else change(l,r,k);
	}
}
