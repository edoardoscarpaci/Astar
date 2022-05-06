#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include<opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>
#include <iostream>
#include "Map.hpp"


Map::Map(const std::string& path):_MapPath(path){
	cv::Mat temp,ImgGray;
	temp = cv::imread(path);
	cv::cvtColor(temp,ImgGray, cv::COLOR_BGR2GRAY);

	cv::threshold(ImgGray, _Map, 170, 255,cv::THRESH_BINARY);

	if(_Map.empty())
    {
        std::cout << "Could not read the image: " << path << std::endl;
        return;
    }

	_Size = _Map.size();


	if(hasWhiteBorder()){
		removeBorder();
		std::cout <<"Bordi rimossi"<<std::endl;
		cv::imwrite("/home/edo/Downloads/nuovamappa.jpg", _Map) ;

	}

	calculateExits();
	
}

bool Map::isExit(uint32_t x,uint32_t y)const {
	for (auto &exit : _Exits){
		if(x == exit->x && y == exit->y) return 1;
	}
	return 0;
}

void Map::calculateExits(){
	uint32_t width = getWidth();
	uint32_t heigth = getHeight();

	for(uint32_t x=0;x < width;x += width-1){
		for(uint32_t y = 0;y< heigth;y++){			
			if(!isWall(x,y))
				_Exits.emplace_back(new MapCell(x,y));
		}
	}

	for(uint32_t y = 0;y< heigth; y += heigth-1){
		for(uint32_t x=0;x <width;x++){
			if(!isWall(x,y))
				_Exits.emplace_back(new MapCell(x,y));
		}
	}
}

void Map::removeBorder(){

	cv::Rect crop_region(1, 1,getWidth() -1,getHeight() -1 );
	_Map = _Map(crop_region);
	_Size = _Map.size();

}


bool Map::hasWhiteBorder(){
	uint32_t width = getWidth();
	uint32_t heigth = getHeight();

	for(uint32_t x=0;x <= width;x += width){
		for(uint32_t y = 0;y<=heigth;y++){
			if(isWall(x,y)){
				return false;
			}
		}
	}

	for(uint32_t y = 0;y<=heigth;y+=heigth){
		for(uint32_t x=0;x <=width;x++){
			if(isWall(x,y))
				return false;
		}
	}

	return true;
}


void Map::printWholeImage(){
	cv::namedWindow("Map");
	cv::imshow("Map",_Map);
	cv::waitKey(0);
	std::cout <<"Depth: " << _Map.depth() << std::endl;

	for(int x=0;x < getWidth();x ++){
		for(int y = 0;y < getHeight();y++){	
			std::cout <<"X: "<<x<<" Y: "<<y<< " " << (uint32_t)_Map.at<uint8_t>(y,x) << std::endl;
		}
	}
}