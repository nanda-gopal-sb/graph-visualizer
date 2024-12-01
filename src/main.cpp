#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
struct node
{
    int x;
    int y;
    node(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};
std::vector<node> Nodes;
void drawCircle(sf::RenderWindow &window)
{
    sf::CircleShape dot(5.f);
    dot.setFillColor(sf::Color::Blue);
    for (int i = 0; i < Nodes.size(); i++)
    {
        dot.setPosition(Nodes[i].x, Nodes[i].y);
        window.draw(dot);
    }
}
int main()
{
    auto window = sf::RenderWindow({600u, 600u}, "CMake SFML Project");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                Nodes.clear();
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {

                int mouse_x = sf::Mouse::getPosition(window).x;
                int mouse_y = sf::Mouse::getPosition(window).y;
                node *newNode = new node(mouse_x, mouse_y);
                Nodes.push_back(*newNode);
            }
            window.clear();
            drawCircle(window);
            window.display();
        }
    }
}
