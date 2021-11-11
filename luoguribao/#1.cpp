#include<bits/stdc++.h>
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
struct zxs{
	int lc,rc;
	int dat;
}tree[maxn*32];
int rt[maxn],tot;
int l,r,k;
int change(int p,int l,int r,int d){
	int x=++tot;
	tree[x]=tree[p];
	tree[x].dat++;
	if(l==r)return x;
	int mid=(l+r)>>1;
	if(d<=mid)tree[x].lc=change(tree[p].lc,l,mid,d);
	else tree[x].rc=change(tree[p].rc,mid+1,r,d);
	return x;
}
int ask(int u,int v,int l,int r,int d){
	if(l==r)return l;
	int mid=(l+r)>>1,sum=tree[tree[v].lc].dat-tree[tree[u].lc].dat;
	if(d<=sum)return ask(tree[u].lc,tree[v].lc,l,mid,d);
	else return ask(tree[u].rc,tree[v].rc,mid+1,r,d-sum);
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
	freopen("testdata.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)rd(a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	cnt=unique(b+1,b+n+1)-b-1;
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+cnt+1,a[i])-b;
	
	for(int i=1;i<=n;i++)rt[i]=change(rt[i-1],1,cnt,a[i]);
	while(m--){
		rd(l),rd(r),rd(k);
		wr(b[ask(rt[l-1],rt[r],1,cnt,k)]),putchar('\n');
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
