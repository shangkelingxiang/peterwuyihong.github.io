#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
#define maxn 200050
int n,m,tmp,l,r,k;
int a[maxn],p[maxn];
struct
{
	int l,r;
	vector<int>num;
}tree[maxn<<2];
void build(int x,int l,int r)
{	
	tree[x].l=l,tree[x].r=r;
	int mid=(l+r)>>1;
	if(l==r)
	{
		tree[x].num.push_back(a[mid]);
		return;
	}
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	vector<int>::iterator it1=tree[x<<1].num.begin();
	vector<int>::iterator it2=tree[x<<1|1].num.begin();
	while(it1!=tree[x<<1].num.end()&&it2!=tree[x<<1|1].num.end())
	if(*it1<*it2)tree[x].num.push_back(*it1),it1++;
	else tree[x].num.push_back(*it2),it2++;
	while(it1!=tree[x<<1].num.end())tree[x].num.push_back(*it1),it1++;
	while(it2!=tree[x<<1|1].num.end())tree[x].num.push_back(*it2),it2++;
}
int ask(int x,int l,int r,int d)
{
	if(l<=tree[x].l&&r>=tree[x].r)
	return upper_bound(tree[x].num.begin(),tree[x].num.end(),d)-tree[x].num.begin();
	int mid=(tree[x].l+tree[x].r)>>1;
	int ans=0;
	if(l<=mid)ans+=ask(x<<1,l,r,d);
	if(r>mid)ans+=ask(x<<1|1,l,r,d);
	return ans;
}
int main()
{
//	freopen("testdata.in","r",stdin);
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",a+i),p[i]=a[i];
	sort(p+1,p+n+1);
	build(1,1,n);
	while(m--)
	{
		scanf("%d %d %d",&l,&r,&k);
		int L=1,R=n;
		while(L<=R)
		{
			int MID=(L+R)>>1;
			if(ask(1,l,r,p[MID])>=k)R=MID-1;
			else L=MID+1;
		}
		printf("%d\n",p[L]);
	}
}
