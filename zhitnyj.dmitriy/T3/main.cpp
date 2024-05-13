#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "FileReader.hpp"
#include "Commands.hpp"
#include "iofmtguard.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>\n";
    return 1;
  }

  std::string filename = argv[1];
  std::vector< Polygon > polygons;

  try
  {
    polygons = FileReader().readPolygons(filename);
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error reading file: " << e.what() << "\n";
    return 2;
  }

  std::string command;
  while (std::cin >> command)
  {
    iofmtguard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);

    if (command == "AREA")
    {
      std::string param;
      std::cin >> param;
      if (param == "ODD")
      {
        std::cout << Commands().calculateAreaEvenOdd(polygons, true) << "\n";
      }
      else if (param == "EVEN")
      {
        std::cout << Commands().calculateAreaEvenOdd(polygons, false) << "\n";
      }
      else if (param == "MEAN")
      {
        std::cout << Commands().calculateMeanArea(polygons) << "\n";
      }
      else
      {
        try
        {
          int vertex_count = std::stoi(param);
          std::cout << Commands().calculateAreaByVertexCount(polygons, vertex_count) << "\n";
        }
        catch (const std::invalid_argument&)
        {
          std::cerr << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (command == "MAX")
    {
      std::string param;
      std::cin >> param;
      if (param == "AREA")
      {
        std::cout << Commands().calculateMaxArea(polygons) << "\n";
      }
      else if (param == "VERTEXES")
      {
        std::cout << Commands().calculateMaxVertexes(polygons) << "\n";
      }
      else
      {
        std::cerr << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "MIN")
    {
      std::string param;
      std::cin >> param;
      if (param == "AREA")
      {
        std::cout << Commands().calculateMinArea(polygons) << "\n";
      }
      else if (param == "VERTEXES")
      {
        std::cout << Commands().calculateMinVertexes(polygons) << "\n";
      }
      else
      {
        std::cerr << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "COUNT")
    {
      std::string param;
      std::cin >> param;
      if (param == "ODD")
      {
        std::cout << Commands().countPolygons(polygons, true) << "\n";
      }
      else if (param == "EVEN")
      {
        std::cout << Commands().countPolygons(polygons, false) << "\n";
      }
      else
      {
        try
        {
          int vertex_count = std::stoi(param);
          std::cout << Commands().countPolygons(polygons, false, vertex_count) << "\n";
        }
        catch (const std::invalid_argument&)
        {
          std::cerr << "<INVALID COMMAND>\n";
        }
      }
    }
    else if (command == "RMECHO")
    {
      int vertex_count;
      std::cin >> vertex_count;
      Polygon target;
      target.points.resize(vertex_count);
      std::for_each(target.points.begin(), target.points.end(), [](Point& point)
      {
        char ignore;
        std::cin >> ignore >> point.x >> ignore >> point.y >> ignore;
      });
      std::cout << Commands().removeEcho(polygons, target) << "\n";
    }
    else if (command == "PERMS")
    {
      int vertex_count;
      std::cin >> vertex_count;
      Polygon target;
      target.points.resize(vertex_count);
      std::for_each(target.points.begin(), target.points.end(), [](Point& point)
      {
        char ignore;
        std::cin >> ignore >> point.x >> ignore >> point.y >> ignore;
      });
      std::cout << Commands().countPerms(polygons, target) << "\n";
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
    }
  }

  return 0;
}
