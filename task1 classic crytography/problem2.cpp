//����ϣ�������ƽ� 18339009
#include<iostream>
#include<iomanip>
using namespace std;

#define N 3    //���Ծ���ά������

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

//����Ϊ�������� 
//����һ��չ������|A|
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

//����ÿһ��ÿһ�е�ÿ��Ԫ������Ӧ������ʽ�����A*
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
            ans[j][i]  =  getA(temp,n-1);  //�˴�˳�������ת��
            if((i+j)%2 == 1)
            {
                ans[j][i] = - ans[j][i];
            }
        }
    }
    
    for(int i=0;i<3;i++)
       for(int j=0;j<3;j++)
          ans[i][j]=(ans[i][j]+26)%26;

    display(ans,"��m2-m1)�������");
}

//�õ���������src������󱣴浽des�У�������Ȼ����ģ���㴦�� 
bool GetMatrixInverse(int src[N][N],int n,int des[N][N])
{
    int flag=getA(src,n);
    int t[N][N];
    if(0==flag)
    {
        cout<< "ԭ��������ʽΪ0���޷����档����������" <<endl;
        return false;//���������������ʽΪ0�������½���
    }
    else
    {
    	cout<<endl<<"��øþ�������ʽΪ��"<<flag<<endl;
        getAStart(src,n,t);//tΪԭʼ������� 
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
            	//�����ͬ������ 
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

//ģ26����˷� 
void multiply(int m[3][3],int n[3][3],int des[3][3])
{
	for(int i=0;i<3;i++){  
        for(int j=0;j<3;j++){  
            des[i][j]=0;//��ʼ�� 
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
	
	cout<<"���ģ�"<<p<<endl;
	cout<<"******���ľ���******";
	for(int i=0;i<p.length();i++){
		if(i%3==0){
			cout<<endl;
		}
		cout<<setw(4)<<p[i]-'A'<<" ";
	}
	
	cout<<endl<<endl<<"�����ľ����Ϊ����3*3�ľ���"<<endl; 
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
	
	cout<<endl<<"���ģ�"<<c<<endl;
	cout<<"******���ľ���******";
	for(int i=0;i<p.length();i++){
		if(i%3==0){
			cout<<endl;
		}
		cout<<setw(4)<<c[i]-'A'<<" ";
	}
	cout<<endl; 
	
    cout<<endl<<"�����ľ����Ϊ����3*3�ľ���"<<endl; 
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
	
	cout<<endl<<"******�������******"<<endl;
	cout<<"n1=m1*ek+B"<<endl;
	cout<<"n2=m2*ek+B --BΪ��3������b��ɵ�3*3����"<<endl;
	cout<<"��ʽ������ɵã�n2-n1=(m2-m1)*ek ---��ʽ"<<endl; 
	
	//���¾������
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			m[i][j]=(m2[i][j]+26-m1[i][j]+26)%26;//���� 
			n[i][j]=(n2[i][j]+26-n1[i][j]+26)%26;//���� 
		}
	} 
	
	cout<<endl<<"����ã�"<<endl;
	display(m,"m2-m1");
	display(n,"n2-n1");
		
	//�����ľ������
	int mver[3][3]={0};

	cout<<endl<<"����ʽA(-1)=A*/|A|���㣨m2-m1��������󣬵þ���m(-1)��"<<endl;
	GetMatrixInverse(m,3,mver); 
	display(mver,"m(-1)"); 
	cout<<endl<<"��m(-1)����ˢ�ʽ,�ý������Ϊ��Կ����L��"<<endl;
	int des[3][3]={0};
	int res[3][3]={0};
	multiply(mver,n,des);
	display(des,"L");
	
	int b[3]={0}; 
	cout<<endl<<"��L����ʽ��n1=m1*ek+B���������b��"<<endl;
    
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
