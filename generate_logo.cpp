#include<iostream>
#include<stdlib.h>
#include<string>
#include <vector> 
#include<fstream>
#include<sstream>
#include<windows.h>
#include<opencv2\opencv.hpp>
#define LOGO_NUM	108;

const int threadnum = 4;
using namespace cv;
using namespace std;

int cvAdd4cMat_q(cv::Mat &dst, cv::Mat &scr, double scale);
void	num2str(string &s,int a);
DWORD WINAPI  image_generate(LPVOID pArg)
{
	int pid = *(int*)pArg;
	srand(pid);
	int ceil = (pid+1)*1000;
	int	i,j,x,y,logo_width,logo_length,new_width,new_length;
	int	back_width, back_length;
	int	divxarea, divyarea;
	ofstream	table;
	ofstream	xml;
	string	xmax, xmin, ymax, ymin;
	string	backnum = "0000";
	string	logonum[] = {   "0001_0","0001_1","0002_0",    "0002_1","0002_2","0002_3",  "0003_0","0003_1", "0003_2", 
							"0003_3", "0003_4", "0003_5", "0004_0", "0004_1", "0004_2", "0005_0", "0005_1", "0005_2",
							 "0006_0", "0006_1", "0006_2", "0007_0", "0007_1", "0007_2", "0007_3", "0007_4", "0008_0",
							"0008_1", "0008_2", "0008_3", "0008_4", "0009_0", "0009_1", "0009_2", "0009_3", "0010_0",
							"0010_1", "0010_2", "0010_3", "0010_4",	"0010_5", "0010_6", "0011_0", "0011_1", "0011_2", 
							 "0012_0", "0012_1", "0012_2", "0013_0","0013_1", "0013_2", "0013_3", "0013_4", 
							"0014_0", "0014_1", "0014_2", "0015_0", "0015_1", "0016_0", "0016_1", "0016_2", "0016_3",
							"0016_4", "0016_5", "0017_0", "0017_1", "0018_0", "0018_1","0018_2", "0018_3",  "0019_0",
							"0019_1","0019_2",  "0020_0", "0020_1","0020_2", "0021_0", "0021_1", "0021_2",   "0021_3", 
							"0021_4", "0022_0", "0022_1", "0022_2",	"0022_3", "0022_4","0023_0", "0023_1",   "0023_2", 
							"0024_0","0024_1", "0024_2", "0025_0", "0025_1",  "0026_0","0026_1", "0027_0",    "0027_1",
							"0027_2", "0028_0", "0028_1", "0028_2", "0029_0","0029_1","0029_2",   "0030_0",   "0030_1",
							"0030_2"
							};
	string		logoid[] = { "0001_0","0001_1","0002_0",    "0002_1","0002_2","0002_3",  "0003_0","0003_1", "0003_2",
		"0003_3", "0003_4", "0003_5", "0004_0", "0004_1", "0004_2", "0005_0", "0005_1", "0005_2",
		"0006_0", "0006_1", "0006_2", "0007_0", "0007_1", "0007_2", "0007_3", "0007_4", "0008_0",
		"0008_1", "0008_2", "0008_3", "0008_4", "0009_0", "0009_1", "0009_2", "0009_3", "0010_0",
		"0010_1", "0010_2", "0010_3", "0010_4",	"0010_5", "0010_6", "0011_0", "0011_1", "0011_2",
		"0012_0", "0012_1", "0012_2", "0013_0","0013_1", "0013_2", "0013_3", "0013_4",
		"0014_0", "0014_1", "0014_2", "0015_0", "0015_1", "0016_0", "0016_1", "0016_2", "0016_3",
		"0016_4", "0016_5", "0017_0", "0017_1", "0018_0", "0018_1","0018_2", "0018_3",  "0019_0",
		"0019_1","0019_2",  "0020_0", "0020_1","0020_2", "0021_0", "0021_1", "0021_2",   "0021_3",
		"0021_4", "0022_0", "0022_1", "0022_2",	"0022_3", "0022_4","0023_0", "0023_1",   "0023_2",
		"0024_0","0024_1", "0024_2", "0025_0", "0025_1",  "0026_0","0026_1", "0027_0",    "0027_1",
		"0027_2", "0028_0", "0028_1", "0028_2", "0029_0","0029_1","0029_2",   "0030_0",   "0030_1",
		"0030_2"
							};
	int		logoindex;
	string	table_id;
	string	table_name;
	string	backdir = "C:/Users/张旭/source/repos/Project1/Project1/car_images_/";
	string	backname;
	string	logodir = "C:/Users/张旭/source/repos/Project1/Project1/logo/";
	string	logoname; 
	string	savedir = "D:/BigData/train_3/";
	string	savepath_xml;
	string	savepath_jpg;
	string	index;
	stringstream	pos;
	char str[16];
	Mat backgroud,logo;
	Mat	newlogo;
	Mat imageROI;
	pos << pid;
	table_id = pos.str();
	pos.str("");
	table_name = savedir + "ImageList_" + table_id + ".txt";
	table.open(table_name.c_str());
	for (j = pid * 1000+1; j <= ceil && j<=4386; j++) {		//4386
		num2str(backnum, j);
		backname = backdir + backnum + ".jpg";
		cout << backname << endl;
		cout << flush;
		for (i = 1; i <= 20; i++) {
			backgroud = imread(backname.c_str());
			back_width = backgroud.size().width;
			back_length = backgroud.size().height;
			divxarea = back_width / 10;
			divyarea = back_length / 10;
			logoindex = rand() % LOGO_NUM;
			//logoindex = i-1;
			logoname = logodir + logonum[logoindex] + ".png";
			//cout << logoname <<" thread: "<<pid<<endl<<flush;
			logo = imread(logoname.c_str(), -1);
			logo_width = logo.size().width;
			logo_length = logo.size().height;
			do {
				new_width = rand() % back_width;
			} while (new_width<divxarea);
			do {
				new_length = rand() % back_length;
			} while (new_length < divyarea);
			resize(logo, newlogo, Size(new_width, new_length));
			x = rand() % (backgroud.size().width - new_width);
			pos << x;
			xmin = pos.str();
			pos.str("");
			pos << (x + new_width);
			xmax = pos.str();
			pos.str("");
			y = rand() % (backgroud.size().height - new_length);
			pos << y;
			ymin = pos.str();
			pos.str("");
			pos << (y + new_length);
			ymax = pos.str();
			pos.str("");
			pos << i;
			index = pos.str();
			pos.str("");
			imageROI = backgroud(Rect(x, y, newlogo.cols, newlogo.rows));
			cvAdd4cMat_q(imageROI, newlogo, 1.0);
			savepath_jpg = savedir + backnum + "_" + logonum[logoindex] + "_" + index + ".jpg";
			savepath_xml = savedir + backnum + "_" + logonum[logoindex] + "_" + index + ".xml";
			xml.open(savepath_xml.c_str());
			xml << "<annotation>" << endl << "\t";
					xml << "<folder>WinnieEatBun</folder>" << endl << "\t";
					xml << "<filename>" << backnum + "_" + logonum[logoindex] + "_" + index << ".jpg" << "</filename>" << endl << "\t";
					xml << "<object>" << endl << "\t\t";
							xml << "<name>" << logoid[logoindex][0] << logoid[logoindex][1]<< logoid[logoindex][2] << logoid[logoindex][3]<<"</name>" << endl << "\t\t";
							xml << "<bndbox>" << endl << "\t\t\t";
									xml << "<xmin>" << xmin << "</xmin>" << endl << "\t\t\t";
									xml << "<ymin>" << ymin << "</ymin>" << endl << "\t\t\t";
									xml << "<xmax>" << xmax << "</xmax>" << endl << "\t\t\t";
									xml << "<ymax>" << ymax << "</ymax>" << endl << "\t\t";
							xml << "</bndbox>" << endl << "\t";
					xml << "</object>" << endl << "\t";
			xml << "</annotation>" << endl << "\t";
			xml.close();
			imwrite(savepath_jpg.c_str(), backgroud);			
			table << backnum + "_" + logonum[logoindex] + "_" + index << endl;
		}
		//cout << "1111" << endl;
		backnum = "0000";
	}
	waitKey(0);
	table.close();
	return 0;
}

