#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#define CELL_SIZE 80
#define COLUMNS 5
#define ROWS 5
#define FONT_HEIGHT = 16

struct Cell
{
    int number = 0;
    int x;         // obvious
    int y;         // obvious
    bool open;     // this is when the player peeks
    bool openPerm; // openPerm is when the player gets a pair correctly
    Cell(int x1, int y1)
    {
        x = x1;
        y = y1;
        open = false;
        openPerm = false;
    }
};

// global variables
std::vector<Cell> cells; // arrays for storing the 64 cells
sf::Font font;           // the font, this needs to be gobal for some reason
int clicks_num = 0;      // I need to use in a lot of functions
sf::Time elapsed1;       // this variable for storing the time elapsed

// to check for wi
// to check if the index is already accounted for
bool isInArray(int num, std::vector<int> &arr)
{
    for (auto nums : arr)
    {
        if (nums == num)
            return true;
    }
    return false;
}

// this appraoch is very expensive, as I have to perform linear searches about 64 times
// currently looking for better ways to do this
void fillNums()
{
    std::random_device rd;
    std::mt19937 gen(rd());                         // seeding the number generator
    std::uniform_int_distribution<> distrib(0, 24); // between 0 and 63(64) indices
    int rand = 0;
    std::vector<int> arr; // to keep track of the indices in the array
    for (int i = 1; i <= ((ROWS * COLUMNS) - 1); i++)
    {
        while (isInArray(rand, arr)) // if the indices is already in the array run again
        {
            rand = distrib(gen);
        }
        arr.push_back(rand);
        cells[rand].number = i; // puts the number 1 into a random position in the array
    }
}

// The text handler for victory screen
sf::Text DrawTextForVictory()
{
    sf::Text text;
    if (!font.loadFromFile("assests/daFont.ttf"))
    {
        std::cout << "unable";
    }
    else
    {
        text.setFont(font);
        text.setCharacterSize(32);
        text.setFillColor(sf::Color(255, 255, 255));
    }
    return text;
}

// The text handler for digits inside squares
sf::Text DrawTextForBoard()
{
    sf::Text text;
    if (!font.loadFromFile("assests/daFont.ttf"))
    {
        std::cout << "unable";
    }
    else
    {
        text.setFont(font);
        text.setCharacterSize(64);
        text.setFillColor(sf::Color(56, 54, 54));
    }
    return text;
}

void fillCell()
{
    for (int a = 0; a < ROWS; a++)
    {
        for (int b = 0; b < COLUMNS; b++)
        {
            cells.push_back(Cell(b, a)); // inversed as SFML has invered axis for some reason
        }
    }
    fillNums(); // fills numbers into the objects as well
}
// this is the longest and most important function(I really need to refactor)
void drawBoard(sf::RenderWindow &window, bool win, bool close)
{
    auto text = DrawTextForBoard();                                            // gets the text config for board
    sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE - 3, CELL_SIZE - 3)); // subtracting 3 to get the thickness of the spacing
    if (win)                                                                   // win is true when player wins(duhh)
    {
        // getting the text config
        text = DrawTextForVictory();
        text.setPosition(0, 0);
        std::string str1("The number of clicks-\n");
        text.setString(str1.append(std::to_string(clicks_num)));
        window.draw(text);
        auto text2 = DrawTextForVictory();
        text2.setPosition(0, 100);
        str1 = "The time you took-\n";
        text2.setString(str1.append(std::to_string(elapsed1.asSeconds())));
        window.draw(text2);
        return; // returning as we dont want this function anymore
    }
    if (close) // when the x button is pressed
    {
        window.clear();
        return;
    }

    // nested loops
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            text.setPosition(CELL_SIZE * i, CELL_SIZE * j);                // sets the text on top of that rectangle
            text.setString(std::to_string(cells[i + COLUMNS * j].number)); // sets the string to that number assigned to cell
            cell_shape.setPosition(CELL_SIZE * i, CELL_SIZE * j);          // sets the position of the rectangle also

            cell_shape.setFillColor(sf::Color(209, 115, 21));
            window.draw(cell_shape);
            if (cells[i + COLUMNS * j].number != 0)
                window.draw(text);
        }
    }
}
int main()
{
    int mouse_x = 0;
    int mouse_y = 0;
    int opened = 0;
    bool win = false;
    bool close = false;
    fillCell();
    sf::RenderWindow window = sf::RenderWindow({COLUMNS * 80, ROWS * 80}, "puzzle");
    window.setFramerateLimit(144);
    sf::Clock clock;
    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                std::cout << "pressed up\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                std::cout << "pressed down\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                std::cout << "pressed left\n";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                std::cout << "pressed right\n";
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
                close = true;
            }
        }
        window.clear();
        drawBoard(window, win, close);
        window.display();
    }
}
