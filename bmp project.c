#include<stdio.h>
//#include<bmpio.h>
#include "bmpio/include/bmpio.h"
#include<math.h>
#include "bmpio/include/bmpio.h"
unsigned char pic[2000][2000][3]={0};
unsigned char pic3[2000][2000][3]={0};
unsigned char pic2[2000][2000][3]={0};
unsigned char pic4[2000][2000][3]={0};
unsigned char pic_w[2000][2000][3]={0};
unsigned char pic_h[2000][2000][3]={0};

int pic_f[10][2000][2000][3];
int WIDTH=0,HEIGHT=0,q,w,xxx=0,aa=0;

int satryab(int width,int height,int a);//top cordinate of pic
int sheklyab_satri(int width,int height,int b);//bottom cordinate
int sotoonyab(int width,int height,int a);//left cordinate of pic
int sheklyab_sotooni(int width,int height,int b);//right cordinate of pic
int sheklyab_sotoonii(int width,int height,int b);//right cordinate of pic

void save(int up,int down,int left,int right);//croping pics with defined cordinates
void crop(int width,int height);//croper
void sum_avg();//avrage's sum
void avg();//avraging
void resize();//resizer
void camparison();
void save_clock();//clock

int main()
{	
	printf("pls wait...\n");

	for(q=0;q<=9;q++)
	{
		for(w=1;w<=15;w++)
		{
			char p[100];//storing the address of datasets in 'p'
						
			int width,height;
	
			sprintf(p,"DataSet\\%d\\%d.bmp",q,w);

			readBMP(p,&width,&height,pic);//reciving dataset
				
			crop(width,height);//croping the recived dataset
	
			resize();//resizing the dataset
			
			sum_avg();//adding the pixels number for avrage
		}
		avg();//avrage
	}

	save_clock();
	
	return 0;
}


void crop(int width,int height)
{
	int up,right,left,down;
	
	up=satryab(width,height,0);//top cordinate
	
	down=sheklyab_satri(width,height,up);//bottom cordinate
	
	left=sotoonyab(width,height,0);//left cordinate
	
	right=sheklyab_sotooni(width,height,left);//right cordinate	
		
	save(up,down,left,right);//saving pic based on gatherd cordinates
}


void save_clock()
{
	int width=0,height=0,i,j,s,ii=0,m,x,up,down;
	int arg[40]={0};//gathering the horizontal cordinates of clock in 'arg'
	char c[100],p[100];
	printf("enter the clock's name or path:\n");
	gets(c);//address of clock
	readBMP(c,&width,&height,pic);//recived clock
	
	for(i=1;i<=40;i++)//definig the horizontal cordinates
	{
		arg[i]=sotoonyab(width,height,arg[i-1]);
		i++;
		arg[i]=sheklyab_sotoonii(width,height,arg[i-1]);
	}
		
	for(i=0;i<height;i++)//we store the clock in 'pic3' because we need 'pic' for single pics
	{
		for(j=0;j<width;j++)
		{
			for(s=0;s<3;s++)pic3[i][j][s]=pic[i][j][s];
		}
	}
	
	for(i=1;i<=40;i+=2)
	{
		for(m=0;m<height;m++)//separating a single pic from the main clock
		{
			for(x=0,j=arg[i];x<width,j<arg[i+1];j++,x++)
			{
				for(s=0;s<3;s++)pic[m][x][s]=pic3[m][j][s];
			}
		}
		
		width=arg[i+1]-arg[i];//updating 'width' because we separeted a single number with diffrent width & height is constant until we crop the number
		up=satryab(width,height,0);//top cordinate of a single number of main clock
		down=sheklyab_satri(width,height,up);//bottom cordinate of a single number of main clock
		/*		we already have the vertical cordinates in 'arg'		*/
		save(up,down,arg[i],arg[i+1]);//croping the single number ith gathered corsinates		
	
		if(WIDTH<=10||HEIGHT<=10) continue;//we consider if the croped pic is not just a few random pixels :)
	
		if(xxx==2||xxx==5)//delating the ':' pics
		{
			xxx++;
			continue;
		}
		
		else
		{
			resize();//resizing the numbers

			camparison();//defining the number we have
		}
		
		xxx++;//counting pics that we get	
		
		if(xxx==8)return 0;//finishing the program after considering the numbers we need
	}
}


int satryab(int width,int height,int a)//top cordinate
{
	int m,j,x,arg1;
	
	for(m=a;m<height;m++)
	{
		x=0;
		for(j=0;j<width;j++)
		{
			if(pic[m][j][0]==255&&pic[m][j][1]==255&&pic[m][j][2]==255)x++;
		}
		if(x!=width)
		{
			arg1=m;
			break;
		}
	}
	return arg1;
}


int sheklyab_satri(int width,int height,int b)//bottom cordinate
{
	int j,x,arg1,m;
	
	for(m=height-1;m>=b;m--)
	{
		x=0;
		for(j=0;j<width;j++)
		{
			if(pic[m][j][0]==255&&pic[m][j][1]==255&&pic[m][j][2]==255)x++;
		}
		if(x!=width)
		{
			arg1=m;
			break;
		}
	}
	return arg1;
}


