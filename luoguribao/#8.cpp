#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
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
template<class T>void rd(T&x){
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
template<class T>void wr(T x){
	if(x<0)putchar('-'),x=-x;
	if(x>=10)wr(x/10);
	putchar(x%10+48);
}

#define maxn 200010
int n,m;
int a[maxn],b[maxn],cnt;
int blo,pos[maxn];
int BLO,POS[maxn];
struct Q{
	int l,r,k,id;
	bool operator<(Q x)const{
		if(pos[x.l]^pos[l])return pos[l]<pos[x.l];
		if(pos[l]&1)return r<x.r;
		return r>x.r;
	}
}q[maxn];
int ans[maxn];
int g[maxn],G[maxn];
int L[maxn],R[maxn];
void add(int x){
	g[x]++;G[POS[x]]++;
}
void del(int x){
	g[x]--;G[POS[x]]--;
}
int ask(int k){
	int i;
	for(i=1;i<=POS[cnt];i++)
	if(k>G[i])k-=G[i];
	else break;
	for(int j=L[i];j<=R[i];j++){
		k-=g[j];
		if(k<=0)return j;
	}
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)rd(a[i]),b[i]=a[i];
	sort(b+1,b+1+n);
	cnt=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	blo=50;
	BLO=sqrt(cnt);
	for(int i=1;i<=n;i++)pos[i]=(i-1)/blo+1;
	for(int i=1;i<=cnt;i++)POS[i]=(i-1)/BLO+1;
	for(int i=1;i<=POS[cnt];i++){
		L[i]=R[i-1]+1;
		R[i]=L[i]+BLO-1;
	}R[POS[cnt]]=cnt;
	for(int i=1;i<=m;i++){
		rd(q[i].l),rd(q[i].r),rd(q[i].k);
		q[i].id=i;
	}
	sort(q+1,q+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;i++){
		while(r<q[i].r)add(a[++r]);
		while(l>q[i].l)add(a[--l]);
		while(l<q[i].l)del(a[l++]);
		while(r>q[i].r)del(a[r--]);
		ans[q[i].id]=ask(q[i].k);
	}
	for(int i=1;i<=m;i++)wr(b[ans[i]]),putchar('\n');
	cerr<<fuck<<endl;
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
