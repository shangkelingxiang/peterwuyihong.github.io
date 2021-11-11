#include<bits/stdc++.h>
using namespace std;
#define debug(x) cerr<<#x<<' '<<x<<endl
#ifndef ONLINE_JUDGE
	#define fuck getchar
#else
	#define fuck nc
#endif
char nc(){
  	static char buf[1<<25],*p=buf,*q=buf;
  	if(p==q&&(q=(p=buf)+fread(buf,1,1<<25,stdin),p==q))return EOF;
  	return *p++;
}
template<class T>void read(T&x){
	short f=1;x=0;
	char ch=fuck();
	while(!isdigit(ch)){
		if(ch=='-')f=-1;
		ch=fuck();
	}while(isdigit(ch)){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=fuck();
	}x*=f;
}
template<class T>void write(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)write(x/10);
	putchar(x%10+48);
}

#define maxn 200010
int n,m,a[maxn],b[maxn];
int t,tot,cnt;
int ans[maxn];
struct point{
	int op,l,r,k;
}q[maxn<<1],q1[maxn<<1],q2[maxn<<1];
int c[maxn];
int ask(int x){
	int ans=0;
	for(;x;x-=x&-x)ans+=c[x];
	return ans;
}
void add(int x,int y){
	for(;x<=n;x+=x&-x)c[x]+=y;
}
void solve(int l,int r,int L,int R){
	if(L>R)return;
	if(l==r){
		for(int i=L;i<=R;i++)
		if(q[i].op)ans[q[i].op]=l;
		return;
	}
	int mid=(l+r)>>1;
	int ll=0,rr=0;
	for(int i=L;i<=R;i++)
	if(q[i].op==0){
		if(q[i].r<=mid)add(q[i].l,1),q1[++ll]=q[i];
		else q2[++rr]=q[i];
	}else{
		int t=ask(q[i].r)-ask(q[i].l-1);
		if(q[i].k<=t)q1[++ll]=q[i];
		else q[i].k-=t,q2[++rr]=q[i];
	}
	for(int i=L;i<=R;i++)
	if(!q[i].op&&q[i].r<=mid)add(q[i].l,-1);
	for(int i=1;i<=ll;i++)q[i+L-1]=q1[i];
	for(int i=1;i<=rr;i++)q[i+L+ll-1]=q2[i];
	solve(l,mid,L,L+ll-1),solve(mid+1,r,R-rr+1,R);
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
	freopen("testdata.ans","w",stdout);
#endif
	read(n),read(m);
	for(int i=1;i<=n;i++)read(a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	tot=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+tot+1,a[i])-b;
	for(int i=1;i<=n;i++)q[++t].l=i,q[t].r=a[i],q[t].op=0;
	for(int i=1;i<=m;i++)read(q[++t].l),read(q[t].r),read(q[t].k),q[t].op=i;
	solve(1,n,1,t);
	for(int i=1;i<=m;i++)write(b[ans[i]]),putchar('\n');
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
