#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


class Spots
{
  private:
	std::vector<sf::RectangleShape> pixels;
	std::vector<std::vector<bool>> table;
	const int pixel_size = 1;
	const int width = 0;
	const int height = 0;

  public:
	/// <summary>Cellular automata with width as number of pixels on X axis and height as number of pixels on Y axis.</summary>
	Spots(int width, int height, int pixel_size, double probability);

	~Spots() = default;


	void update();

	std::vector<std::vector<bool>> getTable() const { return table; }
	const std::vector<sf::RectangleShape>& getPixels() const { return pixels; }
	
	/// <summary>Runs the simulation for a given amount of iterations and saves data for the density chart to a file.</summary>
	void saveDensityChartDataToFile(const std::string& path, unsigned iterations);
	void reset(double probability);

  private:
	void updateTable();
	void updatePixels();
};