#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;//���Ӷ��������ģ��м�û�пյ�λ��
int estimateb();
//int estimatew();
int searchw(int s);//�Ұ�����������λ��
int searchb();//�Һ�����ܻ��µ�λ��
int save();//��������
int read();//��������
bool judge1(int c,int b);//�ж�ĳ���Ƿ�������
bool judge2();//�ж�ĳһ���Ƿ��еط���������
//bool judgew(int c,int b);
int turn(int c,int b);//��ת����
int output();
int findb();//�����º����λ��
int findw();//�����°����λ��
int gob();//�º���
int gow1();//�°���,�˻���ս
int gow2();//˫�˶�ս
int a[8][8][64];//a������¼����
int searchi=0,k = 0,black = 0,white = 0,go = 0,selectg = 0,ha = 0;//searchi��ʾҪ�Ѽ�����black��ʾ��������Ŀ��white��ʾ������Ŀ��k��ʾ���߶��ٲ�
//---------------------------------estimate----------------------------------
int estimateb()
{
	int i,j,value=1;
	findw();
	for (i = 0 ; i < 8 ; i ++)
	{
		for (j = 0; j < 8 ; j ++)
		{
			if (a[i][j][k] == 1 && (i == 0 || i == 7) && (j == 0 || j == 7))  value = value + 10;
			if (a[i][j][k] == 1 && ( (i == 0 || i == 7) || (j == 0 || j == 7) ) )  value = value + 5;
			if (a[i][j][k] == 2 && (i == 0 || i == 7) && (j == 0 || j == 7))  value = value + 1;
			if (a[i][j][k] == 2 && ( (i == 0 || i == 7) || (j == 0 || j == 7) ) )  value = value + 1;
			if (a[i][j][k] == 3 && (i == 0 || i == 7) && (j == 0 || j == 7))  value = value + 10;
			if (a[i][j][k] == 3 && ( (i == 0 || i == 7) || (j == 0 || j == 7) ) )  value = value + 5;
			//if (a[i][j][k] == 1)  value += 3;
		}
	}
	return value;
}
//--------------------------------�����°�������λ��---------------------------
int searchw(int s)
{
	int v = 0;
	int m,i,j,ki = 0,kj=0,es[64],best = 0,mm=0,bestm = 0,recs[64][2],rec[64][2];
	if (s == ha)
	{
		int zz;
		zz=estimateb();
		return zz;
	}
	if (s < ha)
	{
		int esss[64]={0};
		findw();
		ki=0;
		for (i = 0; i < 8; i ++)
			for ( j = 0; j < 8; j ++)
				if (a[i][j][k-1] == 3)
				{
					recs[ki][0] = i;
					recs[ki][1] = j;
					ki ++;
				}
		for ( m = 0 ; m < ki ; m ++)
		{
			k ++;
			for ( i = 0; i < 8 ; i ++ )
			{
				for ( j = 0; j < 8 ; j ++ )
				{
					if ( i == recs[m][0] && j == recs[m][1] )  a[i][j][k] = 1;
					else a[i][j][k] = a[i][j][k-1];
				}
			}
			turn(recs[m][0],recs[m][1]);

			findb();
			kj=0;
			for (i = 0; i < 8; i ++)
				for ( j = 0; j < 8; j ++)
					if (a[i][j][k-1] == 3)
					{
						rec[kj][0] = i;
						rec[kj][1] = j;
						kj ++;
					}
			for ( mm = 0 ; mm < kj ; mm ++)
			{
				k ++;
				for ( i = 0; i < 8 ; i ++ )
				{
					for ( j = 0; j < 8 ; j ++ )
					{
						if ( i == rec[mm][0] && j == rec[mm][1] )  a[i][j][k] = 2;
						else a[i][j][k] = a[i][j][k-1];
					}
				}
				turn(rec[mm][0],rec[mm][1]);
				es[mm] = searchw(s+1);
				k --;
			}
			int sums=0;
			for(mm=0;mm<kj;mm++)sums=sums+es[mm];
			if(kj==0)kj=1;
			esss[m]=sums/kj;
			k --;
		}		
		v = 0;
		for (m = 0 ; m < ki ; m ++)
		{
			v = v + esss[m];
		}
		if(ki==0)ki=1;
		v = v / ki;
		return v;
	}
	return 0;
}
//--------------------------------����---------------------------------------
int save()
{
	int i,j;
	ofstream out("save.txt",ios::out);
	if ( !out )
	{
		cout << "open error!" << endl;
		return 0;
	}
	out.clear();
	out << go <<' ';
	out << k;
	for (i = 0; i < 8;i ++)
	{
		for (j = 0; j < 8; j ++)
		{
			out <<' '<< a[i][j][k];
		}
	}
	out.close();
	cout << "�ѱ���" << endl;
	Sleep(3000);
	return 0;
}
//--------------------------------����---------------------------------------
int read()
{
	int i,j;
	ifstream in("save.txt",ios::in);
	if (!in )  {cout << "cannot open !" << endl; return 0;}
	in >> go;
	in >> k;
	for (i = 0; i < 8; i ++)
	{
		for (j = 0 ; j < 8; j ++ )
		{
			in >> a[i][j][k];
		}
	}
	in.close();

	return 0;
}
//--------------------------------�������-----------------------------------
int output()
{
	int i,j;
	cout <<"    "<<'1'<<"   "<<'2'<<"   "<<'3'<<"   "<<'4'<<"   "<<'5'<<"   "<<'6'<<"   "<<'7'<<"   "<<'8'<<endl;
	cout<<' '<<"�����Щ��Щ��Щ��Щ��Щ��Щ��Щ���"<<endl;
	for ( i = 0; i < 8; i++ )
	{		
		if ( i != 0) cout <<' '<< "�����੤�੤�੤�੤�੤�੤�੤��"<<endl;
		cout << i+1;
		cout <<"��";
		for ( j = 0; j < 8; j ++ )
		{
			if (a[i][j][k] == 0)  cout <<"  ��";//��û�¹����λ��
			if (a[i][j][k] == 1)  cout <<"��";//����
			if (a[i][j][k] == 2)  cout <<"��";//����
			if (a[i][j][k] == 3)  cout <<"����";//����ʾ��������ĵط�
		}
		cout << endl;
	}	
	cout <<' '<<"�����ة��ة��ة��ة��ة��ة��ة���"<<endl;
	cout << "k = "<< k << endl;
	int ccc = 0;
	for (i = 0; i < 8; i ++)
		for (j = 0; j < 8; j ++)
			if (a[i][j][k] == 1 || a[i][j][k] == 2) ccc ++;
	cout << "ccc = " << ccc << endl;
	cout <<"�������������(9��9)"<< endl;
	return 0;
}
//---------------------------�ж�ĳ���Ƿ�������------------------------------//����12,12�����Ѿ��¹����λ�ã���Ҫ������������ʧ��������鷳
bool judge1(int c,int b)
{
	if ( (a[c-1][b-1][k] == 1 || a[c-1][b-1][k] == 2) || c > 8 || b > 8)  
	{
		cout << "�˴����ܷ�����!!  ���������� !!" << endl;
		return true;
	}
	else return false;
}
//---------------------�ж�ĳһ���Ƿ��еط���������------------------------
bool judge2()
{
	int i,j,num = 0;//num��ʾ��������λ�õĸ���
	for ( i = 0; i < 8; i ++)
		for ( j = 0; j < 8; j ++)
			if ( a[i][j][k] == 3) num++;//cout << num << endl;
	if (num > 0)   return true;
	else return false;
}
//----------------------------��ת����---------------------------------------
int turn(int c,int b)
{
	int i,j,row,col;
	if ( a[c-1][b][k] != 0 && a[c-1][b][k] != 3 && a[c-1][b][k] != a[c-1][b-1][k])//������
		for( j = b+1; j < 8 ; j++)
		{
			if ( a[c-1][j][k] == 0 || a[c-1][j][k] == 3)  break;
			if ( a[c-1][j][k] == a[c-1][b-1][k])  
			{
				for( col = b; col < j; col ++)  a[c-1][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c-1][b-2][k] != 0 && a[c-1][b-2][k] != 3 && a[c-1][b-2][k] != a[c-1][b-1][k])//������
		for( j = b - 3; j >= 0 ; j --)
		{
			if ( a[c-1][j][k] == 0 || a[c-1][j][k] == 3)  break;
			if ( a[c-1][j][k] == a[c-1][b-1][k])  
			{
				for( col = b -2; col > j; col --)  a[c-1][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c][b-1][k] != 0 && a[c][b-1][k] != 3 && a[c][b-1][k] != a[c-1][b-1][k])//find downwards
		for ( i = c + 1; i < 8; i ++) 
		{
			if ( a[i][b-1][k] == 0 || a[i][b-1][k] == 3) break;
			if ( a[i][b-1][k] == a[c-1][b-1][k]) 
			{
				for ( row = c; row < i; row ++)  a[row][b-1][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c-2][b-1][k] != 0 && a[c-2][b-1][k] != 3 && a[c-2][b-1][k] != a[c-1][b-1][k])//find upwards
		for ( i = c - 3; i >= 0; i --) 
		{
			if ( a[i][b-1][k] == 0 || a[i][b-1][k] == 3) break;
			if ( a[i][b-1][k] == a[c-1][b-1][k]) 
			{
				for ( row = c -2; row > i; row --)  a[row][b-1][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c][b][k] != 0 && a[c][b][k] != 3 && a[c][b][k] != a[c-1][b-1][k])//�����·�����
		for ( i = c + 1, j = b + 1; i < 8 ,j < 8; i ++, j ++) 
		{
			if ( a[i][j][k] == 0 || a[i][j][k] == 3 ) break;
			if ( a[i][j][k] == a[c-1][b-1][k]) 
			{
				for ( row = c,col = b; row < i,col < j; row ++,col ++)  a[row][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c-2][b-2][k] != 0 && a[c-2][b-2][k] != 3 && a[c-2][b-2][k] != a[c-1][b-1][k]) //�����Ϸ�����
		for ( i = c - 3, j = b - 3; i >= 0,j >= 0; i --, j --)
		{
			if ( a[i][j][k] == 0 || a[i][j][k] == 3 ) break;
			if ( a[i][j][k] == a[c-1][b-1][k]) 
			{
				for ( row = c - 2,col = b - 2; row > i,col > j; row --,col --)  a[row][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c][b-2][k] != 0 && a[c][b-2][k] != 3 && a[c][b-2][k] != a[c-1][b-1][k])//�����·�����
		for ( i = c + 1, j = b - 3; i < 8 ,j >= 0; i ++, j --) 
		{
			if ( a[i][j][k] == 0 || a[i][j][k] == 3 ) break;
			if ( a[i][j][k] == a[c-1][b-1][k]) 
			{
				for ( row = c,col = b - 2; row < i,col > j; row ++,col --)  a[row][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c-2][b][k] != 0 && a[c-2][b][k] != 3 && a[c-2][b][k] != a[c-1][b-1][k])//�����Ϸ�����
		for ( i = c  - 3, j = b + 1; i >= 0 ,j < 8; i --, j ++) 
		{
			if ( a[i][j][k] == 0 || a[i][j][k] == 3 ) break;
			if ( a[i][j][k] == a[c-1][b-1][k]) 
			{
				for ( row = c - 2,col = b; row > i,col < j; row --,col ++)  a[row][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	return 0;
}
//----------------------�º���----------------------------------------
int gob()
{	
	int c, b,i,j;
	cin >> c >> b ;
	if (c==10 && b == 10)
	{
		read();//cout<<go<<endl;cout<< k << endl;
		system("cls");
		if (go == 1) 
		{
			output();
			cout << "��ڷ�����!" << endl;
			gob();
			return 0;
		}
		if (go == 2) 
		{
			output();
			cout << "��׷�����!" << endl;//gow();
			return 0;
		}
		if (go == 0) {cout << "δ����!������" << endl;}
	}
	findb();
	if ( c == 9 && b == 9 )  {go = 1;save();gob();return 0;}
	if (a[c-1][b-1][k] != 3) {cout << "�˴����ܷ�����!!  ����������!!" << endl;gob();return 0;}
	if (judge1(c,b))  { gob();return 0;}//����˴����ܷ����ӣ������º���//k ++;
	k ++;
	for ( i = 0; i < 8 ; i ++ )
		for ( j = 0; j < 8 ; j ++ )
		{
			if ( i == c-1 && j == b-1 )  a[i][j][k] = 2;
			else a[i][j][k] = a[i][j][k-1];
		}
	turn(c,b);
	findw();//��������Ѱ�Ұ�����µ�λ��
	system("cls");
	output();
	judge2();
	if(judge2())
	{
		if (selectg == 1)  cout << "�ȴ��׷�����......"<<endl;
		else cout<<"��׷�����" << endl;
	}
	return 0;
}
//--------------------�°���------------------------- 
//˫�˶�ս
int gow2()
{
	int c,b,i,j;
	cin >> c >> b ;
	if ( c == 9 && b == 9 )  {go = 2;save();gow2();return 0;}
	if (a[c-1][b-1][k] != 3) {cout << "�˴����ܷ�����!!  ����������!!" << endl;gow2();return 0;}
	if (judge1(c,b))  {gow2();return 0;}//����˴����ܷ����ӣ�ֱ�ӽ�������,�����°���//
	k ++;
	for ( i = 0; i < 8 ; i ++ )
		for ( j = 0; j < 8 ; j ++ )
		{
			if ( i == c-1 && j == b-1 )  a[i][j][k] = 1;
			else a[i][j][k] = a[i][j][k-1];
		}
		turn(c,b);
		findb();//�������֮��Ѱ�Һ�����µ�λ��
		system("cls");
		output();
	
			judge2();
		if (judge2())  cout<<"��ڷ�����" << endl;
		return 0;
}
//�˻���ս
int gow1()
{
	int c,b,i,j,rec[64][2],recb[64][2],ki = 0,kj=0,m=0,mm=0,best = 0,bestm = 0;//rec������¼ÿһ��������µ�λ�ã�recb������¼��������ÿһ��������µ�λ��
	for ( i = 0; i < 8; i ++ )//�ҿ������λ��
		for ( j = 0; j < 8; j ++)
			if (a[i][j][k] == 3)
			{
				rec[ki][0] = i;
				rec[ki][1] = j;
				ki ++;
			}
	cout <<"ki = " << ki << endl;
	int esww[64] = {0};//������¼ÿһ������λ���¹������Ĺ�ֵ
	for ( m = 0; m < ki; m ++)//����ÿһ��������λ�õ�ֵ
	{
		int es[64]={0};//��¼ÿһ���������������ƵĹ�ֵ
		k ++;
		for ( i = 0; i < 8 ; i ++ )
		{
			for ( j = 0; j < 8 ; j ++ )
			{
				if ( i == rec[m][0] && j == rec[m][1] )  a[i][j][k] = 1;
				else a[i][j][k] = a[i][j][k-1];
			}
		}
		turn(rec[m][0],rec[m][1]);
		findb();
		kj=0;
		for (i = 0; i < 8; i ++)
			for ( j = 0; j < 8; j ++)
				if (a[i][j][k] == 3)
				{
					recb[kj][0] = i;
					recb[kj][1] = j;
					kj ++;
				}
		for ( mm = 0 ; mm < kj ; mm ++)
		{
			k ++;
			for ( i = 0; i < 8 ; i ++ )
			{
				for ( j = 0; j < 8 ; j ++ )
				{
					if ( i == recb[mm][0] && j == recb[mm][1] )  a[i][j][k] = 2;
					else a[i][j][k] = a[i][j][k-1];
				}
			}
			turn(recb[mm][0],recb[mm][1]);
			es[mm] = searchw(1);
			k --;
		}
		int sum=0,z=0;
		for(z=0;z<kj;z++)sum=sum+es[z];
		if(kj==0)kj=1;
		esww[m]=sum/kj;
		k --;
	}	
	for ( m = 0; m < ki; m ++)
	{
		if (esww[m] > best)  bestm = m;
	}
	c = rec[bestm][0]+1; b = rec[bestm][1]+1;
	cout << "location"<<c <<' '<< b << endl;
	k ++;
	for ( i = 0; i < 8 ; i ++ )
		for ( j = 0; j < 8 ; j ++ )
		{
			if ( i == c-1 && j == b-1 )  a[i][j][k] = 1;
			else a[i][j][k] = a[i][j][k-1];
		}
		turn(c,b);
		findb();//�������֮��Ѱ�Һ�����µ�λ��	
		system("cls");
		output();
		cout << "��ʾ����һ���������ڣ�"<<c<<','<<b<<'��'<<endl;
		judge2();
		if (judge2())  cout<<"��ڷ�����" << endl;
		return 0;
}
//--------------------�Һ���������λ��-----------------
int findb()
{
	int c,b,i,j;
	for (i = 0; i < 8; i ++)//�����һ�ο������λ�� 
		for ( j = 0; j < 8; j ++)  if (a[i][j][k] == 3)  a[i][j][k] = 0;		
	for ( c = 1; c <= 8; c ++)//c��ʾ�ڼ��У�b��ʾ�ڼ���
		for ( b = 1; b <= 8; b ++)
			if ( a[c-1][b-1][k] == 2)
			{
				if ( a[c-1][b][k] != 0 && a[c-1][b][k] != a[c-1][b-1][k] && a[c-1][b][k] != 3 )//������,�Ա߲��ǿյģ�Ҳ�����Լ���ͬ(���ǲ�ͬ��ɫ����)
					for( j = b+1; j < 8 ; j++)
					{
						if ( a[c-1][j][k] == 0)  //����ط���������
						{
							a[c-1][j][k] = 3;
							break;
						}
						if ( a[c-1][j][k] == a[c-1][b-1][k] || a[c-1][j][k] == 3)  break;	//�����һ�������ϻ��������ɫ�ľ���Ч
					}
				if ( a[c-1][b-2][k] != 0 && a[c-1][b-2][k] != a[c-1][b-1][k] && a[c-1][b-2][k] != 3)//������
					for( j = b - 3; j >= 0 ; j --)
					{
						if ( a[c-1][j][k] == 0)   
						{
							a[c-1][j][k] = 3;
							break;
						}
						if ( a[c-1][j][k] == a[c-1][b-1][k] || a[c-1][j][k] == 3)  break;   //�����һ�������ϻ��������ɫ�ľ���Ч
					}
				if ( a[c][b-1][k] != 0 && a[c][b-1][k] != a[c-1][b-1][k] && a[c][b-1][k] != 3)//find downwards
					for ( i = c + 1; i < 8; i ++) 
					{
						if ( a[i][b-1][k] == 0) 
						{
							a[i][b-1][k] = 3;
							break;
						}
						if ( a[i][b-1][k] == a[c-1][b-1][k]  ||a[i][b-1][k] == 3)  break;//����Ѿ���ǹ�������ѭ��
					}
				if ( a[c-2][b-1][k] != 0 && a[c-2][b-1][k] != a[c-1][b-1][k] && a[c-2][b-1][k] != 3)//find upwards
					for ( i = c - 3; i >= 0; i --) 
					{
						if ( a[i][b-1][k] == 0) 
						{
							a[i][b-1][k] = 3;
							break;
						}
						if ( a[i][b-1][k] == a[c-1][b-1][k] || a[i][b-1][k] == 3)  break;
					}
				if ( a[c][b][k] != 0 && a[c][b][k] != a[c-1][b-1][k] && a[c][b][k] != 3)//�����·�����
					for ( i = c + 1, j = b + 1; i < 8 ,j < 8; i ++, j ++) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3 )  break;
					}
				if ( a[c-2][b-2][k] != 0 && a[c-2][b-2][k] != a[c-1][b-1][k] && a[c-2][b-2][k] != 3) //�����Ϸ�����
					for ( i = c - 3, j = b - 3; i >= 0,j >= 0; i --, j --)
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3 )  break;
					}
				if ( a[c][b-2][k] != 0 && a[c][b-2][k] != a[c-1][b-1][k] && a[c][b-2][k] != 3)//�����·�����
					for ( i = c + 1, j = b - 3; i < 8 ,j >= 0; i ++, j --) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3)  break;
					}
				if ( a[c-2][b][k] != 0 && a[c-2][b][k] != a[c-1][b-1][k] && a[c-2][b][k] != 3)//�����Ϸ�����
					for ( i = c  - 3, j = b + 1; i >= 0 ,j < 8; i --, j ++) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3)  break;
					}
			}
	return 0;
}
//-------------------------�Ұ�����µ�λ��------------------------------
int findw()
{
	int c,b,i,j;
	for (i = 0; i < 8; i ++)//�����һ�ο������λ�� 
		for ( j = 0; j < 8; j ++)  if (a[i][j][k] == 3)  a[i][j][k] = 0;
	for ( c = 1; c <= 8; c ++)
		for ( b = 1; b <= 8; b ++)
			if ( a[c-1][b-1][k] == 1)
			{
				if ( a[c-1][b][k] != 0 && a[c-1][b][k] != a[c-1][b-1][k] && a[c-1][b][k] != 3 )//������,�Ա߲��ǿյģ�Ҳ�����Լ���ͬ(���ǲ�ͬ��ɫ����)
					for( j = b+1; j < 8 ; j++)
					{
						if ( a[c-1][j][k] == 0)  //����ط���������
						{
							a[c-1][j][k] = 3;
							break;
						}
						if ( a[c-1][j][k] == a[c-1][b-1][k] || a[c-1][j][k] == 3)  break;	//�����һ�������ϻ��������ɫ�ľ���Ч
					}
				if ( a[c-1][b-2][k] != 0 && a[c-1][b-2][k] != a[c-1][b-1][k] && a[c-1][b-2][k] != 3)//������
					for( j = b - 3; j >= 0 ; j --)
					{
						if ( a[c-1][j][k] == 0)   
						{
							a[c-1][j][k] = 3;
							break;
						}
						if ( a[c-1][j][k] == a[c-1][b-1][k] || a[c-1][j][k] == 3)  break;   //�����һ�������ϻ��������ɫ�ľ���Ч
					}
				if ( a[c][b-1][k] != 0 && a[c][b-1][k] != a[c-1][b-1][k] && a[c][b-1][k] != 3)//find downwards
					for ( i = c + 1; i < 8; i ++) 
					{
						if ( a[i][b-1][k] == 0) 
						{
							a[i][b-1][k] = 3;
							break;
						}
						if ( a[i][b-1][k] == a[c-1][b-1][k]  ||a[i][b-1][k] == 3)  break;//����Ѿ���ǹ�������ѭ��
					}
				if ( a[c-2][b-1][k] != 0 && a[c-2][b-1][k] != a[c-1][b-1][k] && a[c-2][b-1][k] != 3)//find upwards
					for ( i = c - 3; i >= 0; i --) 
					{
						if ( a[i][b-1][k] == 0) 
						{
							a[i][b-1][k] = 3;
							break;
						}
						if ( a[i][b-1][k] == a[c-1][b-1][k] || a[i][b-1][k] == 3)  break;
					}
				if ( a[c][b][k] != 0 && a[c][b][k] != a[c-1][b-1][k] && a[c][b][k] != 3)//�����·�����
					for ( i = c + 1, j = b + 1; i < 8 ,j < 8; i ++, j ++) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3 )  break;
					}
				if ( a[c-2][b-2][k] != 0 && a[c-2][b-2][k] != a[c-1][b-1][k] && a[c-2][b-2][k] != 3) //�����Ϸ�����
					for ( i = c - 3, j = b - 3; i >= 0,j >= 0; i --, j --)
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3 )  break;
					}
				if ( a[c][b-2][k] != 0 && a[c][b-2][k] != a[c-1][b-1][k] && a[c][b-2][k] != 3)//�����·�����
					for ( i = c + 1, j = b - 3; i < 8 ,j >= 0; i ++, j --) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3)  break;
					}
				if ( a[c-2][b][k] != 0 && a[c-2][b][k] != a[c-1][b-1][k] && a[c-2][b][k] != 3)//�����Ϸ�����
					for ( i = c  - 3, j = b + 1; i >= 0 ,j < 8; i --, j ++) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3)  break;
					}
			}
	return 0;
}
//----------------------������Ϸ------------------------------
int  play(void)
{
	int i,j;
	while( k < 60)//������ֻ������60������
	{
		findb();
		if (judge2() ) {gob();}
		else 
		{
			system("cls");
			findw();output();
			if (k < 60)
			{
				cout<< "�ڷ��޴��£���׷�����!" << endl;
				Sleep(2000);
			}
		}//����������壬����һ��������*****�˴���Ҫһ����ʱ
		findw();
		if (judge2() ) 
		{
			if (selectg == 1) gow1();
			if (selectg == 2) gow2();
		}
		else 
		{
			system("cls");
			findb();output();
			if (k<60)
			{
				cout << "�׷��޴����£���ڷ�����!" << endl;
				Sleep(2000);
			}
		}//����������壬����һ��������
		findb();//���˫����������ߣ�˵����Ϸ�������ж���һ��Ӯ��
		int numb = 0;
		for (i = 0; i < 8; i ++)
			for (j = 0; j < 8; j ++)
				if (a[i][j][k] == 3)  numb ++;
		if (numb == 0) 
		{
			findw();
			for (i = 0 ; i < 8 ; i++)
				for ( j = 0; j < 8; j ++)
					if (a[i][j][k] == 3) numb ++;
		}
		if (numb == 0)
		{
			for (i = 0; i < 8;i++)
				for (j = 0; j < 8; j ++ )
					if ( a[i][j][k] != 0 && a[i][j][k] != 3)
					{
						if (a[i][j][k] == 1) 
						{
							
							white ++;//cout <<"��ϲ�׷���ʤ!!!!" << endl; 
							//return 0;
						}
						if (a[i][j][k] == 2)
						{
							black ++;
							//cout <<"��ϲ�ڷ���ʤ!!!!" << endl;
						}
					}
			if ( black > white && selectg == 2)   cout << "��ϲ�ڷ���ʤ!!";
			if ( black > white && selectg == 1)   cout << "��ϲ����ս�ɹ�!!";
			if ( black == white)   cout << "ƽ��!!";
			if ( black < white && selectg == 2)   cout << "��ϲ�׷���ʤ!!";
			if ( black < white && selectg == 1)   cout << "��սʧ��!!";
			return 0;
		}
	}
	return 0;
}
//-----------------------------------------------�������-------------------------------
int main()
{
	int i,j;

	for ( i = 0; i < 8; i ++ )
		for ( j = 0; j < 8; j ++ )
		{
			if ( i == 3 && j == 3 || i == 4 && j == 4 ) a[i][j][k] = 1;
			else if ( i == 3 && j == 4 || i == 4 && j == 3 ) a[i][j][k] = 2;
			else a[i][j][k] = 0;
		}
	findb();
	cout << "��ӭ�����ڰ���!!!" << endl;
	cout << "��ѡ����Ϸģʽ!!!" << endl;
	cout << "��սAI������  1  "<< endl;
	cout << "˫����Ϸ������ 2 "<< endl;
	cin >> selectg;
	while  ( !(selectg == 1 || selectg == 2) ) 
	{
		cout << "û�д�ѡ�������ѡ��!!!"<< endl;
		cin >>selectg;
	}
	if (selectg == 1) 
	{
		cout <<"��ѡ���Ѷ�" << endl;
		cout << "�� : 1"<< endl;
		cout << "�е� : 2"<< endl;
		cout << "���� : 3"<< endl;
		cin >> ha;
	}
	system("cls");
	output();
	cout<<"��ڷ�����" <<"                 �������������(10,10)" <<endl;
	play();
	return 0;
}