void num2str(string &s, int a) {
	int i;
	for (i = 3; i >=0; i--) {
		s[i] += a % 10;
		a /= 10;
	}
}

int cvAdd4cMat_q(cv::Mat &dst, cv::Mat &scr, double scale)
{
	if (dst.channels() != 3 || scr.channels() != 4)
	{
		return true;
	}
	if (scale < 0.01)
		return false;
	std::vector<cv::Mat>scr_channels;
	std::vector<cv::Mat>dstt_channels;
	split(scr, scr_channels);
	split(dst, dstt_channels);
	CV_Assert(scr_channels.size() == 4 && dstt_channels.size() == 3);

	if (scale < 1)
	{
		scr_channels[3] *= scale;
		scale = 1;
	}
	for (int i = 0; i < 3; i++)
	{
		dstt_channels[i] = dstt_channels[i].mul(255.0 / scale - scr_channels[3], scale / 255.0);
		dstt_channels[i] += scr_channels[i].mul(scr_channels[3], scale / 255.0);
	}
	merge(dstt_channels, dst);
	return true;
}

void test_logo() {
	Mat logo, backgroud;
	int i;
	logo = imread("C:/Users/张旭/source/repos/Project1/Project1/logo/0011_2.png", -1);
	backgroud = imread("C:/Users/张旭/source/repos/Project1/Project1/car_images_/0018.jpg");
	//Mat img1_t1(backgroud, cvRect(0, 0, logo.cols, logo.rows));
	Mat img1_t1(backgroud, cvRect(0, 0, 10, 10));
	cvAdd4cMat_q(img1_t1, logo, 1.0);
	imshow("final", backgroud);
	//namedWindow("MyWindow", CV_WINDOW_AUTOSIZE);
	//imshow("MyWindow", logo);
	waitKey(0);
	cin >> i;
}

int main()
{
	HANDLE hThread[threadnum];
	int tNum[4];
	for (int i = 0; i < threadnum; i++)
	{
		tNum[i] = i;
		hThread[i] = CreateThread(NULL, 0, image_generate, &tNum[i], 0, NULL);
	}
	WaitForMultipleObjects(threadnum, hThread, TRUE, INFINITE);
	//test_logo();
	system("pause");
	return 0;
}
