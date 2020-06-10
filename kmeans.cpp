#include <ctime> // for a random seed
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <float.h>

using namespace std;

struct Point {
  double x,y;
  int clusterID;
  double minDist;

  Point(): x(0.0), y(0.0), clusterID(-1), minDist(DBL_MAX){}
  Point(double x, double y): x(x), y(y), clusterID(-1), minDist(DBL_MAX){}

  double distance(Point p){
    return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
  }
};


vector<Point> readcsv(){
  vector<Point> points;
  string line;
  ifstream file("mall_data.csv");
  while(getline(file, line)){
    stringstream lineStream(line); // create stream from file
    string s;
    vector<string> splittedStrings;
    while(getline(lineStream, s, ',')){
      splittedStrings.push_back(s);
    }
    double x, y;
    x = stof(splittedStrings[0]); // read from lineStream, and convert to float.
    y = stof(splittedStrings[1]); // the first one is x coordinates, the second one is y coordinates.
    points.push_back(Point(x,y));
  }
  return points;
}

/* The k-Means clustering algorithm runs like this:
    1. We initialise the clusters by selecting k points (we call them the generating points).
        They represent the k clusters.
    2. We then assign each point to the nearest cluster.
    3. We recalculate the center of each cluster and set those to be the new generating points.
    4. Repeat steps 2-3.
*/

void kMeansClustering(vector<Point> &points, int epochs, int k){
  // 1. Initialising the clusters.
  vector<Point> generatingpoints;
  srand(time(0));
  for(int i = 0;i < k; i++){
    generatingpoints.push_back(points[rand()%points.size()]);
  }

  for(int j = 0; j < epochs; j++){
  // 2. Assigning points to clusters.
    int start = 0;
    for(Point &p : generatingpoints){
      for(Point &q : points){
        double dist = p.distance(q);
        if(dist < q.minDist){
          q.minDist = dist;
          q.clusterID = start;
        }
      }
      start += 1;
    }

  // 3. Recalculate the center of each cluster. We do this by computing the mean coordinates of all the points in a cluster.
    vector<int> nPoints;
    vector<double> sumX, sumY;
    for(int i = 0; i<k;i++){
      nPoints.push_back(0);
      sumX.push_back(0.0);
      sumY.push_back(0.0);
    }
    for(Point &p : points){
      int clusterId = p.clusterID;
      nPoints[clusterId] += 1;
      sumX[clusterId] += p.x;
      sumY[clusterId] += p.y;
      p.minDist = DBL_MAX;
    }
    start = 0;
    for(Point &p : generatingpoints){
      p.x = sumX[start] / nPoints[start];
      p.y = sumY[start] / nPoints[start];
      start += 1;
    }
  }
  ofstream myfile;
  myfile.open("output.csv");
  myfile<< "x,y,c"<<endl;
  for(Point p : points){
    myfile << p.x << "," << p.y << "," << p.clusterID << endl;
  }
  myfile.close();
}


// example
int main(){
  Point p1 = Point(0.0,0.0);
  cout << p1.x << endl;

  Point p2 = Point(3.0, 4.0);
  cout << p1.distance(p2) << endl;

  vector<Point> points = readcsv();
  cout << points.size() << endl;
  kMeansClustering(points,5,5);
}

