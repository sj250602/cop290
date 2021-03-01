#include "opencv2/opencv.hpp"
#include<bits/stdc++.h>
using namespace cv;
using namespace std;

vector<Point2f> pts_src;
vector<Point2f> pts_dst;
Point p1,p2,p3,p4;
bool b1=true,b2=true,b3=true,b4=true;
Rect box;
int count1  = 1,count2 = 1;
void mouse_call(int event,int x,int y,int flags,void* userdata){
	if(event==1 && count1<=4){
		pts_src.push_back(Point2f(x,y));
		count1++;
	}else{
		return;
	}
}
void mouse_call_crop(int event,int x,int y,int flags,void* userdata){
	if(event==1 && b1){
		p1.x = x;
		p1.y = y;
		b1 = false;
	}else if(event==1 && b2){
		p2.x = x;
		p2.y = y;
		b2 = false;
	}else if(!b1 && !b2){
		//cout<<p1.x<<" "<<p2.x<<p1.y<<p2.y;
		box.width=abs(p1.x-p2.x);
        	box.height=abs(p1.y-p2.y);
        	box.x=min(p1.x,p2.x);
        	box.y=min(p1.y,p2.y);
        	//cout<<box.width<<box.height<<box.x<<box.y<<endl;
        }
}
	
int main( int argc, char** argv)
{
// Read source image.
	String str;
	cin>>str;
	//Mat im_src = imread(argv[1]);
	Mat im_src = imread(str);
	if(im_src.empty()){
		cout<<"empty";
		return -1;
	}
	namedWindow("Original Frame",0);
	resizeWindow("Original Frame",1366,768);
	imshow("Original Frame",im_src);
    	setMouseCallback("Original Frame",mouse_call);
	//Mat im_dst = imread("traffic.jpg");
	pts_dst.push_back(Point2f(472, 52));
	pts_dst.push_back(Point2f(472,830));
	pts_dst.push_back(Point2f(800, 830));
	pts_dst.push_back(Point2f(800, 52));
	// Calculate Homography
	Mat im_out; 
	waitKey(0);
	destroyWindow("Original Frame");
	Mat h = findHomography(pts_src, pts_dst);
	// Output image
	// Warp source image to destination based on homography
	warpPerspective(im_src, im_out, h, im_src.size());
	// Display images
	//imshow("Original Frame", im_src);
	//imshow("Destination Image", im_dst);
	//imshow("Projected Frame", im_out);
	//waitKey(0);
	String str_out_save = "Projected Frame.jpg";
	bool check = imwrite(str_out_save,im_out);
	if(check==false){
		cout<<"sorry unable to save image\n";
		return -1;
	}
	Mat read_proj = imread(str_out_save);
	if(read_proj.empty()){
		cout<<"empty";
		return -1;
	}
	namedWindow("Projected Frame",0);
	resizeWindow("Projected Frame",1366,768);
	imshow("Projected Frame",read_proj);
    	setMouseCallback("Projected Frame",mouse_call_crop);
    	waitKey(0);
    	destroyWindow("Projected Frame");
    	Mat crop(read_proj,box);//Selecting a ROI(region of interest) from the original pic
    	imshow("Cropped Frame",crop);
    	String str_out = "Cropped Frame.jpg";
	bool chec = imwrite(str_out,crop);
	if(chec==false){
		cout<<"sorry unable to save image\n";
		return -1;
	}
	waitKey(0);
}
