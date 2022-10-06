#pragma once
#include <string>
class LoaderParams { //load관련 클래스 
public:
	LoaderParams(int x, int y, int width, int height, int currentRow, int currentFrame, std::string textureID)
		: m_x(x),
		m_y(y),
		m_width(width),
		m_height(height),
		m_textureID(textureID),
		m_currentRow(currentRow),
		m_currentFrame(currentFrame) {}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getcurrentRow() const { return m_currentRow; }
	int getcurrentFrame() const { return m_currentFrame; }
	std::string getTextureID() const { return m_textureID; }
private:
	int m_x, m_y;
	int m_width, m_height;
	int m_currentRow, m_currentFrame;
	std::string m_textureID;
};