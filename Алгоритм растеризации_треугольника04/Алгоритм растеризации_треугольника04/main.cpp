//
//  main.cpp
//  Алгоритм растеризации_треугольника04
//
//  Created by 宋云辉 on 11/16/22.
//

#include <iostream>
using namespace std;
#include<fstream>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv/cv.h>
#include<vector>
void drawLine(cv::Mat& mat,int x1,int y1,int x2,int y2){
    for(int i=x1;i<=x2;i++){
           mat.at<int>(y1,i)=1;
    }

}
void fillBottomFlatTriangle(cv::Mat& mat,cv::Point& v1,cv::Point& v2,cv::Point& v3){
    float invslope1 = float(v2.x - v1.x) / float(v2.y - v1.y);
    float invslope2 = float(v3.x - v1.x) / float(v3.y - v1.y);

    float curx1 = v1.x;
    float curx2 = v1.x;

    for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++)
    {
    drawLine(mat,(int)curx1, scanlineY, (int)curx2, scanlineY);
      curx1 += invslope1;
      curx2 += invslope2;
    }
}

void fillTopFlatTriangle(cv::Mat& mat,cv::Point& v1,cv::Point& v2,cv::Point& v3){

  float invslope1 = float(v3.x - v1.x) / float(v3.y - v1.y);
  float invslope2 = float(v3.x - v2.x) / float(v3.y - v2.y);

  float curx1 = v3.x;
  float curx2 = v3.x;

  for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
  {
  drawLine(mat,(int)curx1, scanlineY, (int)curx2, scanlineY);
    curx1 -= invslope1;
    curx2 -= invslope2;
  }
}

void drawTriangle( cv::Mat& mat,std::vector<cv::Point>& triPts)
{
   /* сначала отсортируйте три вершины по координате y по возрастанию, чтобы v1 была самой верхней вершиной */
     std::sort(triPts.begin(),triPts.end(),[](cv::Point& p1,cv::Point&p2){return (p1.y==p2.y)?p1.x<p2.x : p1.y<p2.y;});
       cv::Point& v1=triPts[0];
       cv::Point& v2=triPts[1];
       cv::Point& v3=triPts[2];

  /* здесь мы знаем, что v1.y <= v2.y <= v3.y */
  /* проверить тривиальный случай треугольника с плоской нижней частью */
  if (v2.y == v3.y)
  {
    fillBottomFlatTriangle(mat,v1, v2, v3);
  }
  /* проверить тривиальный случай треугольника с плоской вершиной */
  else if (v1.y == v2.y)
  {
    fillTopFlatTriangle(mat, v1, v2, v3);
  }
  else
  {
    /* общий случай - разделить треугольник на верхний и нижний. */
    cv::Point v4(
      (int)(v1.x + ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)), v2.y);
    fillBottomFlatTriangle(mat, v1, v2, v4);
    fillTopFlatTriangle(mat, v2, v4, v3);
  }
}

int main()
{

    cv::Mat mm(30,20,CV_32SC1,cv::Scalar(0));
    cv::Mat mmm(30,20,CV_32SC1,cv::Scalar(0));
    std::vector<cv::Point> triPts2(3);
   triPts2[0]=(cv::Point(12,2));
   triPts2[1]=(cv::Point(2,9));
  triPts2[2]=(cv::Point(17,29));
   drawTriangle(mm,triPts2);
   cv::fillConvexPoly(mmm,triPts2,cv::Scalar(1));   //растеризация opencv
   std::cout<<"\n";   std::cout<<"\n";   std::cout<<"\n";
   for(int i=0;i<mm.rows;i++){
       for(int j=0;j<mm.cols;j++){
            std::cout<<mm.at<int>(i,j)<<" ";
        }
    std::cout<<"\n";
    }
   std::cout<<"\n";   std::cout<<"\n";
   std::cout<<"\n";   std::cout<<"\n";   std::cout<<"\n";
   for(int i=0;i<mmm.rows;i++){
       for(int j=0;j<mmm.cols;j++){
            std::cout<<mmm.at<int>(i,j)<<" ";
        }
    std::cout<<"\n";
    }
   std::cout<<"\n";   std::cout<<"\n";
    return 0;
}
