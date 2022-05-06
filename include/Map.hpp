#pragma once

#include <cstdint>
#include <vector>
#include <opencv2/core/mat.hpp>

struct MapCell{

	MapCell(uint32_t x,uint32_t y){
		this->x = x;
		this->y = y;
	}

	uint32_t x;
	uint32_t y;
};

class Map{
	
private:
	cv::Size _Size;
	std::vector<MapCell*> _Exits;
	cv::Mat _Map;
	const std::string _MapPath;

public:
	Map(const std::string& path);
	inline int getWidth() const {return _Size.width;}
	inline int getHeight() const {return _Size.height;}
	inline std::vector<MapCell*> getExits() const {return _Exits;}

	inline bool isWall(uint32_t x,uint32_t y) const {return _Map.at<uint8_t>(y,x) == 0;}
	inline bool isPath(uint32_t x,uint32_t y) const {return _Map.at<uint8_t>(y,x) == 255;}
	bool isExit(uint32_t x,uint32_t y) const;
	void printWholeImage();
private:
	void calculateExits();
	bool hasWhiteBorder();
	void removeBorder();

};