int sotoonyab(int width,int height,int a)//left cordinate
{
	int m,j,x,arg1;
	
	for(m=a;m<width;m++)
	{
		x=0;
		for(j=0;j<height;j++)
		{
			if(pic[j][m][0]==255&&pic[j][m][1]==255&&pic[j][m][2]==255)x++;
		}
		if(x!=height)
		{
			arg1=m;
			break;
		}
	}
	return arg1;
}


int sheklyab_sotooni(int width,int height,int b)//right cordinate
{
	int j,x,arg1,m;
	
	for(m=width-1;m>=b;m--)
	{
		x=0;
		for(j=0;j<height;j++)
		{
			if(pic[j][m][0]==255&&pic[j][m][1]==255&&pic[j][m][2]==255)x++;
		}
		
		if(x!=height)
		{
			arg1=m;
			break;
		}
	}
	return arg1;
}


int sheklyab_sotoonii(int width,int height,int b)//right cordinate
{
	int j,x,arg1,m;
	
	for(m=width-1;m>=b;m--)
	{
		x=0;
		for(j=0;j<height;j++)
		{
			if(pic[j][m][0]==255&&pic[j][m][1]==255&&pic[j][m][2]==255)x++;
		}
		
		if(x==height)
		{
			arg1=m;
		}
	}
	return arg1;
}


void sum_avg()//adding the pixels number for avrage
{
	int i,j,s;
	for(i=0;i<HEIGHT;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			for(s=0;s<3;s++)pic_f[q][i][j][s]+=pic_w[i][j][s];
		}
	}
}


void avg()//avrage
{
	int i,j,s;
	char c[50];
	for(i=0;i<HEIGHT;i++)
	{
		for(j=0;j<WIDTH;j++)
		{
			for(s=0;s<3;s++)
			{
				pic_f[q][i][j][s]=pic_f[q][i][j][s]/15;
				if(pic_f[q][i][j][s]>=200)pic_f[q][i][j][s]=255;
				if(pic_f[q][i][j][s]<=100)pic_f[q][i][j][s]=0;
				pic4[i][j][s]=pic_f[q][i][j][s];
			}
			
		}
	}
//	sprintf(c,"%d.bmp",q);
//���	saveBMP(pic4,500,500,c);
}


void save(int up,int down,int left,int right)//croping the pic with defined cordinates
{
	int i,j,m,n;
	
	WIDTH=right-left,HEIGHT=down-up;
		
	for(i=0,m=up;i<HEIGHT,m<down;i++,m++)
	{
		for(j=0,n=left;j<WIDTH,n<right;j++,n++)
		{
			pic2[i][j][0]=pic[m][n][0],pic2[i][j][1]=pic[m][n][1],pic2[i][j][2]=pic[m][n][2];
		}
	}
		
}


void resize()//resizing
{
	double height1=1000,width1=1000;//we can define the the final width & height for pics
	double y=height1/HEIGHT,x=width1/WIDTH,t;
	int i,j,m=0,n=0,s;
	char c[50];
	
	for(j=0;j<WIDTH;j++)//vertical resizing
	{
		t=y;
		m=0;
		for(i=0;i<height1;i++)
		{
			if(t>1)
			{
				t--;
				for(s=0;s<3;s++)pic_h[i][j][s]=pic2[m][j][s];
			}
			else 
			{
				for(s=0;s<3;s++)pic_h[i][j][s]=t*pic2[m][j][s]+(1-t)*pic2[m+1][j][s];
				t=y-(1-t);
				m++;
			}
		}
	}
	
	
	for(i=0;i<height1;i++)//horizontal resizing
	{
		t=x;
		n=0;
		for(j=0;j<width1;j++)
		{
			if(t>1)
			{
				t--;
				for(s=0;s<3;s++)pic_w[i][j][s]=pic_h[i][n][s];
			}
			else
			{
				for(s=0;s<3;s++)pic_w[i][j][s]=t*pic_h[i][n][s]+(1-t)*pic_h[i][n+1][s];
				t=x-(1-t);
				n++;
			}
		}
	}
	
	HEIGHT=height1,WIDTH=width1;//saving the new dimensions in a GLOBAL int

		for(i=0;i<HEIGHT;i++)
		{
			for(j=0;j<WIDTH;j++)
			{
				for(s=0;s<3;s++)
				{
					if(pic_w[i][j][s]>=200)pic_w[i][j][s]=255;
					if(pic_w[i][j][s]<=100)pic_w[i][j][s]==0;
				}
			}
		}	
	
//	HEIGHT=height1,WIDTH=width1;//saving the new dimensions in a GLOBAL int
//	sprintf(c,"DataSet\\%d\\%d.bmp",q,w);
//	saveBMP(pic_w,1000,1000,c);
}


void camparison()
{
	int i,j,s,max=0,arg,f,xx=0;
	long int x;
	for(q=0;q<10;q++)//camparing the avraged numbers with clock's pic
	{
		x=0;
		for(i=0;i<HEIGHT;i++)
		{
			for(j=0;j<WIDTH;j++)
			{
				for(s=0;s<3;s++)
				{
					f=abs(pic_w[i][j][s]-pic_f[q][i][j][s]);//we consider a kind of deviation in order to find the number  
					/*		this method works almost all the time		*/
					if(f<=130)x++;//counting
				}
			}
		}
		
		if(x>=max)
		{
			max=x;//changing the maximum
			arg=q;//storing the counter in order to print it
		}
		
	}
	printf("%d",arg);//printing the indicated number
	aa++;
	if(aa==2||aa==4)printf(":");//printing the':'

}
