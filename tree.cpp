// matanayabarzilay@gmail.com

#include "tree.hpp"
#include <queue>
#include <tuple>
#include <cmath>
#include <iomanip>




template<typename T, size_t K>
void Tree<T, K>::print() const {
    if (!root) return;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Tree Visualization");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        drawTree(window, font);
        window.display();
    }
}

template<typename T, size_t K>
void Tree<T, K>::drawTree(sf::RenderWindow& window, const sf::Font& font) const {
    if (!root) return;

    int levels = getTreeDepth(root);
    float verticalSpacing = 550.0f / levels;
    float horizontalSpacing = 750.0f / std::pow(2, levels - 1);

    float startX = window.getSize().x / 2.0f;


    std::queue<std::tuple<std::shared_ptr<Node<T>>, float, float, int>> nodeQueue;
    nodeQueue.push(std::make_tuple(root, startX, 50.0f, 0));

    while (!nodeQueue.empty()) {
        auto [node, x, y, level] = nodeQueue.front();
        nodeQueue.pop();

        drawNode(window, font, node, x, y);

        float childSpacing = horizontalSpacing / std::pow(2, level + 1) * 3.5;
        float childY = y + verticalSpacing;

        for (size_t i = 0; i < node->children.size(); ++i) {
            float childX = x + (i - (node->children.size() - 1) / 2.0f) * childSpacing;
            drawEdge(window, x, y, childX, childY);
            nodeQueue.push(std::make_tuple(node->children[i], childX, childY, level + 1));
        }
    }
}

template<typename T, size_t K>
void Tree<T, K>::drawNode(sf::RenderWindow& window, const sf::Font& font, const std::shared_ptr<Node<T>>& node, float x, float y) const {
    sf::CircleShape circle(35);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(6);
    circle.setOutlineColor(sf::Color::Black);
    circle.setPosition(x - 20, y - 20);
    window.draw(circle);
    std::ostringstream valueStream;

    std::string nodeValueStr = valueStream.str();


    sf::Text text;
    text.setFont(font);
    valueStream << std::fixed << std::setprecision(0) << node->value;  // Format to 2 decimal places
    text.setString(valueStream.str());
    // text.setString(std::to_string(node->value));
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    
    // Center the text within the circle
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/8.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(x, y);
    window.draw(text);
}

template<typename T, size_t K>
void Tree<T, K>::drawEdge(sf::RenderWindow& window, float x1, float y1, float x2, float y2) const {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(x1, y1), sf::Color::Black),
        sf::Vertex(sf::Vector2f(x2, y2), sf::Color::Black)
    };
    window.draw(line, 2, sf::Lines);
}

template<typename T, size_t K>
int Tree<T, K>::getTreeDepth(const std::shared_ptr<Node<T>>& node) const {
    if (!node) return 0;
    int maxDepth = 0;
    for (const auto& child : node->children) {
        maxDepth = std::max(maxDepth, getTreeDepth(child));
    }
    return 1 + maxDepth;
}
