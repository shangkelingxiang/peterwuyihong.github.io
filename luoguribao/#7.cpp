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
#define maxn 200005
int n,m;
int B1,B2;
int a[maxn],b[maxn],t;
int f[maxn],F[450];
short g[450][maxn];
int G[450][450];
int l,r,k;
int p,q;
int L[450],R[450],POS[maxn],pos[maxn];
void deal(int l,int r,int L=0,int R=0){
	for(int i=l;i<=r;i++)f[a[i]]++;
	for(int i=l;i<=r;i++)F[POS[a[i]]]++;
	for(int i=L;i<=R;i++)f[a[i]]++;
	for(int i=L;i<=R;i++)F[POS[a[i]]]++;
}
void cl(int l,int r,int L=0,int R=0){
	for(int i=l;i<=r;i++)f[a[i]]=0;
	for(int i=l;i<=r;i++)F[POS[a[i]]]=0;
	for(int i=L;i<=R;i++)f[a[i]]=0;
	for(int i=L;i<=R;i++)F[POS[a[i]]]=0;
} 
int gg(int x){
	if(p+1>q-1)return f[x];
	return f[x]+g[q-1][x]-g[p][x];
}
int GG(int x){
	if(p+1>q-1)return F[x];
	return F[x]+G[q-1][x]-G[p][x];
}
int ask(){
	int i,j;
	for(i=1;;i++)
	if(k>GG(i))k-=GG(i);
	else break;
	for(j=(i-1)*B1+1;;j++)
	if(k>gg(j))k-=gg(j);
	else break;
	return j;
}
signed main(){
#ifndef ONLINE_JUDGE
	freopen("testdata.in","r",stdin);
	freopen("Cindy.out","w",stdout);
#endif
	rd(n),rd(m);
	for(int i=1;i<=n;i++)rd(a[i]),b[i]=a[i];
	sort(b+1,b+n+1);t=unique(b+1,b+n+1)-b-1;
	B1=sqrt(t),B2=sqrt(n);
	for(int i=1;i<=n;i++)a[i]=lower_bound(b+1,b+t+1,a[i])-b;
	for(int i=1;i<=t;i++)POS[i]=(i-1)/B1+1;
	for(int i=1;i<=n;i++)pos[i]=(i-1)/B2+1;
	for(int i=1;i<=pos[n];i++){
		L[i]=R[i-1]+1;
		R[i]=L[i]+B2-1;
	}R[pos[n]]=n;
	for(int i=1;i<=n;i++){
		g[pos[i]][a[i]]++;
		G[pos[i]][POS[a[i]]]++;
	}
	for(int i=2;i<=pos[n];i++){
		for(int j=1;j<=t;j++)g[i][j]+=g[i-1][j];
		for(int j=1;j<=POS[t];j++)G[i][j]+=G[i-1][j];
	}
	while(m--){
		rd(l),rd(r),rd(k);
		p=pos[l],q=pos[r];
		if(p==q)deal(l,r);
		else deal(l,R[p],L[q],r);
		wr(b[ask()]),putchar('\n');
		if(p==q)cl(l,r);
		else cl(l,R[p],L[q],r);
	}
#ifndef ONLINE_JUDGE
	cerr<<endl<<(double)clock()/CLOCKS_PER_SEC;
#endif
}
