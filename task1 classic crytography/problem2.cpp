//仿射希尔密码破解 18339009
#include<iostream>
#include<iomanip>
using namespace std;

#define N 3    //测试矩阵维数定义

void display(int m[3][3],string name)
{
	cout<<"******"<<name<<"******"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			cout<<setw(4)<<m[i][j]<<" ";
		}
		cout<<endl;
	}
}

//以下为矩阵求逆 
//按第一行展开计算|A|
int getA(int arcs[N][N],int n)
{
	
    if(n==1)
    {
        return arcs[0][0];
    }
    int ans = 0;
    int temp[N][N]={0.0};
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            for(k=0;k<n-1;k++)
            {
                temp[j][k] = arcs[j+1][(k>=i)?k+1:k];
            }
        }
        int t = getA(temp,n-1);
        if(i%2==0)
        {
            ans += arcs[0][i]*t;
        }
        else
        {
            ans -=  arcs[0][i]*t;
        }
    }
    return (ans+26)%26;
}

//计算每一行每一列的每个元素所对应的余子式，组成A*
void  getAStart(int arcs[N][N],int n,int ans[N][N])
{
    if(n==1)
    {
        ans[0][0] = 1;
        return;
    }
    int i,j,k,t;
    int temp[N][N];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<n-1;k++)
            {
                for(t=0;t<n-1;t++)
                {
                    temp[k][t] = arcs[k>=i?k+1:k][t>=j?t+1:t];
                }
            }
            ans[j][i]  =  getA(temp,n-1);  //此处顺便进行了转置
            if((i+j)%2 == 1)
            {
                ans[j][i] = - ans[j][i];
            }
        }
    }
    
    for(int i=0;i<3;i++)
       for(int j=0;j<3;j++)
          ans[i][j]=(ans[i][j]+26)%26;

    display(ans,"（m2-m1)伴随矩阵");
}

//得到给定矩阵src的逆矩阵保存到des中，这里依然采用模运算处理 
bool GetMatrixInverse(int src[N][N],int n,int des[N][N])
{
    int flag=getA(src,n);
    int t[N][N];
    if(0==flag)
    {
        cout<< "原矩阵行列式为0，无法求逆。请重新运行" <<endl;
        return false;//如果算出矩阵的行列式为0，则不往下进行
    }
    else
    {
    	cout<<endl<<"求得该矩阵行列式为："<<flag<<endl;
        getAStart(src,n,t);//t为原始伴随矩阵 
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
            	//求逆的同余整数 
            	des[i][j]=0;
            	if(t[i][j]%flag==0){
            		des[i][j]=t[i][j]/flag;
				}  
            	else{
            		int k=0;
            		for(k=1;k<26;k++)
            			if((flag*k)%26==t[i][j]){
            				des[i][j]=k;
            				break;
						}  
				}
            }
        }
    }
    return true;
}

//模26矩阵乘法 
void multiply(int m[3][3],int n[3][3],int des[3][3])
{
	for(int i=0;i<3;i++){  
        for(int j=0;j<3;j++){  
            des[i][j]=0;//初始化 
            for(int k=0;k<3;k++){  
                des[i][j]+=((m[i][k]%26)*(n[k][j]%26))%26;  
            }  
        }  
    }  
    for(int i=0;i<3;i++){
    	for(int j=0;j<3;j++)
    	   des[i][j]%=26;
	} 
 } 


int main()
{
	string p="ADISPLAYEDEQUATION";
	string c="DSRMSIOPLXLJBZULLM";
	int m1[3][3]={0},m2[3][3]={0},m[3][3]={0}; 
	int n1[3][3]={0},n2[3][3]={0},n[3][3]={0}; 
	
	cout<<"明文："<<p<<endl;
	cout<<"******明文矩阵******";
	for(int i=0;i<p.length();i++){
		if(i%3==0){
			cout<<endl;
		}
		cout<<setw(4)<<p[i]-'A'<<" ";
	}
	
	cout<<endl<<endl<<"将明文矩阵分为两个3*3的矩阵"<<endl; 
	int k=0;
	cout<<"******m1******"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			m1[i][j]=p[k]-'A';
			cout<<setw(4)<<m1[i][j]<<" ";
			k++;
		}
		cout<<endl;
	}
	cout<<"******m2******"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			m2[i][j]=p[k]-'A';
			cout<<setw(4)<<m2[i][j]<<" ";
			k++;
		}
		cout<<endl;
	}	
	
	cout<<endl<<"密文："<<c<<endl;
	cout<<"******密文矩阵******";
	for(int i=0;i<p.length();i++){
		if(i%3==0){
			cout<<endl;
		}
		cout<<setw(4)<<c[i]-'A'<<" ";
	}
	cout<<endl; 
	
    cout<<endl<<"将密文矩阵分为两个3*3的矩阵"<<endl; 
	k=0;
	cout<<"******n1******"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			n1[i][j]=c[k]-'A';
			cout<<setw(4)<<n1[i][j]<<" "; 
			k++;
		}
		cout<<endl;
	}
	cout<<"******n2******"<<endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			n2[i][j]=c[k]-'A';
			cout<<setw(4)<<n2[i][j]<<" ";
			k++;
		}
		cout<<endl;
	}
	
	cout<<endl<<"******密码分析******"<<endl;
	cout<<"n1=m1*ek+B"<<endl;
	cout<<"n2=m2*ek+B --B为由3个向量b组成的3*3矩阵"<<endl;
	cout<<"两式相减，可得：n2-n1=(m2-m1)*ek ---①式"<<endl; 
	
	//以下矩阵相减
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			m[i][j]=(m2[i][j]+26-m1[i][j]+26)%26;//明文 
			n[i][j]=(n2[i][j]+26-n1[i][j]+26)%26;//密文 
		}
	} 
	
	cout<<endl<<"计算得："<<endl;
	display(m,"m2-m1");
	display(n,"n2-n1");
		
	//求明文矩阵的逆
	int mver[3][3]={0};

	cout<<endl<<"按公式A(-1)=A*/|A|计算（m2-m1）的逆矩阵，得矩阵m(-1)："<<endl;
	GetMatrixInverse(m,3,mver); 
	display(mver,"m(-1)"); 
	cout<<endl<<"得m(-1)后，左乘①式,得结果矩阵即为密钥矩阵L："<<endl;
	int des[3][3]={0};
	int res[3][3]={0};
	multiply(mver,n,des);
	display(des,"L");
	
	int b[3]={0}; 
	cout<<endl<<"将L代入式子n1=m1*ek+B，解得向量b："<<endl;
    
	int tmp[3]={0};
	tmp[0]=p[0]*des[0][0]+p[1]*des[1][0]+p[2]*des[2][0];
	tmp[1]=p[0]*des[0][1]+p[1]*des[1][1]+p[2]*des[2][1];
	tmp[2]=p[0]*des[0][2]+p[1]*des[1][2]+p[2]*des[2][2];
	for(int i=0;i<3;i++)
	   cout<<(c[i]+26-tmp[i]%26)%26<<" ";
	
	cout<<endl<<endl;
	
	system("pause");
	return 0;
} 
