#include "reg51.h" 
#include "stdio.h"
#define uint unsigned int
#define uchar unsigned char
#define KEY P1
sbit RS=P2^6;
sbit RW=P2^5;
sbit E=P2^7;
void delay(uint n)
{
  uint x,y;
	for(x=n;x>0;x--)
	   for(y=110;y>0;y--);
}
void wcomlcd(uchar com)
{
  RS=0;
	RW=0;
	P0=com;
	delay(5);
	E=1;
	E=0;
}
void wdatlcd(uchar dat)
{
  RS=1;
	RW=0;
	P0=dat;
	delay(5);
	E=1;
	E=0;
}
void wdatlcd_disp(uchar x,uchar y,uchar dat)
{
  uchar address;
  if(y==1) address=0x80+x;
  else address=0xc0+x;
  wcomlcd(address);
  wdatlcd(dat);
}
void initlcd()
{
  wcomlcd(0x38);
	wcomlcd(0x0c);
	wcomlcd(0x06);
	wcomlcd(0x01);
}
uint keyscan()
{
  uchar i=0;
	uint keyvalue;
	KEY=0x0f;
	if(KEY!=0x0f)
	{
	  delay(100);
		if(KEY!=0x0f)
		{
		  KEY=0x0f;
			switch(KEY)
			{
			  case(0x07):keyvalue=1;break;
				case(0x0b):keyvalue=2;break;
				case(0x0d):keyvalue=3;break;
				case(0x0e):keyvalue=4;break;
			}
			KEY=0xf0;
			switch(KEY)
			{
			  case(0x70):keyvalue=keyvalue;break;
				case(0xb0):keyvalue=keyvalue+4;break;
				case(0xd0):keyvalue=keyvalue+8;break;
				case(0xe0):keyvalue=keyvalue+12;break;
			}
		}
	}
	while((i<50)&&(KEY!=0xf0))
	{
	  delay(5);
		i++;
	}
	return keyvalue;
}
void main()
{
  uint k,ii,f,y1,y2,y3;
	uint d=0,g=0,i=1,z=0,x2=0,r[4]={0},w[4]={0},ad[6]={0},jud=0,add=0,zz=0;
	uchar x1,adc[8];
	initlcd();
	wcomlcd(0x80);
	delay(5);
	start:
	while(1)
	{
		KEY=0x0f;
		if(KEY!=0x0f)
	  {
	    k=keyscan();
		  switch(k)
		  {
		  	case 1:x1='1';x2=1;break;
		  	case 2:x1='2';x2=2;break;
		  	case 3:x1='3';x2=3;break;
		  	case 4:x1='+';d=1;break;
		  	case 5:x1='4';x2=4;break;
		  	case 6:x1='5';x2=5;break;
		  	case 7:x1='6';x2=6;break;
		  	case 8:x1='-';d=2;break;
		  	case 9:x1='7';x2=7;break;
		  	case 10:x1='8';x2=8;break;
		  	case 11:x1='9';x2=9;break;
		  	case 12:x1='*';d=3;break;
		  	case 13:jud=2;zz=1;break;
	  		case 14:x1='0';x2=0;break;
	  		case 15:x1='=';z=2;break;
	  		case 16:x1='/';d=4;break;
	  	}
			if(k!=13)
			{
				wdatlcd_disp(add,1,x1);
			  add++;
			}
			if(z==2)
			{
				if(i==2) y2=w[3];
				if(i==3) y2=w[3]*10+w[2];
				if(i==4) y2=w[3]*100+w[2]*10+w[1];
				if(i==5) y2=w[3]*1000+w[2]*100+w[1]*10+w[0];
			   switch(g)
				 {
				   case 1:y3=y1+y2;break;
					 case 2:y3=y1-y2;break;
					 case 3:y3=y1*y2;break;
					 case 4:y3=y1/y2;break;
				 }
				 ad[0]=y3/100000%10;
				 ad[1]=y3/10000%10;
				 ad[2]=y3/1000%10;
				 ad[3]=y3/100%10;
				 ad[4]=y3/10%10;
				 ad[5]=y3%10;
				 for(f=0;f<8;f++)
				 {
				    switch(ad[f])
						{
						  case 1:adc[f]='1';break;
							case 2:adc[f]='2';break;
							case 3:adc[f]='3';break;
							case 4:adc[f]='4';break;
							case 5:adc[f]='5';break;
							case 6:adc[f]='6';break;
							case 7:adc[f]='7';break;
							case 8:adc[f]='8';break;
							case 9:adc[f]='9';break;
							case 0:adc[f]='0';break;
							default:adc[f]='0';break;
						}
				 }
				wcomlcd(0x80+0x40);
				for(ii=0;ii<6;ii++)
				  wdatlcd(adc[ii]);		 
		  		 if(jud==2)
        {
          initlcd();wcomlcd(0x80);z=0;
		  		for(ii=0;ii<8;ii++)
	  			  adc[ii]='0';
	  			for(ii=0;ii<7;ii++)
	  			  {r[ii]=0;w[ii]=0;}
	  				d=0,g=0,i=1,z=0,x2=0,add=0;jud=0;
						goto start;
		  	}
			}
			if(k==13)
			{			
			  i--;
			}
			if(k!=13)
			{
			  if(d==0)
			  {
			    r[4-i]=x2;
			  	i++;
		  	}
		  	if(d==5)
		  	{
		  	  w[4-i]=x2;
		    	i++;
		    }	
		  	if(d==1||d==2||d==3||d==4) 
		  	{ 
					if(i==2) y1=r[3];
					if(i==3) y1=r[3]*10+r[2];
					if(i==4) y1=r[3]*100+r[2]*10+r[1];
					if(i==5) y1=r[3]*1000+r[2]*100+r[1]*10+r[0];
		  		g=d,d=5,i=1;
			  }
			}
			if(k==13&&z==0)
			{
				add--;
			  wdatlcd_disp(add,1,' ');
				z=0;jud=0;
			}
	  }
	}
}