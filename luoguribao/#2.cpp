#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
template<class T>
void read(T &x)
{
	T ans=0;short f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=getchar();
	}while(ch>='0'&&ch<='9')
	{
		ans=(ans<<1)+(ans<<3)+(ch^48);
		ch=getchar();
	}x=ans*f;
}
#define maxn 200005
struct
{
	int l,r;
	vector<int>s;
}tree[maxn<<2];
int n,m;
int a[maxn],p[maxn],t;
int l,r,k;
vector<int>S[maxn];
void build(int x,int l,int r)
{
	int mid=(l+r)>>1;
	tree[x].l=l,tree[x].r=r;
	if(l==r)
	{
		tree[x].s=S[mid];
		return;
	}
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	if(x==1)return;
	vector<int>::iterator it1=tree[x<<1].s.begin();
	vector<int>::iterator it2=tree[x<<1|1].s.begin();
	while(it1!=tree[x<<1].s.end()&&it2!=tree[x<<1|1].s.end())
	if(*it1<*it2)tree[x].s.push_back(*it1),it1++;
	else tree[x].s.push_back(*it2),it2++;
	while(it1!=tree[x<<1].s.end())tree[x].s.push_back(*it1),it1++;
	while(it2!=tree[x<<1|1].s.end())tree[x].s.push_back(*it2),it2++;
}
int ask(int x,int k)
{
	if(tree[x].l==tree[x].r)return *tree[x].s.begin();
	int val=upper_bound(tree[x<<1].s.begin(),tree[x<<1].s.end(),r)-upper_bound(tree[x<<1].s.begin(),tree[x<<1].s.end(),l-1);
	if(val>=k)return ask(x<<1,k);
	if(val<k)return ask(x<<1|1,k-val);
}
int main()
{
	read(n),read(m);
	for(int i=1;i<=n;i++)
		read(a[i]),p[i]=a[i];
	sort(p+1,p+n+1);
	t=unique(p+1,p+n+1)-p-1;
	for(int i=1;i<=n;i++)
	{
		a[i]=lower_bound(p+1,p+t+1,a[i])-p;
		S[a[i]].push_back(i);
	}
	build(1,1,t);
	while(m--)
	{
		read(l),read(r),read(k);
		printf("%d\n",p[a[ask(1,k)]]);
	}
}
