import requests
def G(x):
    fp=open(x.split('/')[-1],'wb')
    fp.write(requests.get(x).content)
    fp.close()
for i in range(1,99):
    G('https://cdn.jsdelivr.net/gh/BoringHacker/cdn/emojis/majsoul/maj-'+str(i)+'.png')
    print('get ',i,'!')
