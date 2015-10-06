#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;//棋子都是相连的，中间没有空的位置
int estimateb();
//int estimatew();
int searchw(int s);//找白棋下棋的最佳位置
int searchb();//找黑棋可能会下的位置
int save();//用来存盘
int read();//用来读盘
bool judge1(int c,int b);//判断某处是否能下棋
bool judge2();//判断某一方是否还有地方可以下棋
//bool judgew(int c,int b);
int turn(int c,int b);//翻转棋子
int output();
int findb();//找能下黑棋的位置
int findw();//找能下白棋的位置
int gob();//下黑棋
int gow1();//下白棋,人机对战
int gow2();//双人对战
int a[8][8][64];//a用来记录棋盘
int searchi=0,k = 0,black = 0,white = 0,go = 0,selectg = 0,ha = 0;//searchi表示要搜几步，black表示最后黑棋数目，white表示白棋数目，k表示已走多少步
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
//--------------------------------搜索下白棋的最佳位置---------------------------
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
//--------------------------------存盘---------------------------------------
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
	cout << "已保存" << endl;
	Sleep(3000);
	return 0;
}
//--------------------------------读盘---------------------------------------
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
//--------------------------------输出棋盘-----------------------------------
int output()
{
	int i,j;
	cout <<"    "<<'1'<<"   "<<'2'<<"   "<<'3'<<"   "<<'4'<<"   "<<'5'<<"   "<<'6'<<"   "<<'7'<<"   "<<'8'<<endl;
	cout<<' '<<"┌─┬─┬─┬─┬─┬─┬─┬─┐"<<endl;
	for ( i = 0; i < 8; i++ )
	{		
		if ( i != 0) cout <<' '<< "├─┼─┼─┼─┼─┼─┼─┼─┤"<<endl;
		cout << i+1;
		cout <<"│";
		for ( j = 0; j < 8; j ++ )
		{
			if (a[i][j][k] == 0)  cout <<"  │";//还没下过棋的位置
			if (a[i][j][k] == 1)  cout <<"○│";//白棋
			if (a[i][j][k] == 2)  cout <<"●│";//黑棋
			if (a[i][j][k] == 3)  cout <<"▲│";//▲表示可以下棋的地方
		}
		cout << endl;
	}	
	cout <<' '<<"└─┴─┴─┴─┴─┴─┴─┴─┘"<<endl;
	cout << "k = "<< k << endl;
	int ccc = 0;
	for (i = 0; i < 8; i ++)
		for (j = 0; j < 8; j ++)
			if (a[i][j][k] == 1 || a[i][j][k] == 2) ccc ++;
	cout << "ccc = " << ccc << endl;
	cout <<"如需存盘请输入(9，9)"<< endl;
	return 0;
}
//---------------------------判断某处是否能下棋------------------------------//比如12,12或者已经下过棋的位置，主要用来避免输入失误引起的麻烦
bool judge1(int c,int b)
{
	if ( (a[c-1][b-1][k] == 1 || a[c-1][b-1][k] == 2) || c > 8 || b > 8)  
	{
		cout << "此处不能放棋子!!  请重新输入 !!" << endl;
		return true;
	}
	else return false;
}
//---------------------判断某一方是否还有地方可以下棋------------------------
bool judge2()
{
	int i,j,num = 0;//num表示可以下棋位置的个数
	for ( i = 0; i < 8; i ++)
		for ( j = 0; j < 8; j ++)
			if ( a[i][j][k] == 3) num++;//cout << num << endl;
	if (num > 0)   return true;
	else return false;
}
//----------------------------翻转棋盘---------------------------------------
int turn(int c,int b)
{
	int i,j,row,col;
	if ( a[c-1][b][k] != 0 && a[c-1][b][k] != 3 && a[c-1][b][k] != a[c-1][b-1][k])//往右找
		for( j = b+1; j < 8 ; j++)
		{
			if ( a[c-1][j][k] == 0 || a[c-1][j][k] == 3)  break;
			if ( a[c-1][j][k] == a[c-1][b-1][k])  
			{
				for( col = b; col < j; col ++)  a[c-1][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c-1][b-2][k] != 0 && a[c-1][b-2][k] != 3 && a[c-1][b-2][k] != a[c-1][b-1][k])//往左找
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
	if ( a[c][b][k] != 0 && a[c][b][k] != 3 && a[c][b][k] != a[c-1][b-1][k])//向右下方向找
		for ( i = c + 1, j = b + 1; i < 8 ,j < 8; i ++, j ++) 
		{
			if ( a[i][j][k] == 0 || a[i][j][k] == 3 ) break;
			if ( a[i][j][k] == a[c-1][b-1][k]) 
			{
				for ( row = c,col = b; row < i,col < j; row ++,col ++)  a[row][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c-2][b-2][k] != 0 && a[c-2][b-2][k] != 3 && a[c-2][b-2][k] != a[c-1][b-1][k]) //向左上方向找
		for ( i = c - 3, j = b - 3; i >= 0,j >= 0; i --, j --)
		{
			if ( a[i][j][k] == 0 || a[i][j][k] == 3 ) break;
			if ( a[i][j][k] == a[c-1][b-1][k]) 
			{
				for ( row = c - 2,col = b - 2; row > i,col > j; row --,col --)  a[row][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c][b-2][k] != 0 && a[c][b-2][k] != 3 && a[c][b-2][k] != a[c-1][b-1][k])//向左下方向找
		for ( i = c + 1, j = b - 3; i < 8 ,j >= 0; i ++, j --) 
		{
			if ( a[i][j][k] == 0 || a[i][j][k] == 3 ) break;
			if ( a[i][j][k] == a[c-1][b-1][k]) 
			{
				for ( row = c,col = b - 2; row < i,col > j; row ++,col --)  a[row][col][k] = a[c-1][b-1][k];
				break;
			}
		}
	if ( a[c-2][b][k] != 0 && a[c-2][b][k] != 3 && a[c-2][b][k] != a[c-1][b-1][k])//向右上方向找
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
//----------------------下黑棋----------------------------------------
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
			cout << "请黑方下棋!" << endl;
			gob();
			return 0;
		}
		if (go == 2) 
		{
			output();
			cout << "请白方下棋!" << endl;//gow();
			return 0;
		}
		if (go == 0) {cout << "未存盘!请下棋" << endl;}
	}
	findb();
	if ( c == 9 && b == 9 )  {go = 1;save();gob();return 0;}
	if (a[c-1][b-1][k] != 3) {cout << "此处不能放棋子!!  请重新输入!!" << endl;gob();return 0;}
	if (judge1(c,b))  { gob();return 0;}//如果此处不能放棋子，重新下黑棋//k ++;
	k ++;
	for ( i = 0; i < 8 ; i ++ )
		for ( j = 0; j < 8 ; j ++ )
		{
			if ( i == c-1 && j == b-1 )  a[i][j][k] = 2;
			else a[i][j][k] = a[i][j][k-1];
		}
	turn(c,b);
	findw();//下完黑棋后寻找白棋可下的位置
	system("cls");
	output();
	judge2();
	if(judge2())
	{
		if (selectg == 1)  cout << "等待白方下棋......"<<endl;
		else cout<<"请白方下棋" << endl;
	}
	return 0;
}
//--------------------下白棋------------------------- 
//双人对战
int gow2()
{
	int c,b,i,j;
	cin >> c >> b ;
	if ( c == 9 && b == 9 )  {go = 2;save();gow2();return 0;}
	if (a[c-1][b-1][k] != 3) {cout << "此处不能放棋子!!  请重新输入!!" << endl;gow2();return 0;}
	if (judge1(c,b))  {gow2();return 0;}//如果此处不能放棋子，直接结束本步,重新下白棋//
	k ++;
	for ( i = 0; i < 8 ; i ++ )
		for ( j = 0; j < 8 ; j ++ )
		{
			if ( i == c-1 && j == b-1 )  a[i][j][k] = 1;
			else a[i][j][k] = a[i][j][k-1];
		}
		turn(c,b);
		findb();//下完白棋之后寻找黑棋可下的位置
		system("cls");
		output();
	
			judge2();
		if (judge2())  cout<<"请黑方下棋" << endl;
		return 0;
}
//人机对战
int gow1()
{
	int c,b,i,j,rec[64][2],recb[64][2],ki = 0,kj=0,m=0,mm=0,best = 0,bestm = 0;//rec用来记录每一个白棋可下的位置，recb用来记录下完白棋后每一个黑棋可下的位置
	for ( i = 0; i < 8; i ++ )//找可下棋的位置
		for ( j = 0; j < 8; j ++)
			if (a[i][j][k] == 3)
			{
				rec[ki][0] = i;
				rec[ki][1] = j;
				ki ++;
			}
	cout <<"ki = " << ki << endl;
	int esww[64] = {0};//用来记录每一个可下位置下过白棋后的估值
	for ( m = 0; m < ki; m ++)//估出每一个可下棋位置的值
	{
		int es[64]={0};//记录每一个黑棋棋下完后局势的估值
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
		findb();//下完白棋之后寻找黑棋可下的位置	
		system("cls");
		output();
		cout << "提示：上一步白棋下在（"<<c<<','<<b<<'）'<<endl;
		judge2();
		if (judge2())  cout<<"请黑方下棋" << endl;
		return 0;
}
//--------------------找黑棋可下棋的位置-----------------
int findb()
{
	int c,b,i,j;
	for (i = 0; i < 8; i ++)//清除上一次可下棋的位置 
		for ( j = 0; j < 8; j ++)  if (a[i][j][k] == 3)  a[i][j][k] = 0;		
	for ( c = 1; c <= 8; c ++)//c表示第几行，b表示第几列
		for ( b = 1; b <= 8; b ++)
			if ( a[c-1][b-1][k] == 2)
			{
				if ( a[c-1][b][k] != 0 && a[c-1][b][k] != a[c-1][b-1][k] && a[c-1][b][k] != 3 )//往右找,旁边不是空的，也不和自己相同(即是不同颜色的棋)
					for( j = b+1; j < 8 ; j++)
					{
						if ( a[c-1][j][k] == 0)  //这个地方可以下棋
						{
							a[c-1][j][k] = 3;
							break;
						}
						if ( a[c-1][j][k] == a[c-1][b-1][k] || a[c-1][j][k] == 3)  break;	//如果隔一个或以上还有这个颜色的就无效
					}
				if ( a[c-1][b-2][k] != 0 && a[c-1][b-2][k] != a[c-1][b-1][k] && a[c-1][b-2][k] != 3)//往左找
					for( j = b - 3; j >= 0 ; j --)
					{
						if ( a[c-1][j][k] == 0)   
						{
							a[c-1][j][k] = 3;
							break;
						}
						if ( a[c-1][j][k] == a[c-1][b-1][k] || a[c-1][j][k] == 3)  break;   //如果隔一个或以上还有这个颜色的就无效
					}
				if ( a[c][b-1][k] != 0 && a[c][b-1][k] != a[c-1][b-1][k] && a[c][b-1][k] != 3)//find downwards
					for ( i = c + 1; i < 8; i ++) 
					{
						if ( a[i][b-1][k] == 0) 
						{
							a[i][b-1][k] = 3;
							break;
						}
						if ( a[i][b-1][k] == a[c-1][b-1][k]  ||a[i][b-1][k] == 3)  break;//如果已经标记过则跳出循环
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
				if ( a[c][b][k] != 0 && a[c][b][k] != a[c-1][b-1][k] && a[c][b][k] != 3)//向右下方向找
					for ( i = c + 1, j = b + 1; i < 8 ,j < 8; i ++, j ++) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3 )  break;
					}
				if ( a[c-2][b-2][k] != 0 && a[c-2][b-2][k] != a[c-1][b-1][k] && a[c-2][b-2][k] != 3) //向左上方向找
					for ( i = c - 3, j = b - 3; i >= 0,j >= 0; i --, j --)
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3 )  break;
					}
				if ( a[c][b-2][k] != 0 && a[c][b-2][k] != a[c-1][b-1][k] && a[c][b-2][k] != 3)//向左下方向找
					for ( i = c + 1, j = b - 3; i < 8 ,j >= 0; i ++, j --) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3)  break;
					}
				if ( a[c-2][b][k] != 0 && a[c-2][b][k] != a[c-1][b-1][k] && a[c-2][b][k] != 3)//向右上方向找
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
//-------------------------找白棋可下的位置------------------------------
int findw()
{
	int c,b,i,j;
	for (i = 0; i < 8; i ++)//清除上一次可下棋的位置 
		for ( j = 0; j < 8; j ++)  if (a[i][j][k] == 3)  a[i][j][k] = 0;
	for ( c = 1; c <= 8; c ++)
		for ( b = 1; b <= 8; b ++)
			if ( a[c-1][b-1][k] == 1)
			{
				if ( a[c-1][b][k] != 0 && a[c-1][b][k] != a[c-1][b-1][k] && a[c-1][b][k] != 3 )//往右找,旁边不是空的，也不和自己相同(即是不同颜色的棋)
					for( j = b+1; j < 8 ; j++)
					{
						if ( a[c-1][j][k] == 0)  //这个地方可以下棋
						{
							a[c-1][j][k] = 3;
							break;
						}
						if ( a[c-1][j][k] == a[c-1][b-1][k] || a[c-1][j][k] == 3)  break;	//如果隔一个或以上还有这个颜色的就无效
					}
				if ( a[c-1][b-2][k] != 0 && a[c-1][b-2][k] != a[c-1][b-1][k] && a[c-1][b-2][k] != 3)//往左找
					for( j = b - 3; j >= 0 ; j --)
					{
						if ( a[c-1][j][k] == 0)   
						{
							a[c-1][j][k] = 3;
							break;
						}
						if ( a[c-1][j][k] == a[c-1][b-1][k] || a[c-1][j][k] == 3)  break;   //如果隔一个或以上还有这个颜色的就无效
					}
				if ( a[c][b-1][k] != 0 && a[c][b-1][k] != a[c-1][b-1][k] && a[c][b-1][k] != 3)//find downwards
					for ( i = c + 1; i < 8; i ++) 
					{
						if ( a[i][b-1][k] == 0) 
						{
							a[i][b-1][k] = 3;
							break;
						}
						if ( a[i][b-1][k] == a[c-1][b-1][k]  ||a[i][b-1][k] == 3)  break;//如果已经标记过则跳出循环
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
				if ( a[c][b][k] != 0 && a[c][b][k] != a[c-1][b-1][k] && a[c][b][k] != 3)//向右下方向找
					for ( i = c + 1, j = b + 1; i < 8 ,j < 8; i ++, j ++) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3 )  break;
					}
				if ( a[c-2][b-2][k] != 0 && a[c-2][b-2][k] != a[c-1][b-1][k] && a[c-2][b-2][k] != 3) //向左上方向找
					for ( i = c - 3, j = b - 3; i >= 0,j >= 0; i --, j --)
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3 )  break;
					}
				if ( a[c][b-2][k] != 0 && a[c][b-2][k] != a[c-1][b-1][k] && a[c][b-2][k] != 3)//向左下方向找
					for ( i = c + 1, j = b - 3; i < 8 ,j >= 0; i ++, j --) 
					{
						if ( a[i][j][k] == 0) 
						{
							a[i][j][k] = 3;
							break;
						}
						if ( a[i][j][k] == a[c-1][b-1][k] || a[i][j][k] == 3)  break;
					}
				if ( a[c-2][b][k] != 0 && a[c-2][b][k] != a[c-1][b-1][k] && a[c-2][b][k] != 3)//向右上方向找
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
//----------------------进行游戏------------------------------
int  play(void)
{
	int i,j;
	while( k < 60)//棋盘里只能再下60个棋子
	{
		findb();
		if (judge2() ) {gob();}
		else 
		{
			system("cls");
			findw();output();
			if (k < 60)
			{
				cout<< "黑方无处下，请白方下棋!" << endl;
				Sleep(2000);
			}
		}//如果不能下棋，让另一方继续下*****此处需要一个延时
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
				cout << "白方无处可下，请黑方下棋!" << endl;
				Sleep(2000);
			}
		}//如果不能下棋，让另一方继续下
		findb();//如果双方都无棋可走，说明游戏结束，判断哪一方赢了
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
							
							white ++;//cout <<"恭喜白方获胜!!!!" << endl; 
							//return 0;
						}
						if (a[i][j][k] == 2)
						{
							black ++;
							//cout <<"恭喜黑方获胜!!!!" << endl;
						}
					}
			if ( black > white && selectg == 2)   cout << "恭喜黑方获胜!!";
			if ( black > white && selectg == 1)   cout << "恭喜您挑战成功!!";
			if ( black == white)   cout << "平局!!";
			if ( black < white && selectg == 2)   cout << "恭喜白方获胜!!";
			if ( black < white && selectg == 1)   cout << "挑战失败!!";
			return 0;
		}
	}
	return 0;
}
//-----------------------------------------------输出棋盘-------------------------------
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
	cout << "欢迎来到黑白棋!!!" << endl;
	cout << "请选择游戏模式!!!" << endl;
	cout << "挑战AI请输入  1  "<< endl;
	cout << "双人游戏请输入 2 "<< endl;
	cin >> selectg;
	while  ( !(selectg == 1 || selectg == 2) ) 
	{
		cout << "没有此选项，请重新选择!!!"<< endl;
		cin >>selectg;
	}
	if (selectg == 1) 
	{
		cout <<"请选择难度" << endl;
		cout << "简单 : 1"<< endl;
		cout << "中等 : 2"<< endl;
		cout << "困难 : 3"<< endl;
		cin >> ha;
	}
	system("cls");
	output();
	cout<<"请黑方下棋" <<"                 如需读盘请输入(10,10)" <<endl;
	play();
	return 0;
}