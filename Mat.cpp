#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <direct.h>  
#include"Mat.h"
#include"svpng.inc"
#define MAXPATH  1024  

void MatInitial(Mat &p,int width,int height)
{
	p.width=width;
	p.height=height;
	p.rgb = (unsigned char*)malloc(p.width*p.height*3 * sizeof(unsigned char));
	
	int i,j,num = 0;
	for (i = 0; i < p.width; i++)
	{
		for (j = 0; j < p.height; j++)
		{
			p.rgb[num] = 255; 
			num++;
			p.rgb[num] = 255; 
			num++;
			p.rgb[num] = 255;
			num++;
		}
	}
}  

void MatRect(Mat &p,int start_x,int start_y,int end_x,int end_y,int r,int g,int b)
{
	int i,j,num;
	if(start_x>end_x){
		int temp;
		temp=start_x;
		start_x=start_y;
		start_y=temp;
	}
	if(start_y>end_y){
		int temp;
		temp=start_y;
		start_y=end_y;
		end_y=temp;
	}
	if(start_x<0||start_y<0||end_x>=p.width||end_y>=p.height) 
	{
		printf("绘制存在越界\n"); 
		exit(1);
	}
	for (i = start_x; i < end_x; i++)
	{
		for (j = start_y; j < end_y; j++)
		{
			num =(j*p.width+i)*3;
			p.rgb[num] = (char)r; 
			num++;
			p.rgb[num] = (char)g; 
			num++;
			p.rgb[num] = (char)b;
		}
	}
}

void MatDraw(Mat p)
{
	MatOutput(p,"temp");
	MatShow("temp.png");
} 

void MatOutput(Mat p,char* filename)
{
	char buffer[MAXPATH]="";
	strcat(buffer,filename);
	strcat(buffer,".png");
	FILE *fp = fopen(buffer, "wb");
	svpng(fp, p.width, p.height, p.rgb, 0);
 	fclose(fp);
}



void MatShow(char* filename)
{
	char buffer[MAXPATH];  
    _getcwd(buffer,MAXPATH); 
    char cmd[300]="%SystemRoot%\\system32\\rundll32.exe \"%programfiles%\\Windows photo viewer\\photoviewer.dll\",ImageView_Fullscreen ";
    strcat(buffer,"\\");
	strcat(buffer,filename);
	strcat(cmd,buffer);
	system(cmd); 
}
