#include "Ranking.h"

Ranking::Ranking(const std::string& archivo) : archivo_(archivo) {}

void Ranking::mostrarRanking(sf::RenderWindow& window) {
    window.clear();

    // Cargar la fuente
    sf::Font font;
    if (!font.loadFromFile("Letra.ttf")) {  // Cambia la ruta de la fuente si es necesario
        std::cerr << "No se pudo cargar la fuente" << std::endl;
        return;
    }

    // Título del ranking
    sf::Text title("Ranking", font, 30);
    title.setPosition(300, 50);
    window.draw(title);

    // Abrir el archivo en modo binario
    std::ifstream archivo(archivo_, std::ios::binary);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << archivo_ << std::endl;
        return;
    }

    // Variables de posición para mostrar los jugadores en la ventana
    int y = 100;
    Jugador jugador("", 0);  // Jugador temporal para leer los datos

    // Leer cada jugador desde el archivo y mostrarlo en la ventana
    while (archivo.read(reinterpret_cast<char*>(&jugador), sizeof(Jugador))) {
        std::string texto = jugador.getNombre() + " - " + std::to_string(jugador.getPuntos());
        sf::Text jugadorText(texto, font, 20);
        jugadorText.setPosition(100, y);
        window.draw(jugadorText);
        y += 30;
    }
    archivo.close();
    window.display();  // Mostrar los datos en la ventana

    // Esperar hasta que el usuario cierre la ventana manualmente
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                window.close();
                break;
            }
        }
    }
}
