#include "Spots.h"
#include <random>
#include <fstream>
#include <iterator>


Spots::Spots(int width, int height, int pixel_size, double probability)
	: width(width), height(height), pixel_size(pixel_size)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::bernoulli_distribution bool_dist(probability);
	size_t index = 0;

	for (int W = 0; W < width; W++)
	{
		table.push_back({});

		for (int H = 0; H < height; H++)
		{
			table[W].push_back(bool_dist(rng));
			pixels.emplace_back(sf::Vector2f(pixel_size, pixel_size));
			pixels[index].setPosition(sf::Vector2f(W * pixel_size, H * pixel_size));
			index++;
		}
	}

	updatePixels();
}

void Spots::update()
{
	updateTable();
	updatePixels();
}

void Spots::saveDensityChartDataToFile(const std::string& path, unsigned iterations)
{
	std::vector<double> result = {};
	const double area = width * height;
	double counter = 0;

	for (int i = 0; i < iterations; i++)
	{
		for (int W = 0; W < width; W++)
			for (int H = 0; H < height; H++)
				if (table[W][H]) counter++;

		result.push_back(counter / area);
		counter = 0;

		updateTable();
	}

	std::ofstream output_file(path);
	std::ostream_iterator<double> output_iterator(output_file, "\n");
	std::copy(result.begin(), result.end(), output_iterator);
}

void Spots::reset(double probability)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::bernoulli_distribution bool_dist(probability);

	for (int W = 0; W < width; W++)
		for (int H = 0; H < height; H++)
			table[W][H] = bool_dist(rng);

	updatePixels();
}

void Spots::updateTable()
{
	std::vector<std::vector<bool>> table_copy = table;

	for (int W = 0; W < width; W++)
	{
		for (int H = 0; H < height; H++)
		{
			int counter = 0;
			for (int w = std::max(0, W - 1); w <= std::min(width - 1, W + 1); w++)
			{
				for (int h = std::max(0, H - 1); h <= std::min(height - 1, H + 1); h++)
				{
					/*if (!(w == W && h == H) && table_copy[w][h])  // Not counting itself
						counter++;*/

					if (table_copy[w][h])
						counter++;
				}
			}

			if (counter == 4 || counter >= 6)
				table[W][H] = true;
			else
				table[W][H] = false;
		}
	}
}

void Spots::updatePixels()
{
	/*for (int W = 0; W < width; W++)
		for (int H = 0; H < height; H++)
			image.setPixel(W, H, table[W][H] ? sf::Color::White : sf::Color::Black);*/
	size_t index = 0;

	for (int W = 0; W < width; W++)
	{
		for (int H = 0; H < height; H++)
		{
			pixels[index].setFillColor(table[W][H] ? sf::Color::White : sf::Color::Black);
			index++;
		}
	}
}
