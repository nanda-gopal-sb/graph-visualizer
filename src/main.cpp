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
    sf::VertexArray connect(sf::Lines, 2);
    dot.setFillColor(sf::Color::Blue);
    for (int i = 0; i < Nodes.size(); i++)
    {
        dot.setPosition(Nodes[i].x, Nodes[i].y);
        window.draw(dot);
    }
    if (Nodes.size() >= 1)
    {
        for (int i = 0; i < Nodes.size() - 1; i++)
        {
            connect[0].position = sf::Vector2f(Nodes[i].x, Nodes[i].y);
            connect[1].position = sf::Vector2f(Nodes[i + 1].x, Nodes[i + 1].y);
            window.draw(connect);
        }
    }
}
int main()
{
    auto window = sf::RenderWindow({1000u, 1000u}, "graphs");
    window.setFramerateLimit(144);

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
